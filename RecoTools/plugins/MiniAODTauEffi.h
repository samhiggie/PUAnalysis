// -*- C++ -*-
//
//

// system include files
#include <memory>
#include <iostream>
#include <vector>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

#include "Math/GenVector/VectorUtil.h"
#include "TMath.h"
//
// class declaration
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


// Short alias for this namespace
namespace js = boost::property_tree;

class MiniAODTauEffi : public edm::EDProducer {
   public:
  


       explicit MiniAODTauEffi(const edm::ParameterSet& iConfig):
           src_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("src"))),
           prunedGenToken_(consumes<reco::GenParticleCollection >(iConfig.getParameter<edm::InputTag>("pruned"))),
           names(iConfig.getParameter<std::vector<std::string>>("wps")),
           jsonname(iConfig.getParameter<std::string>("jsonname")),
           data_(iConfig.getParameter<bool>("data"))
           {

               //Get the Json! 
               std::string base = std::getenv("CMSSW_BASE");
               std::string fpath =   "/src/PUAnalysis/Configuration/data/";
               std::string file = base+fpath+jsonname;

               //load the json
               js::read_json(file, json);

               produces<pat::TauCollection>();
           }

       ~MiniAODTauEffi() {}
   private:


       virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
       {
           using namespace edm;
           using namespace reco;
           std::unique_ptr<pat::TauCollection> out(new pat::TauCollection);
           Handle<pat::TauCollection > cands;

           Handle<reco::GenParticleCollection> pruned;
           iEvent.getByToken(prunedGenToken_,pruned);



           if(iEvent.getByToken(src_,cands)) 
               for(unsigned int  i=0;i!=cands->size();++i){
                   pat::Tau tau = cands->at(i);
                   float pt = tau.pt();

                   std::vector<std::string> namesUserFloat = names;
                   std::vector<std::string> namesJson = names;
                   if (!data_){
                       bool match = matched(tau.p4(),*pruned);
                       if (!match){
                           for (unsigned int i=0; i<names.size();i++){
                               std::string faketau = "Fake"+names[i];
                               namesJson[i]=faketau;
                           }
                       }
                   }
                   std::vector<std::string> vars = {"m0","sigma","alpha","n","norm"};
                   std::vector<float> mode;
                   for (unsigned int i=0; i<names.size();i++){
                       mode.clear();
                       for (unsigned int v=0; v<vars.size();v++){
                           std::string get= namesJson[i]+"."+vars[v];
                           mode.push_back(json.get<float>(get));
                       }
                       float value = -999;
                       if (!data_) value = __crystalball_fit(pt,mode);
                       tau.addUserFloat(namesUserFloat[i],value);
                   }

                   out->push_back(tau);
               }
	   iEvent.put(std::move(out),"");    
       } 

       // ----------member data ---------------------------
       edm::EDGetTokenT<pat::TauCollection> src_;
       edm::EDGetTokenT<reco::GenParticleCollection> prunedGenToken_;
       std::vector<std::string> names;
       std::string jsonname;
       js::ptree json;
       bool data_;

       bool matched(const reco::Candidate::LorentzVector& direction, const reco::GenParticleCollection& genParticles){
           for ( reco::GenParticleCollection::const_iterator genParticle = genParticles.begin();
                   genParticle != genParticles.end(); ++genParticle ){
               if (abs(genParticle->pdgId())==15 && reco::deltaR(direction, genParticle->p4())<0.5) 
                   return true;
           }
           return false;
       } 


       float __crystalball_fit(float x, std::vector<float> mode ){
           float m0 = mode[0];
           float sigma = mode[1];
           float alpha = mode[2];
           float n = mode[3];
           float norm = mode[4];

           float sqrtPiOver2 = TMath::Sqrt(TMath::PiOver2());
           float sqrt2 = TMath::Sqrt(2.);
           float sig = std::abs(sigma);
           float t = (x-m0)/sig * alpha/std::abs(alpha);
           float absAlpha = std::abs(alpha/sig);
           float a =  TMath::Power(n/absAlpha,n) * TMath::Exp(-0.5*absAlpha*absAlpha);
           float b = absAlpha - n/absAlpha;
           float arg = absAlpha/sqrt2;
           float ApproxErf = 1.;

           if (arg>5.) ApproxErf = 1.;
           else if (arg<-5.) ApproxErf = -1.;
           else  ApproxErf = TMath::Erf(arg);

           float nm1 = n -1;
           float  leftArea = (1.+ApproxErf)*sqrtPiOver2;
           float  rightArea = (a*1./TMath::Power(absAlpha-b,nm1))/(nm1);
           float  area = leftArea+rightArea;
           if (t<= absAlpha){
               arg = t/sqrt2;
               if (arg>5.) ApproxErf = 1.;
               else if (arg<-5.) ApproxErf = -1.;
               else ApproxErf = TMath::Erf(arg);
               float val = norm * (1.+ApproxErf)*sqrtPiOver2/area;
               return val;
           }
           else {
               float val= norm * (leftArea + a * (1./TMath::Power(t-b,nm1) -
                           1./TMath::Power(absAlpha-b,nm1))/(1-n))/area;
               return val; 
           }
           return 0;
       }


};

