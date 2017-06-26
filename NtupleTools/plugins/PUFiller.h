// system include files
#include <memory>

// user include files

#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

#include "boost/filesystem.hpp"


//
// class decleration
//

class PUFiller : public NtupleFillerBase {
 public:
    PUFiller(){
    }


    PUFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
      src_(iC.consumes<std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("src"))),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = new float[6];
	  t->Branch((tag_+"BXminus").c_str(),&value[0],(tag_+"BXminus/F").c_str());
	  t->Branch((tag_+"Truth").c_str(),&value[1],(tag_+"Truth/F").c_str());
	  t->Branch((tag_+"BX0").c_str(),&value[2],(tag_+"BX0/F").c_str());
	  t->Branch((tag_+"BXplus").c_str(),&value[4],(tag_+"BXplus/F").c_str());
	  t->Branch((tag_+"weight").c_str(),&value[5],(tag_+"weight/F").c_str());
	  std::string base = std::getenv("CMSSW_BASE");
	  std::string fPUMCloc =   "/src/PUAnalysis/Configuration/data/MC_Moriond17_PU25ns_V1.root";
	  std::string fPUDATAloc = "/src/PUAnalysis/Configuration/data/Data_Pileup_2016_271036-284044_80bins.root";
	  std::string fPUMCname =   base+fPUMCloc;
	  std::string fPUDATAname = base+fPUDATAloc;
	  bool fPUMCis   = boost::filesystem::exists( fPUMCname   );
	  bool fPUDATAis = boost::filesystem::exists( fPUDATAname );
	  if (fPUMCis && fPUDATAis){
		  //edm::LumiReWeighting *LumiWeights;
		  LumiWeights = new edm::LumiReWeighting(fPUMCname,fPUDATAname,"pileup","pileup");
	  }

	}


    ~PUFiller()
    { 

    }


    void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
    {
	    edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;

	    if(iEvent.getByToken(src_, PupInfo)) {
		    std::vector<PileupSummaryInfo>::const_iterator PVI;
		    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
			    int BX = PVI->getBunchCrossing();
			    if(BX==-1) {
				    value[0] =  PVI->getPU_NumInteractions(); 
			    }
			    if(BX==0) {
				    value[2] =  PVI->getPU_NumInteractions(); 
				    value[1] =  PVI->getTrueNumInteractions(); 
			    }
			    if(BX==1) {
				    value[4] =  PVI->getPU_NumInteractions(); 
			    }
		    }
		    value[5] = LumiWeights->weight(value[1]);
	    }
	    else
	    {
		    printf("PU Info not found\n");
	    }



    }


 protected:
    edm::EDGetTokenT<std::vector<PileupSummaryInfo> > src_;
    edm::LumiReWeighting *LumiWeights;
    std::string tag_;
    float* value;

};






