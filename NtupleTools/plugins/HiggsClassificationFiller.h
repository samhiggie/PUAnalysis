#include <memory>
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>
#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "SimDataFormats/HTXS/interface/HiggsTemplateCrossSections.h"

//This class inherits from NtupleFillerBase
class HiggsClassificationFiller : public NtupleFillerBase {

  public:
   
    HiggsClassificationFiller() {}

    HiggsClassificationFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC)
      {
      src_ = iC.consumes<HTXS::HiggsClassification>(edm::InputTag("rivetProducerHTXS","HiggsClassification"));
      hProdMode = -1;
      t->Branch("HiggsClassification_prodMode", &hProdMode, "HiggsClassification_prodMode/I");
      t->Branch("HiggsClassification_stage0Cat", &stage0Cat, "HiggsClassification_stage0Cat/I");
      t->Branch("HiggsClassification_stage1p1Cat", &stage1p1Cat, "HiggsClassification_stage1p1Cat/I");
      t->Branch("HiggsClassification_errorCode", &error, "HiggsClassification_errorCode/I");
    }

    ~HiggsClassificationFiller() {}
      
    void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
      edm::Handle<HTXS::HiggsClassification> htxs;
      iEvent.getByToken(src_,htxs);
      HTXS::HiggsClassification htxsRivetInfo;
      if (htxs.isValid()) {
        htxsRivetInfo = * htxs;
        hProdMode = htxsRivetInfo.prodMode;
        stage0Cat = htxsRivetInfo.stage0_cat;
        stage1p1Cat = htxsRivetInfo.stage1p1_cat;
        error = htxsRivetInfo.errorCode;
      }
    }
    
  protected:
    edm::EDGetTokenT<HTXS::HiggsClassification> src_;
    std::string tag_;
    int hProdMode;
    HTXS::Stage0::Category stage0Cat;
    HTXS::Stage1::Category stage1Cat_JetPt25;
    HTXS::Stage1::Category stage1Cat_JetPt30;
    HTXS::Stage1p1::Category stage1p1Cat;
    HTXS::ErrorCode error;
};
