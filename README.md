PUAnalysis
==========


#Set Up instructions:

```
cmsrel CMSSW_8_0_21 #for 2016 analysis
cd CMSSW_8_0_21/src/
cmsenv
git cms-init 
git clone https://github.com/isobelojalvo/PUAnalysis.git   
export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"
scram b -j 8
```
to run test

```
cd PUAnalysis
cmsRun TT-MC.py
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

