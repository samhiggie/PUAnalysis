/*
 * Embeds the muon ID as recommended by the Muon POG
 * Author: Devin N. Taylor, UW-Madison
 */

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/Muon.h"

#include <math.h>

// class declaration
class MiniAODMuonIDEmbedder : public edm::EDProducer {
	public:
		explicit MiniAODMuonIDEmbedder(const edm::ParameterSet& pset);
		virtual ~MiniAODMuonIDEmbedder(){}
		void produce(edm::Event& iEvent, const edm::EventSetup& es);

	private:
		edm::EDGetTokenT<pat::MuonCollection> muonsCollection_;
		edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
		reco::Vertex pv_;
};

// class member functions
MiniAODMuonIDEmbedder::MiniAODMuonIDEmbedder(const edm::ParameterSet& pset) {
	muonsCollection_ = consumes<pat::MuonCollection>(pset.getParameter<edm::InputTag>("src"));
	vtxToken_            = consumes<reco::VertexCollection>(pset.getParameter<edm::InputTag>("vertices"));

	produces<pat::MuonCollection>();
}

void MiniAODMuonIDEmbedder::produce(edm::Event& iEvent, const edm::EventSetup& es) {
	edm::Handle<std::vector<pat::Muon>> muonsCollection;
	iEvent.getByToken(muonsCollection_ , muonsCollection);

	edm::Handle<reco::VertexCollection> vertices;
	iEvent.getByToken(vtxToken_, vertices);
	if (vertices->empty()) return; // skip the event if no PV found
	pv_ = vertices->front();

	const std::vector<pat::Muon> * muons = muonsCollection.product();

	unsigned int nbMuon =  muons->size();

	std::unique_ptr<pat::MuonCollection> out(new pat::MuonCollection);
	out->reserve(nbMuon);

        //std::cout<<"NMuons: "<<nbMuon<<std::endl;
	for(unsigned i = 0 ; i < nbMuon; i++){
		pat::Muon muon(muons->at(i));


		if(muon.muonBestTrack().isNonnull()) {
                        float xy = muon.muonBestTrack()->dxy(vertices->at(0).position());
                        float z = muon.muonBestTrack()->dz(vertices->at(0).position());
			muon.addUserFloat("dXY",xy); //bestTrack
			muon.addUserFloat("dZ",z); //bestTrack

		}
		else {
			muon.addUserFloat("dXY",-999.);
			muon.addUserFloat("dZ",-999.);
		}

		float muIso = (muon.pfIsolationR04().sumChargedHadronPt + std::max(
					muon.pfIsolationR04().sumNeutralHadronEt +
					muon.pfIsolationR04().sumPhotonEt - 
					0.5 * muon.pfIsolationR04().sumPUPt, 0.0)) / muon.pt(); 
		//std::cout<<"Muon Isolation04: "<<muIso<<std::endl;
		float muIso03 = (muon.pfIsolationR03().sumChargedHadronPt + std::max(
					muon.pfIsolationR03().sumNeutralHadronEt + muon.pfIsolationR03().sumPhotonEt - 0.5 * muon.pfIsolationR03().sumPUPt, 0.0)) / muon.pt();
		// (muon.chargedHadronIso()+std::max(muon.photonIso()+muon.neutralHadronIso()-(0.5*(muon.puChargedHadronIso())),0.0))/(muon.pt());
		//std::cout<<"muon "<<i<<" pt: "<<muon.pt()<<" medium ID: "<<muon.isMediumMuon()<<std::endl;
		//std::cout<<"     iso_1: "<<muIso03<<std::endl;

		int muId = 0; 
		if (muon.isLooseMuon()&&muon.innerTrack()->validFraction()>0.49&&((muon.isGlobalMuon()&&muon.globalTrack()->normalizedChi2()<3&&muon.combinedQuality().chi2LocalPosition<12&&muon.combinedQuality().trkKink<20&&muon.segmentCompatibility()>0.303)||(muon.segmentCompatibility()>0.451)))
		{
			muId=1;
		}

		muon.addUserFloat("dBRelIso",muIso);
		muon.addUserFloat("iso",muIso);
		muon.addUserFloat("dBRelIso03",muIso03);
		muon.addUserInt("mediumID",muId);

		out->push_back(muon);
	}
	iEvent.put(std::move(out),"");    
}

// define plugin
DEFINE_FWK_MODULE(MiniAODMuonIDEmbedder);
