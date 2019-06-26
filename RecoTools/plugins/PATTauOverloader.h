// -*- C++ -*-
//
//

// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "PUAnalysis/RecoTools/interface/PATTauClusterVariables.h"

#include "Math/GenVector/VectorUtil.h"
//
// class declaration
#include <boost/foreach.hpp>
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"

//New Tau ID
//#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"


class PATTauOverloader : public edm::EDProducer {
   public:
  
  

  explicit PATTauOverloader(const edm::ParameterSet& iConfig):
  src_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("src"))),
  muons_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  gen_(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("gen"))),
  genHadTaus_(consumes<std::vector<reco::GenJet>>(iConfig.getParameter<edm::InputTag>("genHadTaus"))),
  genMuTaus_(consumes<std::vector<reco::GenJet>>(iConfig.getParameter<edm::InputTag>("genMuTaus"))),
  genEleTaus_(consumes<std::vector<reco::GenJet>>(iConfig.getParameter<edm::InputTag>("genEleTaus"))),
  vtxSrc_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vtxSrc")))
  {

      produces<pat::TauCollection>();
  }

  ~PATTauOverloader() {}
   private:

  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
      using namespace edm;
      using namespace reco;
      std::unique_ptr<pat::TauCollection> out(new pat::TauCollection);
      Handle<pat::TauCollection > cands;
      Handle<pat::MuonCollection > muons;


      edm::Handle<reco::VertexCollection> vertices;
      iEvent.getByToken(vtxSrc_, vertices);
      //const reco::Vertex& thePV = *vertices->begin();


      if(iEvent.getByToken(src_,cands)){ 
          for(unsigned int  i=0;i!=cands->size();++i){
              pat::Tau tau = cands->at(i);
              //std::cout<<"Tau : "<<i<<std::endl;
              //std::cout<<"   Tau  pt: "<<tau.pt()<<" eta: "<<tau.eta()<<" byCmbIso: "<<tau.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits")<<std::endl;  
              tau.addUserInt("gen_match", tauGenMatch2(iEvent,tau.p4()));
              float dZ=-999;
              float dXY=-999;
              float z_2=-999;

              if(vertices->size()){z_2 = tau.vz() + (130. / tan(tau.theta()));}
              else std::cout<<"VERTICES NULL"<<std::endl;

              tau.addUserFloat("zIP",z_2);

              //Tau shape variables
              int dm = tau.decayMode();
              //float EMratio = tau.emFraction();
              //std::cout<<"emfraction: "<<EMratio<<std::endl;
              float pt_weighted_dr_signal = tau_pt_weighted_dr_signal(tau,dm); 
              tau.addUserFloat("tau_pt_weighted_dr_signal", pt_weighted_dr_signal);
              float pt_weighted_deta_strip = tau_pt_weighted_deta_strip(tau,dm);
              tau.addUserFloat("tau_pt_weighted_deta_strip", pt_weighted_deta_strip);
              float pt_weighted_dphi_strip = tau_pt_weighted_dphi_strip(tau,dm);
              tau.addUserFloat("tau_pt_weighted_dphi_strip", pt_weighted_dphi_strip);
              float pt_weighted_dr_iso = tau_pt_weighted_dr_iso(tau,dm);
              tau.addUserFloat("tau_pt_weighted_dr_iso",pt_weighted_dr_iso);
              float n_photons_total= tau_n_photons_total(tau);
              tau.addUserFloat("n_photons_total",n_photons_total);

              //std::cout<<"n_photons_total "<<n_photons_total<<std::endl;

              float nMatchedSegments = -1;
              float muonMatched = 0;
              float leadChargedHadrTrackPt = -1;
              float leadChargedHadrTrackPtErr = -1;
              float nIsoTracks=-1;
              float nIsoNeutral=-1;
              float nIsoGamma=-1;
              float nSigGamma=-1;
              nIsoTracks = tau.isolationChargedHadrCands().size();
              nIsoNeutral = tau.isolationNeutrHadrCands().size();
              nIsoGamma = tau.isolationGammaCands().size();
              nSigGamma = tau.signalGammaCands().size();
              //
              float sigPhoIso = 0.; 
              for(auto cand : tau.signalGammaCands() ) {sigPhoIso += cand->pt();}
              sigPhoIso=sigPhoIso/nSigGamma;
              tau.addUserFloat("sigPhoIsoAvePt",sigPhoIso);
              float phoIso = 0.; 
              float phoIso1 = 0.; 
              float phoIso15 = 0.; 
              float phoIso2 = 0.; 
              for(auto cand : tau.isolationGammaCands() ) {
                  phoIso += cand->pt();
                  if (cand->pt()>2) {phoIso1+=cand->pt(); phoIso15+=cand->pt(); phoIso2+=cand->pt();}
                  else if (cand->pt()>1.5) {phoIso15+=cand->pt(); phoIso1+=cand->pt();}
                  else if (cand->pt()>1) {phoIso1+=cand->pt();}
              }
              if (nIsoGamma>0) phoIso=phoIso/nIsoGamma;
              tau.addUserFloat("phoIsoAvePt",phoIso);
              tau.addUserFloat("phoIso1",phoIso1);
              tau.addUserFloat("phoIso15",phoIso15);
              tau.addUserFloat("phoIso2",phoIso2);
              float chIso  = 0.; 
              for(auto cand : tau.isolationChargedHadrCands() ) {chIso += cand->pt();}
              if (nIsoTracks>0) chIso=chIso/nIsoTracks;
              tau.addUserFloat("chIsoAvePt",chIso);
              float nhIso  = 0.; 
              for(auto cand : tau.isolationNeutrHadrCands() ) {nhIso += cand->pt();}
              if (nIsoNeutral>0) nhIso = nhIso/nIsoNeutral;
              tau.addUserFloat("nhIsoAvePt",nhIso);


              pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(tau.leadChargedHadrCand().get());

              if(tau.leadChargedHadrCand().isNonnull()){
                  leadChargedHadrTrackPt = tau.leadChargedHadrCand()->pt();
                  //leadChargedHadrTrackPtErr = tau.leadChargedHadrCand()->ptError();
                  dZ = packedLeadTauCand->dz();
                  dXY = packedLeadTauCand->dxy();
                  //std::cout<<"Sync Tau dZ is "<<dZ<<std::endl; 
                  if(iEvent.getByToken(muons_,muons)){
                      for(unsigned int k =0; k!=muons->size();k++){
                          if(ROOT::Math::VectorUtil::DeltaR(muons->at(k).p4(),tau.leadChargedHadrCand()->p4())<0.15){
                              if(muons->at(k).numberOfMatches()>nMatchedSegments){
                                  nMatchedSegments = muons->at(k).numberOfMatches();
                                  //std::cout<<"====IN MUON LOOP: Matched Segments ======"<<std::endl;
                                  //std::cout<<" matched muon N Seg: "<<nMatchedSegments<<std::endl;
                              }
                              muonMatched=1;
                          }
                      }
                  }
              }

	      //tau.addUserFloat("iso",tau.tauID("byIsolationMVArun2v1DBoldDMwLTraw"));
	      tau.addUserFloat("iso",tau.tauID("byIsolationMVArun2v1DBnewDMwLTraw"));
              tau.addUserFloat("nIsoTracks",nIsoTracks);
              tau.addUserFloat("nIsoNeutral",nIsoNeutral);
              tau.addUserFloat("nIsoGamma",nIsoGamma);
              tau.addUserFloat("leadChargedHadrTrackPt",leadChargedHadrTrackPt);
              tau.addUserFloat("leadChargedHadrTrackPtErr",leadChargedHadrTrackPtErr);
              tau.addUserFloat("taudZ",dZ);
              tau.addUserFloat("taudXY",dXY);
              tau.addUserFloat("muonNMatchedSeg",nMatchedSegments);
              tau.addUserFloat("muonTauHadMatched",muonMatched);

              out->push_back(tau);
          }
      }
      iEvent.put(std::move(out),"");    
  } 

  // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TauCollection> src_;
  edm::EDGetTokenT<pat::MuonCollection> muons_;
  edm::EDGetTokenT<reco::GenParticleCollection> gen_;
  edm::EDGetTokenT<std::vector<reco::GenJet>> genHadTaus_;
  edm::EDGetTokenT<std::vector<reco::GenJet>> genMuTaus_;
  edm::EDGetTokenT<std::vector<reco::GenJet>> genEleTaus_;
  edm::EDGetTokenT<reco::VertexCollection> vtxSrc_;


  int tauGenMatch2(edm::Event& iEvent, const reco::Candidate::LorentzVector& direction ) {
      // Check that there are gen particles (MC)
      
      edm::Handle<reco::GenParticleCollection> genParticles;
      if(!(iEvent.getByToken(gen_,genParticles))) return -1;

      // Find the closest gen particle to our candidate
      if ( genParticles->size() > 0 ) {
          reco::GenParticle closest = genParticles->at(0);
          double closestDR = 999;
          // The first two codes are based off of matching to true electrons/muons
          // Find the closest gen particle...
          for(size_t m = 0; m != genParticles->size(); ++m) {
              reco::GenParticle genp = genParticles->at(m);
              double tmpDR = reco::deltaR( direction , genp.p4() );
              if ( tmpDR < closestDR ) { closest = genp; closestDR = tmpDR; }
          }
          double genID = abs(closest.pdgId());

          // The remaining codes are based off of matching to reconstructed tau decay products
          edm::Handle<std::vector<reco::GenJet>> genHTaus;
          iEvent.getByToken(genHadTaus_,genHTaus);
          edm::Handle<std::vector<reco::GenJet>> genMTaus;
          iEvent.getByToken(genMuTaus_,genMTaus);
          edm::Handle<std::vector<reco::GenJet>> genETaus;
          iEvent.getByToken(genEleTaus_,genETaus);
          // Loop over all versions of gen taus and find closest one
          double closestDR_HTau = 999;
          double closestDR_ETau = 999;
          double closestDR_MTau = 999;
          if ( genHTaus->size() > 0 ) {
              for (size_t j = 0; j != genHTaus->size(); ++j) {
                  double tmpDR = reco::deltaR( direction, genHTaus->at(j).p4() );
                  if (tmpDR < closestDR_HTau) closestDR_HTau = tmpDR;
              }
          }
          if ( genETaus->size() > 0 ) {
              for (size_t j = 0; j != genETaus->size(); ++j) {
                  double tmpDR = reco::deltaR( direction, genETaus->at(j).p4() );
                  if (tmpDR < closestDR_ETau) closestDR_ETau = tmpDR;
              }
          }
          if ( genMTaus->size() > 0 ) {
              for (size_t j = 0; j != genMTaus->size(); ++j) {
                  double tmpDR = reco::deltaR( direction, genMTaus->at(j).p4() );
                  if (tmpDR < closestDR_MTau) closestDR_MTau = tmpDR;
              }
          }

          // Now return the value based on which object is closer, the closest
          // single gen particle, or the rebuild gen taus
          // The first two codes are based off of matching to true electrons/muons
          double closestGetTau = TMath::Min(closestDR_ETau, closestDR_MTau);
          if (closestDR_HTau < closestGetTau) closestGetTau = closestDR_HTau;
          if (closestDR < closestGetTau) {
              if (genID == 11 && closest.pt() > 8 && closest.statusFlags().isPrompt() && closestDR < 0.2 ) return 1.0;
              if (genID == 13 && closest.pt() > 8 && closest.statusFlags().isPrompt() && closestDR < 0.2 ) return 2.0;
          }
          // Other codes based off of not matching previous 2 options
          // as closest gen particle, retruns based on closest rebuilt gen tau
          if (closestDR_ETau < 0.2 && closestDR_ETau < TMath::Min(closestDR_MTau, closestDR_HTau)) return 3.0;
          if (closestDR_MTau < 0.2 && closestDR_MTau < TMath::Min(closestDR_ETau, closestDR_HTau)) return 4.0;
          if (closestDR_HTau < 0.2 && closestDR_HTau < TMath::Min(closestDR_ETau, closestDR_MTau)) return 5.0;
          return 6.0; // No match, return 6 for "fake tau"
      }
      return -1.0;
  } 



};

