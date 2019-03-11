cat $CMSSW_BASE/src/PUAnalysis/TT-emb.py > SUB_Emb.py
cat submit.py >>SUB_Emb.py

jobID=2018_Nov20

farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-file-list=embeddedSamples/Embedded-Run2017B.txt ${jobID}_emb_tau_B_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-file-list=embeddedSamples/Embedded-Run2017C.txt ${jobID}_emb_tau_C_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-file-list=embeddedSamples/Embedded-Run2017D.txt ${jobID}_emb_tau_D_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-file-list=embeddedSamples/Embedded-Run2017E.txt ${jobID}_emb_tau_E_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --assume-input-files-exist --input-files-per-job=1 --input-file-list=embeddedSamples/Embedded-Run2017F.txt ${jobID}_emb_tau_F_tautau  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_Emb.py
