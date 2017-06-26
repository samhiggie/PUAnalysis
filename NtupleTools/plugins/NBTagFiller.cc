#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/NBTagFiller.h"

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairNBTagFiller, "PATMuTauPairNBTagFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairNBTagFiller, "PATEleTauPairNBTagFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairNBTagFiller, "PATDiTauPairNBTagFiller");
