// system include files
#include <memory>
// user include files

#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include "TH1.h"
#include "TRandom3.h"

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "boost/filesystem.hpp"

//
// class decleration
//

template<typename T>
class POGSFsFiller : public NtupleFillerBase {
	public:
		POGSFsFiller(){
		}


		POGSFsFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC ):
			src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))), 
			Mu_(iConfig.getParameter<bool>("isMu"))
	{
		value = new float[9]; 
		t->Branch("POGtrigger",&value[0],"POGtrigger/F");
		t->Branch("POGtriggerErr",&value[1],"POGtriggerErr/F");
		t->Branch("POGid1",&value[2],"POGid1/F");
		t->Branch("POGid1Err",&value[3],"POGid1Err/F");
		t->Branch("POGid2",&value[4],"POGid2/F");
		t->Branch("POGid2Err",&value[5],"POGid2Err/F");
		t->Branch("POGtrack",&value[6],"POGtrack/F");
		t->Branch("POGtrackErr",&value[7],"POGtrackErr/F");

		std::string base = std::getenv("CMSSW_BASE");
		std::string fPath =   "/src/PUAnalysis/Configuration/data/";
		std::vector<std::string> fFile =  {"SingleMuonTrigger_Z_RunBCD_prompt80X_7p65.root","MuonID_Z_RunBCD_prompt80X_7p65.root","MuonIso_Z_RunBCD_prompt80X_7p65.root","tracking_eta.root"};
		if (!Mu_)
			fFile =  {"EleSoup.root","MVA80.root","MVA90.root","GSFTracking.root"};

		std::string path1= base+fPath+fFile[0];
		std::string path2= base+fPath+fFile[1];
		std::string path3= base+fPath+fFile[2];
		std::string path4= base+fPath+fFile[3];
		isFile_   = boost::filesystem::exists(path1)&&boost::filesystem::exists(path2)&&boost::filesystem::exists(path3)&&boost::filesystem::exists(path4);
		if (isFile_){
			std::cout<<"INFO::POGSFsFiller using files"<<std::endl;
			f_file1 = TFile::Open(path1.c_str());
			f_file2 = TFile::Open(path2.c_str());
			f_file3 = TFile::Open(path3.c_str());
			f_file4 = TFile::Open(path4.c_str());
		}
		else { std::cout<<"WARNING::POGSFsFiller No efficiency file found!!!"<<std::endl;}

		if(Mu_){
			h2_trigger = (TH2D*)f_file1->Get("IsoMu22_OR_IsoTkMu22_PtEtaBins_Run274094_to_276097/efficienciesDATA/abseta_pt_DATA");
			h2_id1    = (TH2D*)f_file2->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_spliteta_bin1/abseta_pt_ratio");
			h2_id2    = (TH2D*)f_file3->Get("MC_NUM_TightRelIso_DEN_TightID_PAR_pt_spliteta_bin1/abseta_pt_ratio");
			h1_trk    = (TH1F*)f_file4->Get("tracking_eta");
		}
		else
		{
			h2_trigger= (TH2D*)f_file1->Get("probe_sc_abseta_probe_sc_pt_PLOT");
			h2_id1    = (TH2D*)f_file2->Get("EGamma_SF2D");
			h2_id2    = (TH2D*)f_file3->Get("EGamma_SF2D");
			h2_trk    = (TH2D*)f_file4->Get("EGamma_SF2D");

		}

	}


		~POGSFsFiller()
		{ 
		}

		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{

			float Trigger = 0;
			float TriggerErr = 0; float ID1=0; float ID1Err=0 ; float ID2=0; float ID2Err =0 ; float TRK=0; float TRKErr=0;
			edm::Handle<std::vector<T>> handle;
			if( iEvent.getByToken(src_,handle)){
				double pt = handle->at(0).leg1()->pt();
				double eta = handle->at(0).leg1()->eta();
				if (Mu_ ){ 
					Trigger = h2_trigger->GetBinContent( h2_trigger->GetXaxis()->FindBin(std::abs(eta)), h2_trigger->GetYaxis()->FindBin(std::min(pt,499.)) );
					TriggerErr = h2_trigger->GetBinError( h2_trigger->GetXaxis()->FindBin(std::abs(eta)), h2_trigger->GetYaxis()->FindBin(std::min(pt,499.)) );
					ID1 = h2_id1->GetBinContent( h2_id1->GetXaxis()->FindBin(std::abs(eta)), h2_id1->GetYaxis()->FindBin(std::min(pt,199.)) );
					ID1Err = h2_id1->GetBinError( h2_id1->GetXaxis()->FindBin(std::abs(eta)), h2_id1->GetYaxis()->FindBin(std::min(pt,199.)) );
					ID2 = h2_id2->GetBinContent( h2_id2->GetXaxis()->FindBin(std::abs(eta)), h2_id2->GetYaxis()->FindBin(std::min(pt,199.)) );
					ID2Err = h2_id2->GetBinError( h2_id2->GetXaxis()->FindBin(std::abs(eta)), h2_id2->GetYaxis()->FindBin(std::min(pt,199.)) );
					TRK = h1_trk->GetBinContent(h1_trk->GetXaxis()->FindBin(eta) ); 
					TRKErr = h1_trk->GetBinError(h1_trk->GetXaxis()->FindBin(eta) ); 
				}
				else{ 
					Trigger = h2_trigger->GetBinContent( h2_trigger->GetXaxis()->FindBin(std::abs(eta)), h2_trigger->GetYaxis()->FindBin(std::min(pt,199.)) );
					TriggerErr = h2_trigger->GetBinError( h2_trigger->GetXaxis()->FindBin(std::abs(eta)), h2_trigger->GetYaxis()->FindBin(std::min(pt,199.)) );
					ID1 = h2_id1->GetBinContent( h2_id1->GetXaxis()->FindBin(eta), h2_id1->GetYaxis()->FindBin(std::min(pt,199.) ));
					ID1Err = h2_id1->GetBinError( h2_id1->GetXaxis()->FindBin(eta), h2_id1->GetYaxis()->FindBin(std::min(pt,199.)) );
					ID2 = h2_id2->GetBinContent( h2_id2->GetXaxis()->FindBin(eta), h2_id2->GetYaxis()->FindBin(std::min(pt,199.)) );
					ID2Err = h2_id2->GetBinError( h2_id2->GetXaxis()->FindBin(eta), h2_id2->GetYaxis()->FindBin(std::min(pt,199.)) );
					TRK = h2_trk->GetBinContent( h2_trk->GetXaxis()->FindBin(eta), h2_trk->GetYaxis()->FindBin(std::min(pt,199.)) );
					TRKErr = h2_trk->GetBinError( h2_trk->GetXaxis()->FindBin(eta), h2_trk->GetYaxis()->FindBin(std::min(pt,199.)) );
				}
			}


			value[0]=Trigger;
			value[1]=TriggerErr;
			value[2]=ID1;
			value[3]=ID1Err;
			value[4]=ID2;
			value[5]=ID2Err;
			value[6]=TRK;
			value[7]=TRKErr;
		}


	protected:
		edm::EDGetTokenT<std::vector<T> > src_;
		std::string tag_;
		bool Mu_;
		bool isFile_;
		//std::vector<float> value;
		float* value;
		TFile *f_file1;
		TFile *f_file2;
		TFile *f_file3;
		TFile *f_file4;
		TH2D *h2_trigger;
		TH2D *h2_id1;
		TH2D *h2_id2;
		TH2D *h2_trk;
		TH1F *h1_trk;


};

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef POGSFsFiller<PATMuTauPair> PATMuTauPairPOGSFsFiller;
typedef POGSFsFiller<PATElecTauPair> PATEleTauPairPOGSFsFiller;

