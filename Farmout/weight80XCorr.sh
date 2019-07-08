#!/bin/sh
infilename=2018_tt_JEC_weighted
filename=2018_tt_JEC_weighted_corr
mkdir /nfs_scratch/$USER/$filename

#for file in ZJETS.root WJETS.root TT.root DiBoson.root ggH120.root ggH125.root ggH130.root vbfH120.root vbfH125.root vbfH130.root ZH120.root  ZH125.root  ZH130.root  WpH120.root WpH125.root WpH130.root WmH120.root WmH125.root WmH130.root ttH120.root ttH125.root ttH130.root 
#for file in ZJETS.root WJETS.root TT.root DiBoson.root ggH125.root vbfH125.root ZH125.root WpH125.root WmH125.root ttH125.root  
#do
cp /nfs_scratch/$USER/$infilename/* /nfs_scratch/$USER/$filename/.
#done
#cp /nfs_scratch/$USER/zpt_weights_2016.root /nfs_scratch/$USER/$filename/.

#mv /nfs_scratch/$USER/$infilename/tauDATA.root /nfs_scratch/$USER/$filename/.

cd /nfs_scratch/$USER/$filename/

#echo "EventWeightsIterativeZPt"
#EventWeightsIterativeZPt
EventWeightsForEfficiencyTrigger2017 outputFile='ZJETS.root'
EventWeightsForEfficiencyTrigger2017 outputFile='WJETS.root'
EventWeightsForEfficiencyTrigger2017 outputFile='TT.root'
EventWeightsForEfficiencyTrigger2017 outputFile='DiBoson.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='ggH120.root'
EventWeightsForEfficiencyTrigger2017 outputFile='ggH125.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='ggH130.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='vbfH120.root'
EventWeightsForEfficiencyTrigger2017 outputFile='vbfH125.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='vbfH130.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='ZH120.root'
EventWeightsForEfficiencyTrigger2017 outputFile='ZH125.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='ZH130.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='WpH120.root'
EventWeightsForEfficiencyTrigger2017 outputFile='WpH125.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='WpH130.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='WmH120.root'
EventWeightsForEfficiencyTrigger2017 outputFile='WmH125.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='WmH130.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='ttH120.root'
EventWeightsForEfficiencyTrigger2017 outputFile='ttH125.root'
#EventWeightsForEfficiencyTrigger2017 outputFile='ttH130.root'


