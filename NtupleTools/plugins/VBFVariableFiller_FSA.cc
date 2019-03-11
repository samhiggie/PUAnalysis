#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/VBFVariableFiller_FSA.h"
#include "Math/GenVector/VectorUtil.h" 

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairVBFVariableFiller_FSA, "PATMuTauPairVBFVariableFiller_FSA");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairVBFVariableFiller_FSA, "PATEleTauPairVBFVariableFiller_FSA");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairVBFVariableFiller_FSA, "PATDiTauPairVBFVariableFiller_FSA");

