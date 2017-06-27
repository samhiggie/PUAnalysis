// -*- C++ -*-
//
// Package:    PATMuonTrackVetoSelector
// Class:      PATMuonTrackVetoSelector
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
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration





template <class T>
class DiCandidateSorterByIsoDiTau : public edm::EDProducer {
   public:
  explicit DiCandidateSorterByIsoDiTau(const edm::ParameterSet& iConfig):
    src_(consumes<std::vector<T>>(iConfig.getParameter<edm::InputTag>("src")))
     {
       produces<std::vector<T> >();
     }

  ~DiCandidateSorterByIsoDiTau() {}


   private:
  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    
    std::vector<T> toBeSorted;
    Handle<std::vector<T> > cands;
    if(iEvent.getByToken(src_,cands)) {toBeSorted =  *cands;}

    if(toBeSorted.size()>0) {
      Sorter sorter;
      std::sort(toBeSorted.begin(),toBeSorted.end(),sorter);
    }
    else {std::cout<<"SorterSize==0!"<<std::endl;}

    std::unique_ptr<std::vector<T> > out(new std::vector<T>);
    for(unsigned int i=0;i<toBeSorted.size();++i)
      out->push_back(toBeSorted.at(i));
    
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
      //std::cout<<" Cand 1 Leg 1 isolation: "<<t1.leg1()->userFloat("iso")<<std::endl;
      //std::cout<<" Cand 2 Leg 1 isolation: "<<t2.leg1()->userFloat("iso")<<std::endl;
      //std::cout<<" Cand 1 Leg 2 isolation: "<<t1.leg2()->userFloat("iso")<<std::endl;
      //std::cout<<" Cand 2 Leg 2 isolation: "<<t2.leg2()->userFloat("iso")<<std::endl;
      if (  (((t1.leg1()->userFloat("iso") ) > (t2.leg1()->userFloat("iso"))) && ((t1.leg1()->userFloat("iso") ) > (t2.leg2()->userFloat("iso"))))){ 
	//std::cout<<"cand 1 Isolation 1: "<<t1.leg1()->userFloat("iso")<<" < cand 2 Isolation 1: "<<t2.leg1()->userFloat("iso")<<std::endl;
	//std::cout<<"cand 1 Isolation 2: "<<t1.leg2()->userFloat("iso")<<" < cand 2 Isolation 2: "<<t2.leg2()->userFloat("iso")<<std::endl;
	return true;
      }
      //check if cand1 leg1 iso is equal to cand2 leg1 iso            and cand1leg1 pt is > cand2leg1pt            and cand1leg1 iso is greater than cand2leg2iso
      else if((t1.leg1()->userFloat("iso")==t2.leg1()->userFloat("iso")) && ( (t1.leg1()->pt()) > (t2.leg1()->pt()) ) && (t1.leg1()->userFloat("iso") > t2.leg2()->userFloat("iso")) 
	      ){
	return true;
      }//check if     cand1 leg1 iso is equal to cand2 leg2 iso            and cand1leg1 pt is > cand2leg2pt            and cand1leg1 iso is greater than cand1leg1iso
      else if((t1.leg1()->userFloat("iso")==t2.leg2()->userFloat("iso")) && ( (t1.leg1()->pt()) > (t2.leg2()->pt()) ) && (t1.leg1()->userFloat("iso") > t2.leg1()->userFloat("iso")) ){
	return true;
      }
      //NOW CHECK if iso equal but second leg is more isolated
      //check if     cand1 leg1 iso is equal to cand2 leg1 iso          and    cand1leg1 pt is > cand2leg1pt        and    cand1leg1 iso is greater than cand2leg2iso
      else if((t1.leg1()->userFloat("iso")==t2.leg1()->userFloat("iso")) && ( (t1.leg1()->pt()) == (t2.leg1()->pt()) ) && (t1.leg1()->userFloat("iso") > t2.leg2()->userFloat("iso")) &&
	      //then check if cand1leg2 is the most isolated
	      (t1.leg2()->userFloat("iso") > t2.leg2()->userFloat("iso"))
	      ){
	return true;
      }//check if     cand1 leg1 iso is equal to cand2 leg2 iso            and cand1leg1 pt is equal cand2leg2pt            and cand1leg1 iso is greater than cand1leg1iso
      else if((t1.leg1()->userFloat("iso")==t2.leg2()->userFloat("iso")) && ( (t1.leg1()->pt()) == (t2.leg2()->pt()) ) && (t1.leg1()->userFloat("iso") > t2.leg1()->userFloat("iso")) &&
	      //then check if cand1leg2 is the most isolated
	      (t1.leg2()->userFloat("iso") > t2.leg1()->userFloat("iso"))
	      ){
	std::cout<<"Returning the correct option"<<std::endl;
	return true;
      }
      /// NOW CHECK the pt of the second leg in addition to the Iso of the second leg
      else if((t1.leg1()->userFloat("iso")==t2.leg1()->userFloat("iso")) && ( (t1.leg1()->pt()) == (t2.leg1()->pt()) ) && (t1.leg1()->userFloat("iso") > t2.leg2()->userFloat("iso")) &&
	      //then check if cand1leg2 is equally isolated but with greater pt
	      (t1.leg2()->userFloat("iso") == t2.leg2()->userFloat("iso")) && (t1.leg2()->pt() > t2.leg2()->pt())
	      ){
	return true;

      }//check if     cand1 leg1 iso is equal to cand2 leg2 iso            and cand1leg1 pt is equal cand2leg2pt            and cand1leg1 iso is greater than cand1leg1iso
      else if((t1.leg1()->userFloat("iso")==t2.leg2()->userFloat("iso")) && ( (t1.leg1()->pt()) == (t2.leg2()->pt()) ) && (t1.leg1()->userFloat("iso") > t2.leg1()->userFloat("iso")) &&
	      //then check if cand1leg2 is equally isolated but with greater pt
	      (t1.leg2()->userFloat("iso") > t2.leg1()->userFloat("iso")) && (t1.leg2()->pt() > t2.leg1()->pt())
	      ){
	return true;
      }
      else {return false;}
      
    } 
  };
  
  // ----------member data ---------------------------
  edm::EDGetTokenT<std::vector<T>>  src_;



};
