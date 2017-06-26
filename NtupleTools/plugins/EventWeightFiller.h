// system include files
#include <memory>

// user include files

#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "boost/filesystem.hpp"

//
// class decleration
//

template<typename T>
class EventWeightFiller : public NtupleFillerBase {
	public:
		EventWeightFiller(){
		}


		EventWeightFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC ):
			src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))), 
			tag_(iConfig.getParameter<std::string>("tag")),
			isMu_(iConfig.getParameter<bool>("isMuon"))
	{
		value = new float[3];
		t->Branch("idisoweight_1",&value[0],"idisoweight_1/F");
		t->Branch("trigweight_1",&value[1],"trigweight_1/F");
		t->Branch((tag_+"EffWeight").c_str(),&value[2],(tag_+"EffWeight/F").c_str());
		std::string base = std::getenv("CMSSW_BASE");
		std::string fMuonIsolation =   "/src/HTT-utilities/LepEffInterface/data/Muon/Run2016BCD/Muon_IdIso0p15_eff.root";
		std::string fMuonTrigger =   "/src/HTT-utilities/LepEffInterface/data/Muon/Run2016BCD/Muon_IsoMu22_OR_TkIsoMu22_eff.root";
		std::string fEleIsolation =   "/src/HTT-utilities/LepEffInterface/data/Electron/Run2016BCD/Electron_IdIso0p10_eff.root";
		std::string fEleTrigger =   "/src/HTT-utilities/LepEffInterface/data/Electron/Run2016BCD/Electron_Ele25eta2p1WPTight_eff.root";
		std::string fileIso;
		std::string fileTrig;
		if (isMu_) {
			fileIso= base+fMuonIsolation;
			fileTrig= base+fMuonTrigger;
			bool fis   = boost::filesystem::exists( fileTrig   ) && boost::filesystem::exists( fileIso ) ;
			std::cout<<"file exist: "<<fis<<std::endl;
		}
		else {
			fileIso= base+fEleIsolation;
			fileTrig= base+fEleTrigger;
			bool fis   = boost::filesystem::exists( fileTrig   ) && boost::filesystem::exists( fileIso ) ;
			std::cout<<"file exist: "<<fis<<std::endl;

		}

	}


		~EventWeightFiller()
		{ 
		}

		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			float pt = 0;
			float eta = 0;

			//function_pt = new StringObjectFunction<T>("leg1.pt");
			//function_eta = new StringObjectFunction<T>("leg1.eta");
			edm::Handle<std::vector<T>> handle;
			if( iEvent.getByToken(src_,handle)){
				pt = handle->at(0).leg1()->pt();
				eta = handle->at(0).leg1()->eta();
			}


		}


	protected:
		edm::EDGetTokenT<std::vector<T> > src_;
		std::string tag_;
		bool isMu_;
		float* value;


};




#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef EventWeightFiller<PATMuTauPair> PATMuTauPairWeightFiller;
typedef EventWeightFiller<PATElecTauPair> PATEleTauPairWeightFiller;



