#!/bin/sh

#nohup bash ./merge.sh >merge.log & 
#to see if finished running check 'top' and tail below
#tail -f merge.log

#mkdir /scratch/$USER/ztt_unweighted_Nov13
#mkdir /hdfs/store/user/shigginb/2019_Mar_2017_ntuples
#cd /hdfs/store/user/shigginb/2019_Mar_2017_ntuples
mkdir /nfs_scratch/samuellh/2019_Mar_2017_ntuples_pileup
cp data_pileup_pudistributions_mc_2017.root /nfs_scratch/samuellh/2019_Mar_2017_ntuples_pileup/.
cp data_pileup_pudistributions_data_2017.root /nfs_scratch/samuellh/2019_Mar_2017_ntuples_pileup/.
cd /nfs_scratch/samuellh/2019_Mar_2017_ntuples_pileup
#cd /scratch/$USER/ztt_unweighted_Nov13
jobID='2018_Nov13_data_tau'

user=samuellh
mergedata=0;
mergemc=1;
mergeW=1;
mergeZ=1;
mergehiggs=1;

if [ $mergedata -eq 1 ]
    then
    hadd -f tauDATA-B.root 	/hdfs/store/user/$user/${jobID}_B_tautau-SUB_Data/* &
    hadd -f tauDATA-C.root 	/hdfs/store/user/$user/${jobID}_C_tautau-SUB_Data/* &
    hadd -f tauDATA-D.root 	/hdfs/store/user/$user/${jobID}_D_tautau-SUB_Data/* &
    hadd -f tauDATA-E.root 	/hdfs/store/user/$user/${jobID}_E_tautau-SUB_Data/* &
    hadd -f tauDATA-F.root 	/hdfs/store/user/$user/${jobID}_F_tautau-SUB_Data/* &
    wait;
    hadd -f tauDATA.root tauDATA-B.root tauDATA-C.root tauDATA-D.root tauDATA-E.root tauDATA-F.root
    PileUpReweight outputFile="tauDATA.root" dataset="pileup" branch="PUweight"
fi
jobID='2019_Mar18_tautau'
#2018_Oct_2017MC_ggH_ggHtautau_125-SUB/
if [ $mergehiggs -eq 1 ]
    then #ggHtautau_125
    #hadd -f  ggH110.root /hdfs/store/user/$user/${jobID}_ggHtautau_110-SUB-TT/* 
    #hadd -f  ggH120.root /hdfs/store/user/$user/${jobID}_ggHtautau_120-SUB-TT/* 
    hadd -f  ggH1251.root /hdfs/store/user/$user/${jobID}_ggH125-SUB_MC/* 
    hadd -f  ggH125-ext.root /hdfs/store/user/$user/${jobID}_ggH125_ext-SUB_MC/* 
    PileUpReweight outputFile="ggH125-ext.root" dataset="#GluGluHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="ggH1251.root" dataset="#GluGluHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f ggH125.root ggH1251.root ggH125-ext.root   
    #hadd -f  ggH130.root /hdfs/store/user/$user/${jobID}_ggHtautau_130-SUB-TT/* 
    #hadd -f  ggH140.root /hdfs/store/user/$user/${jobID}_ggHtautau_140-SUB-TT/* 

    #hadd -f  vbfH120.root /hdfs/store/user/$user/${jobID}_vbfHtautau_110-SUB-TT/* 
    #hadd -f  vbfH120.root /hdfs/store/user/$user/${jobID}_vbfHtautau_120-SUB-TT/* 
    hadd -f  vbfH125.root /hdfs/store/user/$user/${jobID}_vbfH125-SUB_MC/* 
    PileUpReweight outputFile="vbfH125.root" dataset="#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f  vbfH130.root /hdfs/store/user/$user/${jobID}_vbfHtautau_130-SUB-TT/* 
    #hadd -f  vbfH130.root /hdfs/store/user/$user/${jobID}_vbfHtautau_140-SUB-TT/* 

    #hadd -f  WpH120.root /hdfs/store/user/$user/${jobID}_WpHtautau_120-SUB-TT/* 
    hadd -f  WpH125.root /hdfs/store/user/$user/${jobID}_WHplus-SUB_MC/* 
    PileUpReweight outputFile="WpH125.root" dataset="#WplusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f  WpH130.root /hdfs/store/user/$user/${jobID}_WpHtautau_130-SUB-TT/* 

    #hadd -f  WmH120.root /hdfs/store/user/$user/${jobID}_WmHtautau_120-SUB-TT/* 
    hadd -f  WmH125.root /hdfs/store/user/$user/${jobID}_WHminus-SUB_MC/* 
    PileUpReweight outputFile="WmH125.root" dataset="#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f  WmH130.root /hdfs/store/user/$user/${jobID}_WmHtautau_130-SUB-TT/* 

    #hadd -f  ZH120.root /hdfs/store/user/$user/${jobID}_ZHtautau_120-SUB-TT/* 
    hadd -f  ZH125.root /hdfs/store/user/$user/${jobID}_ZH-SUB_MC/* 
    PileUpReweight outputFile="ZH125.root" dataset="#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f  ZH130.root /hdfs/store/user/$user/${jobID}_ZHtautau_130-SUB-TT/* 

    #hadd -f  ttH120.root /hdfs/store/user/$user/${jobID}_ttHtautau_120-SUB-TT/* 
    hadd -f  ttH125.root /hdfs/store/user/$user/${jobID}_ttH-SUB_MC/* 
    #PileUpReweight outputFile="ttH125.root" dataset="#ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="ttH125.root" dataset="#ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f  ttH130.root /hdfs/store/user/$user/${jobID}_ttHtautau_130-SUB-TT/* 
    wait;
fi 

if [ $mergeW -eq 1 ]
    then
    #hadd -f  W1Jets.root /hdfs/store/user/$user/${jobID}i_W1J_lnu-SUB_MC/*
    hadd -f  W1Jets.root /hdfs/store/user/$user/${jobID}_W1J_lnu-SUB_MC/*
    PileUpReweight outputFile="W1Jets.root" dataset="#W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3#MINIAODSIM" branch="PUweight"
    hadd -f  W2Jets.root /hdfs/store/user/$user/${jobID}_W2J_lnu-SUB_MC/*
    PileUpReweight outputFile="W2Jets.root" dataset="#W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v4#MINIAODSIM" branch="PUweight"
    hadd -f  W3Jets.root /hdfs/store/user/$user/${jobID}_W3J_lnu-SUB_MC/* 
    PileUpReweight outputFile="W3Jets.root" dataset="#W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f  W4Jets.root /hdfs/store/user/$user/${jobID}_W4J_lnu-SUB_MC/*
    PileUpReweight outputFile="W4Jets.root" dataset="#W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f  WJets1.root /hdfs/store/user/$user/${jobID}_WJ_lnu-SUB_MC/* 
    PileUpReweight outputFile="WJets1.root" dataset="#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f  WJets-ext.root /hdfs/store/user/$user/${jobID}_WJ_lnu_ext-SUB_MC/* 
    PileUpReweight outputFile="WJets-ext.root" dataset="#WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2#MINIAODSIM" branch="PUweight"
    hadd -f WJets.root WJets1.root WJets-ext.root
    wait;
fi 

if [ $mergeZ -eq 1 ]
    then
    ##merge nominal and extension at the same time
    #hadd -f  ZJets1.root  /hdfs/store/user/$user/${jobID}_DYJ-SUB_MC/*
    #hadd -f  ZJets-ext1.root  /hdfs/store/user/$user/${jobID}_DYJ_ext-SUB_MC/* 
    #PileUpReweight outputFile="ZJets1.root" dataset="#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile="ZJets-ext1.root" dataset="#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    #hadd -f ZJets.root ZJets1.root ZJets-ext1.root
    #PileUpReweight outputFile="" dataset="#DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    #PileUpReweight outputFile="" dataset="#DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"

    hadd -f  Z1Jets1.root /hdfs/store/user/$user/${jobID}_DY1-SUB_MC/* 
    PileUpReweight outputFile="Z1Jets1.root" dataset="#DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile="" dataset="#DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile="" dataset="#DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    hadd -f  Z1Jets-ext1.root /hdfs/store/user/$user/${jobID}_DY1_ext-SUB_MC/*
    PileUpReweight outputFile="Z1Jets-ext1.root" dataset="#DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v3_94X_mc2017_realistic_v14_ext1-v2#MINIAODSIM" branch="PUweight"
    hadd -f Z1Jets.root Z1Jets1.root Z1Jets-ext1.root

    hadd -f  Z2Jets1.root /hdfs/store/user/$user/${jobID}_DY2-SUB_MC/*  
PileUpReweight outputFile="Z2Jets1.root" dataset="#DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f  Z2Jets-ext1.root /hdfs/store/user/$user/${jobID}_DY2_ext-SUB_MC/* 
PileUpReweight outputFile="Z2Jets-ext1.root" dataset="#DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    hadd -f Z2Jets.root Z2Jets1.root Z2Jets-ext1.root
    hadd -f  Z3Jets1.root /hdfs/store/user/$user/${jobID}_DY3-SUB_MC/*
PileUpReweight outputFile="Z3Jets1.root" dataset="#DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f  Z3Jets-ext1.root /hdfs/store/user/$user/${jobID}_DY3_ext-SUB_MC/*
    PileUpReweight outputFile="Z3Jets-ext1.root" dataset="#DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    hadd -f Z3Jets.root Z3Jets1.root Z3Jets-ext1.root
    hadd -f  Z4Jets.root /hdfs/store/user/$user/${jobID}_DY4-SUB_MC/*
    PileUpReweight outputFile="Z4Jets.root" dataset="#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    #hadd -f  Z4Jets2.root /hdfs/store/user/$user/${jobID}_DY4-SUB_MC/*
    #PileUpReweight outputFile=Z4Jets2.root dataset="#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f Z4Jets.root Z4Jets1.root Z4Jets2.root
    wait;
fi 

if [ $mergemc -eq 1 ]
    then

   #uncomment below for SM Backgorund sample 2016_Sep23_TT-SUB-TT
    hadd -f   TT_had.root 	/hdfs/store/user/$user/${jobID}_TT_had-SUB_MC/*  
    PileUpReweight outputFile="TT_had.root" dataset="#TTToHadronic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile= dataset="#TTToHadronic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f   TT_SL.root 	/hdfs/store/user/$user/${jobID}_TT_sl-SUB_MC/*  
    #PileUpReweight outputFile="TT_SL.root" dataset="#TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="TT_SL.root" dataset="#TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f   TT_DL.root 	/hdfs/store/user/$user/${jobID}_TT_2l2nu-SUB_MC/*  
    PileUpReweight outputFile="TT_DL.root" dataset="#TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile= dataset="#TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    hadd -f   WZTo1L3Nu.root    /hdfs/store/user/$user/${jobID}_WZ_1l3nu-SUB_MC/* 
    PileUpReweight outputFile="WZTo1L3Nu.root" dataset="#WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   WZTo1L1Nu2Q.root  /hdfs/store/user/$user/${jobID}_WZ_lnu2q-SUB_MC/* 
    PileUpReweight outputFile="WZTo1L1Nu2Q.root" dataset="#WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f   WZTo2L2Q.root     /hdfs/store/user/$user/${jobID}_WZ_2l2q-SUB_MC/* 
    PileUpReweight outputFile="WZTo2L2Q.root" dataset="#WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   WZTo3L1Nu.root    /hdfs/store/user/$user/${jobID}_WZ_3lnu-SUB_MC/* 
    PileUpReweight outputFile="WZTo3L1Nu.root" dataset="#WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile="WZTo3L1Nu.root" dataset="#WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    #PileUpReweight outputFile= dataset="#WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile= dataset="#WZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    hadd -f   tBar_tW.root 	/hdfs/store/user/$user/${jobID}_ST_tw_at-SUB_MC/*
    #PileUpReweight outputFile="tBar_tW.root" dataset="#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="tBar_tW.root" dataset="#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f   t_tW.root 	/hdfs/store/user/$user/${jobID}_ST_tW_t-SUB_MC/* 
    #PileUpReweight outputFile="t_tW.root" dataset="#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="t_tW.root" dataset="#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f   St_tBar.root 	/hdfs/store/user/$user/${jobID}_ST_t_at-SUB_MC/*
    #PileUpReweight outputFile="St_tBar.root" dataset="#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="St_tBar.root" dataset="#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"
    hadd -f   St_t.root 	/hdfs/store/user/$user/${jobID}_ST_t_t-SUB_MC/* 
    PileUpReweight outputFile="St_t.root" dataset="#ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile="St_t.root" dataset="#ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    hadd -f   WWTo1L1Nu2Q.root  /hdfs/store/user/$user/${jobID}_WW_lnu2q*-SUB_MC/* 
    PileUpReweight outputFile="WWTo1L1Nu2Q.root" dataset="#WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   WWTo4Q.root       /hdfs/store/user/$user/${jobID}_WW_4q-SUB_MC/*
    #PileUpReweight outputFile="WWTo4Q-ext.root" dataset="#WWTo4Q_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="WWTo4Q.root" dataset="#WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   WWTo2L2Nu.root    /hdfs/store/user/$user/${jobID}_WW_2l2nu-SUB_MC/* 
    PileUpReweight outputFile="WWTo2L2Nu.root" dataset="#WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile="WWTo2L2Nu-ext.root" dataset="#WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    
    #PileUpReweight outputFile= dataset="#WW_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    hadd -f   ZZTo2L2Q.root     /hdfs/store/user/$user/${jobID}_ZZ_2l2q-SUB_MC/* 
    PileUpReweight outputFile="ZZTo2L2Q.root" dataset="#ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   ZZTo2L2Nu.root    /hdfs/store/user/$user/${jobID}_ZZ_2l2nu-SUB_MC/* 
    PileUpReweight outputFile="ZZTo2L2Nu.root" dataset="#ZZTo2L2Nu_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   ZZTo4L1.root       /hdfs/store/user/$user/${jobID}_ZZ_4l-SUB_MC/* 
    hadd -f   ZZTo4L-ext.root       /hdfs/store/user/$user/${jobID}_ZZ_4l_ext-SUB_MC/* 
    #PileUpReweight outputFile="ZZTo4L.root" dataset="#ZZTo4L_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="ZZTo4L-ext.root" dataset="#ZZTo4L_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    PileUpReweight outputFile="ZZTo4L1.root" dataset="#ZZTo4L_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f ZZTo4L.root ZZTo4L1.root ZZTo4L-ext.root
    #PileUpReweight outputFile="ZZTo4L.root" dataset="#ZZTo4L_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM" branch="PUweight"

    #PileUpReweight outputFile= dataset="#ZZ_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    hadd -f   EWKWp2j.root      /hdfs/store/user/$user/${jobID}_EWKWPlus2j-SUB_MC/*
    PileUpReweight outputFile="EWKWp2j.root" dataset="#EWKWPlus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   EWKWm2j.root      /hdfs/store/user/$user/${jobID}_EWKWminus2j-SUB_MC/*
    PileUpReweight outputFile="EWKWm2j.root" dataset="#EWKWMinus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   EWKZ2l.root       /hdfs/store/user/$user/${jobID}_EWKZ2j_2l-SUB_MC/* 
    PileUpReweight outputFile="EWKZ2l.root" dataset="#EWKZ2Jets_ZToLL_M-50_TuneCP5_13TeV-madgraph-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    hadd -f   EWKZ2Nu.root      /hdfs/store/user/$user/${jobID}_EWKZ2j_2nu-SUB_MC* 
    PileUpReweight outputFile="EWKZ2Nu.root" dataset="#EWKZ2Jets_ZToNuNu_TuneCP5_13TeV-madgraph-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

    wait;
    #hadd     	--reuse-cache-files ZJets1050.root	/hdfs/store/user/$user/${jobID}_ZJets1050-SUB-MC 
    #hadd 	--reuse-cache-files WWTo2L2Nu.root 	/hdfs/store/user/$user/${jobID}_WWTo2L2Nu-SUB-MC 
    #hadd 	--reuse-cache-files WWTo4Q.root 	/hdfs/store/user/$user/${jobID}_WWTo4Q-SUB-MC 
    #PileUpReweight outputFile= dataset="#WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd 	--reuse-cache-files WWToLNuQQ.root 	/hdfs/store/user/$user/${jobID}_WWToLNuQQ-SUB-MC 
    #PileUpReweight outputFile= dataset="#WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile= dataset="#WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #PileUpReweight outputFile= dataset="#WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM" branch="PUweight"
    #hadd 	--reuse-cache-files ZZTo2L2Q.root 	/hdfs/store/user/$user/${jobID}_ZZTo2L2Q-SUB-MC 
    #PileUpReweight outputFile= dataset="#ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd 	--reuse-cache-files ZZTo4Q.root 	/hdfs/store/user/$user/${jobID}_ZZTo4Q-SUB-MC 
    #hadd 	--reuse-cache-files TT.root 	        /hdfs/store/user/$user/${jobID}_TT-SUB-MC  
    #hadd 	--reuse-cache-files WJetsMLM.root 	/hdfs/store/user/$user/${jobID}_WJetsMLM-SUB-MC 
    #hadd 	--reuse-cache-files t_s.root 	        /hdfs/store/user/$user/${jobID}_t_s-SUB-MC 
    #hadd 	--reuse-cache-files t_s_Ext.root 	/hdfs/store/user/$user/${jobID}_t_Ext-SUB-MC 
    #hadd -f   VVTo2L2Nu.root       /hdfs/store/user/$user/${jobID}_VVTo2L2Nu*/* & 
    #PileUpReweight outputFile= dataset="#VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
    #hadd -f   WWW.root          /hdfs/store/user/$user/${jobID}_WWW-SUB-TT/* &
    #hadd -f   ZZZ.root          /hdfs/store/user/$user/${jobID}_ZZZ-SUB-TT/* &

fi

#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-1200_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-400_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-110_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-350_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-1600_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-1600_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"

#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-1200_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-1800_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-200_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-140_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-1400_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-130_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-1400_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-450_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-450_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-80_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-300_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-140_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-90_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-700_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-600_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-200_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-900_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-1500_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-160_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-1500_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-350_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-2300_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-180_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-2600_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-600_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-2000_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-250_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-180_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-900_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-300_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-100_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-700_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-400_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-2300_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-130_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-2900_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-80_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-110_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-120_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-1800_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-250_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-120_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-2600_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-800_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-3200_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToHToTauTau_M-2900_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-3200_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-90_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-800_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-100_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
#PileUpReweight outputFile= dataset="#SUSYGluGluToBBHToTauTau_M-2000_TuneCP5_13TeV-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM" branch="PUweight"
