cat $CMSSW_BASE/src/PUAnalysis/TT-MC-Sync.py > SUB_MC.py
cat submit.py >>SUB_MC.py

jobID=2019_Mar11



farmoutAnalysisJobs  --site-requirements='OpSysAndVer == "SL6"'  --vsize-limit=8000 --max-usercode-size=180 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM ${jobID}_tautau_vbfH125  $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/farmout/SUB_MC.py
