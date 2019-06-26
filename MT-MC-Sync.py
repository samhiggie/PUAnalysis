import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

#process.GlobalTag.globaltag = '94X_mc2017_realistic_v15'
process.GlobalTag.globaltag = '100X_upgrade2018_realistic_v10'


process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))
process.options.allowUnscheduled = cms.untracked.bool(True)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)


# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
                #"/store/mc/RunIIFall17MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/RECOSIMstep_94X_mc2017_realistic_v10-v1/00000/0293A280-B5F3-E711-8303-3417EBE33927.root"
                #"/store/mc/RunIIFall17MiniAODv2/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/D092A5CA-B343-E811-96EB-002590E7D7C2.root"
                "/store/mc/RunIIAutumn18MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v1/110000/CA6B3CD3-D2D5-784D-B2F9-78770C9E4BD9.root"
		),
		inputCommands=cms.untracked.vstring(
						'keep *',
						'keep *_l1extraParticles_*_*',
		)
)



#added in etau and mutau triggers
from PUAnalysis.Configuration.tools.analysisTools_LTau import *
defaultReconstructionMC(process,'HLT',
        [
            'HLT_IsoMu24_v',
            'HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v',
            'HLT_Ele32_WPTight_Gsf_v',
            'HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v'
            ])




        #EventSelection
process.load("PUAnalysis.Configuration.hTauTau_LTau_Sync_cff")


process.eventSelectionMT = cms.Path(process.selectionSequenceMT)

createGeneratedParticles(process,
        'genDaughters',
        [
            "keep++ pdgId = {Z0}",
            "keep pdgId = {tau+}",
            "keep pdgId = {tau-}",
            "keep pdgId = {mu+}",
            "keep pdgId = {mu-}",
            "keep pdgId = 6",
            "keep pdgId = -6",
            "keep pdgId = 11",
            "keep pdgId = -11",
            "keep pdgId = 25",
            "keep pdgId = 35",
            "keep pdgId = 37",
            "keep pdgId = 36"
            ]
        )


createGeneratedParticles(process,
        'genTauCands',
        [
            "keep pdgId = {tau+} & mother.pdgId()= {Z0}",
            "keep pdgId = {tau-} & mother.pdgId() = {Z0}"
            ]
        )


fileout = 'analysis_mutau.root'
from PUAnalysis.Configuration.tools.ntupleTools_LTau import addMuTauEventTree
addMuTauEventTree(process,'muTauEventTree','muTausSync',fileout,'diMuonsOSSorted')


addEventSummary(process,True,'MT','eventSelectionMT',fileout)



