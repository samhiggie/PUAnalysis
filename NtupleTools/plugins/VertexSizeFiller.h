
// system include files
#include <memory>

// user include files
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include <TTree.h>
#include "FWCore/Framework/interface/EDConsumerBase.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//

class VertexSizeFiller : public NtupleFillerBase {
 public:
    VertexSizeFiller(){
    }


    VertexSizeFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      src_(iC.consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("src"))),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
	}


  ~VertexSizeFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<reco::VertexCollection > handle;
    value=0;
    if(iEvent.getByToken(src_,handle)) {
      value = handle->size();
    }
  }
  

 protected:
  edm::EDGetTokenT<reco::VertexCollection> src_;
  std::string tag_;
  int value;


};






