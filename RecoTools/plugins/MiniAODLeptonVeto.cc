#include "PUAnalysis/RecoTools/plugins/MiniAODLeptonVeto.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"


typedef MiniAODLeptonVeto<pat::Muon, pat::Tau> PATMuTauLVeto;
typedef MiniAODLeptonVeto<pat::Electron, pat::Tau> PATElecTauLVeto;
typedef MiniAODLeptonVeto<pat::Tau, pat::Tau> PATDiTauLVeto;



DEFINE_FWK_MODULE(PATMuTauLVeto);
DEFINE_FWK_MODULE(PATElecTauLVeto);
DEFINE_FWK_MODULE(PATDiTauLVeto);

