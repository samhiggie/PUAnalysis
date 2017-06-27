#include "PUAnalysis/RecoTools/plugins/SmearedTauProducer.h"

SmearedTauProducer::SmearedTauProducer(const edm::ParameterSet& iConfig):
    src_(consumes<std::vector<pat::Tau> >(iConfig.getParameter<edm::InputTag>("src"))),  
    smearConstituents_(iConfig.getParameter<bool>("smearConstituents")),  
    hadronEnergyScale_(iConfig.getParameter<double>("hadronEnergyScale")),
    gammaEnergyScale_(iConfig.getParameter<double>("gammaEnergyScale")),
    oneProngEnergyScale_(iConfig.getParameter<double>("oneProngEnergyScale")),
    oneProngPi0EnergyScale_(iConfig.getParameter<double>("oneProngPi0EnergyScale")),
    threeProngEnergyScale_(iConfig.getParameter<double>("threeProngEnergyScale"))
    {
      smearingModule = new SmearedParticleMaker<pat::Tau,GenJetRetriever<pat::Tau> >(iConfig);
      produces<std::vector<pat::Tau> >();
    }


SmearedTauProducer::~SmearedTauProducer()
{}

void 
SmearedTauProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    //std::cout << "<SmearedTauProducer::produce>:" << std::endl;
    //std::cout << "(label = " << moduleLabel_ << ")" << std::endl;

    using namespace edm;
    using namespace reco;

    std::unique_ptr<std::vector<pat::Tau> > out(new std::vector<pat::Tau> );
    Handle<std::vector<pat::Tau> > srcH;

    //std::cout<<"1prong: "<<oneProngEnergyScale_<<" 1prongpi0 "<<oneProngPi0EnergyScale_<<" 3prong "<<threeProngEnergyScale_<<std::endl;
    if(iEvent.getByToken(src_,srcH) &&srcH->size()>0) 
      for(unsigned int i=0;i<srcH->size();++i) {
	pat::Tau object = srcH->at(i);
	//std::cout << " original object(" << i << "): Pt = " << object.pt() << "," 
	//	    << " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;

	smearingModule->smear(object);

	//smearing by decay mode
	math::XYZTLorentzVector vToSmear;
	vToSmear = object.p4();
	float decayModeES = 1.0;
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

	//std::cout<<"decayMode "<< object.decayMode()<<" decayModeES "<<decayModeES<<std::endl;


        if(smearConstituents_) {
	  math::XYZTLorentzVector hadronLV;
	  const std::vector<edm::Ptr<reco::PFCandidate> > hadrons = object.signalPFChargedHadrCands();

	  if(hadrons.size()>0)
	    for(unsigned int i=0;i<hadrons.size();++i)
	      hadronLV+=hadrons.at(i)->p4();
	  //apply hadron energy scale
	  hadronLV=hadronEnergyScale_*hadronLV;
	  math::XYZTLorentzVector gammaLV;
	  const std::vector<edm::Ptr<reco::PFCandidate> > gammas = object.signalPFGammaCands();

	  if(gammas.size()>0)
	    for(unsigned int i=0;i<gammas.size();++i)
	      gammaLV+=gammas.at(i)->p4();
	  gammaLV=gammaEnergyScale_*gammaLV;
 	  object.setP4(gammaLV+hadronLV);
	}
	
	//std::cout << "smeared object(" << i << "): Pt = " << object.pt() << "," 
	//	    << " eta = " << object.eta() << ", phi = " << object.phi() << std::endl;

	out->push_back(object);
      }
    iEvent.put(std::move(out),"");    
} 




#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(SmearedTauProducer);
