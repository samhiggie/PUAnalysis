// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "DataFormats/Math/interface/Error.h"
#include <TTree.h>
#include <math.h>
#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "DataFormats/PatCandidates/interface/MET.h"

//
// class declaration
//


class METSignificanceFiller : public NtupleFillerBase {
 public:
    METSignificanceFiller(){
    }


    METSignificanceFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      sig_(iC.consumes<double>(edm::InputTag("METSignificance:METSignificance"))),
      cov_(iC.consumes<math::Error<2>::type>(edm::InputTag("METSignificance:METCovariance"))),
      met_(iC.consumes<edm::View<pat::MET>>(edm::InputTag("slimmedMETs"))),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = new float[7];
	  t->Branch((tag_+"Sig").c_str(),&value[0],(tag_+"Sig/F").c_str());
	  t->Branch((tag_+"00").c_str(),&value[1],(tag_+"00/F").c_str());
	  t->Branch((tag_+"01").c_str(),&value[2],(tag_+"01/F").c_str());
	  t->Branch((tag_+"10").c_str(),&value[3],(tag_+"10/F").c_str());
	  t->Branch((tag_+"11").c_str(),&value[4],(tag_+"11/F").c_str());
	  t->Branch("met",&value[5],"met/F");
	  t->Branch("metphi",&value[6],"metphi/F");
	}


  ~METSignificanceFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<double> significanceHandle;
    edm::Handle<math::Error<2>::type> covHandle;
    edm::Handle<edm::View<pat::MET>> metHandle;

    if(iEvent.getByToken(sig_, significanceHandle)) {
	  value[0] = (float) (*significanceHandle); 
	}
    else
      {
	  //std::cout<<"METSignificance Not Found"<<std::endl;
          value[0] = -999;	
      }

    if (iEvent.getByToken(cov_,covHandle)) {
        value[1] = (*covHandle)(0,0);
        value[3] = (*covHandle)(1,0);
        value[2] = value[3]; // (1,0) is the only one saved
        value[4] = (*covHandle)(1,1);
    }
    else{ 
	//std::cout<<"METcovariance Not Found"<<std::endl;
	for (int i=1;i<5;i++) value[i] = -999;
    }

    if (iEvent.getByToken(met_,metHandle)) {
	const pat::MET *pfMET = 0;
	pfMET = &(metHandle->front());
        value[5] = pfMET->pt();
        value[6] = pfMET->phi();
    }
    else{
        std::cout<<"slimmedMETs not found for ntuple"<<std::endl;
        value [5]= -999;
        value [6]= -999;
    }
  }

 private:
  edm::EDGetTokenT<double> sig_;
  edm::EDGetTokenT<math::Error<2>::type> cov_;
  edm::EDGetTokenT<edm::View<pat::MET>> met_;
  std::string tag_;
  float* value;

};






