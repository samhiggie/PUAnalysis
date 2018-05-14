//Ovserloads the lepton with the rho factor


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "Math/GenVector/VectorUtil.h"

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEtFwd.h"

#include "DataFormats/HLTReco/interface/TriggerRefsCollections.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"


//
//
// class declaration
//
template <typename T> 
class MiniAODTriggerMatcher : public edm::EDProducer {

	public:
		explicit MiniAODTriggerMatcher (const edm::ParameterSet& iConfig):
			src_(consumes<edm::View<T>>(iConfig.getParameter<edm::InputTag>("src"))),
			filters_(iConfig.getParameter<std::vector<std::string> >("filters")),
			filtersAND_(iConfig.getParameter<std::vector<std::string> >("filtersAND")),
			triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
			triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
			triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
			ptCut_(iConfig.getParameter<int>("ptCut"))
	{
		produces<std::vector<T> >();
	}

		~MiniAODTriggerMatcher ()
		{

		}

	private:
		edm::EDGetTokenT<edm::View<T>> src_;
		std::vector<std::string> filters_;
		std::vector<std::string> filtersAND_;

		edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
		edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
		edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;

		int ptCut_;


		virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
		{

		  using namespace reco;
		  using namespace trigger;
		  using namespace edm;
		  
		  typedef reco::Candidate::LorentzVector LV;
		  edm::Handle<edm::TriggerResults> triggerBits;
		  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
		  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
		  
		  iEvent.getByToken(triggerBits_, triggerBits);
		  iEvent.getByToken(triggerObjects_, triggerObjects);
		  iEvent.getByToken(triggerPrescales_, triggerPrescales);
		  
		  //Read the shallow clones of a candidate and save the SECOND Clone
		  std::unique_ptr<std::vector<T> > out(new std::vector<T> );
		  edm::Handle<edm::View<T> > src;

		  if(iEvent.getByToken(src_,src)){
		    
		    for(unsigned int k=0;k<src->size();++k) {
		      T pat = src->at(k);
		      //loop the filters
		      for(unsigned int i=0;i<filters_.size();++i) {
			std::vector<LV> trigObjects = getFilterCollectionMiniAOD(iEvent, triggerBits, ptCut_,filters_[i],*triggerObjects);
			std::vector<LV> trigObjectsAND = getFilterCollectionMiniAOD(iEvent, triggerBits, ptCut_,filtersAND_[i],*triggerObjects); 
			
			bool match = false;
			bool doAND = true;
			
			
			if ( filtersAND_[i]==filters_[i]){ //See if filtersAND is non zero for same i
			  doAND=false;
			  //std::cout << "\n === TRIGGER Filters: SingleFilter  === " << std::endl;
			}
			
			//std::cout << "\n === TRIGGER OBJECT Filters: "<< filters_[i]<< std::endl;
			//std::cout << "\n === TRIGGER OBJECT FiltersAND: "<< filtersAND_[i]<< std::endl;
			
			for(unsigned int j=0;j<trigObjects.size();++j){ 
			  //std::cout<<"trigObject eta: "<<trigObjects.at(j).eta() <<" phi: "<<trigObjects.at(j).phi()<<std::endl;
			  if(deltaR(trigObjects.at(j),pat)<0.5) {
			    //std::cout << "\n === TRIGGER OBJECT DeltaR Calculation === " << std::endl;
			    match=true;
			    break;
			  }//end match if no AND requirements. 
			  
			    //else if(deltaR(trigObjects.at(j),pat)<0.5&&doAND==true ) {
			    //for(unsigned int r=0;r<trigObjectsAND.size();++r){
			    //if(deltaR(trigObjectsAND.at(r),pat)<0.5){
			    //match=true;
			    //goto endTriggerObjects;
			    //}//end if the AND passes
			    //}//end for loop over the AND Trigger objects
			    //}//end match if AND reuirements
			  
			}//end for loop over trigger objects
			//endTriggerObjects:;
			if(match){
			  pat.addUserFloat(filters_[i],1.0);
			  if (doAND) pat.addUserFloat(filtersAND_[i],1.0);
			  //std::cout << "\n === TRIGGER OBJECT MATCHED === " << std::endl;
			  //std::cout << "\n === TRIGGER OBJECT Filters: "<< filters_[i]<< std::endl;
			  //if (doAND) std::cout << "\n === TRIGGER OBJECT FiltersAND: "<< filtersAND_[i]<< std::endl;
			  
			  //std::cout << "\n === TRIGGER OBJECT ADD USER FLOAT === " << std::endl;
			}
			else{
			  pat.addUserFloat(filters_[i],0.0);
			  if (doAND) pat.addUserFloat(filtersAND_[i],0.0);
			}
		      }
		      
		      
		      out->push_back(pat);
		    }
		  }
		  iEvent.put(std::move(out),"");    

		  //std::cout<<"iEvent added trigger"<<std::endl;
		}
		
		virtual void endJob() { }

		//MiniAod 
		std::vector<reco::Candidate::LorentzVector> getFilterCollectionMiniAOD(edm::Event& iEvent, edm::Handle<edm::TriggerResults> triggerBits, int ptcut,std::string filter,pat::TriggerObjectStandAloneCollection triggerObjects)
		  {
		    //const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
			  //Create output Collection
		    std::vector<reco::Candidate::LorentzVector>  out;
			  //get All the final trigger objects
			  for (pat::TriggerObjectStandAlone obj : triggerObjects) { // note: not "const &" since we want to call unpackPathNames
			    obj.unpackFilterLabels(iEvent, *triggerBits); 
			    //obj.unpackPathNames(names);
			    
			    reco::Candidate::LorentzVector a(obj.px(),obj.py(),obj.pz(),sqrt(obj.px()*obj.px()+obj.py()*obj.py()+obj.pz()*obj.pz()));
			    for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
			      
			      //std::cout<<"=====Before Filter====="<<std::endl;
			      //std::cout<<"Filter Label :"<<obj.filterLabels()[h]<<std::endl;
			      //std::cout<<"Given Filter :"<<filter<<std::endl;
			      //if (obj.filterIds()[h]==id && obj.filter(filter)){
			      if (obj.filter(filter)&&obj.pt()>=ptcut){
				out.push_back(a);
				//std::cout<<"=====After Filter====="<<std::endl;
				//std::cout<<"Filter Label :"<<obj.filterLabels()[h]<<std::endl;
				//std::cout<<"Given Filter :"<<filter<<std::endl;
				
			      }//end filterlabels
			    }//end id
			  }
			  
			  return out;
			}

		
		
};
