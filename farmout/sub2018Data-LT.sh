cat $CMSSW_BASE/src/PUAnalysis/LT.py > SUB_LT_Data.py
cat submit.py >> SUB_LT_Data.py

#jobID=2019_Jul21_V15JEC_2018Data_ALL
jobID=2019_Jul20-try2_2018Data_ALL

#farmoutAnalysisJobs    --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD ${jobID}_data_e_B  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
#farmoutAnalysisJobs    --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017C-17Nov2017-v1/MINIAOD ${jobID}_data_e_C  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
#farmoutAnalysisJobs    --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017D-17Nov2017-v1/MINIAOD ${jobID}_data_e_D  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
#farmoutAnalysisJobs    --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017E-17Nov2017-v1/MINIAOD ${jobID}_data_e_E  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
#farmoutAnalysisJobs    --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017F-17Nov2017-v1/MINIAOD ${jobID}_data_e_F  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py

farmoutAnalysisJobs  $1  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2018A-17Sep2018-v2/MINIAOD  ${jobID}_data_m_A $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
farmoutAnalysisJobs  $1  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2018B-17Sep2018-v1/MINIAOD  ${jobID}_data_m_B $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
farmoutAnalysisJobs  $1  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2018C-17Sep2018-v1/MINIAOD  ${jobID}_data_m_C $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py
farmoutAnalysisJobs  $1  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2018D-PromptReco-v2/MINIAOD ${jobID}_data_m_D $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_LT_Data.py


