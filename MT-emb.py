import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.GlobalTag.globaltag = '102X_dataRun2_Sep2018Rereco_v1'

process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))
process.options.allowUnscheduled = cms.untracked.bool(True)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        ##'/store/user/jbechtel/gc_storage/TauTau_data_2018ABC_CMSSW1020/TauEmbedding_TauTau_data_2018ABC_CMSSW1020_Run2018A/99/merged_9798.root '
        '/store/user/jbechtel/gc_storage/MuTau_data_2018ABC_CMSSW1020/TauEmbedding_MuTau_data_2018ABC_CMSSW1020_Run2018A/39/merged_17738.root'
		),
		inputCommands=cms.untracked.vstring(
						'keep *',
						'keep *_l1extraParticles_*_*',
		)
)

import FWCore.PythonUtilities.LumiList as LumiList #check lumilist name, not sure it matches to golden
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/hep.wisc.edu/home/samuellh/WorkingArea/HTT/CMSSW_10_2_14/src/PUAnalysis/Configuration/data/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt').getVLuminosityBlockRange() 
process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/hep.wisc.edu/home/samuellh/WorkingArea/HTT/mutau2018/src/PUAnalysis/Configuration/python/2018_JSON.txt').getVLuminosityBlockRange() 
#import Configuration.2018_JSON as json
#process = json.myLumiList(process)

#Default Reconstruction from the analysTools.py config file
#The main 'setup' processes can be found in "defaultReconstruction" and "defaultReconstructionMC"
#analysisTools takes care of pre-selections, adding in extra ID's that do not come in the miniAOD
#files and embedding trigger matching (the trigger for di-Tau hadronic still should be added and checked)
#defaultRecontruction and defaultReconstructionMC are generic enough to work for any final state
#needed: muTau, tauTau, eTau, mumuTauTau, ect. However, different analyses may want to embed
#different ID's, isolations, ect. Trigger paths are input below. These plugins are typically
#found in RecoTools/plugins/
from PUAnalysis.Configuration.tools.analysisTools_LTau import *
defaultReconstructionEMB(process,'HLT',
                         [
                          'HLT_Mu17_TkMu8',
                          'HLT_Mu17_Mu8' 
                          ],
                         HLT = 'TriggerResults',
                         triggerFilter='SIMembedding')

#defaultReconstructionEMB(process,'HLT',
#                         [
#                          'HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v',
#                          'HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v',
#                          'HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v'       
#                          ])
#EventSelection
#Most of the selections for the analysis go in hTauTau_cff
#The selections proceed sequentially, each time a "di-candidate pair" fails a cut in
#this configuration then the sequence will start over with another di-candidate pair.
#The final 'sorting' is implemented there as well, either by di-tau PT or isolation.
process.load("PUAnalysis.Configuration.hTauTau_LTau_Sync_cff")

process.metCalibration.applyCalibration = cms.bool(False)

process.eventSelectionMT = cms.Path(process.selectionSequenceMT)

from PUAnalysis.Configuration.tools.ntupleTools_LTau import addMuTauEventTree

addMuTauEventTree(process,'muTauEventTree','muTausSync','diMuonsOSSorted',isEmbedded=True)

addEventSummary(process,True,'MT','eventSelectionMT')

