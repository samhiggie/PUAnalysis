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

/*
 * Sort jets by CSV value and return the requested Rank'ed jet
 * Author: Isobel Ojalvo (last mod July 2014)
 */

template<typename T>
class CSVJetVarFiller : public NtupleFillerBase {
 public:
    CSVJetVarFiller(){}

    CSVJetVarFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      NtupleFillerBase(iConfig,t,iC),
      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
      var_(iConfig.getParameter<std::string>("method")),
      tag_(iConfig.getParameter<std::string>("tag")),
      cut_(iConfig.getParameter<std::string>("cut")),
      rank_(iConfig.getUntrackedParameter<double>("rank",1.))
	{
	  singleValue=0.;
	  function = new StringObjectFunction<pat::Jet>(var_);
	  cut = new StringCutObjectSelector<pat::Jet>(cut_,true);
	  vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());
	}


  ~CSVJetVarFiller()
    { 
      if(function!=0) delete function;
      if(cut!=0) delete cut;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;

    singleValue=-1;

    if(iEvent.getByToken(src_,handle)) {
      singleValue = 0;

      if(handle->size()>0){
	if( handle->at(0).jets().size() > rank_){
	  std::vector<edm::Ptr<pat::Jet> > cleanedJetsCSVsorted ;
	  cleanedJetsCSVsorted.reserve((int)handle->at(0).jets().size());
	  
	  for( int i=0; i<(int)handle->at(0).jets().size(); i++)
	    if((*cut)(*(handle->at(0).jets().at(i))))
	      cleanedJetsCSVsorted.push_back( handle->at(0).jets().at(i) );
	  
	  sortRefVectorByCSV(cleanedJetsCSVsorted);
	  
	  /* Previous Bug was here! Wasn't grabbing info from the sorted object!!*/
	  
	  if(cleanedJetsCSVsorted.size() > rank_){
	    singleValue = (*function)(*(cleanedJetsCSVsorted.at((int) rank_)));
	  }
	}
      }
    }
  }

  void sortRefVectorByCSV(std::vector<edm::Ptr<pat::Jet> >& vec)
  {
    std::vector<size_t> indices;
    indices.reserve(vec.size());

    for(unsigned int i=0;i<vec.size();++i)
      indices.push_back(i);
    
    refVectorCSVSorter sorter(vec);
    std::sort(indices.begin(),indices.end(),sorter);
        
    std::vector<edm::Ptr<pat::Jet> > sorted;
    sorted.reserve(vec.size());
    
    for(unsigned int i=0;i<indices.size();++i)
      sorted.push_back(vec.at(indices.at(i)));

    /*for(int i = 0; i<sorted.size(); ++i)
      printf("%i th pt: %f CSV: %f\n", i , sorted.at(i)->pt(),
	     sorted.at(i)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")); */

      vec = sorted;

  }

  //bool csvsort(){}

  class refVectorCSVSorter {

  public:
    refVectorCSVSorter(const std::vector<edm::Ptr<pat::Jet> > vec)
      {
	vec_ = vec;
      }
    refVectorCSVSorter()
      {
      }
    ~refVectorCSVSorter()
      {}

    bool operator()(size_t a , size_t b) {
      return (vec_.at(a)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags") > vec_.at(b)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    }

  private:
    std::vector<edm::Ptr<pat::Jet> > vec_;
  
  };

 protected:
  edm::EDGetTokenT<std::vector<T> > src_;
  std::string var_;
  std::string tag_;
  std::string cut_;
  float rank_;
  float singleValue;
  StringCutObjectSelector<pat::Jet>*cut;
  StringObjectFunction<pat::Jet>*function;
  TBranch *vbranch;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef CSVJetVarFiller<PATDiTauPair> PATDiTauPairCSVJetVarFiller;
typedef CSVJetVarFiller<PATMuTauPair> PATMuTauPairCSVJetVarFiller;
typedef CSVJetVarFiller<PATMuTauPair> PATMuPaircsvjetvarfiller;
typedef CSVJetVarFiller<PATElecTauPair> PATEleTauPairCSVJetVarFiller;
typedef CSVJetVarFiller<PATMuPair> PATMuPairCSVJetVarFiller;




