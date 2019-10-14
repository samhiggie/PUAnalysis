#include "PUAnalysis/RecoTools/plugins/ESTauProducerMET.h"

/*
   Decay mode Tau Momentum scaling vs Tau pT
   1-prong no-pi0 no correction
   1-prong 1-pi0 p4' = p4 * (1.015 + 0.001 * TMath::Min(TMath::Max(pT-45.,0.),10.)
   3-prong p4' = p4 * (1.012 + 0.001 * TMath::Min(TMath::Max(pT-32.,0.),18.) 
   */

ESTauProducerMET::ESTauProducerMET(const edm::ParameterSet& iConfig):
	smearConstituents_(iConfig.getParameter<bool>("smearConstituents")),
	src_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("src"))), 
	met_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("srcMET"))), 
	genParticles_(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"))),
	data_(iConfig.getParameter<bool>("data")),
	oneProngEnergyScale_(iConfig.getParameter<double>("oneProngEnergyScale")),
	oneProngPi0EnergyScale_(iConfig.getParameter<double>("oneProngPi0EnergyScale")),
	threeProngEnergyScale_(iConfig.getParameter<double>("threeProngEnergyScale"))
{
	smearingModule = new SmearedParticleMaker<pat::Tau,GenJetRetriever<pat::Tau> >(iConfig);
	produces<std::vector<pat::Tau> >();
	produces<pat::METCollection >();
}


ESTauProducerMET::~ESTauProducerMET()
{}

void 
ESTauProducerMET::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

	//std::cout << "<ESTauProducerMET::produce>:" << std::endl;

	using namespace edm;
	using namespace reco;

	edm::Handle<pat::TauCollection > srcH;

	edm::Handle<reco::GenParticleCollection> genParticleCollection;

	bool tauPresent = false;    
	bool genParticlesPresent = false;     
	math::XYZTLorentzVector originalVector;	    
	math::XYZTLorentzVector smearedVector;	    

	/*
	if(!data_)
	  if(iEvent.getByToken(genParticles_,genParticleCollection)){
	    ////first check if there is a tau somewhere in the collection
	    genParticlesPresent=true;
	    for(unsigned int j=0; j < genParticleCollection->size();j++){
	      if(abs(genParticleCollection->at(j).pdgId())==15){
		tauPresent=true;
		break;
	      }
	    }
	  }
	*/
	if(iEvent.getByToken(src_,srcH)) 
	  for(unsigned int i=0;i<srcH->size();++i) {
	    
	    pat::Tau object = srcH->at(i);
	    //std::cout << " original object(" << i << "): Pt = " << object.pt()<< " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;
	    if(!data_){
	      smearingModule->smear(object);
	      /*
		float initialpt = object.pt();
		float initialpx = object.px();
		float initialpy = object.py();
		float initialpz = object.pz();
		float initialeta = object.eta();
		float initialphi = object.phi();
		float initialMass = object.mass();
		object.addUserFloat("preESMass",initialMass);
		object.addUserFloat("preESpt",initialpt);
		object.addUserFloat("preESpx",initialpx);
		object.addUserFloat("preESpy",initialpy);
		object.addUserFloat("preESpz",initialpz);
		object.addUserFloat("preESeta",initialeta);
		object.addUserFloat("preESphi",initialphi);
	      */
	      
	      math::XYZTLorentzVector finalP4 = object.p4();
	      if(object.userInt("gen_match")==5){
		  math::XYZTLorentzVector vToSmear;
		  vToSmear = object.p4();
		  float decayModeES = 1.0;

		  object.setP4(finalP4);
		  originalVector += finalP4;
		  switch(object.decayMode()){
		  case(0):
		    decayModeES = oneProngEnergyScale_;
		    object.setP4(vToSmear*decayModeES);	
		    object.setMass(0.1395699);
		    break;
		  case(1):
		    decayModeES = oneProngPi0EnergyScale_;
		    object.setP4(vToSmear*decayModeES);	
		    break;
		  case(2):// this is a neglible contribution
		    decayModeES = oneProngPi0EnergyScale_;
		    object.setP4(vToSmear*decayModeES);	
		    break;
		  case(10):
		    decayModeES = threeProngEnergyScale_;
		    object.setP4(vToSmear*decayModeES);	
		    break;
		  }
		  smearedVector += object.p4();

		  //std::cout << "smeared object(" << i << ") : decay mode = " << object.decayMode() <<" : Pt = " << object.pt() << " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;
	      }
	      

	    }	      
	  }
	
	// now for the met
	std::unique_ptr<pat::METCollection > outMET(new pat::METCollection);
	Handle<pat::METCollection> srcMET;
  
	if(iEvent.getByToken(met_,srcMET)) 
	  for(unsigned int i=0;i<srcMET->size();++i) {
	    pat::MET  met = srcMET->at(i);
	    math::XYZTLorentzVector unclustered =-met.p4()-originalVector;
	    //std::cout<<"oldMET: "<<met.pt()<<std::endl;
	    //std::cout<<"original.pt(), smeared.pt(), diff"<<originalVector.pt()<<", "<<smearedVector.pt()<<", "<<originalVector.pt()-smearedVector.pt()<<std::endl;
	    math::XYZTLorentzVector newMET = -(unclustered+smearedVector);
	    //std::cout<<"newMET: "<<newMET.pt()<<std::endl;
	    met.setP4(math::XYZTLorentzVector(newMET.px(),newMET.py(),0.0,sqrt(newMET.px()*newMET.px()+newMET.py()*newMET.py())));
	    outMET->push_back(met);
    }
	
	iEvent.put(std::move(outMET),"");    


}




#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(ESTauProducerMET);
