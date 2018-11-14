#!/bin/sh
#voms-proxy-init --voms cms --valid 100:00
#UWAnalysis/CRAB/HTT_25ns/SUB-TT.py
jobID=2016_Feb11

jobOptions="--vsize-limit=8000 --assume-input-files-exist --skip-existing-output --assume-input-files-exist --input-files-per-job=1"
tailOptions="  $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT.py"
######HIGGS SAMPLES #############
#ggH
##missing samples commented
#farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/GluGluHToTauTau_M120_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM         ${jobID}_ggHtautau_120  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM         ${jobID}_ggHtautau_125  $tailOptions
#farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/GluGluHToTauTau_M130_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM         ${jobID}_ggHtautau_130  $tailOptions

#farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/VBFHToTauTau_M120_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM             ${jobID}_vbfHtautau_120  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM             ${jobID}_vbfHtautau_125  $tailOptions
#farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/VBFHToTauTau_M130_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM             ${jobID}_vbfHtautau_130  $tailOptions

farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/WplusHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM           ${jobID}_WpHtautau_120  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/WplusHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM           ${jobID}_WpHtautau_125  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/WplusHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM           ${jobID}_WpHtautau_130  $tailOptions

farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/WminusHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM          ${jobID}_WmHtautau_120  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/WminusHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM          ${jobID}_WmHtautau_125  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/WminusHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM          ${jobID}_WmHtautau_130  $tailOptions

farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/ZHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM               ${jobID}_ZHtautau_120  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM               ${jobID}_ZHtautau_125  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/ZHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM               ${jobID}_ZHtautau_130  $tailOptions

farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/ttHJetToTT_M120_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM ${jobID}_ttHtautau_120  $tailOptions
#farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/ttHJetToTT_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM ${jobID}_ttHtautau_125  $tailOptions
farmoutAnalysisJobs  $1 $jobOptions --input-dbs-path=/ttHJetToTT_M130_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM ${jobID}_ttHtautau_130  $tailOptions

########ZJETS SAMPLES#############
farmoutAnalysisJobs  $1  $header --input-dbs-path=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM ${jobID}_ZJets $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM     ${jobID}_Z1Jets $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM     ${jobID}_Z2Jets $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM     ${jobID}_Z3Jets $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM     ${jobID}_Z4Jets $1 $tailOptions
##Need me
#farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM     ${jobID}_ZJets_150 $tailOptions  

########TT SAMPLES################
farmoutAnalysisJobs  $1  $header --input-dbs-path=/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM                            ${jobID}_TT        $tailOptions
#farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM ${jobID}_TT_SLTbar $tailOptions  
#farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM    ${jobID}_TT_SLT    $tailOptions  
#farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM        ${jobID}_TT_DL     $tailOptions  

##########WJETS SAMPLES#############
farmoutAnalysisJobs  $1 $header --input-dbs-path=/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM       ${jobID}_WJets  $1 $tailOptions
farmoutAnalysisJobs  $1 $header --input-dbs-path=/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM      ${jobID}_W1Jets $1 $tailOptions
farmoutAnalysisJobs  $1 $header --input-dbs-path=/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM      ${jobID}_W2Jets $1 $tailOptions
farmoutAnalysisJobs  $1 $header --input-dbs-path=/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM      ${jobID}_W3Jets $1 $tailOptions
farmoutAnalysisJobs  $1 $header --input-dbs-path=/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM      ${jobID}_W4Jets $1 $tailOptions
farmoutAnalysisJobs  $1 $header --input-dbs-path=/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM ${jobID}_W4Jets-ext2 $1 $tailOptions

farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM   ${jobID}_WJets_amc $tailOptions  

###########WZ SAMPLES#############

#WZ
farmoutAnalysisJobs  $1  $header --input-dbs-path=/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM   ${jobID}_WZTo3L1Nu       $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM       ${jobID}_WZTo1L3Nu      $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM     ${jobID}_WZTo1L1Nu2Q    $1 $tailOptions
farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM                ${jobID}_WZJTo3L1Nu  $tailOptions  

#need these ones
#farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM                               ${jobID}_WZ          $tailOptions  
#farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM                 ${jobID}_WZTo2L2Q    $tailOptions

##########SINGLE TOP SAMPLES############# 
farmoutAnalysisJobs  $1  $header --input-dbs-path=/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM              ${jobID}_tBar_tW       $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM                  ${jobID}_t_tW          $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM  ${jobID}_ST_t_antitop  $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM      ${jobID}_ST_t_top      $tailOptions

###########WW SAMPLES#############
##need these samples
#farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/WW_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM                                ${jobID}_WW           $tailOptions  
#farmoutAnalysisJobs $1 $jobOptions --input-dbs-path=/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM               ${jobID}_WWTo1L1Nu2Q  $tailOptions  

###########ZZ SAMPLES#############
farmoutAnalysisJobs  $1  $header --input-dbs-path=/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM       ${jobID}_VVTo2L2Nu      $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM  ${jobID}_VVTo2L2Nu-ext1 $1 $tailOptions
farmoutAnalysisJobs  $1  $header --input-dbs-path=/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM        ${jobID}_ZZTo2L2Q       $1 $tailOptions
farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM                                 ${jobID}_ZZTo4L       $tailOptions  

##Need me
#farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM                               ${jobID}_ZZ           $tailOptions  

##########TriBoson SAMPLES#######
##need me
#farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM                  ${jobID}_WWW    $tailOptions  
#farmoutAnalysisJobs $1 $jobOptions  --input-dbs-path=/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM                     ${jobID}_ZZZ    $tailOptions  

