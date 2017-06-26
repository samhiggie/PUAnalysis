// system include files
#include <memory>
#include <cmath>
// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>
#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//Trigger Files
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

//
// class decleration
//

class TriggerFilterFiller : public NtupleFillerBase {
 public:

  TriggerFilterFiller(){
  }

 TriggerFilterFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
  src_(iC.consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("src"))),
    BadChCandFilterToken_(iC.consumes<bool>(iConfig.getParameter<edm::InputTag>("BadChargedCandidateFilter"))),
    BadPFMuonFilterToken_(iC.consumes<bool>(iConfig.getParameter<edm::InputTag>("BadPFMuonFilter"))),
    paths_(iConfig.getParameter<std::vector<std::string> >("paths"))
      {
	fired    = std::vector<int>(paths_.size());
        any=1;


	for(unsigned int i=0;i<paths_.size();++i) {
	  fired[i]=0;

	  t->Branch((paths_[i]+"_fired").c_str(),&fired[i],(paths_[i]+"_fired/I").c_str());

	}
	t->Branch("BadMuonFilter",&any,"BadMuonFilter/I");

      }



  ~TriggerFilterFiller()
    { 

    }


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    using namespace std; 

    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<bool> ifilterbadChCand;
    edm::Handle<bool> ifilterbadPFMuon;

    //std::cout<<"filling the MET filter---------"<<std::endl;

    if(!iEvent.getByToken(src_, triggerBits))
      std::cout<<"ERROR GETTING THE TRIGGERBITS!!"<<std::endl;

    if(!iEvent.getByToken(BadChCandFilterToken_, ifilterbadChCand))
      std::cout<<"ERROR GETTING THE CHARGED HADRON FILTER TOKEN!!"<<std::endl;

    if(!iEvent.getByToken(BadPFMuonFilterToken_, ifilterbadPFMuon))
      std::cout<<"ERROR GETTING THE PF MUON FILTER TOKEN!!"<<std::endl;

    //std::cout<<"bad pf muon filter "<<ifilterbadPFMuon<<std::endl;
    //std::cout<<"bad ch hadron filter "<<ifilterbadChCand<<std::endl;

    bool filterbadChCandidate = *ifilterbadChCand;
    bool filterbadPFMuon = *ifilterbadPFMuon;

    //std::cout<<"filter bad 1: " << filterbadChCandidate<<std::endl;
    //std::cout<<"filter bad 2: " << filterbadPFMuon<<std::endl;

    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
    any=filterbadChCandidate + filterbadPFMuon;
    //std::cout<<"filterBadAny "<<any<<std::endl;

    //get the names of the triggers
    for(unsigned int i=0;i<paths_.size();++i) {
      bool found=false;
      bool fired_t=false;
      //std::cout<<"Find a Trigger Path: "<<paths_[i]<<std::endl;
      for(unsigned int j=0 ,  n = triggerBits->size(); j < n && fired_t == false; ++j) {
	size_t trigPath = names.triggerName(j).find(paths_.at(i));
	if ( trigPath == 0) {
	  //std::cout<<"Found a Trigger Name!: "<<names.triggerName(j)<<std::endl;
	  found=true;
	  fired[i]=triggerBits->accept(j); 
	  if(triggerBits->accept(j) ){
	    fired_t=true;
	    //std::cout<<"Found a Trigger Name"<<names.triggerName(j)<<"! FIRED"<<std::endl;
	  }
	  break;
	}
      }
      if(!found) {
	fired[i]=0;
	//std::cout<<"Did not find a Trigger Filter!"<<std::endl;
      }
    }//end path 



  }


 protected:
  edm::EDGetTokenT<edm::TriggerResults> src_;
  edm::EDGetTokenT<bool> BadChCandFilterToken_;
  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;


  std::vector<std::string> paths_;

  std::vector<int> fired;
  int any;
};
