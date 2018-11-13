#!/bin/sh
#voms-proxy-init --voms cms --valid 100:00
jobID="2016_Jan17"
header="--assume-input-files-exist --vsize-limit=8000 --skip-existing-output  --input-files-per-job=1"
#PromptREco
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016B-23Sep2016-v3/MINIAOD  ${jobID}_TAU2016B $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016C-23Sep2016-v1/MINIAOD  ${jobID}_TAU2016C $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016D-23Sep2016-v1/MINIAOD  ${jobID}_TAU2016D $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016E-23Sep2016-v1/MINIAOD  ${jobID}_TAU2016E $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016F-23Sep2016-v1/MINIAOD  ${jobID}_TAU2016F $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016G-23Sep2016-v1/MINIAOD  ${jobID}_TAU2016G $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
farmoutAnalysisJobs  $1  $header --input-dbs-path=/Tau/Run2016H-PromptReco-v3/MINIAOD ${jobID}_TAU2016H $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py


#Submit the reprocessed Data
#jobID=2016_Dec5

#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-file-list=TauRun2016B.txt ${jobID}_TAU2016B_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-file-list=TauRun2016C.txt ${jobID}_TAU2016C_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-file-list=TauRun2016D.txt ${jobID}_TAU2016D_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-file-list=TauRun2016E.txt ${jobID}_TAU2016E_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-file-list=TauRun2016F.txt ${jobID}_TAU2016F_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py

#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-dbs-path=/Tau/Run2016B-PromptReco-v2/MINIAOD ${jobID}_TAU2016B_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-dbs-path=/Tau/Run2016C-PromptReco-v2/MINIAOD ${jobID}_TAU2016C_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-dbs-path=/Tau/Run2016D-PromptReco-v2/MINIAOD ${jobID}_TAU2016D_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-dbs-path=/Tau/Run2016E-PromptReco-v2/MINIAOD ${jobID}_TAU2016E_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#farmoutAnalysisJobs  $1  --assume-input-files-exist --skip-existing-output --vsize-limit=8000   --input-files-per-job=1 --input-dbs-path=/Tau/Run2016F-PromptReco-v1/MINIAOD ${jobID}_TAU2016F_Jul21 $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/CRAB/HTT_25ns/SUB-TT-JSON.py
#/Tau/Run2016B-PromptReco-v2/MINIAOD
#/Tau/Run2016C-PromptReco-v2/MINIAOD
#/Tau/Run2016E-PromptReco-v2/MINIAOD
#/Tau/Run2016F-PromptReco-v1/MINIAOD
