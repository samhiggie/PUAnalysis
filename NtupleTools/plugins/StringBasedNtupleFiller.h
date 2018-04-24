// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//
template<typename T>
class StringBasedNtupleFiller : public NtupleFillerBase {
 public:
    StringBasedNtupleFiller(){
    }


    StringBasedNtupleFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      var_(iConfig.getParameter<std::string>("method")),
      tag_(iConfig.getParameter<std::string>("tag")),
      leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
	{
	  value = new std::vector<double>();
	  singleValue=0.;
	  function = new StringObjectFunction<T>(var_);
	  if(!leadingOnly_)
	    vbranch = t->Branch(tag_.c_str(),"std::vector<double>",&value);
	  else
	    vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());

	}


  ~StringBasedNtupleFiller()
    { 
      if(function!=0) delete function;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    singleValue=-1;
    
    if(value->size()>0)
            value->clear();
    
    if(iEvent.getByToken(src_,handle)) {


      if(leadingOnly_)
	{
	  if(handle->size()>0)
	    singleValue = (*function)(handle->at(0));
	}
      else
	for(unsigned int i=0;i<handle->size();++i) {
	  value->push_back((*function)(handle->at(i)));
	}    


    }
    else
      {
	//printf("StringBasedNtupleFiller: Obj not found \n");
      }
    //    vbranch->Fill();
  }
  

 protected:
  edm::EDGetTokenT<std::vector<T> > src_;
  std::string var_;
  std::string tag_;
  bool leadingOnly_;
  std::vector<double>* value;
  float singleValue;
  StringObjectFunction<T>*function;
  TBranch *vbranch;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMET.h"
typedef StringBasedNtupleFiller<reco::GenParticle> PATGenParticleFiller;
typedef StringBasedNtupleFiller<PATMuTauPair> PATMuTauPairFiller;
typedef StringBasedNtupleFiller<PATDiTauPair> PATDiTauPairFiller;
typedef StringBasedNtupleFiller<PATElecTauPair> PATEleTauPairFiller;
typedef StringBasedNtupleFiller<pat::Muon> PATMuonFiller;
typedef StringBasedNtupleFiller<PATElecPair> PATElePairFiller;
typedef StringBasedNtupleFiller<reco::MET> PATMETFiller;
typedef StringBasedNtupleFiller<reco::PFMET> PATPFMETFiller;
typedef StringBasedNtupleFiller<reco::GenMET> PATGenMETFiller;
typedef StringBasedNtupleFiller<PATMuMuTauTauQuad> PATMuMuTauTauQuadFiller;
typedef StringBasedNtupleFiller<PATMuPair> PATMuPairFiller;
