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
class EmbeddedSFFiller : public NtupleFillerBase {
 public:
    EmbeddedSFFiller(){}

    TFile* theFile;
    
    EmbeddedSFFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      isEmbedded_(iConfig.getParameter<bool>("isEmbedded")),
      tag_(iConfig.getParameter<std::string>("tag")),
      pt1_(iConfig.getParameter<std::string>("pt1")),
      eta1_(iConfig.getParameter<std::string>("eta1")),
      pt2_( iConfig.getParameter<std::string>("pt2")),
      eta2_(iConfig.getParameter<std::string>("eta2"))
	{
	  triggerValue=1.;
	  trigBranch = t->Branch(tag_.c_str(),&triggerValue,(tag_+"/F").c_str());
	  idBranch_1 = t->Branch("emb_id_SF_1",&idValue_1,"emb_id_SF_1/F");
	  idBranch_2 = t->Branch("emb_id_SF_2",&idValue_2,"emb_id_SF_2/F");

	  function_pt1  = new StringObjectFunction<T>(pt1_);
	  function_eta1 = new StringObjectFunction<T>(eta1_);
	  function_pt2  = new StringObjectFunction<T>(pt2_);
	  function_eta2 = new StringObjectFunction<T>(eta2_);

	  std::string cmssw = std::getenv("CMSSW_BASE");
	  std::string filename = cmssw+"/src/PUAnalysis/Configuration/data/htt_scalefactors_v17_5.root";
	  theFile = new TFile(filename.c_str());
	  w = (RooWorkspace*)theFile->Get("w");
	  theFile->Close();
	}


  ~EmbeddedSFFiller()
    { 
      if(function_pt1!=0)  delete function_pt1;
      if(function_eta1!=0) delete function_eta1;
      if(function_pt2!=0)  delete function_pt2;
      if(function_eta2!=0) delete function_eta2;

    }
       


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    triggerValue=1;
    idValue_1 = 1;
    idValue_2 = 1;

    triggerWeight = 1;

    if(iEvent.getByToken(src_,handle)) {
      if(handle->size()>0){

	//std::cout<<"pt: "<<pt<<" eta: "<<eta<<" dm: "<<dm<<std::endl;
	if(isEmbedded_){

	  double pt1  = (*function_pt1)(handle->at(0));
	  double eta1 = (*function_eta1)(handle->at(0));
	  double pt2  = (*function_pt2)(handle->at(0));
	  double eta2 = (*function_eta2)(handle->at(0));
	  
	  w->var("gt1_pt")->setVal(pt1);
	  w->var("gt1_eta")->setVal(eta1);
	  w->var("gt2_pt")->setVal(pt2);
	  w->var("gt2_eta")->setVal(eta2);
	  
	  //get gen pt of 
	  double embedded_SF = 1;//default to do no harm
	  embedded_SF = w->function("m_sel_trg_ratio")->getVal();
	  triggerValue = embedded_SF;

	  idValue_1 = w->function("m_sel_idEmb_ratio")->getVal();

	  w->var("gt1_pt")->setVal(pt2);
	  w->var("gt1_eta")->setVal(eta2);
	  idValue_2 = w->function("m_sel_idEmb_ratio")->getVal();
	  
	  //now the tau trigger weights which should NOT be needed in the next iteration
	  float trigWeight1 = getTriggerWeight(pt1);
	  float trigWeight2 = getTriggerWeight(pt2);
	  triggerWeight = trigWeight1*trigWeight2; 
	  //triggerWeight = getTriggerWeight(pt1) * getTriggerWeight(pt2);

	}
      }
    }
  }

  float getTriggerWeight(double pt){
    float value = (0.18321*(pt>=30 && pt<35) + 0.53906*(pt>=35 && pt<40) + 0.63658*(pt>=40 && pt<45) + 0.73152*(pt>=45 && pt<50) + 0.79002*(pt>=50 && pt<60) + 0.84666*(pt>=60 && pt<80) + 0.84919*(pt>=80 && pt<100) + 0.86819*(pt>=100 && pt<150) + 0.88206*(pt>=150 && pt<200) + (pt>=200));
    return value;
  }


 protected:

  edm::EDGetTokenT<std::vector<T> > src_;
  bool isEmbedded_;
  std::string tag_;
  std::string pt1_;
  std::string eta1_;
  std::string pt2_;
  std::string eta2_;

  StringObjectFunction<T>*function_pt1;
  StringObjectFunction<T>*function_eta1;
  StringObjectFunction<T>*function_pt2;
  StringObjectFunction<T>*function_eta2;
  float triggerValue;
  float idValue_1;
  float idValue_2;
  float triggerWeight;
  TBranch *trigBranch;
  TBranch *idBranch_1;
  TBranch *idBranch_2;
  RooWorkspace *w;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef EmbeddedSFFiller<PATDiTauPair> PATDiTauPairEmbeddedSFFiller;
typedef EmbeddedSFFiller<PATMuTauPair> PATMuTauPairEmbeddedSFFiller;
typedef EmbeddedSFFiller<PATMuTauPair> PATMuPaircsvjetvarfiller;
typedef EmbeddedSFFiller<PATElecTauPair> PATEleTauPairEmbeddedSFFiller;
typedef EmbeddedSFFiller<PATMuPair> PATMuPairEmbeddedSFFiller;




