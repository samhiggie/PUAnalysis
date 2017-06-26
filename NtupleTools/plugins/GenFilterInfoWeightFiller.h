// system include files
#include <memory>

// user include files
#include <TTree.h>
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//

class GenFilterInfoWeightFiller : public NtupleFillerBase {
  public:
    GenFilterInfoWeightFiller(){
    }


    GenFilterInfoWeightFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      src_(iC.consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("src"))),
      tag_(iConfig.getParameter<std::string>("tag"))
  {
    value = 0;
    t->Branch(tag_.c_str(),&value,(tag_+"/F").c_str());
  }


    ~GenFilterInfoWeightFiller()
    {

    }


    void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
    {
      //edm::Handle<GenFilterInfo> handle;
      edm::Handle<GenEventInfoProduct> genEvt;
      value=0;
      if(iEvent.getByToken(src_,genEvt)) {
        //value = handle->filterEfficiency();
        value = genEvt->weight();
      }
    }


  protected:
    edm::EDGetTokenT<GenEventInfoProduct> src_;
    std::string tag_;
    float value;


};


