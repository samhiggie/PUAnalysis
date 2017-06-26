// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//
template<typename T>
class HighestPtJetVarFiller : public NtupleFillerBase {
 public:
    HighestPtJetVarFiller(){
    }


    HighestPtJetVarFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T>>(iConfig.getParameter<edm::InputTag>("src"))),
      var_(iConfig.getParameter<std::string>("method")),
      tag_(iConfig.getParameter<std::string>("tag"))
	{

	  singleValue=0.;
	  function = new StringObjectFunction<pat::Jet>(var_);
	  vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());

	}


  ~HighestPtJetVarFiller()
    { 
      if(function!=0) delete function;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    singleValue=-1;
    float minPt=0.0;

    if(iEvent.getByToken(src_,handle)) {
	  if(handle->size()>0)
	    for(unsigned int i=0;i<handle->at(0).jets().size();++i)
	      if(handle->at(0).jets().at(i)->pt()>minPt) {
		minPt = handle->at(0).jets().at(i)->pt();
		singleValue = (*function)(*(handle->at(0).jets().at(i)));
	      }
    }
    else
      {
	printf("HighestPtJetVarFiller: Obj not found \n");
      }
  }
  

 protected:
  edm::EDGetTokenT<std::vector<T>> src_;
  std::string var_;
  std::string tag_;
  float singleValue;
  StringObjectFunction<pat::Jet>*function;
  TBranch *vbranch;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef HighestPtJetVarFiller<PATMuTauPair> PATMuTauPairHighestPtJetVarFiller;
//typedef HighestPtJetVarFiller<PATMuJetPair> PATMuJetPairHighestPtJetVarFiller;
//typedef HighestPtJetVarFiller<PATMuPair> PATMuPairHighestPtJetVarFiller;
typedef HighestPtJetVarFiller<PATElecTauPair> PATEleTauPairHighestPtJetVarFiller;
//typedef HighestPtJetVarFiller<PATElecMuPair> PATEleMuPairHighestPtJetVarFiller;
typedef HighestPtJetVarFiller<PATDiTauPair> PATDiTauPairHighestPtJetVarFiller;





