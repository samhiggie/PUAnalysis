#ifndef PUAnalysis_RecoTools_DiCandidatePairProducer_h
#define PUAnalysis_RecoTools_DiCandidatePairProducer_h

#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "DataFormats/Common/interface/RefVector.h"

#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleElementCollectionSelector.h"

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/PatCandidates/interface/Muon.h" 
#include "DataFormats/PatCandidates/interface/Tau.h" 


typedef CompositePtrCandidateT1T2MEtProducer<reco::Candidate, reco::Candidate> DiCandidatePairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<pat::Jet, pat::Jet> PATJetPairProducer;
typedef CompositePtrCandidateT1T2MEtProducer<pat::Muon, pat::Tau> PATMuTauPairProducer;
typedef CompositePtrCandidateT1T2MEtProducer<pat::Muon, pat::Muon> PATMuPairProducer;
typedef CompositePtrCandidateT1T2MEtProducer<pat::Electron, pat::Electron> PATElePairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<pat::Electron, pat::Muon> PATEleMuPairProducer;
typedef CompositePtrCandidateT1T2MEtProducer<pat::Electron, pat::Tau> PATEleTauPairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<pat::Electron, reco::RecoEcalCandidate> PATEleSCPairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<pat::Muon, reco::RecoChargedCandidate> PATMuTrackPairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<pat::Muon, pat::Jet> PATMuJetPairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<pat::Electron,reco::RecoChargedCandidate> PATEleTrackPairProducer;
typedef CompositePtrCandidateT1T2MEtProducer<pat::Tau,pat::Tau> PATDiTauPairProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATJetPair> PATMuMuJJQuadProducer; ///IO
//typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATMuTauPair> PATMuMuMuTauQuadProducer;
typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATDiTauPair> PATMuMuTauTauQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATElecTauPair> PATMuMuEleTauQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATElecMuPair> PATMuMuEleMuQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATElecPair> PATMuMuEleEleQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATMuPair,PATMuPair> PATMuMuMuMuQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATElecPair,PATElecTauPair> PATEleEleEleTauQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATElecPair,PATDiTauPair> PATEleEleTauTauQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATElecPair,PATElecPair> PATEleEleEleEleQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATElecPair,PATMuTauPair> PATEleEleMuTauQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATElecPair,PATElecMuPair> PATEleEleEleMuQuadProducer;
//typedef CompositePtrCandidateT1T2MEtProducer<PATElecPair,PATMuPair> PATEleEleMuMuQuadProducer;




#endif
