#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/PtJetPairVarFiller.h"
#include "Math/GenVector/VectorUtil.h" 

DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairPtJetPairVarFiller, "PATMuTauPairPtJetPairVarFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairPtJetPairVarFiller, "PATEleTauPairPtJetPairVarFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairPtJetPairVarFiller, "PATDiTauPairPtJetPairVarFiller");


