#include "PUAnalysis/RecoTools/plugins/MiniAODTriggerMatcher.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef MiniAODTriggerMatcher<pat::Muon> MuonTriggerMatcherMiniAOD;
typedef MiniAODTriggerMatcher<pat::Tau> TauTriggerMatcherMiniAOD;
typedef MiniAODTriggerMatcher<pat::Electron> ElectronTriggerMatcherMiniAOD;

DEFINE_FWK_MODULE(MuonTriggerMatcherMiniAOD);
DEFINE_FWK_MODULE(ElectronTriggerMatcherMiniAOD);
DEFINE_FWK_MODULE(TauTriggerMatcherMiniAOD);

