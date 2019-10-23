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
 * Author: Sam Higginbotham (last mod Oct 2019)
 */

template<typename T>
class EmbeddedTriggerFilterMatcher : public NtupleFillerBase {
 public:
    EmbeddedTriggerFilterMatcher(){}

    TFile* theFile;
    
    EmbeddedTriggerFilterMatcher(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      isEmbedded_(iConfig.getParameter<bool>("isEmbedded")),
      triggerBits_(iC.consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerBits"))),
      triggerObjects_(iC.consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects")))
	{


	  t->Branch("emb_trig_Match_Mu24_1",&trigMatchValue_Mu24_1,"emb_trig_MatchMu24_1/I");
	  t->Branch("emb_trig_Match_Mu27_1",&trigMatchValue_Mu27_1,"emb_trig_MatchMu27_1/I");
	  t->Branch("emb_trig_Match_Mu20Tau27_2018_1",&trigMatchValue_Mu20Tau27_2018_1,"emb_trig_MatchMu20Tau27_2018_1/I");
	  t->Branch("emb_trig_Match_Mu20Tau27_2017_1",&trigMatchValue_Mu20Tau27_2017_1,"emb_trig_MatchMu20Tau27_2017_1/I");
	  t->Branch("emb_trig_Match_Mu19Tau20_2016_1",&trigMatchValue_Mu19Tau20_2016_1,"emb_trig_MatchMu19Tau20_2016_1/I");

	  t->Branch("emb_trig_Match_Mu20Tau27_2",&trigMatchValue_Mu20Tau27_2,"emb_trig_MatchMu20Tau27_2/I");
	  t->Branch("emb_trig_Match_Mu19Tau20_2",&trigMatchValue_Mu19Tau20_2,"emb_trig_MatchMu19Tau20_2/I");
	  t->Branch("emb_trig_Match_Mu20HPSTau27_2",&trigMatchValue_Mu20HPSTau27_2,"emb_trig_MatchMu20HPSTau27_2/I");
	  t->Branch("emb_trig_Match_Ele24Tau30_2",&trigMatchValue_Ele24Tau30_2,"emb_trig_MatchEle24Tau30_2/I");
	  t->Branch("emb_trig_Match_TauTau_2",&trigMatchValue_TauTau_2,"emb_trig_MatchTauTau_2/I");
	  t->Branch("emb_trig_Match_TauTau_2",&trigMatchValue_TauTau2016_2,"emb_trig_MatchTauTau_2/I");


	}


  ~EmbeddedTriggerFilterMatcher()
    { 

    }
       


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    edm::Handle<std::vector<T> > handle;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::TriggerResults> triggerBits;

    iEvent.getByToken(triggerBits_, triggerBits);
    iEvent.getByToken(triggerObjects_, triggerObjects);


    if(iEvent.getByToken(src_,handle)) {
      if(handle->size()>0){

      trigMatchValue_Mu24_1=0;
      trigMatchValue_Mu27_1=0;
      trigMatchValue_Mu20Tau27_2018_1=0;
      trigMatchValue_Mu20Tau27_2017_1=0;
      trigMatchValue_Mu19Tau20_2016_1=0;


      trigMatchValue_Mu20Tau27_2=0;
      trigMatchValue_Mu19Tau20_2=0;
      trigMatchValue_Mu20HPSTau27_2=0;
      trigMatchValue_Ele24Tau30_2=0;
      trigMatchValue_TauTau_2=0;
      trigMatchValue_TauTau2016_2=0;
	//std::cout<<"pt: "<<pt<<" eta: "<<eta<<" dm: "<<dm<<std::endl;
	if(isEmbedded_){

	  //find all the trigger objects that match to the input filter, there should be 2 per good event
	  matchFilters(iEvent, triggerBits, *triggerObjects);
	  
	}
      }
    }
  }
 
  void matchFilters(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> triggerBits,pat::TriggerObjectStandAloneCollection triggerObjects)
  {
      //get All the final trigger objects
      for (pat::TriggerObjectStandAlone obj : triggerObjects) { 

          obj.unpackFilterLabels(iEvent, *triggerBits); 

          for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
              //std::cout<<"Filter Label :"<<obj.filterLabels()[h]<<std::endl;
              std::string filter = obj.filterLabels()[h];

              //std::cout<<"The filter that we are looking at now is:   "<<filter<<std::endl;

              if (filter.compare("hltL3crIsoBigORMu18erTauXXer2p1L1f0L2f10QL3f20QL3trkIsoFiltered0p07")==0) {
                  trigMatchValue_Mu20Tau27_2018_1=1;
                  std::cout<<"Found the filter!"<<std::endl;
              }
              if (filter.compare("hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")==0) {
                  trigMatchValue_Mu20Tau27_2017_1=1;
              }
              if (filter.compare("hltL1sMu18erTau20er")==0) {
                  trigMatchValue_Mu19Tau20_2016_1=1;
              }
              if (filter.compare("hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07")==0) {
                  trigMatchValue_Mu24_1=1;
              }
              if (filter.compare("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07")==0) {
                  trigMatchValue_Mu27_1=1;
              }

              if (filter.compare("hltL1sMu18erTau24erIorMu20erTau24er")==0) {
                  trigMatchValue_Mu20Tau27_2=1;
              }
              if (filter.compare("hltL1sMu18erTau20er")==0) {
                  trigMatchValue_Mu19Tau20_2=1;
              }
              if (filter.compare("hltL1sBigORMu18erTauXXer2p1")==0) {
                  trigMatchValue_Mu20HPSTau27_2=1;
              }
              if (filter.compare("hltL1sBigORLooseIsoEGXXerIsoTauYYerdRMin0p3")==0) {
                  trigMatchValue_Ele24Tau30_2=1;
              }
              if (filter.compare("hltDoubleL2IsoTau26eta2p2")==0) {
                  trigMatchValue_TauTau_2=1;
              }
              if (filter.compare("hltDoublePFTau35Reg")==0) {
                  trigMatchValue_TauTau2016_2=1;
              }

          }
      }
  }
 



 protected:

  edm::EDGetTokenT<std::vector<T> > src_;
  bool isEmbedded_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  StringObjectFunction<T>*function_pt_1;
  StringObjectFunction<T>*function_eta_1;
  StringObjectFunction<T>*function_phi_1;
  StringObjectFunction<T>*function_pt_2;
  StringObjectFunction<T>*function_eta_2;
  StringObjectFunction<T>*function_phi_2;

  int trigMatchValue_Mu24_1;
  int trigMatchValue_Mu27_1;
  int trigMatchValue_Mu20Tau27_2018_1;
  int trigMatchValue_Mu20Tau27_2017_1;
  int trigMatchValue_Mu19Tau20_2016_1;


  int trigMatchValue_Mu20Tau27_2;
  int trigMatchValue_Mu19Tau20_2;
  int trigMatchValue_Mu20HPSTau27_2;
  int trigMatchValue_Ele24Tau30_2;
  int trigMatchValue_TauTau_2;
  int trigMatchValue_TauTau2016_2;

  RooWorkspace *w;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef EmbeddedTriggerFilterMatcher<PATDiTauPair> PATDiTauPairEmbeddedTriggerFilterMatcher;
typedef EmbeddedTriggerFilterMatcher<PATMuTauPair> PATMuTauPairEmbeddedTriggerFilterMatcher;
typedef EmbeddedTriggerFilterMatcher<PATMuTauPair> PATMuPaircsvjetvarfiller;
typedef EmbeddedTriggerFilterMatcher<PATElecTauPair> PATEleTauPairEmbeddedTriggerFilterMatcher;
typedef EmbeddedTriggerFilterMatcher<PATMuPair> PATMuPairEmbeddedTriggerFilterMatcher;




