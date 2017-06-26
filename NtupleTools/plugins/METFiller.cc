#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/METFiller.h"

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairMETFiller, "PATMuTauPairMETFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairMETFiller, "PATEleTauPairMETFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairMETFiller, "PATDiTauPairMETFiller");
