// -*- C++ -*-
//
//
// Original Author:  Isobel Ojalvo
//         Created:  Nov 16
// $Id: PATJetBRreco.h
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
#include "DataFormats/JetReco/interface/PFJet.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "Math/GenVector/VectorUtil.h"

#include <boost/foreach.hpp>
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BTauReco/interface/TrackIPTagInfo.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TLorentzVector.h"
#include "DataFormats/BTauReco/interface/TaggingVariable.h"

class PATJetBReco : public edm::EDProducer {
   public:
  
  

  explicit PATJetBReco(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    leptons_(iConfig.getParameter<edm::InputTag>("leptons")),
    vertex_(iConfig.getParameter<edm::InputTag>("vertices"))
  {
    produces<pat::JetCollection>();
  }
  
  ~PATJetBReco() {}
   private:

  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    std::unique_ptr<pat::JetCollection> out(new pat::JetCollection);
    Handle<pat::JetCollection > cands;
    Handle<pat::MuonCollection > leptons; ///adding muons! :D
    Handle<reco::VertexCollection> vertices;
    bool verticesExist = iEvent.getByLabel(vertex_,vertices);

    if(verticesExist)
      verticesExist*=(vertices->size()>0)&&(vertices->at(0).isValid());

    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  l=0;l!=cands->size();++l){
	pat::Jet jet = cands->at(l);
	reco::PFCandidatePtr pfcand;
	std::vector<reco::PFCandidatePtr> chargedParticles;
	std::vector<reco::PFCandidatePtr> chargedParticlesNoD0;
	std::vector<reco::PFCandidatePtr> muons;
	std::vector<reco::PFCandidatePtr> elecs;

	for(unsigned int j=0;j<jet.getPFConstituents().size();++j) {
	  pfcand = jet.getPFConstituents().at(j);

	  if(!pfcand.isNonnull())
	    continue;

	  if(abs(pfcand->pdgId())==211&&pfcand->pt()>1)
	    chargedParticles.push_back(pfcand);
	  
	  
	  if(abs(pfcand->pdgId())==13&&pfcand->pt()>3)
	    muons.push_back(pfcand);
	  
	  
	  if(abs(pfcand->pdgId())==11&&pfcand->pt()>1)
	    elecs.push_back(pfcand);
	  
	}

	double massDpm = 0;
	math::PtEtaPhiMLorentzVector Dpm;

	if(jet.pt()>20&&chargedParticles.size()>2)
	  for(unsigned int k = 0; k<chargedParticles.size()-1;k++)
	    for(unsigned int j = k+1; j<chargedParticles.size();j++)
	      for(unsigned int n = j+1; n<chargedParticles.size();n++)
		if(fabs( chargedParticles.at(k)->charge()
			+chargedParticles.at(j)->charge()
			+chargedParticles.at(n)->charge())==1){

		  //printf("chargedparticles size %i\n",(int)chargedParticles.size());
		  math::PtEtaPhiMLorentzVector kaon(chargedParticles.at(k)->pt(),
						    chargedParticles.at(k)->eta(),
						    chargedParticles.at(k)->phi(),
						    0.494);
		  math::PtEtaPhiMLorentzVector pion1(chargedParticles.at(j)->pt(),
						    chargedParticles.at(j)->eta(),
						    chargedParticles.at(j)->phi(),
						    0.140);
		  
		  math::PtEtaPhiMLorentzVector pion2(chargedParticles.at(n)->pt(),
						    chargedParticles.at(n)->eta(),
						    chargedParticles.at(n)->phi(),
						    0.140);
		  
		  if(chargedParticles.at(k)->charge()>0){
		    pion1 =math::PtEtaPhiMLorentzVector(chargedParticles.at(k)->pt(),
						       chargedParticles.at(k)->eta(),
						       chargedParticles.at(k)->phi(),
						       0.140);
		    kaon =math::PtEtaPhiMLorentzVector(chargedParticles.at(j)->pt(),
						       chargedParticles.at(j)->eta(),
						     chargedParticles.at(j)->phi(),
						       0.494);
		  }
		  else if(chargedParticles.at(n)->charge()>0){
		    pion2 =math::PtEtaPhiMLorentzVector(chargedParticles.at(k)->pt(),
						       chargedParticles.at(k)->eta(),
						       chargedParticles.at(k)->phi(),
						       0.140);
		    kaon =math::PtEtaPhiMLorentzVector(chargedParticles.at(n)->pt(),
						       chargedParticles.at(n)->eta(),
						       chargedParticles.at(n)->phi(),
						       0.494);
		  }

		  Dpm = pion1+pion2+kaon;
		  double mass = (pion1+pion2+kaon).M();
		  
		  if(fabs(mass-1.869)<fabs(massDpm-1.869)){ //find the candidate closest to Dpm mass
		    massDpm = mass;
		  }
		}

	jet.addUserFloat("massDpm",massDpm);



	int finalpion;
	int finalkaon = 0;
	double massD0 = 0;
	math::PtEtaPhiMLorentzVector D0;
	if(jet.pt()>20&&chargedParticles.size()>1)
	  for(unsigned int k = 0; k<chargedParticles.size()-1;k++)
	    for(unsigned int j = k+1; j<chargedParticles.size();j++)
	      if(chargedParticles.at(k)->charge()+chargedParticles.at(j)->charge()==0){
		//printf("chargedparticles size %i\n",(int)chargedParticles.size());
		math::PtEtaPhiMLorentzVector kaon(chargedParticles.at(k)->pt(),
						  chargedParticles.at(k)->eta(),
						  chargedParticles.at(k)->phi(),
						  0.494);
		math::PtEtaPhiMLorentzVector pion(chargedParticles.at(j)->pt(),
						  chargedParticles.at(j)->eta(),
						  chargedParticles.at(j)->phi(),
						  0.140);
		
		if(chargedParticles.at(k)->charge()>0){
		  pion =math::PtEtaPhiMLorentzVector(chargedParticles.at(k)->pt(),
						     chargedParticles.at(k)->eta(),
						     chargedParticles.at(k)->phi(),
						     0.140);
		  kaon =math::PtEtaPhiMLorentzVector(chargedParticles.at(j)->pt(),
						     chargedParticles.at(j)->eta(),
						     chargedParticles.at(j)->phi(),
						     0.494);
		}

		D0 = pion+kaon;
		double mass = (pion+kaon).M();

		if(fabs(mass-1.864)<fabs(massD0-1.864)){ //find the candidate closest to D0 mass
		  massD0 = mass;
		  finalpion = k;
		  finalkaon = j;
		  //printf("k= %i th particle pt %f, j= %i th particle pt %f \n",k,chargedParticles.at(k)->pt(),j,chargedParticles.at(j)->pt());
		}
	      }

	jet.addUserFloat("massD0",massD0);
	////try d0 pi pi pi decay mode
	double massBpm2 = 0;
	math::PtEtaPhiMLorentzVector Bpm2;
	if(jet.pt()>20&&chargedParticles.size()>4&&massD0>0){
	  chargedParticlesNoD0 = chargedParticles;
	  chargedParticlesNoD0.erase(chargedParticlesNoD0.begin()+finalpion);
	 
	  if(finalpion>finalkaon)
	    chargedParticlesNoD0.erase(chargedParticlesNoD0.begin()+finalkaon);
	  else
	    chargedParticlesNoD0.erase(chargedParticlesNoD0.begin()+(finalkaon-1));

	  //for(unsigned int t= 0; t<chargedParticlesNoD0.size();t++){
	  // printf("%i pt: %f\n",t,chargedParticlesNoD0.at(t)->pt());
	  //}


	  for(unsigned int k = 0; k<chargedParticlesNoD0.size()-1;k++)
	    for(unsigned int j = k+1; j<chargedParticlesNoD0.size();j++)
	      for(unsigned int n = j+1; n<chargedParticlesNoD0.size();n++)
		if(chargedParticlesNoD0.at(k)->charge()
		   +chargedParticlesNoD0.at(j)->charge()
		   +chargedParticlesNoD0.at(n)->charge()==1){
		  //printf("chargedparticles size %i\n",(int)chargedParticles.size());
		  math::PtEtaPhiMLorentzVector pion1(chargedParticlesNoD0.at(k)->pt(),
						    chargedParticlesNoD0.at(k)->eta(),
						    chargedParticlesNoD0.at(k)->phi(),
						    0.140);
		  math::PtEtaPhiMLorentzVector pion2(chargedParticlesNoD0.at(j)->pt(),
						    chargedParticlesNoD0.at(j)->eta(),
						    chargedParticlesNoD0.at(j)->phi(),
						    0.140);
		  math::PtEtaPhiMLorentzVector pion3(chargedParticlesNoD0.at(j)->pt(),
						    chargedParticlesNoD0.at(j)->eta(),
						    chargedParticlesNoD0.at(j)->phi(),
						    0.140);		

		  Bpm2 = pion1+pion2+pion3;
		  double mass = (pion1+pion2+pion3+D0).M();
		  
		  if(fabs(mass-5.279)<fabs(massD0-5.279)){ //find the candidate closest to D0 mass
		    massBpm2 = mass;
		  }
		}
	}
	jet.addUserFloat("massBpm2",massBpm2);


	math::PtEtaPhiMLorentzVector Bpm;
	double massBpm = 0;
	double massBpm_charge = 0;
	double massBpm_pt = 0;
	double massBpm_eta = 0;
	double massBpm_phi = 0;
	if(jet.pt()>20&&chargedParticles.size()>1&&muons.size()==1){
	  //for(unsigned int k = 0; k<muons.size();k++){
	  //printf("muon pt %f\n",muons.at(0)->pt());
	    math::PtEtaPhiMLorentzVector muon(muons.at(0)->pt(),
					      muons.at(0)->eta(),
					      muons.at(0)->phi(),
					      0.105);
	    double mass = (D0+muon).M();
	    Bpm = D0+muon;
	    massBpm=mass;
	    massBpm_charge = muons.at(0)->charge();
	    massBpm_pt = Bpm.pt();
	    massBpm_eta = Bpm.eta();
	    massBpm_phi = Bpm.phi();
	  }

	jet.addUserFloat("massBpm",massBpm);	
	jet.addUserFloat("massBpm_charge",massBpm_charge);
	jet.addUserFloat("massBpm_pt",massBpm_pt);
	jet.addUserFloat("massBpm_eta",massBpm_eta);
	jet.addUserFloat("massBpm_phi",massBpm_phi);
	
	double massBpmElecs = 0;

	if(jet.pt()>20&&chargedParticles.size()>1&&elecs.size()>0)
	  for(unsigned int k = 0; k<elecs.size();k++){
	    
	    math::PtEtaPhiMLorentzVector elec(elecs.at(k)->pt(),
					      elecs.at(k)->eta(),
					      elecs.at(k)->phi(),
					      0.000511);
	    double mass = (D0+elec).M();
	    
	    if(fabs(mass-5.279)<fabs(massBpmElecs-5.279))
	      massBpmElecs = mass;
	  }
      
	jet.addUserFloat("massBpmElecs",massBpmElecs);
	out->push_back(jet);
      }
    iEvent.put(std::move(out),"");    
  } 
  
  // ----------member data ---------------------------
  edm::InputTag src_;
  edm::InputTag leptons_;
  edm::InputTag vertex_;
    
};

