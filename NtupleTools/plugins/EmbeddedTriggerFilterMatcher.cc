#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/EmbeddedTriggerFilterMatcher.h"
#include "Math/GenVector/VectorUtil.h" 

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonNuPairEmbeddedTriggerFilterMatcher, "PATMuonNuPairEmbeddedTriggerFilterMatcher");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairEmbeddedTriggerFilterMatcher, "PATMuTauPairEmbeddedTriggerFilterMatcher");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairEmbeddedTriggerFilterMatcher, "PATEleTauPairEmbeddedTriggerFilterMatcher");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuJetPairEmbeddedTriggerFilterMatcher, "PATMuJetPairEmbeddedTriggerFilterMatcher");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuPairEmbeddedTriggerFilterMatcher, "PATMuPairEmbeddedTriggerFilterMatcher");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleMuPairEmbeddedTriggerFilterMatcher, "PATEleMuPairEmbeddedTriggerFilterMatcher");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairEmbeddedTriggerFilterMatcher, "PATDiTauPairEmbeddedTriggerFilterMatcher");



