// system include files
#include <memory>
#include "PUAnalysis/RecoTools/interface/SmearedParticleMaker.h"

class SmearedTauProducer : public edm::EDProducer  {
 public:
  explicit SmearedTauProducer(const edm::ParameterSet& iConfig);
  ~SmearedTauProducer();
    
 private:
  void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);

  
  // ----------member data ---------------------------
  edm::EDGetTokenT<std::vector<pat::Tau> > src_;           //input Collection
  bool smearConstituents_;
  double hadronEnergyScale_;
  double gammaEnergyScale_;
  double oneProngEnergyScale_;
  double oneProngPi0EnergyScale_;
  double threeProngEnergyScale_;

  SmearedParticleMaker<pat::Tau,GenJetRetriever<pat::Tau> > *smearingModule;
  
};



 

