#include "PUAnalysis/RecoTools/plugins/PATTauMatchSelector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "PUAnalysis/RecoTools/plugins/DiCandidateSorterByIso.h"

typedef DiCandidateSorterByIso<PATMuTauPair> PATMuTauPairSorterByIso;
typedef DiCandidateSorterByIso<PATElecTauPair> PATEleTauPairSorterByIso;


DEFINE_FWK_MODULE(PATMuTauPairSorterByIso);
DEFINE_FWK_MODULE(PATEleTauPairSorterByIso);
