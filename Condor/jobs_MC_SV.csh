#!/bin/tcsh
echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node
source /cvmfs/cms.cern.ch/cmsset_default.csh  ## if a bash script, use .sh instead of .csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
xrdcp -s root://cmseos.fnal.gov//store/user/samuellh/CMSSW944.tgz .
tar -xf CMSSW944.tgz
rm CMSSW944.tgz
setenv SCRAM_ARCH slc6_amd64_gcc530
cd Yur_Classic_SV_944/
scramv1 b ProjectRename
eval `scramv1 runtime -csh` # cmsenv is an alias not on the workers
scram b -j 21
echo "Arguments passed to this script are: for 1: $1"
##xrdcp -s root://cmseos.fnal.gov//store/user/samuellh/forIsobel/ztt_weighted_2016_SM/$1 .

xrdcp -s root://cmseos.fnal.gov/$1 .
echo "Copied the file over... see"
ls -lhtr 
echo "Running MELA!"
##EventWeightsIterativeGen outputFile="$1"     weight=1.0       histoName='TT/results' sumHistoName='sumweights/genWeights'
##EventWeightsForEfficiencyTrigger2016 outputFile="$1" 
##MELA_HTT_PUA InFile="$1"
setenv s `echo "$1" | awk -F'[/.]' '{print $6}'`
setenv f `basename $1`
echo "working on file $f"
SVFitStandAlonePUATauDM inputFile="$f"
echo "Done with MELA... transfering File"
#xrdfs root://cmseos.fnal.gov mkdir /store/user/shigginb/testSV/$s
#xrdcp $f root://cmseos.fnal.gov//store/user/shigginb/testSV/$s/.
xrdfs root://cmseos.fnal.gov mkdir /store/user/shigginb/redo2016_processed/$s
xrdcp $f root://cmseos.fnal.gov//store/user/shigginb/redo2016_processed/$s/.
echo "Transfer complete and cleaning up"
### remove the output file if you don't want it automatically transferred when the job ends
#rm $1
cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_9_4_0
