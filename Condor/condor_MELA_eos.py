#submit batch jobs for selection plots

import sys, os
import shutil
import getpass
import glob
import argparse
import subprocess
#set paths

parser = argparse.ArgumentParser(description='Submit condor jobs for making histgrams')
parser.add_argument('-i', "--input", default="", help="The input directory where the analyzer output trees are")
parser.add_argument('-o', "--output", default="", help="The output directory for flat trees")
parser.add_argument('-b', "--blind", default=False, action="store_true",  help="Blind the signal region")
parser.add_argument("-a", "--abs", default=False, action="store_true", help="use absolute path")
parser.add_argument("-r", "--reweight", default=True, action="store_false", help="use reweight factor")
parser.add_argument("-t", "--trigger", default=False, action="store_true", help="Don't apply both triggers") 
parser.add_argument("-c", "--control", default=False, action="store_true", help="Control Region")
parser.add_argument("-s", "--scale", default=False, action="store_true", help="Apply Scale Factor")
parser.add_argument("-n", "--notrig", default=False, action="store_true", help="Apply no trigger (for signal)")
parser.add_argument("-l", "--like", default=False, action="store_true", help="Recalculate Likelihood")
parser.add_argument("-j", "--jk", default=False, action="store_true", help="Apply CaloHT reweighting")
parser.add_argument("--ht", default=False, action="store_true", help="Use the HLT_HT425_v Trigger")
parser.add_argument('-fl','--flist',type=argparse.FileType('r'),help='File List of PCC ntuples')

args=parser.parse_args()

current=os.getcwd()
basefolder=args.input
#bashjob="MELA_HTT"
#bashjob="jobs_JHU_weight.csh"
bashjob="jobs_MC.csh"
pathbashjob="{0}/{1}".format(current, bashjob)
#pyscript="perModuleXSEC_2017format.py"
#pathpyscript="{0}/{1}".format(current, pyscript)

#root_files = glob.glob("{0}/*.root".format(basefolder))
if args.flist!="":
    root_files=[]
    with args.flist as f:
        print "Found list ",f
        lines = f.readlines()
        for line in lines:
            root_files.append(line.split('\n')[0])

if args.abs:
    root_files=glob.glob("/eos/uscms{0}/*.root".format(basefolder))
    #root_files = subprocess.check_output(["eosls", "{0}/*.root".format(basefolder)])
i=0
for rootfile in root_files:
    print("+look at the root file: {0}".format(rootfile))
    if args.abs:
        rootfile=rootfile[rootfile.find("/store"): ]
    #rootfile = rootfile.lstrip("/eos/uscms")
    print rootfile
    folder0 = rootfile.split("/")[-1].rstrip(".root")
    #folder1 = rootfile.split("/")[-2]

    folder = args.output+"/"
    if not os.path.isdir(folder): os.mkdir(folder)
    folder = folder+folder0
    if not os.path.isdir(folder): os.mkdir(folder)

    os.chdir(folder)

    #shutil.copyfile(pathpyscript, pyscript)
    shutil.copyfile(pathbashjob, bashjob)

    if not args.reweight:
        REWEIGHT="-r "
    else:
        REWEIGHT=""
   
    if args.blind:
        BLIND="-b"
    else:
        BLIND=""
  
    if args.trigger:
        TRIGGER="-t"
    else:
        TRIGGER=""
    
    if args.control:
        Control="-c"
    else:
        Control=""

    if args.scale:
        SCALE="-s"
    else:
        SCALE=""

    if args.notrig:
        NOTRIG="-n"
    else:
        NOTRIG=""

    if args.ht:
        HTTRIG="--ht"
    else:
        HTTRIG=""

    if args.like:
        LIKE="-l"
    else:
        LIKE=""

    if args.jk:
        JK="--jk"
    else:
        JK=""

    condor_filename="analyze_condor_{0}".format(folder0)
    fcondor=open(condor_filename, "w")
    fcondor.write("Executable = {0}\n".format(bashjob))
    fcondor.write("Universe = vanilla\n")
    fcondor.write("use_x509userproxy = true\n")
    #fcondor.write("transfer_input_files = perModuleXSEC_2017format.py\n") 
    #fcondor.write("transfer_input_files = MELA_HTT,libDataFormatsCTPPSReco.so,libPUAnalysisDataFormats.so,libPUAnalysisNtupleTools.so,libPUAnalysisRecoTools.so,libTauAnalysisSVfitStandalone.so,libZZMatrixElementMEKD.so,libZZMatrixElementMELA.so,libZZMatrixElementMEMCalculators.so,libZZMatrixElementPythonWrapper.so,libcollier.so,libjhugenmela.so,libmcfm_705.so,pluginPUAnalysisNtupleTools_plugins.so,pluginPUAnalysisRecoTools_plugins.so\n") 
    fcondor.write("transfer_executable = TRUE\n") 
    fcondor.write("should_transfer_files = YES\n")
    fcondor.write("Output = {0}/{1}/run.out\n".format(current, folder))
    fcondor.write("Error  = {0}/{1}/run.err\n".format(current, folder))
    fcondor.write("Log    = {0}/{1}/run.log\n".format(current, folder))
    if args.abs:
        rootfile="root://cmsxrootd.fnal.gov/"+rootfile
        #fcondor.write("Arguments = {0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10} {11}\n".format(pyscript, rootfile, folder0, REWEIGHT, BLIND, TRIGGER, Control, SCALE, NOTRIG, HTTRIG, LIKE, JK))
        #fcondor.write("Arguments = {0} {1} {2}\n".format(pyscript, rootfile,i))
        fcondor.write("Arguments = {0}\n".format(rootfile))
    else:
        #fcondor.write("Arguments = {0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10} {11}\n".format(pyscript, current+"/"+rootfile, folder0, REWEIGHT, BLIND, TRIGGER, Control, SCALE, NOTRIG, HTTRIG, LIKE, JK))
        #fcondor.write("Arguments = {0} {1} {2}\n".format(pyscript, rootfile,i))
        fcondor.write("Arguments = {0}\n".format(rootfile))
    fcondor.write("Queue\n")
    fcondor.close()
    i=i+1
    
    #os.system("chmod +x {0} {1} analyze_condor_{2}".format(bashjob,pyscript, folder0))
    os.system("chmod +x {0} analyze_condor_{1}".format(bashjob, folder0))
    #os.system("cp /uscms_data/d3/samuellh/WorkingArea/CpHiggs/CMSSW_8_0_21/bin/slc6_amd64_gcc530/* .")
    #os.system("cp /uscms_data/d3/samuellh/WorkingArea/CpHiggs/CMSSW_8_0_21/lib/slc6_amd64_gcc530/* .")
    os.system("condor_submit analyze_condor_{0}".format(folder0))
 
    os.chdir(current)
