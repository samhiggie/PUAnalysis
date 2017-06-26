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

//
// class declaration
//
template<typename T>
class PtJetVarFiller : public NtupleFillerBase {
 public:
    PtJetVarFiller(){
    }


    PtJetVarFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T>>(iConfig.getParameter<edm::InputTag>("src"))),
      var_(iConfig.getParameter<std::string>("method")),
      tag_(iConfig.getParameter<std::string>("tag")),
      cut_(iConfig.getParameter<std::string>("cut")),
      rank_(iConfig.getUntrackedParameter<double>("rank",1.))
	{

	  singleValue=-999.;
	  function = new StringObjectFunction<pat::Jet>(var_);
	  cut = new StringCutObjectSelector<pat::Jet>(cut_,true);
	  vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());
	}


  ~PtJetVarFiller()
    { 
      if(function!=0) delete function;
      if(cut!=0) delete cut;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    singleValue=-999;

    if(iEvent.getByToken(src_,handle)) {
      if(handle->size()>0){
	if(handle->at(0).jets().size()>rank_){
	  //printf("nJets: %i\n",(int)handle->at(0).jets().size());
	  //printf("%i th pt: %f\n",(int)rank_,handle->at(0).jets().at((int)rank_)->pt());
	  //printf("%i th eta: %f\n",(int)rank_,handle->at(0).jets().at((int)rank_)->eta());
	  //printf("%i th phi: %f\n",(int)rank_,handle->at(0).jets().at((int)rank_)->phi());
	  if((*cut)(*(handle->at(0).jets().at((int) rank_ ))))
	    singleValue = (*function)(*(handle->at(0).jets().at((int) rank_)));
	  //else printf("Jet Failed Cut Selection\n");
	}
      }
    }
  }

 protected:
  edm::EDGetTokenT<std::vector<T>>  src_;
  std::string var_;
  std::string tag_;
  std::string cut_;
  float rank_;
  float singleValue;
  StringObjectFunction<pat::Jet>*function;
  StringCutObjectSelector<pat::Jet>*cut;
  TBranch *vbranch;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef PtJetVarFiller<PATMuTauPair> PATMuTauPairPtJetVarFiller;
typedef PtJetVarFiller<PATElecTauPair> PATEleTauPairPtJetVarFiller;
typedef PtJetVarFiller<PATDiTauPair> PATDiTauPairPtJetVarFiller;





