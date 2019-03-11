#!/bin/sh
#voms-proxy-init --voms cms --valid 100:00
#UWAnalysis/CRAB/HTT_25ns/SUB-TT.py
cat $CMSSW_BASE/src/PUAnalysis/TT-JHU-MC.py > SUB_MC.py
cat submit.py >>SUB_MC.py

jobID=2018_Nov30

jobOptions="--vsize-limit=8000 --input-files-per-job=1 --max-usercode-size=250"
tailOptions="  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_MC.py"
######JHU HIGGS SAMPLES #############
#Total of 22 Samples

farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-file-list=JHUMC/WHiggs0L1fWH05ph0.txt            ${jobID}_WHiggs0L1fWH05ph0                  $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-file-list=JHUMC/WHiggs0L1.txt                    ${jobID}_WHiggs0L1                          $tailOptions

#farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/VBFHiggs0L1f05ph0_M-125_13TeV-JHUGenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM         ${jobID}_VBFHiggs_0L1f05ph0  $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/VBFHiggs0L1_M-125_13TeV-JHUGenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM                 ${jobID}_VBFHiggs0L1_M-125 $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/VBFHiggs0Mf05ph0_M-125_13TeV-JHUGenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM            ${jobID}_VBFHiggs0Mf05     $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/VBFHiggs0M_M-125_13TeV-JHUGenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM                  ${jobID}_VBFHiggs0M_M      $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/VBFHiggs0PHf05ph0_M-125_13TeV-JHUGenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM           ${jobID}_VBFHiggs0PHf05ph0 $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/VBFHiggs0PM_M-125_13TeV-JHUGenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM                 ${jobID}_VBFHiggs0PH       $tailOptions

farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/WHiggs0MfWH05ph0_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM  ${jobID}_WHiggs0MfWH05ph0  $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/WHiggs0M_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM          ${jobID}_WHiggs0M          $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/WHiggs0PHfWH05ph0_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM ${jobID}_WHiggs0PHfWH05ph0 $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/WHiggs0PH_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM         ${jobID}_WHiggs0PH         $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/WHiggs0PM_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM         ${jobID}_WHiggs0PM         $tailOptions

farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0L1fZH05ph0_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM ${jobID}_ZHiggs0L1fZH05ph0 $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0L1_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM         ${jobID}_ZHiggs0L1         $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0MfZH05ph0_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM  ${jobID}_ZHiggs0MfZH05ph0  $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0M_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM          ${jobID}_ZHiggs0M          $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0PHfZH05ph0_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM ${jobID}_ZHiggs0PHfZH05ph0 $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0PH_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM         ${jobID}_ZHiggs0PH         $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-dbs-path=/ZHiggs0PM_Undecayed_M-125_13TeV-JHUgenV6/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM         ${jobID}_ZHiggs0PM         $tailOptions

farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-file-list=JHUMC/GluGluH2JetsToTauTau_maxmix.txt           ${jobID}_GluGluH2JetsToTauTau_maxmix        $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-file-list=JHUMC/GluGluH2JetsToTauTau_pseudoscalar.txt     ${jobID}_GluGluH2JetsToTauTau_pseudoscalar  $tailOptions
farmoutAnalysisJobs  $1 --site-requirements='OpSysAndVer == "SL6"' $jobOptions --input-file-list=JHUMC/GluGluH2JetsToTauTau_sm.txt               ${jobID}_GluGluH2JetsToTauTau_sm            $tailOptions

#GluGluH2JetsToTauTau_maxmix.txt  GluGluH2JetsToTauTau_pseudoscalar.txtGluGluH2JetsToTauTau_sm.txt
#WHiggs0L1.txt  WHiggs0L1fWH05ph0.txt