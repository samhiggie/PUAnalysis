#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/VBFVariableFiller.h"
#include "Math/GenVector/VectorUtil.h" 

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairVBFVariableFiller, "PATMuTauPairVBFVariableFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairVBFVariableFiller, "PATEleTauPairVBFVariableFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairVBFVariableFiller, "PATDiTauPairVBFVariableFiller");


