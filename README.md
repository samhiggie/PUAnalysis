PUAnalysis
==========


#Set Up instructions:

```
cmsrel CMSSW_8_0_29 #for 2016 analysis
cd CMSSW_8_0_29/src/
cmsenv
git cms-init 
git clone https://github.com/isobelojalvo/PUAnalysis.git   
export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"
cd PUAnalysis
git fetch origin
git checkout devel_Htt_Mar_7
bash recipe.sh #Note Recipe13TeV.sh should be the full recipe but we are keeping it simple for now
scram b -j 8
```
to run test of analysis fw

```
cd PUAnalysis
cmsRun TT-MC.py
```

__To create Htt plots, these are the main files used for running are:__
PUAnalysis/StatTools/data/sm_higgs_tautau/makeTauTauPlots_Published
PUAnalysis/StatTools/data/sm_higgs_tautau/makeTemplatePlotsDiTau.C

__For Datacard creation:__
PUAnalysis/StatTools/interface/DataCardCreatorHThTh_2016.h
PUAnalysis/StatTools/bin/MakeDataCardHThTh_2016.cc

__And for plotting:__
PUAnalysis/ROOT/plotMacros/makePlotHThTh.C


```
cd PUAnalysis/StatTools/data/sm_higgs_tautau/
##First check to see the $direc variable is sourced to a place that actually contains your root files!
bash makeTauTauPlots_Published
#wait...
#Check to see where your files are being saved, I save to ~/www/ which is a private structure setup.
root -l -b -q makeTemplatePlotsDiTau.C
```

The output file, analysis.root

In general To see what needs to be fixed ``` grep -r FIXME *``` or ``` CHECKME```. 


| Kind Of Issue  | Issue Detail |
| ------------- | ------------- |
| ES Scaling    | Put me back?  |
| Cut Sequence Producer | Can still be reduced |
| Farmout/Crab tools | need to be updated, not currently checked|
| configuration sequence | check me |
| ntuple tools | reduce tree size |
| 4 lepton final state| still needs to be finished for 2017 analyses |

