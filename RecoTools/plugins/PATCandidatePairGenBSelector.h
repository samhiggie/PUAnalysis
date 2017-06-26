#ifndef PUAnalysis_RecoTools_PATCandGenBSelector_h
#define PUAnalysis_RecoTools_PATCandGenBSelector_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "PUAnalysis/RecoTools/interface/FetchCollection.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"

#include "PUAnalysis/RecoTools/interface/candidateAuxFunctions.h"
#include "PUAnalysis/RecoTools/interface/generalAuxFunctions.h"

template<typename T1, typename T2>
class PATCandidatePairGenBSelector : public edm::EDProducer
{
  typedef edm::Ptr<T1> T1Ptr;
  typedef edm::Ptr<T2> T2Ptr;
  typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;
  typedef std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > CompositePtrCandidateCollection;

 public:

  explicit PATCandidatePairGenBSelector(const edm::ParameterSet& cfg)
  {
    src_     = cfg.getParameter<edm::InputTag>("src");
    srcPV_       =  cfg.getParameter<edm::InputTag>("srcPrimaryVertex") ;
    genBs_       =  cfg.getParameter<edm::InputTag>("genParticles") ;
    jets_       =  cfg.getParameter<edm::InputTag>("jets") ;

//     label_ = cfg.getParameter<std::string>("resultLabel");
// 
//     printf("Will use NSV FIt\n");
//     edm::ParameterSet cfg_config = cfg.getParameter<edm::ParameterSet>("config");
//     edm::ParameterSet cfg_event = cfg_config.getParameter<edm::ParameterSet>("event");

    //edm::ParameterSet cfg_algorithm = cfg.getParameter<edm::ParameterSet>("algorithm");
    //cfg_algorithm.addParameter<edm::ParameterSet>("event", cfg_event);
    //std::string pluginType = cfg_algorithm.getParameter<std::string>("pluginType");
    //algorithm_ = NSVfitAlgorithmPluginFactory::get()->create(pluginType, cfg_algorithm);

    produces<CompositePtrCandidateCollection>();
  }

  ~PATCandidatePairGenBSelector(){}

  void beginJob()
  {

  }


  void produce(edm::Event& evt, const edm::EventSetup& es) {
    std::cout<<" Gets to BSelector\n"<<std::endl;
    std::auto_ptr<CompositePtrCandidateCollection> out(new CompositePtrCandidateCollection);
    edm::Handle<pat::JetCollection > jets;
    edm::Handle<reco::GenParticleCollection > genBs;
    edm::Handle<std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > > cands;
    pat::JetCollection MatchedJets;

    if(evt.getByLabel(src_,cands)) {

      for (unsigned int i=0;i<cands->size();++i) {
	CompositePtrCandidateT1T2MEt<T1,T2> compositePtrCandidate = cands->at(i);
	//std::cout<<"Here0"<<std::endl;
	if(evt.getByLabel(genBs_,genBs)) 
	  for(unsigned int  k=0;k!=genBs->size();++k){
	    const reco::GenParticle & p = (*genBs)[k];
	    //double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass(), energy=p.E();
	    //reco::Candidate::PolarLorentzVector b(mass,pt,eta,phi,energy);
	    //std::cout<<"Here1"<<std::endl;
	    const reco::Candidate * mom = p.mother();
	    if(abs(p.pdgId())==5&&mom->pdgId()==25)
	      if(evt.getByLabel(jets_,jets)) 
		for(unsigned int  j=0;j!=jets->size();++j){
		  //std::cout<<"Here2"<<std::endl;
		  pat::Jet jet = jets->at(j);
		  if(ROOT::Math::VectorUtil::DeltaR(p.p4(),jet.p4())<0.5){
		    MatchedJets.push_back(jet);
		  }
		}
	  }
      
	if(MatchedJets.size()>1){
	  pat::Jet highBJet = MatchedJets.at(0);
	  pat::Jet secondBJet = MatchedJets.at(1);
	  compositePtrCandidate.setJJVariables(highBJet.p4()+secondBJet.p4());
	  compositePtrCandidate.setMatchedBJets(highBJet,secondBJet);
	  //std::cout << "Matched JJ Mass:"<< (highBJet.p4()+secondBJet.p4()).M() << " Pt: "<<(highBJet.p4()+secondBJet.p4()).pt() <<" Eta: "<<(highBJet.p4()+secondBJet.p4()).eta()<<" Phi: "<< (highBJet.p4()+secondBJet.p4()).phi()<<" highBjetpt"<<highBJet.pt() <<std::endl;    
	}
	else{
	  reco::Candidate::LorentzVector b(-5,-5,-5,-5);
	  compositePtrCandidate.setJJVariables(b);
	}
	out->push_back(compositePtrCandidate);
	
      }
    }

    evt.put(out);
  }


 private:
  edm::InputTag src_;
  edm::InputTag jets_;
  edm::InputTag genBs_;
  edm::InputTag srcPV_;
  std::string label_;
  typedef std::vector<int> vint;

};


#endif
