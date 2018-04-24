#!/bin/sh

jobID=2017_Oct14
cd /nfs_scratch/$USER/${jobID}_weighted/

#EventWeightsFromHisto histoFile="../PileUp/PileUp2017.root" histoName="pu2017" srcBranch="npv" outputFile='ggH125.root'  
EventWeightsFromHisto histoFile="../PileUp/PileUp2017.root" histoName="pu2017" srcBranch="npv" outputFile='vbfH125.root' 
EventWeightsFromHisto histoFile="../PileUp/PileUp2017.root" histoName="pu2017" srcBranch="npv" outputFile='ZJETS.root'   
EventWeightsFromHisto histoFile="../PileUp/PileUp2017.root" histoName="pu2017" srcBranch="npv" outputFile='WJETS.root'   
EventWeightsFromHisto histoFile="../PileUp/PileUp2017.root" histoName="pu2017" srcBranch="npv" outputFile='TT.root'      
EventWeightsFromHisto histoFile="../PileUp/PileUp2017.root" histoName="pu2017" srcBranch="npv" outputFile='DiBoson.root' 




