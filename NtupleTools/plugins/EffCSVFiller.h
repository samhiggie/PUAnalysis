// system include files
#include <memory>

// user include files

#include <TTree.h>
#include <TH2D.h>
#include <TFile.h>

#include "TRandom3.h"

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "Math/GenVector/VectorUtil.h" 
#include "TMath.h"
//
// class decleration
//

template<typename T>
class EffCSVFiller : public NtupleFillerBase {
	public:
		EffCSVFiller(){
		}


		EffCSVFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC ):
			src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))) 
	{
		value = new float[14];
		t->Branch("EffCSVWeight0",&value[0],"EffCSVWeight0/F");
		t->Branch("EffCSVWeight0Up",&value[1],"EffCSVWeight0Up/F");
		t->Branch("EffCSVWeight0UpHF",&value[2],"EffCSVWeight0UpHF/F");
		t->Branch("EffCSVWeight0UpLF",&value[3],"EffCSVWeight0UpLF/F");
		t->Branch("EffCSVWeight0Down",&value[4],"EffCSVWeight0Down/F");
		t->Branch("EffCSVWeight0DownHF",&value[5],"EffCSVWeight0DownHF/F");
		t->Branch("EffCSVWeight0DownLF",&value[6],"EffCSVWeight0DownLF/F");
		t->Branch("EffCSVWeight1",&value[7],"EffCSVWeight1/F");
		t->Branch("EffCSVWeight1Up",&value[8],"EffCSVWeight1Up/F");
		t->Branch("EffCSVWeight1UpHF",&value[9],"EffCSVWeight1UpHF/F");
		t->Branch("EffCSVWeight1UpLF",&value[10],"EffCSVWeight1UpLF/F");
		t->Branch("EffCSVWeight1Down",&value[11],"EffCSVWeight1Down/F");
		t->Branch("EffCSVWeight1DownHF",&value[12],"EffCSVWeight1DownHF/F");
		t->Branch("EffCSVWeight1DownLF",&value[13],"EffCSVWeight1DownLF/F");
		calib=BTagCalibration("CSVv2", std::string(std::getenv("CMSSW_BASE"))+"/src/PUAnalysis/Configuration/data/CSVv2_ichep.csv");
		//reader=new BTagCalibrationReader(calib, BTagEntry::OP_MEDIUM, "comb", "central");
		reader=BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central",{"up","down"});
		reader.load(calib, BTagEntry::FLAV_B, "comb");
		reader.load(calib, BTagEntry::FLAV_C, "comb");
		reader.load(calib, BTagEntry::FLAV_UDSG, "incl");
	}


		~EffCSVFiller()
		{ 
		}

		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{



			edm::Handle<std::vector<T>> handle;


			std::vector<double> SF,SFup,SFdown;
			std::vector<double> SFupHF,SFdownHF,SFupLF,SFdownLF;
			//std::vector<double> SFupLF,SFdownLF;

			if( iEvent.getByToken(src_,handle)){
				for( unsigned int i=0; i<handle->at(0).jets().size(); i++){
					if(handle->at(0).jets().at(i)->pt()<30 && abs(handle->at(0).jets().at(i)->eta())>2.4 ) continue;
					double pt = handle->at(0).jets().at(i)->pt();
					double eta = handle->at(0).jets().at(i)->eta();
					if (pt <20 || abs(eta)>2.4) continue;
					int jetflavor = abs(handle->at(0).jets().at(i)->partonFlavour());
					if (handle->at(0).jets().at(i)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.80){
						//std::cout<< "Flavor: "<<jetflavor<<std::endl;
						BTagEntry::JetFlavor jf= BTagEntry::FLAV_B;
						if (jetflavor==4) jf = BTagEntry::FLAV_C;
						else jf = BTagEntry::FLAV_UDSG; 
						if (jetflavor==5||jetflavor==4){
							SF.push_back(reader.eval_auto_bounds("central",jf, eta, pt ));
							SFup.push_back(reader.eval_auto_bounds("up",jf, eta, pt ));
							SFupHF.push_back(reader.eval_auto_bounds("up",jf, eta, pt ));
							SFdown.push_back(reader.eval_auto_bounds("down",jf, eta, pt ));
							SFdownHF.push_back(reader.eval_auto_bounds("down",jf, eta, pt ));
						}
						else {
							SF.push_back(reader.eval_auto_bounds("central",jf, eta, pt ));
							SFup.push_back(reader.eval_auto_bounds("up",jf, eta, pt ));
							SFupLF.push_back(reader.eval_auto_bounds("up",jf, eta, pt ));
							SFdown.push_back(reader.eval_auto_bounds("down",jf, eta, pt ));
							SFdownLF.push_back(reader.eval_auto_bounds("down",jf, eta, pt ));
						}
					}//end pass btag
				}//end for jets
			}//end handle



			value[0]=bTagEventWeight(SF, 0);
			value[1]=bTagEventWeight(SFup, 0);
			value[2]=bTagEventWeight(SFupHF, 0);
			value[3]=bTagEventWeight(SFupLF, 0);
			value[4]=bTagEventWeight(SFdown, 0);
			value[5]=bTagEventWeight(SFdownHF, 0);
			value[6]=bTagEventWeight(SFdownLF, 0);
			value[7]=bTagEventWeight(SF, 1);
			value[8]=bTagEventWeight(SFup, 1);
			value[9]=bTagEventWeight(SFupHF, 1);
			value[10]=bTagEventWeight(SFupLF, 1);
			value[11]=bTagEventWeight(SFdown, 1);
			value[12]=bTagEventWeight(SFdownHF, 1);
			value[13]=bTagEventWeight(SFdownLF, 1);
		}


		double bTagEventWeight(std::vector<double>& SFsForBTaggedJets, unsigned int nBTags){
			if( nBTags > 1 )
			{
				edm::LogError("bTagEventWeight") << "Only 0 btag and 1+ btagincluded. btag!>1 ";
				exit(1);
			}
			//##################################################################
			//Event weight matrix:
			//------------------------------------------------------------------
			//nBTags\b-tagged jets  |    0        1+    
			//------------------------------------------------------------------
			//0                     |    1        Product_ibtagged (1-SF_i)     
			//
			//1+                    |    0        1- (Product_ibtagged (1-SF_i) )   
			//
			//##################################################################

			if( nBTags > SFsForBTaggedJets.size() ) return 0.0;

			if( nBTags==0 && SFsForBTaggedJets.size()==0 ) return 1.0;

			double weight = 1;

			for (unsigned int i=0;i<SFsForBTaggedJets.size() ; ++i){
				double SF_i = SFsForBTaggedJets.at(i);
				weight *= (1-SF_i);
			}
			double atleastone = 1-weight;
			if (nBTags==1) {return atleastone;}
			else {return weight;}
		}

	protected:
		edm::EDGetTokenT<std::vector<T> > src_;
		std::string tag_;
		float* value;

		BTagCalibration calib;
		BTagCalibrationReader reader;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef EffCSVFiller<PATMuTauPair> PATMuTauPairEffCSVFiller;
typedef EffCSVFiller<PATElecTauPair> PATEleTauPairEffCSVFiller;
typedef EffCSVFiller<PATDiTauPair> PATDiTauPairEffCSVFiller;



