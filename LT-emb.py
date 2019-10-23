import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.GlobalTag.globaltag = '102X_dataRun2_Sep2018Rereco_v1'

process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))
process.options.allowUnscheduled = cms.untracked.bool(True)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)


process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        "file:root://cms-xrd-global.cern.ch///store/user/jbechtel/gc_storage/MuTau_data_2018ABC_CMSSW1020/TauEmbedding_MuTau_data_2018ABC_CMSSW1020_Run2018A/39/merged_17738.root"
		),
		inputCommands=cms.untracked.vstring(
						'keep *',
						'keep *_l1extraParticles_*_*',
		)
)

#import FWCore.PythonUtilities.LumiList as LumiList #check lumilist name, not sure it matches to golden
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/hep.wisc.edu/home/samuellh/WorkingArea/HTT/CMSSW_10_2_14/src/PUAnalysis/Configuration/data/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt').getVLuminosityBlockRange() 


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
                          'HLT_IsoMu24_v',
                          'HLT_IsoMu27_v',
                          'HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1_v',
                          'HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1_v',
                          'HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_v',
                          'HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_v' 
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

#Name of the path in hTauTau_cff
process.eventSelectionMT = cms.Path(process.selectionSequenceMT)


#Create the Ntuples, the name "analysis.root" is set here as well
#This takes the output from the configuration sequence and fills
#the tree that will later be used for plotting. Notice the names
#added here 'diTauOS' is the default, however, this 'diTauOS' can
#be replaced with any of the labled collections produced in htautau_cff.py
#in order to create two different trees, one with all the final selections
#and one with looser selections.

from PUAnalysis.Configuration.tools.ntupleTools_LTau import addMuTauEventTree
addMuTauEventTree(process,'muTauEventTree',src = 'muTausSorted',fileout='analysis_mutau.root',srcLL = 'diMuonsOSSorted', srcU='TightMuons', srcE='TightElectrons', isEmbedded=True)
#addMuTauEventTree(process,'muTauEventTreeFinal','muTausOS','diMuonsOSSorted')

#This event summary tells you how many objects pass each of the steps
#in the configuration. It is extremely useful for debugging. 
#Normally does not need to be touched. :) 
addEventSummary(process,True,'MT','eventSelectionMT')

