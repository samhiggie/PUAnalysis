// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "Math/GenVector/VectorUtil.h" 
#include "TMath.h"
#include <TTree.h>
#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include <TFile.h>

#include "DataFormats/HLTReco/interface/TriggerRefsCollections.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"


/*
 * Get the SF for Embedded samples
 * Author: Isobel Ojalvo (last mod July 2014)
 */

template<typename T>
class EmbeddedTriggerFilterFiller : public NtupleFillerBase {
 public:
    EmbeddedTriggerFilterFiller(){}

    TFile* theFile;
    
    EmbeddedTriggerFilterFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      isEmbedded_(iConfig.getParameter<bool>("isEmbedded")),
      pt_1_(iConfig.getParameter<std::string>("pt_1")),
      eta_1_(iConfig.getParameter<std::string>("eta_1")),
      phi_1_(iConfig.getParameter<std::string>("phi_1")),
      pt_2_( iConfig.getParameter<std::string>("pt_2")),
      eta_2_( iConfig.getParameter<std::string>("eta_2")),
      phi_2_( iConfig.getParameter<std::string>("phi_2")),
      filter_(iConfig.getParameter<std::string>("triggerFilter")),
      triggerBits_(iC.consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBits"))),
      triggerObjects_(iC.consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects")))
	{
	  idBranch_1 = t->Branch("emb_trig_Match_1",&idValue_1,"emb_trig_Match_1/I");
	  idBranch_2 = t->Branch("emb_trig_Match_2",&idValue_2,"emb_trig_Match_2/I");

	  function_pt_1  = new StringObjectFunction<T>(pt_1_);
	  function_eta_1  = new StringObjectFunction<T>(eta_1_);
	  function_phi_1  = new StringObjectFunction<T>(phi_1_);
	  function_pt_2  = new StringObjectFunction<T>(pt_2_);
	  function_eta_2  = new StringObjectFunction<T>(eta_2_);
	  function_phi_2  = new StringObjectFunction<T>(phi_2_);
	}


  ~EmbeddedTriggerFilterFiller()
    { 
      if(function_pt_1!=0)  delete function_pt_1;
      if(function_eta_1!=0)  delete function_eta_1;
      if(function_phi_1!=0)  delete function_phi_1;
      if(function_pt_2!=0)  delete function_pt_2;
      if(function_eta_2!=0)  delete function_eta_2;
      if(function_phi_2!=0)  delete function_phi_2;
    }
       


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    edm::Handle<std::vector<T> > handle;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::TriggerResults> triggerBits;

    idValue_1 = 1;
    idValue_2 = 1;

    iEvent.getByToken(triggerBits_, triggerBits);
    iEvent.getByToken(triggerObjects_, triggerObjects);


    if(iEvent.getByToken(src_,handle)) {
      if(handle->size()>0){

	//std::cout<<"pt: "<<pt<<" eta: "<<eta<<" dm: "<<dm<<std::endl;
	if(isEmbedded_){
	  double pt_1  = (*function_pt_1)(handle->at(0));
	  double eta_1  = (*function_eta_1)(handle->at(0));
	  double phi_1  = (*function_phi_1)(handle->at(0));
	  double pt_2  = (*function_pt_2)(handle->at(0));
	  double eta_2  = (*function_eta_2)(handle->at(0));
	  double phi_2  = (*function_phi_2)(handle->at(0));

	  reco::Candidate::LorentzVector p4_1(pt_1,eta_1,phi_1,115);
	  reco::Candidate::LorentzVector p4_2(pt_2,eta_2,phi_2,115);
	  //find all the trigger objects that match to the input filter, there should be 2 per good event
	  std::vector<reco::Candidate::LorentzVector>  filters_p4;
	  filters_p4 = getFilters(iEvent, triggerBits, filter_, *triggerObjects);
	  
	  idValue_1 = matchFilter(p4_1,filters_p4);
	  idValue_2 = matchFilter(p4_2,filters_p4);
	  
	}
      }
    }
  }

  bool matchFilter(reco::Candidate::LorentzVector gen_leg, std::vector<reco::Candidate::LorentzVector> filters){
    for(auto filter: filters){
      if(deltaR(filter,gen_leg)<0.5){
	//std::cout<<"found matched filter for embedded sample"<<std::endl;
	return true;
      }
    }
    //std::cout<<"NO found matched filter for embedded sample"<<std::endl;
    return false;
  }

  std::vector<reco::Candidate::LorentzVector> getFilters(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> triggerBits,std::string filter,pat::TriggerObjectStandAloneCollection triggerObjects)
    {
      std::vector<reco::Candidate::LorentzVector> out; out.clear();

      //get All the final trigger objects
      for (pat::TriggerObjectStandAlone obj : triggerObjects) { 

	obj.unpackFilterLabels(iEvent, *triggerBits); 
	reco::Candidate::LorentzVector a(obj.px(),obj.py(),obj.pz(),sqrt(obj.px()*obj.px()+obj.py()*obj.py()+obj.pz()*obj.pz()));



	for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
	  //std::cout<<"Filter Label :"<<obj.filterLabels()[h]<<std::endl;
	  if (obj.filter(filter))
	    out.push_back(a);
	}
      }
      //std::cout<<out.size()<< " filters found"<<std::endl;
      return out;
    }


 protected:

  edm::EDGetTokenT<std::vector<T> > src_;
  bool isEmbedded_;
  std::string pt_1_;
  std::string eta_1_;
  std::string phi_1_;
  std::string pt_2_;
  std::string eta_2_;
  std::string phi_2_;
  std::string filter_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  StringObjectFunction<T>*function_pt_1;
  StringObjectFunction<T>*function_eta_1;
  StringObjectFunction<T>*function_phi_1;
  StringObjectFunction<T>*function_pt_2;
  StringObjectFunction<T>*function_eta_2;
  StringObjectFunction<T>*function_phi_2;

  float idValue_1;
  float idValue_2;
  TBranch *idBranch_1;
  TBranch *idBranch_2;
  RooWorkspace *w;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef EmbeddedTriggerFilterFiller<PATDiTauPair> PATDiTauPairEmbeddedTriggerFilterFiller;
typedef EmbeddedTriggerFilterFiller<PATMuTauPair> PATMuTauPairEmbeddedTriggerFilterFiller;
typedef EmbeddedTriggerFilterFiller<PATMuTauPair> PATMuPaircsvjetvarfiller;
typedef EmbeddedTriggerFilterFiller<PATElecTauPair> PATEleTauPairEmbeddedTriggerFilterFiller;
typedef EmbeddedTriggerFilterFiller<PATMuPair> PATMuPairEmbeddedTriggerFilterFiller;




