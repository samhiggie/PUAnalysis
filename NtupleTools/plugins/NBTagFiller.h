// system include files
#include <memory>

// user include files

#include <TTree.h>
#include <TH2D.h>
#include <TFile.h>

#include "TRandom3.h"

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "boost/filesystem.hpp"

//
// class decleration
//

template<typename T>
class NBTagFiller : public NtupleFillerBase {
	public:
		NBTagFiller(){
		}


		NBTagFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC ):
			src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))), 
			doEff_(iConfig.getParameter<bool>("doEffMap"))
	{
		value = new float[3];
		t->Branch("nbtag",&value[0],"nbtag/F");
		t->Branch("nbtagUp",&value[1],"nbtagUp/F");
		t->Branch("nbtagDown",&value[2],"nbtagDown/F");
	        calib=BTagCalibration("CSVv2", std::string(std::getenv("CMSSW_BASE"))+"/src/PUAnalysis/Configuration/data/CSVv2Moriond17_2017_1_26_GtoH.csv");
		reader= BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central",{"up","down"});
                reader.load(calib,BTagEntry::FLAV_UDSG,"incl");
                reader.load(calib,BTagEntry::FLAV_B,"comb");
                reader.load(calib,BTagEntry::FLAV_C,"comb");

		std::string base = std::getenv("CMSSW_BASE");
		std::string fEff =   "/src/PUAnalysis/Configuration/data/tagging_efficiencies.root";
		//std::string fEff =   "/src/PUAnalysis/Configuration/data/efficiency.root";
		std::string path= base+fEff;
		isEffFile_   = boost::filesystem::exists( path  );
		if (isEffFile_ && doEff_){
			std::cout<<"INFO::NBTagFiller using efficiency map"<<std::endl;
			f_EffMap = new TFile(path.c_str(),"READONLY");
			h2_TTEffMapB    = (TH2D*)f_EffMap->Get("btag_eff_b");
			h2_TTEffMapC    = (TH2D*)f_EffMap->Get("btag_eff_c");
			h2_TTEffMapUDSG = (TH2D*)f_EffMap->Get("btag_eff_oth");
			h2_ZJetsEffMapB    = (TH2D*)f_EffMap->Get("btag_eff_b");
			h2_ZJetsEffMapC    = (TH2D*)f_EffMap->Get("btag_eff_c");
			h2_ZJetsEffMapUDSG = (TH2D*)f_EffMap->Get("btag_eff_oth");
		}
		else { std::cout<<"WARNING::NBTagFiller No efficiency file found!!!"<<std::endl;}

	}


		~NBTagFiller()
		{ 
		}

		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			int nbtags=0;
			int nbtagsup=0;
			int nbtagsdown=0;
			bool top =false;

			edm::Handle<std::vector<T>> handle;
			if( iEvent.getByToken(src_,handle)){

				if (handle->at(0).isTop()){top =true;}
				for ( unsigned int i=0;i<handle->at(0).jets().size();i++){
					bool btagged = false;
					bool btaggedup = false;
					bool btaggeddown = false;
					bool pass = false;
					double pt = handle->at(0).jets().at(i)->pt();
					double eta = std::abs(handle->at(0).jets().at(i)->eta());
					//std::cout<<"=====Jet====="<<std::endl;
					//std::cout<<"Jet Pt: "<<pt<<std::endl;
					//std::cout<<"Jet Eta: "<<eta<<std::endl;
					if (pt<20 || std::abs(eta)>2.4) {continue;}
					int jetflavor = handle->at(0).jets().at(i)->partonFlavour();
					double SF =0,SFup=0,SFdown=0,eff=0;
					if (handle->at(0).jets().at(i)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.80&&handle->at(0).jets().at(i)->userFloat("idLoose")) pass =true;
					if (fabs(jetflavor) == 5) {                // real b-jet


						//std::cout<<"=====Jet Flavor B====="<<std::endl;
						//std::cout<<"=====Jet SF"<<std::endl;
						SF = reader.eval_auto_bounds(
								"central", 
								BTagEntry::FLAV_B, 
								eta, 
								pt );
						SFup = reader.eval_auto_bounds(
								"up",
								BTagEntry::FLAV_B, 
								eta, 
								pt );
						SFdown = reader.eval_auto_bounds(
								"down",
								BTagEntry::FLAV_B, 
								eta, 
								pt );
						eff = 0.6829; 
						//std::cout<<"=====Jet EFF"<<std::endl;
						if (doEff_ && top )eff = h2_TTEffMapB->GetBinContent( h2_TTEffMapB->GetXaxis()->FindBin(pt), h2_TTEffMapB->GetYaxis()->FindBin(eta) );
						else if (doEff_ )eff = h2_ZJetsEffMapB->GetBinContent( h2_ZJetsEffMapB->GetXaxis()->FindBin(pt), h2_ZJetsEffMapB->GetYaxis()->FindBin(eta) );
					}
					else if (fabs(jetflavor) == 4) { 
						//std::cout<<"=====Jet Flavor C====="<<std::endl;
						//std::cout<<"=====Jet SF"<<std::endl;
						//
						SF = reader.eval_auto_bounds(
								"central", 
								BTagEntry::FLAV_C, 
								eta, 
								pt );
						SFup = reader.eval_auto_bounds(
								"up",
								BTagEntry::FLAV_C, 
								eta, 
								pt );
						SFdown = reader.eval_auto_bounds(
								"down",
								BTagEntry::FLAV_C, 
								eta, 
								pt );
						eff =0.18;
						//std::cout<<"=====Jet EFF"<<std::endl;
						if (doEff_&&top) eff = h2_TTEffMapC->GetBinContent( h2_TTEffMapC->GetXaxis()->FindBin(pt), h2_TTEffMapC->GetYaxis()->FindBin(eta) );
						else if (doEff_) eff = h2_ZJetsEffMapC->GetBinContent( h2_ZJetsEffMapC->GetXaxis()->FindBin(pt), h2_ZJetsEffMapC->GetYaxis()->FindBin(eta) );
					}  
					else {
						//std::cout<<"=====Jet Flavor UDSG====="<<std::endl;
						//std::cout<<"=====Jet SF"<<std::endl;
						SF = reader.eval_auto_bounds(
								"central", 
								BTagEntry::FLAV_C, 
								eta, 
								pt );
						SFup = reader.eval_auto_bounds(
								"up",
								BTagEntry::FLAV_C, 
								eta, 
								pt );
						SFdown = reader.eval_auto_bounds(
								"down",
								BTagEntry::FLAV_C, 
								eta, 
								pt );					
						eff =0.012;
						//std::cout<<"=====Jet EFF"<<std::endl;
						if (doEff_&&top ){ 
							eff = h2_TTEffMapUDSG->GetBinContent( h2_TTEffMapUDSG->GetXaxis()->FindBin(pt), h2_TTEffMapUDSG->GetYaxis()->FindBin(eta) );

						}
						else if (doEff_){ 
							//std::cout<<"=====Jet Pt Bin"<<std::endl;
							//std::cout<<"pt bin: "<<h2_ZJetsEffMapUDSG->GetXaxis()->FindBin(pt)<<std::endl;
							//std::cout<<"=====Jet Eta bin"<<std::endl;
							//std::cout<<"eta bin: "<<h2_ZJetsEffMapUDSG->GetYaxis()->FindBin(eta)<<std::endl;
							eff = h2_ZJetsEffMapUDSG->GetBinContent( h2_ZJetsEffMapUDSG->GetXaxis()->FindBin(pt), h2_ZJetsEffMapUDSG->GetYaxis()->FindBin(eta) );
						}
						//std::cout<<"=====After Jet EFF"<<std::endl;
						//cout<< "Flavor UDSG: EFF" <<endl;
					}

					//std::cout<<"pt: "<<pt<<std::endl;
					//std::cout<<"flavor: "<<fabs(jetflavor)<<std::endl;
					//std::cout<<"SF: "<<SF<<std::endl;
					//std::cout<<"eff: "<<eff<<std::endl;
					int seed = (int)((eta+5)*100000);
					btagged = applySF(pass, SF, eff,seed);
					btaggedup = applySF(pass, SFup, eff,seed);
					btaggeddown = applySF(pass, SFdown, eff,seed);

					//std::cout<< "Gets To Return" <<std::endl;
					if (handle->at(0).isData()){
						if (pass) nbtags++;
						//nosystematic shifts up and down
					}
					else{
						if (btagged) nbtags++;
						if (btaggedup) nbtagsup++;
						if (btaggeddown) nbtagsdown++;
					}
				}//end for jets
			}


			value[0]=nbtags;
			value[1]=nbtagsup;
			value[2]=nbtagsdown;
		}


	protected:
		edm::EDGetTokenT<std::vector<T> > src_;
		std::string tag_;
		bool doEff_;
		bool isEffFile_;
		float* value;
		TFile *f_EffMap;
		TH2D *h2_TTEffMapB;
		TH2D *h2_TTEffMapC;
		TH2D *h2_TTEffMapUDSG;
		TH2D *h2_ZJetsEffMapB;
		TH2D *h2_ZJetsEffMapC;
		TH2D *h2_ZJetsEffMapUDSG;


		BTagCalibration calib;
		BTagCalibrationReader reader;

		bool applySF(bool& isBTagged, float Btag_SF, float Btag_eff,int seed){
			TRandom3 rand_;
			rand_ = TRandom3(seed);

			bool newBTag = isBTagged;

			if (Btag_SF == 1) return newBTag; //no correction needed 

			//throw die
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


};

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef NBTagFiller<PATMuTauPair> PATMuTauPairNBTagFiller;
typedef NBTagFiller<PATElecTauPair> PATEleTauPairNBTagFiller;
typedef NBTagFiller<PATDiTauPair> PATDiTauPairNBTagFiller;



