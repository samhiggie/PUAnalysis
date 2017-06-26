// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

//
// class decleration
//
template<typename T>
class JetCountFiller : public NtupleFillerBase {
 public:
    JetCountFiller(){
    }

    JetCountFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      var_(iConfig.getParameter<std::string>("method")),
      tag_(iConfig.getParameter<std::string>("tag")),
      leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
	{
	  value = new std::vector<int>();
	  singleValue=0;
	  function = new StringCutObjectSelector<pat::Jet>(var_,true);
	  if(!leadingOnly_)
	    vbranch = t->Branch(tag_.c_str(),"std::vector<int>",&value);
	  else
	    vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/I").c_str());

	}


  ~JetCountFiller()
    { 
      if(function!=0) delete function;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup &iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    singleValue=0;
    
    if(value->size()>0)
            value->clear();
    
    if(iEvent.getByToken(src_,handle)) {


      if(leadingOnly_)
	{
	  if(handle->size()>0) {
	    singleValue=0;
	    for(unsigned int i=0;i<handle->at(0).jets().size();++i)
	      if((*function)(*(handle->at(0).jets().at(i))))
		singleValue++;
	  }
	}
      else {
	  if(handle->size()>0)
	    for(unsigned int j=0;j<handle->size();++j) {
	      singleValue=0;
	      for(unsigned int i=0;i<handle->at(j).jets().size();++i)
		if((*function)(*(handle->at(j).jets().at(i))))
		  singleValue ++;
	      value->push_back(singleValue);
	    }    
      }


    }
  }
  

 protected:
  edm::EDGetTokenT<std::vector<T> > src_;
  std::string var_;
  std::string tag_;
  bool leadingOnly_;
  std::vector<int>* value;
  int singleValue;
  StringCutObjectSelector<pat::Jet>*function;
  TBranch *vbranch;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef JetCountFiller<PATMuTauPair> PATMuTauPairJetCountFiller;
typedef JetCountFiller<PATElecTauPair> PATEleTauPairJetCountFiller;
typedef JetCountFiller<PATDiTauPair> PATDiTauPairJetCountFiller;
typedef JetCountFiller<PATMuMuTauTauQuad> PATMuMuTauTauQuadJetCountFiller;



