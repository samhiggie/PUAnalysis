#########################
#Author: Sam Higginbotham
#########################

#from WMCore.Configuration import Configuration
#config = Configuration()

from CRABClient.UserUtilities import config
config = config()


import os
#print("Please include full name of dataset")
from PUAnalysis.CrabTools.datasets_2017_full import samples 
dset = os.getcwd().replace(os.path.dirname(os.getcwd())+'/', '')
print 'Submitting jobs for dataset ' + samples[dset][0]



#config.section_("General")
config.General.requestName = samples[dset][0].split('/')[0] 
config.General.workArea = 'SM_2018_Sync'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../../../MT-MC-Sync.py'
config.JobType.allowUndistributedCMSSW = True
#For the correctionsC.db files needed in the lumiproducer
#config.JobType.inputFiles = ['../../../Configuration/data/PhaseIISummer16_25nsV3_MC.db']
#config.JobType.inputFiles = ['../../../Configuration/data/Fall17_17Nov2017_V6_MC.db',
config.JobType.inputFiles = ['../../../Configuration/data/Autumn18_V8_MC.db',
    "../../../../RecoEgamma/ElectronIdentification/data/Fall17/EIDmva_EB1_5_2017_puinfo_BDT.weights.xml",
    "../../../../RecoEgamma/ElectronIdentification/data/Fall17/EIDmva_EB2_5_2017_puinfo_BDT.weights.xml",
    "../../../../RecoEgamma/ElectronIdentification/data/Fall17/EIDmva_EE_5_2017_puinfo_BDT.weights.xml",
    "../../../../RecoEgamma/ElectronIdentification/data/Fall17/EIDmva_EB1_10_2017_puinfo_BDT.weights.xml",
    "../../../../RecoEgamma/ElectronIdentification/data/Fall17/EIDmva_EB2_10_2017_puinfo_BDT.weights.xml",
    "../../../../RecoEgamma/ElectronIdentification/data/Fall17/EIDmva_EE_10_2017_puinfo_BDT.weights.xml"]
config.JobType.outputFiles = ['analysis_mutau.root']


config.section_("Data")
config.Data.inputDataset = samples[dset][0]
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.publication = False
config.Data.unitsPerJob = 1
config.Data.allowNonValidInputDataset = True
#config.Data.publishDbsUrl = 'test'
config.Data.outLFNDirBase = '/store/user/samuellh/2019_2018_mutau_sync/'


config.section_("Site")
config.Site.storageSite = 'T2_US_Wisconsin'
