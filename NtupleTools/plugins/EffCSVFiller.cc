#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/EffCSVFiller.h"

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairEffCSVFiller, "PATMuTauPairEffCSVFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairEffCSVFiller, "PATEleTauPairEffCSVFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairEffCSVFiller, "PATDiTauPairEffCSVFiller");
