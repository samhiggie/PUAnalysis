// -*- C++ -*-
//
// Package:    PATMuonTrackVetoSelector
// Class:      PATMuonTrackVetoSelector
// 
/**\class PATMuonTrackVetoSelector PATMuonTrackVetoSelector.cc PUAnalysis/PATMuonTrackVetoSelector/src/PATMuonTrackVetoSelector.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: DiCandidateSorterByZMass.h,v 1.1 2011/06/17 15:59:57 iross Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration





template <class T>
class DiCandidateSorterByZMass : public edm::EDProducer {
   public:
  explicit DiCandidateSorterByZMass(const edm::ParameterSet& iConfig):
    src_(consumes<std::vector<T>>(iConfig.getParameter<edm::InputTag>("src")))
     {
       produces<std::vector<T> >();
     }

  ~DiCandidateSorterByZMass() {}


   private:
  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    
    std::vector<T> toBeSorted;
    Handle<std::vector<T> > cands;
    if(iEvent.getByToken(src_,cands)) 
      toBeSorted =  *cands;

    if(toBeSorted.size()>0) {
      Sorter sorter;
      std::sort(toBeSorted.begin(),toBeSorted.end(),sorter);
    }

    std::unique_ptr<std::vector<T> > out(new std::vector<T>);
    //	double tempSum=0;
    for(unsigned int i=0;i<toBeSorted.size();++i){
      //	tempSum=toBeSorted.at(i).leg1()->pt()+toBeSorted.at(i).leg2()->pt();
      //std::cout << "First Z mass: " << toBeSorted.at(i).leg1()->mass() << ", second Z mass: " << toBeSorted.at(i).leg2()->mass() << ", pt sum: " << tempSum << std::endl;
      out->push_back(toBeSorted.at(i));
    }

    iEvent.put(std::move(out),"");    

  } 

  //  template<class T>
  class Sorter {
  public:
    Sorter() 
    {}
    ~Sorter()
    {}
    bool operator()(T t1,T t2)
    {
      return (abs(t1.leg1()->mass()-91.2) < abs(t2.leg1()->mass()-91.2));
    } 
};

      // ----------member data ---------------------------
      edm::EDGetTokenT<std::vector<T>>  src_;



};
