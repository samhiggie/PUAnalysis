#!/bin/bash

pushd $CMSSW_BASE/src
cd PUAnalysis
git clone -b tauTriggers2017_reMiniaod_test  https://github.com/truggles/TauTriggerSFs2017.git TauTriggerSFs2017

pushd $CMSSW_BASE/src
git clone https://github.com/CMS-HTT/LeptonEff-interface.git HTT-utilities
cd HTT-utilities/LepEffInterface/
git clone https://github.com/CMS-HTT/LeptonEfficiencies.git data
pushd $CMSSW_BASE/src


git clone https://github.com/CMS-HTT/RecoilCorrections.git  HTT-utilities/RecoilCorrections 
pushd $CMSSW_BASE/src

git cms-merge-topic guitargeek:EgammaID_9_4_X
pushd $CMSSW_BASE/src

git cms-merge-topic cms-met:METFixEE2017_949_v2

cd $CMSSW_BASE/src


#METSignificance
#git cms-addpkg RecoMET/METProducers
git cms-merge-topic cms-met:METFixEE2017_949_v2


#MELA
git clone https://github.com/cms-analysis/HiggsAnalysis-ZZMatrixElement.git ZZMatrixElement
cd ZZMatrixElement/
bash setup.sh -j 12

cd $CMSSW_BASE/src

#SV-fit and TauAnalysis Tools
git clone -b fastMTT_21_06_2018 https://github.com/SVfit/ClassicSVfit TauAnalysis/ClassicSVfit #### for fast mtt use this branch -b fastMTT_21_06_2018
git clone https://github.com/SVfit/SVfitTF TauAnalysis/SVfitTF
pushd $CMSSW_BASE/src

cd $CMSSW_BASE/src

