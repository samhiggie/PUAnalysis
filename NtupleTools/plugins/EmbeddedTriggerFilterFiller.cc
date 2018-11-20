#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/EmbeddedTriggerFilterFiller.h"
#include "Math/GenVector/VectorUtil.h" 

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonNuPairEmbeddedTriggerFilterFiller, "PATMuonNuPairEmbeddedTriggerFilterFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairEmbeddedTriggerFilterFiller, "PATMuTauPairEmbeddedTriggerFilterFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairEmbeddedTriggerFilterFiller, "PATEleTauPairEmbeddedTriggerFilterFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuJetPairEmbeddedTriggerFilterFiller, "PATMuJetPairEmbeddedTriggerFilterFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuPairEmbeddedTriggerFilterFiller, "PATMuPairEmbeddedTriggerFilterFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleMuPairEmbeddedTriggerFilterFiller, "PATEleMuPairEmbeddedTriggerFilterFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairEmbeddedTriggerFilterFiller, "PATDiTauPairEmbeddedTriggerFilterFiller");



