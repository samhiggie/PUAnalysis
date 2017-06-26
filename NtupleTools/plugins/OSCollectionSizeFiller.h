// system include files
#include <memory>

// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//

class OSCollectionSizeFiller : public NtupleFillerBase {
 public:
    OSCollectionSizeFiller(){
    }


    OSCollectionSizeFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
      src_(iC.consumes<edm::View<reco::Candidate> >(iConfig.getParameter<edm::InputTag>("src"))),
      size_(iConfig.getUntrackedParameter<double>("size",0.)),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
	}


  ~OSCollectionSizeFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<edm::View<reco::Candidate> > handle;
    value=0; //initially false
    if(iEvent.getByToken(src_,handle)) {
      int charge = handle->at(0).charge();
      if (charge==size_)
	value=1;//set to one if size is expected
    }
  }
  

 protected:
  edm::EDGetTokenT<edm::View<reco::Candidate>> src_;
  double size_;
  std::string tag_;
  int value;


};






