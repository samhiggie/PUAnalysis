// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "Math/GenVector/VectorUtil.h" 
#include "TMath.h"

#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

//
// class decleration
//
template<typename T>
class PtJetPairVarFiller : public NtupleFillerBase {
	public:
		PtJetPairVarFiller(){
		}


		PtJetPairVarFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
			NtupleFillerBase(iConfig,t,iC),
			src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
			var_(iConfig.getParameter<std::string>("method")),
			tag_(iConfig.getParameter<std::string>("tag")),
			cut_(iConfig.getParameter<std::string>("cut")),
			rank_(iConfig.getUntrackedParameter<double>("rank",1.))
	{

		singleValue=-999.;
		function = new StringObjectFunction<pat::Jet>(var_);
		cut = new StringCutObjectSelector<pat::Jet>(cut_,true);
		vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());
	}


		~PtJetPairVarFiller()
		{ 
			if(function!=0) delete function;
			if(cut!=0) delete cut;
		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			edm::Handle<std::vector<T> > handle;

			singleValue=-999;

			//rank is 1 or 2
			int rnk1=-1;
			int rnk2=-1;
			unsigned int i=0;
			unsigned int j=0;
			//printf("Get Jets\n");
			if(iEvent.getByToken(src_,handle)) {
				if(handle->size()>0){
					if(handle->at(0).jets().size()>rank_){
						while (rnk1==-1 && handle->at(0).jets().size()>i){
							if((*cut)(*(handle->at(0).jets().at(i)))) rnk1=i;
							i++;
						}
						j=rnk1+1;
						while (rnk2==-1&&handle->at(0).jets().size()>j){
							if((*cut)(*(handle->at(0).jets().at(j)))) rnk2=j;
							j++;
						}


						if (rnk1!=-1 && rank_==0) singleValue = (*function)(*(handle->at(0).jets().at((int) rnk1)));
						if (rnk2!=-1 && rank_==1) singleValue = (*function)(*(handle->at(0).jets().at((int) rnk2)));
					}
				}
			}
		}

	protected:
		edm::EDGetTokenT<std::vector<T>> src_;
		std::string var_;
		std::string tag_;
		std::string cut_;
		float rank_;
		float singleValue;
		StringObjectFunction<pat::Jet>*function;
		StringCutObjectSelector<pat::Jet>*cut;
		TBranch *vbranch;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef PtJetPairVarFiller<PATMuTauPair> PATMuTauPairPtJetPairVarFiller;
typedef PtJetPairVarFiller<PATElecTauPair> PATEleTauPairPtJetPairVarFiller;
typedef PtJetPairVarFiller<PATDiTauPair> PATDiTauPairPtJetPairVarFiller;





