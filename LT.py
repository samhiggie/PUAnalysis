import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.GlobalTag.globaltag = '94X_dataRun2_v6'

process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))
process.options.allowUnscheduled = cms.untracked.bool(True)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)


# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:singleMu.root'
        #'/store/data/Run2017B/SingleMuon/MINIAOD/17Nov2017-v1/40000/0021369B-9BD8-E711-BFE9-FA163EAA42CB.root'
        #"/store/data/Run2016D/SingleMuon/MINIAOD/PromptReco-v2/000/276/384/00000/AAEA15A0-FE46-E611-A7BA-02163E012368.root"
        #'file:event-21753.root'
        #'/store/mc/RunIISummer17MiniAOD/VBFHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/92X_upgrade2017_realistic_v10-v2/50000/02098EBB-029C-E711-8FED-441EA1714E4C.root'
		),
		inputCommands=cms.untracked.vstring(
						'keep *',
						'keep *_l1extraParticles_*_*',
		)
)


import FWCore.PythonUtilities.LumiList as LumiList #check lumilist name, not sure it matches to golden
process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt').getVLuminosityBlockRange() 


#added in etau and mutau triggers
from PUAnalysis.Configuration.tools.analysisTools_LTau import *
defaultReconstruction(process,'HLT',
        [
            'HLT_IsoMu20_v11',
            'HLT_IsoMu24_eta2p1_v',
            'HLT_IsoMu24_v', 
            'HLT_IsoTkMu24_v', 
            'HLT_IsoMu27_v',
            'HLT_IsoMu19_eta2p1_LooseIsoPFTau20_v',
            'HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v',
            'HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v'
            ])




        #EventSelection
process.load("PUAnalysis.Configuration.hTauTau_LTau_cff")


process.eventSelectionMT = cms.Path(process.selectionSequenceMT)
process.eventSelectionET = cms.Path(process.selectionSequenceET)


from PUAnalysis.Configuration.tools.ntupleTools_LTau import addMuTauEventTree
addMuTauEventTree(process,'muTauEventTree')
addMuTauEventTree(process,'muTauEventTreeFinal','muTausOS','diMuonsOSSorted')

from PUAnalysis.Configuration.tools.ntupleTools_LTau import addEleTauEventTree
addEleTauEventTree(process,'eleTauEventTree')
addEleTauEventTree(process,'eleTauEventTreeFinal','eleTausOS','diElectronsOSSorted')

addEventSummary(process,True,'MT','eventSelectionMT')
addEventSummary(process,True,'ET','eventSelectionET')



