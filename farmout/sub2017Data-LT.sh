cat $CMSSW_BASE/src/PUAnalysis/LT.py > SUB_LT_Data.py
cat submit.py >>SUB_LT_Data.py

jobID=2018_Oct_2017Data_ALL


farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD ${jobID}_data_e_B  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017C-17Nov2017-v1/MINIAOD ${jobID}_data_e_C  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017D-17Nov2017-v1/MINIAOD ${jobID}_data_e_D  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017E-17Nov2017-v1/MINIAOD ${jobID}_data_e_E  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleElectron/Run2017F-17Nov2017-v1/MINIAOD ${jobID}_data_e_F  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2017B-17Nov2017-v1/MINIAOD ${jobID}_data_mu_B  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD ${jobID}_data_mu_C  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2017D-17Nov2017-v1/MINIAOD ${jobID}_data_mu_D  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD ${jobID}_data_mu_E  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/SingleMuon/Run2017F-17Nov2017-v1/MINIAOD ${jobID}_data_mu_F  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_LT_Data.py