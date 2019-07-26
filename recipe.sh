#!/bin/bash

pushd $CMSSW_BASE/src
cd PUAnalysis
#git clone -b final_2017_MCv2 https://github.com/cms-tau-pog/TauTriggerSFs $CMSSW_BASE/src/TauAnalysisTools/TauTriggerSFs
cp -r /afs/hep.wisc.edu/home/samuellh/WorkingArea/HTT/Sam_2017/src/PUAnalysis/TauTriggerSFs2017 .

pushd $CMSSW_BASE/src
git clone https://github.com/CMS-HTT/LeptonEff-interface.git HTT-utilities
cd HTT-utilities/LepEffInterface/
git clone https://github.com/CMS-HTT/LeptonEfficiencies.git data
pushd $CMSSW_BASE/src


git clone https://github.com/CMS-HTT/RecoilCorrections.git  HTT-utilities/RecoilCorrections 
pushd $CMSSW_BASE/src

#git cms-merge-topic guitargeek:EgammaID_9_4_X
#pushd $CMSSW_BASE/src
#
#git cms-merge-topic cms-met:METFixEE2017_949_v2

cd $CMSSW_BASE/src


#METSignificance
#git cms-addpkg RecoMET/METProducers
#git cms-merge-topic cms-met:METFixEE2017_949_v2


#MELA
#git clone https://github.com/cms-analysis/HiggsAnalysis-ZZMatrixElement.git ZZMatrixElement
#cd ZZMatrixElement/
#bash setup.sh -j 12

cd $CMSSW_BASE/src
#FakeFactor methods
git clone https://github.com/CMS-HTT/Jet2TauFakes.git HTTutilities/Jet2TauFakes
cd HTTutilities/Jet2TauFakes
git checkout v0.2.2
##scram b
mkdir data
#git clone -b 2017 ssh://git@gitlab.cern.ch:7999/cms-htt/Jet2TauFakesFiles.git data
#git clone -b 2017 git@gitlab.cern.ch:7999/cms-htt/Jet2TauFakesFiles.git data
cp -r /afs/hep.wisc.edu/home/samuellh/WorkingArea/HTT/Sam_2017/src/HTTutilities/Jet2TauFakes/data/2018/ .
cd $CMSSW_BASE/src
#SV-fit and TauAnalysis Tools
git clone -b fastMTT_21_06_2018 https://github.com/SVfit/ClassicSVfit TauAnalysis/ClassicSVfit #### for fast mtt use this branch -b fastMTT_21_06_2018
git clone https://github.com/SVfit/SVfitTF TauAnalysis/SVfitTF
pushd $CMSSW_BASE/src


#for rivet tool
cd $CMSSW_BASE/src 
git cms-addpkg Configuration/Generator
git cms-addpkg GeneratorInterface/RivetInterface
git cms-addpkg SimDataFormats/HTXS
git clone https://gitlab.cern.ch/cms-gen/Rivet.git
cd GeneratorInterface/RivetInterface/plugins/
rm HTXSRivetProducer.cc
wget https://raw.githubusercontent.com/amarini/cmssw/htxs_stage1p1_cmssw949_v2/GeneratorInterface/RivetInterface/plugins/HTXSRivetProducer.cc
cd $CMSSW_BASE/src
cd SimDataFormats/HTXS/interface/
rm HiggsTemplateCrossSections.h
wget https://raw.githubusercontent.com/amarini/cmssw/htxs_stage1p1_cmssw949_v2/SimDataFormats/HTXS/interface/HiggsTemplateCrossSections.h
cd $CMSSW_BASE/src
cd GeneratorInterface/RivetInterface/src/
rm HiggsTemplateCrossSections.cc
wget https://raw.githubusercontent.com/amarini/cmssw/htxs_stage1p1_cmssw949_v2/GeneratorInterface/RivetInterface/src/HiggsTemplateCrossSections.cc
cd $CMSSW_BASE/src
source Rivet/rivetSetup.sh
rm Rivet/TOP/src/CMS_2016_I1491950.cc
rm Rivet/TOP/src/CMS_2016_PAS_TOP_15_006.cc

export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"

echo "Time to do! scram b -j 21"
