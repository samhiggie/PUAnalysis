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

cd $CMSSW_BASE/src

#METSignificance
#git cms-addpkg RecoMET/METProducers