#########################
#Author: Sam Higginbotham
#########################

#from WMCore.Configuration import Configuration
#config = Configuration()

from CRABClient.UserUtilities import config
config = config()


import os
#print("Please include full name of dataset")
from PUAnalysis.CrabTools.datasets_2018_data import samples 
dset = os.getcwd().replace(os.path.dirname(os.getcwd())+'/', '')
print 'Submitting jobs for dataset ' + samples[dset][0]



#config.section_("General")
config.General.requestName = samples[dset][0].split('/')[0] 
config.General.workArea = 'SM_HTT_2018'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../../../TT.py'
config.JobType.allowUndistributedCMSSW = True
#For the correctionsC.db files needed in the lumiproducer
#config.JobType.inputFiles = ['../../../Configuration/data/PhaseIISummer16_25nsV3_MC.db']
config.JobType.inputFiles = ['../../../Configuration/data/Autumn18_V8_MC.db',
    "../../../Configuration/data/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt"]
config.JobType.outputFiles = ['analysis_TauTau.root']


config.section_("Data")
config.Data.inputDataset = samples[dset][0]
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.publication = False
config.Data.unitsPerJob = 1
#config.Data.publishDbsUrl = 'test'
config.Data.outLFNDirBase = '/store/user/shigginb/2019_June_15_2018_Data_tt'


config.section_("Site")
config.Site.storageSite = 'T2_US_Wisconsin'
