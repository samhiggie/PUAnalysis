#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/PtJetVarFiller.h"
#include "Math/GenVector/VectorUtil.h" 

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairPtJetVarFiller, "PATMuTauPairPtJetVarFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairPtJetVarFiller, "PATEleTauPairPtJetVarFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairPtJetVarFiller, "PATDiTauPairPtJetVarFiller");



