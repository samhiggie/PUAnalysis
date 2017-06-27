/*
Author: Isobel Ojalvo
October 13 2013 12:21 AM
*/

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "Utilities/General/interface/FileInPath.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/BTauReco/interface/TrackIPTagInfo.h"

#include "Math/GenVector/VectorUtil.h"
#include "TMVA/Reader.h"
#include "TMVA/Factory.h"
//
// class decleration


class PATJetMVAEmbedder : public edm::EDProducer {
   public:
 

  explicit PATJetMVAEmbedder(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src"))
  {
    produces<pat::JetCollection>();
    
    reader = new TMVA::Reader();
    reader->AddVariable("jetBtag", &jetBtag );
    reader->AddVariable("jetPt", &jetPt );
    reader->AddVariable("jetEta", &jetEta );
    reader->AddVariable("jetChf", &jetChf );
    reader->AddVariable("jetPhf", &jetPhf );
    reader->AddVariable("jetNhf", &jetNhf );
    reader->AddVariable("jetElf", &jetElf );
    reader->AddVariable("jetMuf", &jetMuf );


    reader->AddVariable("jetVtxPt", &jetVtxPt );
    reader->AddVariable("jetVtx3dL", &jetVtx3dL );
    reader->AddVariable("jetVtx3deL", &jetVtx3deL );

    reader->AddSpectator( "jetPt",  &jetPt);
    reader->AddSpectator( "jetGenPt",  &jetGenPt );
    reader->AddSpectator( "jetEta",  &jetEta);


    edm::FileInPath file1("PUAnalysis/Configuration/data/factoryJetRegNewGenJetsAll_BDT_LT100.weights.xml");
    edm::FileInPath file2("PUAnalysis/Configuration/data/factoryJetRegNewGenJetsAll_BDT_GT100.weights.xml");
    reader->BookMVA("BDT",file1.fullPath());
    reader->BookMVA("BDTGT",file2.fullPath());
    //reader->BookMVA("BDT",file1.fullPath());
    
  }
  
  ~PATJetMVAEmbedder() {}
   private:

  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    std::unique_ptr<pat::JetCollection > out(new pat::JetCollection);// change to jet collection

    Handle<pat::JetCollection > cands;// change to jet collection
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	pat::Jet jet = cands->at(i);/// keep changing here
	double mvaFi = 1;
	jetBtag   =0;
	jetPt     =0;
	jetGenPt  =0;
	jetEta    =0;
	jetChf    =0;
	jetElf    =0;
	jetMuf    =0;
	jetNhf    =0;
	jetPhf    =0;
	jetVtxPt  =0;
	jetVtx3dL =0;
	jetVtx3deL=0;

	if(jet.pt()>20){
	  if(jet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0)
	    jetBtag   =jet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");

	  jetPt     =jet.pt();
	  jetGenPt     =jet.userFloat("genJetPt");
	  jetEta    =jet.eta();

	  if(jet.chargedHadronEnergyFraction()>0)
	    jetChf    =jet.chargedHadronEnergyFraction();
	  if(jet.electronEnergyFraction()>0)
	    jetElf    =jet.electronEnergyFraction();
	  if(jet.muonEnergyFraction()>0)
	    jetMuf    =jet.muonEnergyFraction();
	  if(jet.neutralHadronEnergyFraction()>0)
	    jetNhf    =jet.neutralHadronEnergyFraction();
	  if(jet.photonEnergyFraction()>0)
	    jetPhf    =jet.photonEnergyFraction();
	  if(jet.userFloat("VtxPt")>0)
	    jetVtxPt  =jet.userFloat("VtxPt");
	  if(jet.userFloat("Vtx3dL")>0)
	    jetVtx3dL =jet.userFloat("Vtx3dL");
	  if(jet.userFloat("Vtx3deL")>0)
	    jetVtx3deL=jet.userFloat("Vtx3deL");

	  //printf("SVMassb %f TCHPbtag %f nTracksSSV %f threedcharm %f SVNV %f\n",SVMassb,TCHPbtag,nTracksSSV,threedcharm,SVNV);
	  //if(SVMassb>0&&TCHPbtag>0&&nTracksSSV>0&&threedcharm>0&&SVNV>0)
	  if(jet.pt()>20&&jet.pt()<100&&jetBtag>0)
	    mvaFi = reader->EvaluateMVA("BDT",0);

	  if(jet.pt()>=100&&jetBtag>0)
	    mvaFi = reader->EvaluateMVA("BDTGT",0);


	  //printf("==============MVA result: %f\n",mvaFi/jetPt);
	}
	jet.addUserFloat("mvaSF",mvaFi);
	out->push_back(jet);

      }
  
    iEvent.put(std::move(out),"");    

  } 

      // ----------member data ---------------------------
  edm::InputTag src_;
  Float_t jetBtag;
  Float_t jetPt;
  Float_t jetGenPt;
  Float_t jetEta;
  Float_t jetChf;
  Float_t jetElf;
  Float_t jetMuf;
  Float_t jetNhf;
  Float_t jetPhf;
  Float_t jetVtxPt;
  Float_t jetVtx3dL;
  Float_t jetVtx3deL;
  TMVA::Reader *reader;

};

