cat $CMSSW_BASE/src/PUAnalysis/TT.py > SUB_Data.py
cat submit.py >>SUB_Data.py

jobID=2018_Nov13

farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/Tau/Run2017B-31Mar2018-v1/MINIAOD ${jobID}_data_tau_B_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/Tau/Run2017B-31Mar2018-v1/MINIAOD ${jobID}_data_tau_C_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/Tau/Run2017B-31Mar2018-v1/MINIAOD ${jobID}_data_tau_D_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/Tau/Run2017E-31Mar2018-v1/MINIAOD ${jobID}_data_tau_E_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_Data.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/Tau/Run2017F-31Mar2018-v1/MINIAOD ${jobID}_data_tau_F_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_Data.py
