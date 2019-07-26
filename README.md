PUAnalysis
==========


#Set Up instructions:

```
cmsrel CMSSW_10_2_14 #for 2017 analysis
cd CMSSW_10_2_14/src/
cmsenv
git cms-init 
git clone https://github.com/samhiggie/PUA.git   
export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"
cd PUAnalysis
git fetch origin
git checkout cmssw10_2_14_2018
bash recipe.sh 
scram b -j 8
```
to run test of analysis fw - that is going from miniAOD sample to ntuple

```
cd PUAnalysis
cmsRun TT-MC.py
```
The output ntuple is __analysis.root__


__To create Htt plots, these are the main files used for running are:__
PUAnalysis/StatTools/data/sm_higgs_tautau_2017/makeTauTauPlots_Published
PUAnalysis/StatTools/data/sm_higgs_tautau_2017/makeTemplatePlotsDiTau.C

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

In general To see what needs to be fixed ``` grep -r FIXME *``` or ``` CHECKME```. 


| Kind Of Issue  | Issue Detail |
| ------------- | ------------- |
| Ntupler  | |
| ------------- | ------------- |
| ES Scaling    |   |
| ES Scaling    | Put me back?  |
| Fix FF fractions | FF fractions currently hardcoded |
| Plotting |  |
| ------------- | ------------- |
| TES 
| FF uncertainties | include them!|
| JES plotter | Make tools more friendly for JES studies |

