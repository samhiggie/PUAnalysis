#ifndef PUAnalysis_RecoTools_CompositePtrCandidateT1T2MEtProducer_h
#define PUAnalysis_RecoTools_CompositePtrCandidateT1T2MEtProducer_h

/** \class CompositePtrCandidateT1T2MEtProducer
 *
 * Produce combinations of leptonic and hadronic decay products 
 * of a pair of tau leptons plus missing transverse momentum 
 * (representing the undetected momentum carried away by the neutrinos 
 *  produced in the two tau decays) 
 * 
 * \authors Colin Bernet,
 *          Michal Bluj,
 *          Christian Veelken
 *
 * \version $Revision: 1.9 $
 *
 * $Id: CompositePtrCandidateT1T2MEtProducer.h,v 1.9 2013/06/20 16:35:01 ojalvo Exp $
 *
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "PUAnalysis/RecoTools/interface/FetchCollection.h"

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"

#include "PUAnalysis/RecoTools/interface/CompositePtrCandidateT1T2MEtAlgorithm.h"
#include "PUAnalysis/RecoTools/interface/CompositePtrCandidateT1T2MEtVertexAlgorithm.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <string>

bool IsRealData=false; 

template<typename T1, typename T2>
class CompositePtrCandidateT1T2MEtProducer : public edm::EDProducer 
{
	typedef edm::Ptr<T1> T1Ptr;
	typedef edm::View<T1> T1View;
	typedef edm::Ptr<T2> T2Ptr;
	typedef edm::View<T2> T2View;
	typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;
	typedef std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > CompositePtrCandidateCollection;

	public:

	explicit CompositePtrCandidateT1T2MEtProducer(const edm::ParameterSet& cfg)
		: algorithm_(cfg), cfgError_(0)
	{
		useLeadingTausOnly_ = cfg.getParameter<bool>("useLeadingTausOnly");
		srcLeg1_ = consumes<T1View>(cfg.getParameter<edm::InputTag>("srcLeg1"));
		srcLeg2_ = consumes<T2View>(cfg.getParameter<edm::InputTag>("srcLeg2"));
		srcJets_ = consumes<edm::View<pat::Jet> >(cfg.getParameter<edm::InputTag>("srcJets"));
		dRmin12_ = cfg.getParameter<double>("dRmin12");
		srcMET_ = consumes<edm::View<pat::MET>>(cfg.getParameter<edm::InputTag>("srcMET"));
		//srcMET_ = consumes<reco::CandidateView>(cfg.getParameter<edm::InputTag>("srcMET"));
		srcTaus_ =  consumes<std::vector<pat::Tau> >(cfg.getParameter<edm::InputTag>("srcTaus"));
		srcGenParticles_ = consumes<reco::GenParticleCollection>(cfg.getParameter<edm::InputTag>("srcGenParticles")); 
		recoMode_ = cfg.getParameter<std::string>("recoMode");
		verbosity_ = cfg.getUntrackedParameter<int>("verbosity", 0);
		minPt_ = cfg.getUntrackedParameter<double>("minJetPt", 20.0);


		//--- check that InputTag for MET collection has been defined,
		//    in case it is needed for the reconstruction mode 
		//    specified in the configuration parameter set
		if ( srcMET_.isUninitialized() && recoMode_ != "" ) {
			edm::LogError ("CompositePtrCandidateT1T2MEtProducer") << " Configuration Parameter srcMET undefined," 
				<< " needed for recoMode = " << recoMode_ << " !!";
			cfgError_ = 1;
		}

		produces<CompositePtrCandidateCollection>("");
	}

	~CompositePtrCandidateT1T2MEtProducer() {}

	void produce(edm::Event& evt, const edm::EventSetup& es)
	{
		//Instantiate the vertex Algorithm
		//CompositePtrCandidateT1T2MEtVertexAlgorithm<T1,T2> vAlgo(evt,es);

		//--- print-out an error message and add an empty collection to the event 
		//    in case of erroneous configuration parameters

		if(evt.isRealData()){
			IsRealData=true;
		}

		if ( cfgError_ ) {
			edm::LogError ("produce") << " Error in Configuration ParameterSet" 
				<< " --> CompositePtrCandidateT1T2MEt collection will NOT be produced !!";
			std::auto_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());
			evt.put(emptyCompositePtrCandidateCollection);
			return;
		}

		//typedef edm::View<T1> T1View;
		edm::Handle<T1View> leg1Collection;
		pf::fetchCollection(leg1Collection, srcLeg1_, evt);

		edm::Handle<edm::View<pat::Jet> > jetCollection;
		pf::fetchCollection(jetCollection, srcJets_, evt);

		//typedef edm::View<T2> T2View;
		edm::Handle<T2View> leg2Collection;
		pf::fetchCollection(leg2Collection, srcLeg2_, evt);

		const std::vector<pat::Tau>* tauPtr = 0;
		if ( !(srcTaus_.isUninitialized()) ) {
			edm::Handle<std::vector<pat::Tau> > tauCollection;
			if(evt.getByToken(srcTaus_,tauCollection))
				tauPtr = tauCollection.product();
			//pf::fetchCollection(tauCollection, srcTaus_, evt);

			//std::cout<< "Got Taus: " << tauCollection->size()<<endl;
		}


		reco::CandidatePtr metPtr;
		edm::Handle<edm::View<pat::MET>> metCollection;
		pf::fetchCollection(metCollection, srcMET_, evt);
		if (metCollection->size() == 0) { 
			edm::LogError ("produce") << " Found " << metCollection->size() << " MET objects in collection "
				<< " --> CompositePtrCandidateT1T2MEt collection will NOT be produced !!";
			std::auto_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());      
			evt.put(emptyCompositePtrCandidateCollection);
			return;
		}                

		const reco::GenParticleCollection* genParticles = 0;
		if ( !(srcGenParticles_.isUninitialized()) ) {
			edm::Handle<reco::GenParticleCollection> genParticleCollection;
			if(evt.getByToken(srcGenParticles_,genParticleCollection))
				genParticles = genParticleCollection.product();
		}


		JetPtrVector pfJets;
		for(unsigned int i=0;i<jetCollection->size();++i)
			if(jetCollection->at(i).pt()>minPt_)
				pfJets.push_back(jetCollection->ptrAt(i));



		//--- check if only one combination of tau decay products 
		//    (the combination of highest Pt object in leg1 collection + highest Pt object in leg2 collection)
		//    shall be produced, or all possible combinations of leg1 and leg2 objects
		std::auto_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());
		if ( useLeadingTausOnly_ ) {
			//--- find highest Pt particles in leg1 and leg2 collections
			int idxLeadingLeg1 = -1;
			double leg1PtMax = 0.;
			for ( unsigned idxLeg1 = 0, numLeg1 = leg1Collection->size(); 
					idxLeg1 < numLeg1; ++idxLeg1 ) {
				T1Ptr leg1Ptr = leg1Collection->ptrAt(idxLeg1);
				if ( idxLeadingLeg1 == -1 || leg1Ptr->pt() > leg1PtMax ) {
					idxLeadingLeg1 = idxLeg1;
					leg1PtMax = leg1Ptr->pt();
				}
			}

			int idxLeadingLeg2 = -1;
			double leg2PtMax = 0.;
			for ( unsigned idxLeg2 = 0, numLeg2 = leg2Collection->size(); 
					idxLeg2 < numLeg2; ++idxLeg2 ) {
				T2Ptr leg2Ptr = leg2Collection->ptrAt(idxLeg2);

				//--- do not create CompositePtrCandidateT1T2MEt object 
				//    for combination of particle with itself
				if ( idxLeadingLeg1 != -1 ) {
					T1Ptr leadingLeg1Ptr = leg1Collection->ptrAt(idxLeadingLeg1);
					double dR = reco::deltaR(leadingLeg1Ptr->p4(), leg2Ptr->p4());
					if ( dR < dRmin12_ ) continue;
				}

				if ( idxLeadingLeg2 == -1 || leg2Ptr->pt() > leg2PtMax ) {
					idxLeadingLeg2 = idxLeg2;
					leg2PtMax = leg2Ptr->pt();
				}
			}

			if ( idxLeadingLeg1 != -1 &&
					idxLeadingLeg2 != -1 ) {
				T1Ptr leadingLeg1Ptr = leg1Collection->ptrAt(idxLeadingLeg1);
				T2Ptr leadingLeg2Ptr = leg2Collection->ptrAt(idxLeadingLeg2);
				//ADD MVA MET HERE

				CompositePtrCandidateT1T2MEt<T1,T2> compositePtrCandidate = 
					algorithm_.buildCompositePtrCandidate(leadingLeg1Ptr, leadingLeg2Ptr,pfJets, metPtr, tauPtr, IsRealData, genParticles);
				compositePtrCandidateCollection->push_back(compositePtrCandidate);
			} else {
				if ( verbosity_ >= 1 ) {
					edm::LogInfo ("produce") << " Found no combination of particles in Collections" 
						<< " leg1 and leg2 = " ;
					//<< " leg1 = " << srcLeg1_ << " and leg2 = " << srcLeg2_ << ".";
				}
			}
		} else {
			//--- check if the same collection is used on both legs;
			//    if so, skip diTau(j,i), j > i combination in order to avoid two diTau objects being produced
			//    for combinations (i,j) and (j,i) of the same pair of particles in leg1 and leg2 collections
			bool sameCollection = (leg1Collection.id() == leg2Collection.id());

			for ( unsigned idxLeg1 = 0, numLeg1 = leg1Collection->size(); 
					idxLeg1 < numLeg1; ++idxLeg1 ) {
				T1Ptr leg1Ptr = leg1Collection->ptrAt(idxLeg1);

				unsigned idxLeg2_first = ( sameCollection ) ? (idxLeg1 + 1) : 0;
				for ( unsigned idxLeg2 = idxLeg2_first, numLeg2 = leg2Collection->size(); 
						idxLeg2 < numLeg2; ++idxLeg2 ) {
					T2Ptr leg2Ptr = leg2Collection->ptrAt(idxLeg2);

					//--- do not create CompositePtrCandidateT1T2MEt object 
					//    for combination of particle with itself
					double dR = reco::deltaR(leg1Ptr->p4(), leg2Ptr->p4());
					if ( dR < dRmin12_ ) continue;
					bool foundMET = false;
					if ( metCollection->size() == 1 ) 
					{
						metPtr = metCollection->ptrAt(0);
						foundMET=true;
					} //required for pfMet
					else { 
						//std::cout<<"~~~~~~~~~I AM INSIDE MVA MET ELSE MATCHING~~~~~~~~"<<std::endl;
						for (size_t i = 0; i < metCollection->size(); ++i) {
							const pat::MET& met = (*metCollection)[i];
							//for ( auto name : met.userCandNames() ) std::cout << name << std::endl;	
	 						double l1pdg = leg1Ptr->pdgId();
	 						double l1eta = (round(leg1Ptr->eta()*1000))/1000.0;
	 						double l1phi = (round(leg1Ptr->phi()*1000))/1000.0;
	 						double l2pdg = leg2Ptr->pdgId();
	 						double l2eta = (round(leg2Ptr->eta()*1000))/1000.0;
	 						double l2phi = (round(leg2Ptr->phi()*1000))/1000.0;
	 						double m1pdg = met.userCand("lepton0")->pdgId();
	 						double m1eta = (round(met.userCand("lepton0")->eta()*1000))/1000.0;
	 						double m1phi = (round(met.userCand("lepton0")->phi()*1000))/1000.0;
	 						double m2pdg = met.userCand("lepton1")->pdgId();
	 						double m2eta = (round(met.userCand("lepton1")->eta()*1000))/1000.0;
	 						double m2phi = (round(met.userCand("lepton1")->phi()*1000))/1000.0;
							

							/*std::cout<<"MVA MET loop: "<<i<<std::endl;
							if (l1pt == m1pt) {std::cout<<"l1pt "<<l1pt<<" matches m1pt "<<m1pt<<std::endl;} 
							if (l2pt == m2pt) {std::cout<<"l2pt "<<l2pt<<" matches m2pt "<<m2pt<<std::endl;} 
							if (l1eta == m1eta) {std::cout<<"l1eta "<<l1eta<<" matches m1eta "<<m1eta<<std::endl;} 
							if (l2eta == m2eta) {std::cout<<"l2eta "<<l2eta<<" matches m2eta "<<m2eta<<std::endl;} 
							if (l1pt == m2pt) {std::cout<<"NOTE: l1pt "<<l1pt<<" matches m2pt "<<m2pt<<std::endl;} 
							*/

							if ( l1pdg==m1pdg && l2pdg==m2pdg && l1phi == m1phi && l2phi == m2phi && l1eta==m1eta && l2eta==m2eta)
							{ 
								//std::cout<<"FOUND MET MATCH 1"<<std::endl;
								metPtr = metCollection->ptrAt(i); 
								foundMET=true; 
								break;
							}
						}//end met loop
					}//end else
					if(!foundMET) {	
						std::cout<<"===============MET NOT FOUND============="<<std::endl;
						std::cout<<"Leg1 Pt: "<<leg1Ptr->pt()<<" Eta: "<<leg1Ptr->eta()<<" Phi: "<<leg1Ptr->phi()<<std::endl;
						std::cout<<"Leg2 Pt: "<<leg2Ptr->pt()<<" Eta: "<<leg2Ptr->eta()<<" Phi: "<<leg2Ptr->phi()<<std::endl;
						for (size_t i = 0; i < metCollection->size(); ++i) {
							const pat::MET& met = (*metCollection)[i];
							std::cout<<"MVA Lepton Pair # "<<i<<std::endl;
							std::cout<<"MVA1 Pt: "<<met.userCand("lepton0")->pt()<<" Eta: "<<met.userCand("lepton0")->eta()<<" Phi: "<<met.userCand("lepton0")->phi()<<std::endl;
							std::cout<<"MVA2 Pt: "<<met.userCand("lepton1")->pt()<<" Eta: "<<met.userCand("lepton1")->eta()<<" Phi: "<<met.userCand("lepton1")->phi()<<std::endl;
						}
						//edm::LogError ("produce") << " Found " << metCollection->size() << " MET objects in collection "
						//<< " but NO LEPTON MATCH --> CompositePtrCandidateT1T2MEt collection will NOT be produced !!";
						std::auto_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());      
						evt.put(emptyCompositePtrCandidateCollection);
						return;
					}


					CompositePtrCandidateT1T2MEt<T1,T2> compositePtrCandidate = 
						algorithm_.buildCompositePtrCandidate(leg1Ptr, leg2Ptr, pfJets, metPtr, tauPtr, IsRealData, genParticles);

					//vAlgo.calculateVertexVariables(compositePtrCandidate);
					compositePtrCandidateCollection->push_back(compositePtrCandidate);
				}
			}
		}

		//--- add the collection of reconstructed CompositePtrCandidateT1T2MEts to the event
		evt.put(compositePtrCandidateCollection);
	}

	private:

	CompositePtrCandidateT1T2MEtAlgorithm<T1,T2> algorithm_;

	bool useLeadingTausOnly_;
	edm::EDGetTokenT<T1View> srcLeg1_;
	edm::EDGetTokenT<T2View> srcLeg2_;
	edm::EDGetTokenT<edm::View<pat::Jet> >  srcJets_;
	double dRmin12_;
	edm::EDGetTokenT<edm::View<pat::MET>> srcMET_;
	//edm::EDGetTokenT<reco::CandidateView> srcMET_;
	edm::EDGetTokenT<std::vector<pat::Tau> > srcTaus_;
	edm::EDGetTokenT<reco::GenParticleCollection> srcGenParticles_;
	std::string recoMode_;
	int verbosity_;
	double minPt_;
	int cfgError_;



};

#endif

