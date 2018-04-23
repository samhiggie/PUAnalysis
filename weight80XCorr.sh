#!/bin/sh
infilename=ztt_weightedSvfit_Feb8
filename=ztt_weightedSvfit_Feb8_Corr
mkdir /data/$USER/$filename

for file in ZJETS.root WJETS.root TT.root DiBoson.root ggH120.root ggH125.root ggH130.root vbfH120.root vbfH125.root vbfH130.root ZH120.root  ZH125.root  ZH130.root  WpH120.root WpH125.root WpH130.root WmH120.root WmH125.root WmH130.root ttH120.root ttH125.root ttH130.root 
do
    cp /data/$USER/$infilename/$file /data/$USER/$filename/.
done
cp /data/$USER/zpt_weights_2016.root /data/$USER/$filename/.

mv /data/$USER/$infilename/tauDATA.root /data/$USER/$filename/.

cd /data/$USER/$filename/

echo "EventWeightsIterativeZPt"
EventWeightsIterativeZPt
EventWeightsForEfficiencyTrigger2016 outputFile='ZJETS.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WJETS.root'
EventWeightsForEfficiencyTrigger2016 outputFile='TT.root'
EventWeightsForEfficiencyTrigger2016 outputFile='DiBoson.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ggH120.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ggH125.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ggH130.root'
EventWeightsForEfficiencyTrigger2016 outputFile='vbfH120.root'
EventWeightsForEfficiencyTrigger2016 outputFile='vbfH125.root'
EventWeightsForEfficiencyTrigger2016 outputFile='vbfH130.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ZH120.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ZH125.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ZH130.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WpH120.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WpH125.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WpH130.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WmH120.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WmH125.root'
EventWeightsForEfficiencyTrigger2016 outputFile='WmH130.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ttH120.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ttH125.root'
EventWeightsForEfficiencyTrigger2016 outputFile='ttH130.root'


