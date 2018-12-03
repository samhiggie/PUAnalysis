#!/bin/sh

#nohup bash ./merge.sh >merge.log & 
#to see if finished running check 'top' and tail below
#tail -f merge.log

#MAKE SURE /scratch/$USER/ is empty!!!
#mkdir /scratch/$USER/ztt_unweighted_Nov21
unweighteddir='ztt_unweighted_Nov21'
weighteddir='ztt_weighted_Nov21_Corr'
cd /scratch/$USER/$unweighteddir
jobID='2018_Nov21'


hadd -f	ggH2Jet_maxmix.root    /hdfs/store/user/$USER/${jobID}_GluGluH2JetsToTauTau_maxmix-SUB_MC/*
hadd -f	ggH2Jet_pseudo.root    /hdfs/store/user/$USER/${jobID}_GluGluH2JetsToTauTau_pseudoscalar-SUB_MC/*
hadd -f	ggH2Jet_smodel.root    /hdfs/store/user/$USER/${jobID}_GluGluH2JetsToTauTau_sm-SUB_MC/*
hadd -f	VBFHiggs0L1.root       /hdfs/store/user/$USER/${jobID}_VBFHiggs0L1_M-125-SUB_MC/*
hadd -f	VBFHiggs0Mf05.root     /hdfs/store/user/$USER/${jobID}_VBFHiggs0Mf05-SUB_MC/*
hadd -f	VBFHiggs0M.root        /hdfs/store/user/$USER/${jobID}_VBFHiggs0M_M-SUB_MC/*
hadd -f	VBFHiggs0PHf05ph0.root /hdfs/store/user/$USER/${jobID}_VBFHiggs0PHf05ph0-SUB_MC/*
hadd -f	VBFHiggs0PH.root       /hdfs/store/user/$USER/${jobID}_VBFHiggs0PH-SUB_MC/*
hadd -f	WHiggs0L1fWH05ph0.root /hdfs/store/user/$USER/${jobID}_WHiggs0L1fWH05ph0-SUB_MC/*
hadd -f	WHiggs0L1.root         /hdfs/store/user/$USER/${jobID}_WHiggs0L1-SUB_MC/*
hadd -f	WHiggs0MfWH05ph0.root  /hdfs/store/user/$USER/${jobID}_WHiggs0MfWH05ph0-SUB_MC/*
hadd -f	WHiggs0M.root          /hdfs/store/user/$USER/${jobID}_WHiggs0M-SUB_MC/*
hadd -f	WHiggs0PHfWH05ph0.root /hdfs/store/user/$USER/${jobID}_WHiggs0PHfWH05ph0-SUB_MC/*
hadd -f	WHiggs0PH.root         /hdfs/store/user/$USER/${jobID}_WHiggs0PH-SUB_MC/*
hadd -f	WHiggs0PM.root         /hdfs/store/user/$USER/${jobID}_WHiggs0PM-SUB_MC/*
hadd -f	Higgs0L1fZH05ph0.root  /hdfs/store/user/$USER/${jobID}_ZHiggs0L1fZH05ph0-SUB_MC/*
hadd -f	ZHiggs0L1.root         /hdfs/store/user/$USER/${jobID}_ZHiggs0L1-SUB_MC/*
hadd -f	ZHiggs0MfZH05ph0.root  /hdfs/store/user/$USER/${jobID}_ZHiggs0MfZH05ph0-SUB_MC/*
hadd -f	ZHiggs0M.root          /hdfs/store/user/$USER/${jobID}_ZHiggs0M-SUB_MC/*
hadd -f	ZHiggs0PHfZH05ph0.root /hdfs/store/user/$USER/${jobID}_ZHiggs0PHfZH05ph0-SUB_MC/*
hadd -f	ZHiggs0PH.root         /hdfs/store/user/$USER/${jobID}_ZHiggs0PH-SUB_MC/*
hadd -f	ZHiggs0PM.root         /hdfs/store/user/$USER/${jobID}_ZHiggs0PM-SUB_MC/*



for dir in ggH2Jet_maxmix.root ggH2Jet_pseudo.root ggH2Jet_smodel.root VBFHiggs0L1.root VBFHiggs0Mf05.root VBFHiggs0M.root VBFHiggs0PHf05ph0.root VBFHiggs0PH.root WHiggs0L1fWH05ph0.root WHiggs0L1.root WHiggs0MfWH05ph0.root WHiggs0M.root WHiggs0PHfWH05ph0.root WHiggs0PH.root WHiggs0PM.root Higgs0L1fZH05ph0.root ZHiggs0L1.root ZHiggs0MfZH05ph0.root ZHiggs0M.root ZHiggs0PHfZH05ph0.root ZHiggs0PH.root ZHiggs0PM.root 
do 
    echo "copying and weighting "$dir
    cp /scratch/$USER/$unweighteddir/$dir /scratch/$USER/$weighteddir/.
    cd /scratch/$USER/$weighteddir/
    EventWeightsIterativeGen outputFile=$dir     weight=1       histoName='TT/results' sumHistoName='sumweights/genWeights' 
    EventWeightsForEfficiencyTrigger2017 outputFile=$dir
done

