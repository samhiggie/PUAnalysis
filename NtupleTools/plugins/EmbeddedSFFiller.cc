#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/EmbeddedSFFiller.h"
#include "Math/GenVector/VectorUtil.h" 

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonNuPairEmbeddedSFFiller, "PATMuonNuPairEmbeddedSFFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairEmbeddedSFFiller, "PATMuTauPairEmbeddedSFFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairEmbeddedSFFiller, "PATEleTauPairEmbeddedSFFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuJetPairEmbeddedSFFiller, "PATMuJetPairEmbeddedSFFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuPairEmbeddedSFFiller, "PATMuPairEmbeddedSFFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleMuPairEmbeddedSFFiller, "PATEleMuPairEmbeddedSFFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairEmbeddedSFFiller, "PATDiTauPairEmbeddedSFFiller");



