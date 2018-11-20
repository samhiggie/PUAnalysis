cat $CMSSW_BASE/src/PUAnalysis/TT-emb.py > SUB_Emb.py
cat submit.py >>SUB_Emb.py

jobID=2018_Nov19

farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EmbeddingRun2017B/TauTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER ${jobID}_data_tau_B_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EmbeddingRun2017C/TauTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER ${jobID}_data_tau_C_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EmbeddingRun2017C/TauTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER ${jobID}_data_tau_D_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EmbeddingRun2017E/TauTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER ${jobID}_data_tau_E_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EmbeddingRun2017F/TauTauFinalState-inputDoubleMu_94X_miniAOD-v2/USER ${jobID}_data_tau_F_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
