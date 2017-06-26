// system include files
#include <memory>
#include <cmath>
// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>
#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//Trigger Files
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

//
// class decleration
//

class TriggerFiller : public NtupleFillerBase {
	public:

		TriggerFiller(){
		}

		TriggerFiller(const edm::ParameterSet& iConfig, TTree* t, edm::ConsumesCollector && iC):
			src_(iC.consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("src"))),
			triggerPrescales_(iC.consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
			paths_(iConfig.getParameter<std::vector<std::string> >("paths"))
	{
		fired    = std::vector<int>(paths_.size());
		prescale = std::vector<int>(paths_.size());

		any=0;

		for(unsigned int i=0;i<paths_.size();++i) {
			fired[i]=0;
			prescale[i]=0;

			t->Branch((paths_[i]+"_fired").c_str(),&fired[i],(paths_[i]+"_fired/I").c_str());
			t->Branch((paths_[i]+"_prescale").c_str(),&prescale[i],(paths_[i]+"_prescale/I").c_str());

		}
		t->Branch("HLT_Any",&any,"HLT_Any/I");

	}



		~TriggerFiller()
		{ 

		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{

			using namespace std; 
			any=0;

			edm::Handle<edm::TriggerResults> triggerBits;
			edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

			//std::cout<<"NTUPLE TRIGGER FILLER!"<<std::endl;

			iEvent.getByToken(src_, triggerBits);
			iEvent.getByToken(triggerPrescales_, triggerPrescales); 
			const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
			//std::cout << "\n === TRIGGER PATHS === " << std::endl;
			//for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
			//   std::string name =  names.triggerName(i) ; 
			//   int prescale triggerPrescales->getPrescaleForIndex(i);
			//	 bool accept = (triggerBits->accept(i);
			//	 bool fail = !(triggerBits->accept(i);
			// } 

			//get the names of the triggers
			for(unsigned int i=0;i<paths_.size();++i) {
				bool found=false;
				bool fired_t=false;
				//std::cout<<"Find a Trigger Path: "<<paths_[i]<<std::endl;
				for(unsigned int j=0 ,  n = triggerBits->size(); j < n && fired_t==false; ++j) {
					size_t trigPath = names.triggerName(j).find(paths_.at(i));
					if ( trigPath == 0) {
						//std::cout<<"Found a Trigger Name!: "<<names.triggerName(j)<<std::endl;
						found=true;
						fired[i]=triggerBits->accept(j); 
						prescale[i] = triggerPrescales->getPrescaleForIndex(j);
						if(triggerPrescales->getPrescaleForIndex(j)==1 &&triggerBits->accept(j) ){
							any=1; fired_t=true;
							//std::cout<<"Found a Trigger Name! FIRED"<<std::endl;
						}
						break;
					}
				}
				if(!found) {
					fired[i]=0;
					prescale[i]=0;
				}
			}

		}


	protected:
		edm::EDGetTokenT<edm::TriggerResults> src_;
		edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;

		std::vector<std::string> paths_;

		std::vector<int> fired;
		std::vector<int> prescale;
		int any;

};






