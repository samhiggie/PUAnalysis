#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/StringBasedNtupleFiller.h"

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairFiller, "PATMuTauPairFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATGenParticleFiller, "PATGenParticleFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairFiller, "PATEleTauPairFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairFiller, "PATDiTauPairFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuPairFiller, "PATMuPairFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATElePairFiller, "PATElePairFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonFiller, "PATMuonFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATPFMETFiller, "PATPFMETFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMETFiller, "PATMETFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATGenMETFiller, "PATGenMETFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuMuTauTauQuadFiller, "PATMuMuTauTauQuadFiller");

