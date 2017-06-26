/*
 * Copied from TauAnalysis/RecoTools
 *
 */
#include "PUAnalysis/RecoTools/interface/ParticleAntiOverlapSelector.h"

#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"

typedef ObjectSelector<ParticleAntiOverlapSelector<reco::CaloJet> > UWCaloJetAntiOverlapSelector;
typedef ObjectSelector<ParticleAntiOverlapSelector<reco::PFJet> > UWPFJetAntiOverlapSelector;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(UWCaloJetAntiOverlapSelector);
DEFINE_FWK_MODULE(UWPFJetAntiOverlapSelector);
