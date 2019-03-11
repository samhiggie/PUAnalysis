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

/*
 * Get the SF for Embedded samples
 * Author: Isobel Ojalvo (last mod July 2014)
 */

template<typename T>
class ZWeightFiller : public NtupleFillerBase {
 public:
    ZWeightFiller(){}

    TFile* theFile;
    
    ZWeightFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      tag_(iConfig.getParameter<std::string>("tag")),
      massZ_(iConfig.getParameter<std::string>("massZ")),
      ptZ_(iConfig.getParameter<std::string>("ptZ"))
	{
	  weightValue=1.;
	  weightBranch = t->Branch(tag_.c_str(),&weightValue,(tag_+"/F").c_str());

	  function_massZ  = new StringObjectFunction<T>(massZ_);
	  function_ptZ  = new StringObjectFunction<T>(ptZ_);

	  std::string cmssw = std::getenv("CMSSW_BASE");
	  std::string filename = cmssw+"/src/PUAnalysis/Configuration/data/htt_scalefactors_2017_v2.root";
	  theFile = new TFile(filename.c_str());
	  w = (RooWorkspace*)theFile->Get("w");
	  theFile->Close();
	}


  ~ZWeightFiller()
    { 
      if(function_massZ!=0)  delete function_massZ;
      if(function_ptZ!=0)  delete function_ptZ;

    }
       


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    weightValue=1;

    if(iEvent.getByToken(src_,handle)) {
      if(handle->size()>0){

	//std::cout<<"pt: "<<pt<<" eta: "<<eta<<" dm: "<<dm<<std::endl;
	if(isEmbedded_){

	  double massZ  = (*function_massZ)(handle->at(0));
	  double ptZ    = (*function_ptZ)(handle->at(0));
	  
	  w->var("z_gen_mass")->setVal(massZ);
	  w->var("z_gen_pt")->setVal(ptZ);
	  
	  weightValue = w->function("zptmass_weight_nom")->getVal();

	}
      }
    }
  }



 protected:

  edm::EDGetTokenT<std::vector<T> > src_;
  bool isEmbedded_;
  std::string tag_;
  std::string massZ_;
  std::string ptZ_;

  StringObjectFunction<T>*function_massZ;
  StringObjectFunction<T>*function_ptZ;
  float weightValue;
  TBranch *weightBranch;
  RooWorkspace *w;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef ZWeightFiller<PATDiTauPair> PATDiTauPairZWeightFiller;
typedef ZWeightFiller<PATMuTauPair> PATMuTauPairZWeightFiller;
typedef ZWeightFiller<PATMuTauPair> PATMuPaircsvjetvarfiller;
typedef ZWeightFiller<PATElecTauPair> PATEleTauPairZWeightFiller;
typedef ZWeightFiller<PATMuPair> PATMuPairZWeightFiller;




