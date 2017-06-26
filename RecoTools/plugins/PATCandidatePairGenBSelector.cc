#include "PUAnalysis/RecoTools/plugins/PATCandidatePairGenBSelector.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"


typedef PATCandidatePairGenBSelector<pat::Muon, pat::Tau> PATMuTauGenBJetSel;


DEFINE_FWK_MODULE(PATMuTauGenBJetSel);
