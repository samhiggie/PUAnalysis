import os
import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))
process.options.allowUnscheduled = cms.untracked.bool(True)


process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v7'


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:pickevents/pickevents1.root',
        'file:pickevents/pickevents2.root'
        #'file:pickevents/pickevents3.root',
        #'file:pickevents/pickevents4.root',
        #'file:pickevents/pickevents5.root',
        #'file:pickevents/pickevents6.root',
        #'file:pickevents/pickevents7.root',
        #'file:pickevents/pickevents8.root',
        #'file:pickevents/pickevents9.root',
        #'file:pickevents/pickevents10.root',
        #'file:pickevents/pickevents11.root',
        #'file:pickevents/pickevents12.root',
        #'file:pickevents/pickevents13.root',
        #'file:pickevents/pickevents14.root',
        #'file:pickevents/pickevents15.root'
        #'/store/data/Run2016B/Tau/MINIAOD/23Sep2016-v3/00000/0004DF01-8099-E611-8C1C-0242AC130003.root'
		),
		inputCommands=cms.untracked.vstring(
						'keep *',
						'keep *_l1extraParticles_*_*',
		)
)

#import FWCore.PythonUtilities.LumiList as LumiList
from PUAnalysis.Configuration.JSONBtoH import myLumiList
myLumiList(process);


from PUAnalysis.Configuration.tools.analysisToolsHTauTau_WIP import *

defaultReconstruction(process,'HLT',
                      [
			'HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v',
                        'HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v'
                      ])

#EventSelection
process.load("PUAnalysis.Configuration.hTauTauHadronicEmu_cff")
#process.metCalibration.applyCalibration = cms.bool(False)

process.eventSelectionTT = cms.Path(process.selectionSequenceTT)

from PUAnalysis.Configuration.tools.ntupleToolsHTauTau_WIP import addDiTauEventTree

addDiTauEventTree(process,'diTauEventTree','diTausSync',triggerCollection='HLT')
addDiTauEventTree(process,'diTauEventTreeFinal','diTausSyncTrig',triggerCollection='HLT')

addEventSummary(process,True,'TT','eventSelectionTT')


