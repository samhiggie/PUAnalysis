//systemincludes
#include <memory>
#include <vector>
#include <iostream>

// CMS includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"


class MiniAODElectronVIDEmbedder : public edm::EDProducer
{
public:
  explicit MiniAODElectronVIDEmbedder(const edm::ParameterSet&);
  ~MiniAODElectronVIDEmbedder() {}

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  // Methods
  virtual void beginJob();
  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);
  virtual void endJob();

  // Data
  edm::EDGetTokenT<edm::View<pat::Electron> > electronCollectionToken_;
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  std::vector<edm::EDGetTokenT<edm::ValueMap<bool> > > idMapTokens_; // store all ID tokens
  std::vector<std::string> idLabels_; // labels for the userInts holding results
  std::string eleIsoLabel_; //label for the dBRelIso UserFloat
  std::string eleConvLabel_; //label for the dBRelIso UserFloat
  std::unique_ptr<std::vector<pat::Electron> > out; // Collection we'll output at the end
};


// Constructors and destructors
// class member functions
MiniAODElectronVIDEmbedder::MiniAODElectronVIDEmbedder(const edm::ParameterSet& iConfig):
	electronCollectionToken_(consumes<edm::View<pat::Electron> >(iConfig.exists("src") ? 
			iConfig.getParameter<edm::InputTag>("src") :
			edm::InputTag("slimmedElectrons"))),
	vtxToken_(consumes<reco::VertexCollection>(iConfig.exists("vtxSrc") ? 
			iConfig.getParameter<edm::InputTag>("vtxSrc") :
			edm::InputTag("offlineSlimmedPrimaryVertices"))),
	idLabels_(iConfig.exists("idLabels") ?
			iConfig.getParameter<std::vector<std::string> >("idLabels") :
			std::vector<std::string>()),
	eleIsoLabel_(iConfig.exists("eleIsoLabel") ?
			iConfig.getParameter<std::string>("eleIsoLabel") :
			std::string("dBRelIso")),
	eleConvLabel_(iConfig.exists("eleConvLabel") ?
			iConfig.getParameter<std::string>("eleConvLabel") :
			std::string("eleConversion"))
{
	std::vector<edm::InputTag> idTags = iConfig.getParameter<std::vector<edm::InputTag> >("ids");

	for(unsigned int i = 0;
			(i < idTags.size() && i < idLabels_.size()); // ignore IDs with no known label
			++i)
	{
		idMapTokens_.push_back(consumes<edm::ValueMap<bool> >(idTags.at(i)));
	}

	produces<std::vector<pat::Electron> >();
}


void MiniAODElectronVIDEmbedder::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	out = std::unique_ptr<std::vector<pat::Electron> >(new std::vector<pat::Electron>);

	edm::Handle<edm::View<pat::Electron> > electronsIn;
	std::vector<edm::Handle<edm::ValueMap<bool> > > ids(idMapTokens_.size(), edm::Handle<edm::ValueMap<bool> >() );

	iEvent.getByToken(electronCollectionToken_, electronsIn);


	edm::Handle<reco::VertexCollection> vertices;
	iEvent.getByToken(vtxToken_, vertices);
	if (vertices->empty()) return;//skip event if no vertices found
        //std::cout<<"size of IDMap tokens: "<<idMapTokens_.size()<<std::endl;
	for(unsigned int i = 0;
			i < idMapTokens_.size();
			++i)
	{
		iEvent.getByToken(idMapTokens_.at(i), ids.at(i));
	}

	for(edm::View<pat::Electron>::const_iterator ei = electronsIn->begin();
			ei != electronsIn->end(); ei++) // loop over electrons
	{
		const edm::Ptr<pat::Electron> eptr(electronsIn, ei - electronsIn->begin());

		out->push_back(*ei); // copy electron to save correctly in event

		//Add electron isolation to the tree
		float eleIso04 = 999;
		//std::cout<<"ElectronPt: "<<ei->pt()<<std::endl;
		eleIso04 = (ei->chargedHadronIso()+std::max(ei->photonIso()+ei->neutralHadronIso()-(0.5*(ei->puChargedHadronIso())),0.0))/(ei->pt());
                //std::cout<<"electron Isolation04: "<<eleIso04<<std::endl;
		float eleIso03 = 999;
		eleIso03 = (eptr->pfIsolationVariables().sumChargedHadronPt + std::max(eptr->pfIsolationVariables().sumNeutralHadronEt +
					eptr->pfIsolationVariables().sumPhotonEt - 0.5 * eptr->pfIsolationVariables().sumPUPt, 0.0)) / ei->pt(); 
                //std::cout<<"electron Isolation03: "<<eleIso03<<std::endl;
		out->back().addUserFloat(eleIsoLabel_, eleIso04);
		out->back().addUserFloat("iso", eleIso03);
		out->back().addUserFloat("dBRelIso03", eleIso03);

		out->back().addUserFloat("eleIsoChHadIso", ei->chargedHadronIso()); 
		out->back().addUserFloat("eleIsoPUChHadIso", ei->puChargedHadronIso()); 
		out->back().addUserFloat("eleIsoPhotonIso",ei->photonIso());
		out->back().addUserFloat("eleIsoNeuHadIso",ei->neutralHadronIso());

		out->back().addUserFloat("eleIsoSumChHadPt", eptr->pfIsolationVariables().sumChargedHadronPt);
		out->back().addUserFloat("eleIsoSumNeuHadPt", eptr->pfIsolationVariables().sumNeutralHadronEt);
		out->back().addUserFloat("eleIsoSumPhoEt", eptr->pfIsolationVariables().sumPhotonEt);
		out->back().addUserFloat("eleIsoSumPUPt", eptr->pfIsolationVariables().sumPUPt);

		//electron conversion
		if ((ei->gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS))<=1&&ei->passConversionVeto()){
			out->back().addUserInt(eleConvLabel_, 0);
		}
		else{out->back().addUserInt(eleConvLabel_, 1);}

		//embed dxy and dz for electron
		out->back().addUserFloat("dZ",ei->gsfTrack()->dz(vertices->at(0).position())); 
		out->back().addUserFloat("dXY",ei->gsfTrack()->dxy(vertices->at(0).position())); 

		//loop throught the 1:1 VIDs and their labels
		for(unsigned int i = 0; // Loop over ID working points
				i < ids.size(); ++i)
		{
			bool result = (*(ids.at(i)))[eptr];
			out->back().addUserFloat(idLabels_.at(i), float(result)); // 1 for true, 0 for false
                        //std::cout<<"Adding User Float: "<<idLabels_.at(i)<<" with result: "<<float(result)<<std::endl;
		}
	}
	iEvent.put(std::move(out),"");    
}


void MiniAODElectronVIDEmbedder::beginJob()
{}


void MiniAODElectronVIDEmbedder::endJob()
{}


void
MiniAODElectronVIDEmbedder::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODElectronVIDEmbedder);



