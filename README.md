PUAnalysis
==========


#Set Up instructions:

```
cmsrel CMSSW_8_0_21 #for 2016 analysis
cd CMSSW_8_0_21/src/
cmsenv
git cms-init 
git clone --recursive -b Moriond17 https://github.com/isobelojalvo/PUAnalysis.git   
cd PUAnalysis
export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"
scram b -j 8
```
to run test

```
cd PUAnalysis
cmsRun TT-MC.py
```

In general To see what needs to be fixed ``` grep -r FIXME *``` or ``` CHECKME```. 


