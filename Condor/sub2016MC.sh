cat $CMSSW_BASE/src/PUAnalysis/TT-MC-Legacy.py > SUB_MC.py
cat submit.py >>SUB_MC.py

jobID=2019_July9_legacy2016


farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_ggH125_3v1_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py  
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v3/MINIAODSIM ${jobID}_ggH125_3v3_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_vbfH125_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WplusHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WpH125_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WminusHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WmH125_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ZH125_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/GluGluHToTauTau_M110_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ggH110_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/GluGluHToTauTau_M140_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ggH140_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToTauTau_M110_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_vbfH110_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_vbfH120_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM ${jobID}_vbfH130_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToTauTau_M140_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_vbfH140_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WplusHToTauTau_M110_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WpH110_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WplusHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WpH120_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WplusHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WpH130_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WplusHToTauTau_M140_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WpH140_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WminusHToTauTau_M110_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WmH110_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WminusHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WmH120_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WminusHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WmH130_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WminusHToTauTau_M140_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WmH140_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZHToTauTau_M110_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ZH110_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZHToTauTau_M120_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ZH120_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZHToTauTau_M130_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ZH130_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZHToTauTau_M140_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ZH140_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py

farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_TT_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM ${jobID}_WJets_3v2ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WJets_3v2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-FlatPU28to62HcalNZSRAW_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_WJets_3v1_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_W1Jets_3v1_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_W2Jets_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_W3Jets_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM ${jobID}_W4Jets_3v1ext2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_W4Jets_3v2ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUSummer16v3Fast_lhe_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM ${jobID}_DYJets_3v1ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DYJets_3v2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY1Jets_3v2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY2Jets_3v2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY3Jets_3v2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY4Jets_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM ${jobID}_DYJets50_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_DYJets50_ext2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_DY1Jets50_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY2Jets50_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY3Jets50_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_DY4Jets50_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WW_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_WW_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_WZ_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_WZ_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ZZ_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_ZZ_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_St_t_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM ${jobID}_St_ttbar_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM ${jobID}_tW_ttbar_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM ${jobID}_tW_t_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM ${jobID}_EWKWp_ext2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_EWKWp_ext1_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_EWKWp_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM ${jobID}_EWKWm_ext2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_EWKWm_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_EWKWm_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v3/MINIAODSIM ${jobID}_EWKZToLL_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_EWKZToLL_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM ${jobID}_EWKZToLL_ext2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKZ2Jets_ZToNuNu_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_EWKZTo2Nu_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKZ2Jets_ZToNuNu_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM ${jobID}_EWKZTo2Nu_ext_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/EWKZ2Jets_ZToNuNu_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM ${jobID}_EWKZTo2Nu_ext2_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_ggWW2l2Nu_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
farmoutAnalysisJobs  --vsize-limit=8000 --max-usercode-size=570 --assume-input-files-exist --input-files-per-job=1 --input-dbs-path=/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM ${jobID}_vbfWW2l2Nu_tautau $CMSSW_BASE $CMSSW_BASE/src/PUAnalysis/Condor/SUB_MC.py
