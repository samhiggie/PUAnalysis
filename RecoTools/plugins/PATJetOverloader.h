// -*- C++ -*-
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: PATJetOverloader.h,v 1.3 2013/10/25 21:01:55 ojalvo Exp $
//
//
#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
//
// class declaration
#include <boost/foreach.hpp>
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"
// user include files

#include <TTree.h>
#include <TH2D.h>
#include <TFile.h>

#include "TRandom3.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "boost/filesystem.hpp"

class PATJetOverloader : public edm::EDProducer {
	public:


		explicit PATJetOverloader(const edm::ParameterSet& iConfig):
			src_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("src"))),
			genJets_(consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genJets"))),
			data_(iConfig.getParameter<bool>("isData"))
	{
		produces<pat::JetCollection>();

		calib=BTagCalibration("CSVv2", std::string(std::getenv("CMSSW_BASE"))+"/src/PUAnalysis/Configuration/data/CSVv2Moriond17_2017_1_26_GtoH.csv");
		reader=BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central",{"up","down"});
		reader.load(calib, BTagEntry::FLAV_B, "comb");
		reader.load(calib, BTagEntry::FLAV_C, "comb");
		reader.load(calib, BTagEntry::FLAV_UDSG, "incl");

		std::string base = std::getenv("CMSSW_BASE");
		std::string fEff =   "/src/PUAnalysis/Configuration/data/tagging_efficiencies.root";
		std::string path= base+fEff;
		bool isEffFile_   = boost::filesystem::exists( path  );
		if (isEffFile_){
			std::cout<<"INFO::PATJetOverloader using efficiency map"<<std::endl;
			f_EffMap = new TFile(path.c_str(),"READONLY");
			h2_EffMapB    = (TH2D*)f_EffMap->Get("btag_eff_b");
			h2_EffMapC    = (TH2D*)f_EffMap->Get("btag_eff_c");
			h2_EffMapUDSG = (TH2D*)f_EffMap->Get("btag_eff_oth");
		}
		else {
			std::cout<<"INFO::PATJetOverloader using efficiency map NOT FOUND!?!?!?!?!"<<std::endl;
		}



	}

		~PATJetOverloader() {}
	private:
		TFile *f_EffMap;
		TH2D *h2_EffMapB;
		TH2D *h2_EffMapC;
		TH2D *h2_EffMapUDSG;

		BTagCalibration calib;
		BTagCalibrationReader reader;

		bool applySF(bool& isBTagged, float Btag_SF, float Btag_eff,int seed){
			TRandom3 rand_;
			rand_ = TRandom3(seed);
			bool newBTag = isBTagged;
			if (Btag_SF == 1) return newBTag; //no correction needed 
			//throw die
			rand_.SetSeed(seed);
			float coin = rand_.Uniform();
			//std::cout<<"Uniform coin: "<<coin<<std::endl;
			if(Btag_SF > 1){  // use this if SF>1
				if( !isBTagged ) {
					//fraction of jets that need to be upgraded
					float mistagPercent = (1.0 - Btag_SF) / (1.0 - (Btag_SF/Btag_eff) );
					//upgrade to tagged
					if( coin < mistagPercent ) {newBTag = true;}
				}
			}else{  // use this if SF<1
				//downgrade tagged to untagged
				if( isBTagged && coin > Btag_SF ) {newBTag = false;}
			}
			return newBTag;
		}


		virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			//std::cout<<"===== PATJetOverloader NAMESPACE ====="<<std::endl;
			using namespace edm;
			using namespace reco;
			using namespace std;
			//std::cout<<"===== PATJetOverloader JetCollection ====="<<std::endl;
			std::auto_ptr<pat::JetCollection> jets(new pat::JetCollection);
			Handle<pat::JetCollection > cands;
			Handle<reco::GenJetCollection > genJets;
			if(iEvent.getByToken(src_,cands)) 
				for(unsigned int  i=0;i!=cands->size();++i){
					pat::Jet jet = cands->at(i);
					float pt=0.0;
					float sumPt=0.0;
					float sumPt2=0.0;
					//std::cout<<"===== PATJetOverloader Jet Number of Daughters ====="<<std::endl;
					//std::cout<<"numberOfDaughters(Constituents): "<<jet.numberOfDaughters()<<std::endl;
					std::vector<reco::CandidatePtr> daus(jet.daughterPtrVector());
					std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); }); // the joys of C++11
					for (unsigned int i2 = 0, n = daus.size(); i2 < n; ++i2) {
						const pat::PackedCandidate &cand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
						pt=cand.pt();
						//std::cout<<"Constituent Pt: "<<pt<<std::endl;
						sumPt+=pt;
						sumPt2+=pt*pt;
					}
					//std::cout<<"Constituent SumPt: "<<sumPt<<std::endl;
					//std::cout<<"Constituent SumPt^2: "<<sumPt2<<std::endl;

					bool loose = true;
					bool medium = true; //tightLep veto
                    bool tight = true;
                    if (std::abs(jet.eta()) <= 2.7){
                        if (jet.neutralHadronEnergyFraction() >= 0.99)
                            loose = false;
                        if (jet.neutralHadronEnergyFraction() >= 0.90){
                            tight = false;
                            medium = false;
                        }
                        if (jet.neutralEmEnergyFraction() >= 0.99)
                            loose = false;
                        if (jet.neutralEmEnergyFraction() >= 0.90)
                            tight = false;
                        if ((jet.chargedMultiplicity()+jet.neutralMultiplicity()) <= 1) { //getPFConstitutents broken in miniAOD
                            loose = false;
                            medium = false;
                            tight = false;
                        }
                        if (jet.muonEnergyFraction() >= 0.8){
                            medium = false;
                        }
                        if (std::abs(jet.eta()) <= 2.4) {
                            if (jet.chargedHadronEnergyFraction() == 0) {
                                loose = false;
                                medium = false;
                                tight = false;
                            }
                            if (jet.chargedHadronMultiplicity() == 0) {
                                loose = false;
                                medium = false;
                                tight = false;
                            }
                            if (jet.chargedEmEnergyFraction() >= 0.99) {
                                loose = false;
                                medium = false;
                                tight = false;
                            }
                            if (jet.chargedEmEnergyFraction() >= 0.90) {
                                medium = false;
                            }
                        }
                    }
                    else if (std::abs(jet.eta()) <= 3.0 ) {
                        medium = false;
                        if (jet.neutralMultiplicity() <= 2){
                            loose = false;
                            tight = false;
                        }
                        if (jet.neutralEmEnergyFraction() >= 0.90){
                            loose = false;
                            tight = false;
                        }
                    }
                    else if (std::abs(jet.eta()) > 3.0) {
                        medium = false;
                        if (jet.neutralEmEnergyFraction() >= 0.90) {
                            loose = false;
                            medium = false;
                            tight = false;
                        }
                        if (jet.neutralMultiplicity() <= 10) {
                            loose = false;
                            medium = false;
                            tight = false;
                        }
                    }
                    jet.addUserFloat("idLoose", loose);
                    jet.addUserFloat("idTightLepVeto", medium);
                    jet.addUserFloat("idTight", tight);

                    int isbtagged=0;
                    int isbtaggedup=0;
                    int isbtaggeddown=0;
                    bool pass =false;
                    double bpt = jet.pt();
                    double beta = std::abs(jet.eta());
                    double bcsv = jet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                    //std::cout<<" jet.eta() "<< beta<<std::endl;
                    //std::cout<<" std::abs(jet.eta()) "<< std::abs(beta)<<std::endl;
                    if (!(bpt<20 || beta>2.4 || !loose )) {
                        if (bcsv>0.8484) pass =true;
                        int jetflavor = jet.partonFlavour();
                        double SF =0,SFup=0,SFdown=0,eff=0;
                        //std::cout<< "Gets To Return" <<std::endl;
                        if (data_){
                            isbtagged= pass;
                            isbtaggedup= pass;
                            isbtaggeddown= pass;
                            //nosystematic shifts up and down
                        }
                        else{
                            if (fabs(jetflavor) == 5) {                // real b-jet
                                //std::cout<<"=====Jet Flavor B====="<<std::endl;
                                //std::cout<<"=====Jet SF"<<std::endl;
                                SF = reader.eval_auto_bounds("central",BTagEntry::FLAV_B, beta,bpt );
                                SFup = reader.eval_auto_bounds("up",BTagEntry::FLAV_B, beta,bpt );
                                SFdown = reader.eval_auto_bounds("down",BTagEntry::FLAV_B, beta,bpt );
                                eff = h2_EffMapB->GetBinContent( h2_EffMapB->GetXaxis()->FindBin(bpt), h2_EffMapB->GetYaxis()->FindBin(beta) );
                            }
                            else if (fabs(jetflavor) == 4){
                                SF = reader.eval_auto_bounds("central",BTagEntry::FLAV_C, beta,bpt );
                                SFup = reader.eval_auto_bounds("up",BTagEntry::FLAV_C, beta,bpt );
                                SFdown = reader.eval_auto_bounds("down",BTagEntry::FLAV_C, beta,bpt );
                                //std::cout<<"=====Jet EFF"<<std::endl;
                                eff = h2_EffMapC->GetBinContent( h2_EffMapC->GetXaxis()->FindBin(bpt), h2_EffMapC->GetYaxis()->FindBin(beta) );
                            }
                            else {
                                //std::cout<<"=====Jet Flavor UDSG====="<<std::endl;
                                //std::cout<<"=====Jet SF"<<std::endl;
                                SF = reader.eval_auto_bounds("central",BTagEntry::FLAV_UDSG, beta, bpt );
                                SFup = reader.eval_auto_bounds("up",BTagEntry::FLAV_UDSG, beta, bpt );
                                SFdown = reader.eval_auto_bounds("down",BTagEntry::FLAV_UDSG, beta, bpt );
                                //std::cout<<"=====Jet EFF"<<std::endl;
                                eff = h2_EffMapUDSG->GetBinContent( h2_EffMapUDSG->GetXaxis()->FindBin(bpt), h2_EffMapUDSG->GetYaxis()->FindBin(beta) );

                            }

                            int seed = (int)((jet.eta()+5)*100000);
                            isbtagged = applySF(pass, SF, eff,seed);
                            isbtaggedup = applySF(pass, SFup, eff,seed);
                            isbtaggeddown = applySF(pass, SFdown, eff,seed);
                        }
                    }

                    jet.addUserFloat("isbtagged", float(isbtagged));
                    jet.addUserFloat("isbtaggedup", float(isbtaggedup));
                    jet.addUserFloat("isbtaggeddown", float(isbtaggeddown));

                    // Pileup discriminant
                    bool passPUL = false;
                    bool passPUM = false;
                    bool passPUT = false;
                    //	float jpumva = jet.userFloat("pileupJetId:fullDiscriminant");
                    float jpu = jet.userInt("pileupJetId:fullId");
                    if (jpu==1){
                        passPUL = true;
                        passPUM = true;
                        passPUT = true;
                    }
                    else if (jpu==2){
                        passPUM = true;
                        passPUL = true;
                    }
                    else if (jpu==4){
                        passPUL = true;
                    }

                    jet.addUserFloat("puID",jpu);
                    jet.addUserFloat("puIDLoose",float(passPUL));
                    jet.addUserFloat("puIDMedium",float(passPUM));
                    jet.addUserFloat("puIDTight",float(passPUT));



                    float genJetPt =-10;
                    float genJetEta =-10;
                    float genJetPhi =-10;
                    float DRMin = 0.5;
                    float Vtx3dL = -10;
                    float Vtx3deL = -10;
                    float VtxPt = -10;
                    float uncorrectedPt= -10;
                    //std::cout<<"===== PATJetOverloader UncorrectedPt ====="<<std::endl;
                    uncorrectedPt = jet.correctedP4(0).pt();
                    //CHECKME
                    //std::cout<<"'Uncorrected' jet pt: "<<uncorrectedPt<<std::endl;

                    //std::cout<<"===== PATJetOverloader GenJet ====="<<std::endl;
                    if(iEvent.getByToken(genJets_,genJets))
                        for(unsigned int k=0;k!=genJets->size();k++){
                            if(ROOT::Math::VectorUtil::DeltaR(genJets->at(k).p4(),jet.p4())<DRMin){
                                DRMin = ROOT::Math::VectorUtil::DeltaR(genJets->at(k).p4(),jet.p4());
                                genJetPt=genJets->at(k).pt();
                                genJetEta=genJets->at(k).eta();
                                genJetPhi=genJets->at(k).phi();
                            }
                        }

                    //std::cout<<"===== PATJetOverloader Secondary Vertex ====="<<std::endl;
                    const reco::SecondaryVertexTagInfo* secInfo = jet.tagInfoSecondaryVertex("secondaryVertex");
                    if(secInfo && secInfo->vertexTracks().size()>0){
                        const reco::Vertex&sv= secInfo->secondaryVertex(0);
                        //jetVtxPt = sv.pt();
                        Vtx3dL = (secInfo->flightDistance(0).value());
                        Vtx3deL = (secInfo->flightDistance(0).error());
                        reco::Candidate::LorentzVector sumP4(0,0,0,0);
                        //FIXME
                        if ( sv.tracksSize()>1){
                            for(reco::Vertex::trackRef_iterator track = sv.tracks_begin(); track!= sv.tracks_end(); ++track)
                                for(unsigned int pfj=0;pfj<jet.getPFConstituents().size();++pfj) {
                                    pfcand = jet.getPFConstituents().at(pfj);
                                    if(pfcand.isNonnull())
                                        //if(abs(pfcand->pdgId())==211&&pfcand->pt()>0.25&&pfcand->charge()!=0) ///create charged particle collection
                                        if((*track).key() == pfcand->trackRef().key())
                                            sumP4+=pfcand->p4();
                                }
                        }
                        /*
                           for (unsigned int h=0; h<secInfo->vertexTracks().size(); h++) {
                        //sumP4=(secInfo->vertexTracks()[h]->px(),0,0,0);
                        float pt=secInfo->track(h).pt();
                        }*/
                        VtxPt=sumP4.pt();
                    }


                    jet.addUserFloat("PtUncorr",uncorrectedPt);
                    jet.addUserFloat("VtxPt",VtxPt);
                    jet.addUserFloat("Vtx3dL",Vtx3dL);
                    jet.addUserFloat("Vtx3deL",Vtx3deL);
                    jet.addUserFloat("genJetEta",genJetEta);
                    jet.addUserFloat("genJetPhi",genJetPhi);
                    jet.addUserFloat("genJetPt",genJetPt);
                    jet.addUserFloat("ptRMS",sqrt(sumPt2/(sumPt*sumPt)));
                    jets->push_back(jet);

                }  

            iEvent.put(jets);

        } 

        // ----------member data ---------------------------
        edm::EDGetTokenT<pat::JetCollection> src_;
        edm::EDGetTokenT<reco::GenJetCollection> genJets_;
        bool data_;
        reco::PFCandidatePtr pfcand;
};

