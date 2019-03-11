#!/bin/sh
infilename=ztt_weighted_Nov21
filename=ztt_weighted_Nov21_Corr
mkdir /scratch/$USER/$filename

for file in ZJETS.root WJETS.root TT.root DiBoson.root ggH120.root ggH125.root ggH130.root vbfH120.root vbfH125.root vbfH130.root ZH120.root  ZH125.root  ZH130.root  WpH120.root WpH125.root WpH130.root WmH120.root WmH125.root WmH130.root ttH120.root ttH125.root ttH130.root 
do
    cp /scratch/$USER/$infilename/$file /scratch/$USER/$filename/.
done

mv /scratch/$USER/$infilename/tauDATA.root /scratch/$USER/$filename/.

cd /scratch/$USER/$filename/

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


hadd -f WH125.root WpH125.root WmH125.root