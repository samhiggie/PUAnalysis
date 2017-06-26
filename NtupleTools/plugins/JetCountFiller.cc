#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/JetCountFiller.h"

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairJetCountFiller, "PATDiTauPairJetCountFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairJetCountFiller, "PATMuTauPairJetCountFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairJetCountFiller, "PATEleTauPairJetCountFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuMuTauTauQuadJetCountFiller, "PATMuMuTauTauQuadJetCountFiller");


