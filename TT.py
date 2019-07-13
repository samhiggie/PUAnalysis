import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

#process.GlobalTag.globaltag = '102X_dataRun2_Prompt_v11'   #Run D only
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
        ##'/store/data/Run2017B/Tau/MINIAOD/31Mar2018-v1/00000/005D8BAB-7C37-E811-B1D9-001E67E6F90E.root'
        #'/store/data/Run2018A/Tau/MINIAOD/17Sep2018-v1/60000/E2C8EEBF-2B7B-7E4A-BA1F-BC37967059D0.root'
        '/store/data/Run2018A/Tau/MINIAOD/17Sep2018-v1/60000/E6F0AA69-9B1B-7A4B-980C-ADE2CBE16164.root'   
		),
		inputCommands=cms.untracked.vstring(
						'keep *',
						'keep *_l1extraParticles_*_*',
		)
)

import FWCore.PythonUtilities.LumiList as LumiList #check lumilist name, not sure it matches to golden
#process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/hep.wisc.edu/home/samuellh/WorkingArea/HTT/CMSSW_10_2_14/src/PUAnalysis/Configuration/data/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt').getVLuminosityBlockRange() 
#60.02
from PUAnalysis.Configuration.JSOND import myLumiList
myLumiList(process);

#Default Reconstruction from the analysTools.py config file
#The main 'setup' processes can be found in "defaultReconstruction" and "defaultReconstructionMC"
#analysisTools takes care of pre-selections, adding in extra ID's that do not come in the miniAOD
#files and embedding trigger matching (the trigger for di-Tau hadronic still should be added and checked)
#defaultRecontruction and defaultReconstructionMC are generic enough to work for any final state
#needed: muTau, tauTau, eTau, mumuTauTau, ect. However, different analyses may want to embed
#different ID's, isolations, ect. Trigger paths are input below. These plugins are typically
#found in RecoTools/plugins/
        #'HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v',
        #'HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v',
        #'HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v'
from PUAnalysis.Configuration.tools.analysisTools import *
defaultReconstruction(process,'HLT',
        [
        'HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v',
        'HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_v',
        'HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_v',
        'HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_v',
        'HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg_v',
        'HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg_v',
        'HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg_v',
        'HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg_v',
        'HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_v',
        'HLT_VBF_DoubleLooseChargedIsoPFTauHPS20_Trk1_eta2p1_Reg_v'
        ])

#EventSelection
#Most of the selections for the analysis go in hTauTau_cff
#The selections proceed sequentially, each time a "di-candidate pair" fails a cut in
#this configuration then the sequence will start over with another di-candidate pair.
#The final 'sorting' is implemented there as well, either by di-tau PT or isolation.
process.load("PUAnalysis.Configuration.hTauTau_Sync_cff")

process.metCalibration.applyCalibration = cms.bool(False)

#Name of the path in hTauTau_cff
process.eventSelectionTT = cms.Path(process.selectionSequenceTT)


#Create the Ntuples, the name "analysis.root" is set here as well
#This takes the output from the configuration sequence and fills
#the tree that will later be used for plotting. Notice the names
#added here 'diTauOS' is the default, however, this 'diTauOS' can
#be replaced with any of the labled collections produced in htautau_cff.py
#in order to create two different trees, one with all the final selections
#and one with looser selections.
from PUAnalysis.Configuration.tools.ntupleTools import addDiTauEventTree

addDiTauEventTree(process,'diTauEventTree','diTausSync','TightMuons','TightElectrons',triggerCollection='HLT')


#This event summary tells you how many objects pass each of the steps
#in the configuration. It is extremely useful for debugging. 
#Normally does not need to be touched. :) 
addEventSummary(process,True,'TT','eventSelectionTT')

