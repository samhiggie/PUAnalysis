#!/bin/bash


pushd $CMSSW_BASE/src
git clone https://github.com/CMS-HTT/LeptonEff-interface.git HTT-utilities
cd HTT-utilities/LepEffInterface/
git clone https://github.com/CMS-HTT/LeptonEfficiencies.git data
pushd $CMSSW_BASE/src


git clone https://github.com/CMS-HTT/RecoilCorrections.git  HTT-utilities/RecoilCorrections 
pushd $CMSSW_BASE/src

git cms-merge-topic guitargeek:ElectronID_MVA2017_940pre3
cd $CMSSW_BASE/external

# below, you may have a different architecture, this is just one example from lxplus
cd slc6_amd64_gcc630/
git clone https://github.com/lsoffi/RecoEgamma-PhotonIdentification.git data/RecoEgamma/PhotonIdentification/data
cd data/RecoEgamma/PhotonIdentification/data
git checkout CMSSW_9_4_0_pre3_TnP
cd $CMSSW_BASE/external
cd slc6_amd64_gcc630/
git clone https://github.com/lsoffi/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data
cd data/RecoEgamma/ElectronIdentification/data
git checkout CMSSW_9_4_0_pre3_TnP
# Go back to the src/
cd $CMSSW_BASE/src


#METSignificance
#git cms-addpkg RecoMET/METProducers