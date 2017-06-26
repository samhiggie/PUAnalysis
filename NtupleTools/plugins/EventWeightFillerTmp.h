// system include files
#include <memory>

// user include files

#include <TTree.h>
#include "TH2D.h"
#include <TFile.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "boost/filesystem.hpp"
#include "PUAnalysis/NtupleTools/plugins/HTTTnP.C"

//
// class decleration
//

template<typename T>
class EventWeightFillerTmp : public NtupleFillerBase {
	public:
		EventWeightFillerTmp(){
		}


		EventWeightFillerTmp(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC ):
			src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))), 
			tag_(iConfig.getParameter<std::string>("tag")),
			isMu_(iConfig.getParameter<bool>("isMuon"))
	{
		value = new float[3];
		t->Branch("myisoweight_1",&value[0],"myisoweight_1/F");
		t->Branch("mytrigweight_1",&value[1],"mytrigweight_1/F");
		t->Branch((tag_+"EffWeight").c_str(),&value[2],(tag_+"EffWeight/F").c_str());
		std::string base = std::getenv("CMSSW_BASE");
		std::string fMuonTrigger =   "/src/PUAnalysis/Configuration/data/IsoMuSoup.root";
		std::string fEleTrigger =   "/src/PUAnalysis/Configuration/data/2016_EleSoup.root";
		//std::string fEleTrigger =   "/src/PUAnalysis/Configuration/data/EleSoup.root";
		std::string fileTrig;
		if (isMu_) {
			fileTrig= base+fMuonTrigger;
		}
		else {
			fileTrig= base+fEleTrigger;
		}

		bool fis   = boost::filesystem::exists( fileTrig   );
		if (fis ){
			std::cout<<"INFO::EffiTmpFiller using efficiency map"<<std::endl;
			f_EffMap = new TFile(fileTrig.c_str(),"READONLY");
			//h2_Eff    = (TH2D*)f_EffMap->Get("probe_abseta_probe_pt_PLOT");
			h2_Eff    = (TH2D*)f_EffMap->Get("abseta_pt_PLOT");
			if (!isMu_) h2_Eff    = (TH2D*)f_EffMap->Get("probe_sc_abseta_probe_sc_pt_PLOT");
		}
		else{
			std::cout<<"INFO::EffiTmpFiller NOT using efficiency map"<<std::endl;
		}



	}


		~EventWeightFillerTmp()
		{ 
		}

		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			float pt = 0;
			float eta = 0;

			edm::Handle<std::vector<T>> handle;
			if( iEvent.getByToken(src_,handle)){
				pt = handle->at(0).leg1()->pt();
				eta = std::abs(handle->at(0).leg1()->eta());
			}

			if (pt>200.) pt=201.;
			//printf("pt: %0.2f eta: %0.2f \n", p, abseta);

			double scaleFactorIso = weightMuTau(pt,eta); 
			if (!isMu_)  scaleFactorIso = weightETau(pt,eta); 
			double scaleFactorTrig = h2_Eff->GetBinContent(h2_Eff->GetXaxis()->FindBin(eta),h2_Eff->GetYaxis()->FindBin(pt));

			value[0]=scaleFactorIso;
			value[1]=scaleFactorTrig;
			value[2]=(scaleFactorTrig*scaleFactorIso);
		}


	protected:
		edm::EDGetTokenT<std::vector<T> > src_;
		std::string tag_;
		bool isMu_;
		TFile *f_EffMap;
		TH2D *h2_Eff;
		float* value;

		float weightMuTau(float pt1,float eta1) {
			return mHTTID(pt1,eta1)*mHTTISO(pt1,eta1);

		}



		float weightETau(float pt1,float eta1) {
			return eHTTID(pt1,eta1)*eHTTISO(pt1,eta1);
		}


};




#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef EventWeightFillerTmp<PATMuTauPair> PATMuTauPairWeightFillerTmp;
typedef EventWeightFillerTmp<PATElecTauPair> PATEleTauPairWeightFillerTmp;



