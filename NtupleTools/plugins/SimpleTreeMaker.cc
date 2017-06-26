#include "FWCore/Framework/interface/MakerMacros.h"
#include "PUAnalysis/NtupleTools/plugins/SimpleTreeMaker.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEtFwd.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"


typedef SimpleTreeMaker<pat::Tau> PATTauTree;


DEFINE_FWK_MODULE(PATTauTree);

