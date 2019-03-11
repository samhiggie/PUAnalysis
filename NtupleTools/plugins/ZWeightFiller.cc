#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/ZWeightFiller.h"
#include "Math/GenVector/VectorUtil.h" 

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonNuPairZWeightFiller, "PATMuonNuPairZWeightFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairZWeightFiller, "PATMuTauPairZWeightFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairZWeightFiller, "PATEleTauPairZWeightFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuJetPairZWeightFiller, "PATMuJetPairZWeightFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuPairZWeightFiller, "PATMuPairZWeightFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleMuPairZWeightFiller, "PATEleMuPairZWeightFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairZWeightFiller, "PATDiTauPairZWeightFiller");



