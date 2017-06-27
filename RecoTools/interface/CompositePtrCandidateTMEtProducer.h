#ifndef PUAnalysis_RecoTools_CompositePtrCandidateTMEtProducer_h
#define PUAnalysis_RecoTools_CompositePtrCandidateTMEtProducer_h

/** \class CompositePtrCandidateTMEtProducer
 *
 * Produce combinations of visible tau decay products and missing transverse momentum 
 * (representing the undetected momentum carried away 
 *  the neutrino produced in a W --> tau nu decay and the neutrinos produced in the tau decay)
 * 
 * \authors Christian Veelken
 *
 * \version $Revision: 1.5 $
 *
 * $Id: CompositePtrCandidateTMEtProducer.h,v 1.5 2012/07/20 10:54:54 ojalvo Exp $
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

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEtFwd.h"
#include "PUAnalysis/RecoTools/interface/CompositePtrCandidateTMEtAlgorithm.h"

#include <string>

template<typename T>
class CompositePtrCandidateTMEtProducer : public edm::EDProducer 
{
  typedef edm::Ptr<T> TPtr;
  typedef edm::Ptr<pat::MET> METPtr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;


  typedef std::vector<CompositePtrCandidateTMEt<T> > CompositePtrCandidateCollection;
  
 public:

  explicit CompositePtrCandidateTMEtProducer(const edm::ParameterSet& cfg)
    : algorithm_()
  {
    srcVisDecayProducts_ = cfg.getParameter<edm::InputTag>("srcLeptons");
    srcJets_ = cfg.getParameter<edm::InputTag>("srcJets");
    srcMET_ = cfg.getParameter<edm::InputTag>("srcMET");
    verbosity_ = cfg.getUntrackedParameter<int>("verbosity", 0);
    srcGenParticles_ = ( cfg.exists("srcGenParticles") ) ? cfg.getParameter<edm::InputTag>("srcGenParticles") : edm::InputTag();
    produces<CompositePtrCandidateCollection>("");


  }

  ~CompositePtrCandidateTMEtProducer() {}

  void produce(edm::Event& iEvent, const edm::EventSetup& es)
  {
    typedef edm::View<T> TView;
    edm::Handle<TView> visDecayProductsCollection;
    bool gotVisProducts = iEvent.getByLabel(srcVisDecayProducts_,visDecayProductsCollection);

  
    METPtr metPtr;
    edm::Handle<edm::View<pat::MET> > metCollection;
    bool gotMET = iEvent.getByLabel(srcMET_,metCollection);

    edm::Handle<edm::View<pat::Jet> > jetCollection;
    iEvent.getByLabel(srcJets_,jetCollection);

    JetPtrVector pfJets;
    for(unsigned int i=0;i<jetCollection->size();++i)
      pfJets.push_back(jetCollection->ptrAt(i));


    const reco::GenParticleCollection* genParticles = 0;
    if ( srcGenParticles_.label() != "" ) {
      edm::Handle<reco::GenParticleCollection> genParticleCollection;
      if(iEvent.getByLabel(srcGenParticles_,genParticleCollection))
        genParticles = genParticleCollection.product();
    }
      
    if(gotVisProducts&&gotMET) {

      //--- check that there is exactly one MET object in the event
      //    (missing transverse momentum is an **event level** quantity)
      if ( metCollection->size() >0 ) {
	metPtr = metCollection->ptrAt(0);
      } else {
	edm::LogError ("produce") << " Found " << metCollection->size() << " MET objects in collection = " << srcMET_ << ","
				  << " --> CompositePtrCandidateTMEt collection will NOT be produced !!";
	std::unique_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());
	iEvent.put(std::move(emptyCompositePtrCandidateCollection),"");
	return;
      }
      
      std::unique_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());
      for ( unsigned idxVisDecayProducts = 0, numVisDecayProducts = visDecayProductsCollection->size(); 
	    idxVisDecayProducts < numVisDecayProducts; ++idxVisDecayProducts ) {
	TPtr visDecayProductsPtr = visDecayProductsCollection->ptrAt(idxVisDecayProducts);
	
	CompositePtrCandidateTMEt<T> compositePtrCandidate = 
	  algorithm_.buildCompositePtrCandidate(visDecayProductsPtr, metPtr,pfJets,*visDecayProductsCollection,genParticles);
	
	compositePtrCandidateCollection->push_back(compositePtrCandidate);
      }
      
      //--- add the collection of reconstructed CompositePtrCandidateTMEts to the event
      iEvent.put(std::move(compositePtrCandidateCollection),"");
    }
    else
      {
	std::unique_ptr<CompositePtrCandidateCollection> emptyCompositePtrCandidateCollection(new CompositePtrCandidateCollection());
	iEvent.put(std::move(emptyCompositePtrCandidateCollection),"");
      }
  }

  

 private:

  CompositePtrCandidateTMEtAlgorithm<T> algorithm_;
  
  edm::InputTag srcVisDecayProducts_;
  edm::InputTag srcMET_;
  edm::InputTag srcJets_;
  edm::InputTag srcGenParticles_;
  int verbosity_;



};

#endif

