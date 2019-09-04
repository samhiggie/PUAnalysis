import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.GlobalTag.globaltag = '102X_upgrade2018_realistic_v12'

process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))
process.options.allowUnscheduled = cms.untracked.bool(True)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)


# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
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
            'HLT_IsoMu27_v',
            'HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v',
            'HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1_v'
            ])




        #EventSelection
process.load("PUAnalysis.Configuration.hTauTau_LTau_Sync_cff")


process.eventSelectionMT = cms.Path(process.selectionSequenceMT)
#process.eventSelectionET = cms.Path(process.selectionSequenceET)

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



from PUAnalysis.Configuration.tools.ntupleTools_LTau import addMuTauEventTree
addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeFinal','muTausOS','diMuonsOSSorted')

#from PUAnalysis.Configuration.tools.ntupleTools_LTau import addEleTauEventTree
#addEleTauEventTree(process,'eleTauEventTree')
#addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','diElectronsOSSorted')

addEventSummary(process,True,'MT','eventSelectionMT')
#addEventSummary(process,True,'ET','eventSelectionET')



# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 20


process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            $inputFileNames
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            )
        )

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

#process.TFileService.fileName=cms.string("$outputFileName")
process.TFileService = cms.Service(
        "TFileService",
        fileName = cms.string("$outputFileName")
        )
