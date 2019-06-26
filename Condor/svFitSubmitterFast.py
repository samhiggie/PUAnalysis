
import sys, getopt

import os
import sys
import glob
import pwd
import argparse
import errno
import socket
import signal
import logging
import math
#parser = argparse.ArgumentParser()
#parser.add_argument("--verbosity", help="increase output verbosity")

def get_parser(desc):
    parser = argparse.ArgumentParser(description=desc)

    #parser.add_argument('channel', default='Z', type=str, choices=['Z','WZ','FakeRate','HZZFakeRate','TT','Hpp2l','Hpp3l','Hpp4l','ZZ','HppAP','HppPP','HppComb','LowMass','Charge','NoVeto'], help='Channel to run for given analysis')
    #parser.add_argument('period', default=13, type=int, choices=[8,13], help='Energy (TeV)')
    #parser.add_argument('-l','--log',nargs='?',type=str,const='INFO',default='INFO',choices=['INFO','DEBUG','WARNING','ERROR','CRITICAL'],help='Log level for logger')

    return parser

def parse_command_line(argv):
    parser = get_parser("Run the desired analyzer on FSA n-tuples")

    #parser.add_argument('sample_names', nargs='+',help='Sample names w/ UNIX wildcards')
    parser.add_argument('-s','--submit',action='store_true',help='Submit jobs to condor')
    parser.add_argument('-dr','--dryrun',action='store_true',help='Create jobs but dont submit')
    parser.add_argument('-t','--test',action='store_true',help='Do a test (output test.root)')
    parser.add_argument('-jn','--jobName',nargs='?',type=str,const='',help='Job Name for condor submission')
    parser.add_argument('-d','--customDir',nargs='?',type=str,const='',help='Custom input directory')
    parser.add_argument('-sd','--sampledir',nargs='?',type=str,const='',help='The Sample Input directory')
    parser.add_argument('-ms','--metShift',nargs='?',type=str,const='',help='Shift the met')
    parser.add_argument('-es','--doES',nargs='?',type=str,const='',help='Doing TES / EES shifts?')
    parser.add_argument('-r','--recoilType',nargs='?',type=str,const='',help='Input files are which recoil type?')
    parser.add_argument('-iswj','--isWJets',nargs='?',type=str,const='',help='Are input files WJets samples?')
    parser.add_argument('-mt','--metType',nargs='?',type=str,const='',help='MvaMet = 1, Pf Met = -1')
    args = parser.parse_args(argv)

    return args

print "svfit standalone submit"

#args = parser.parse_args()

def main(argv=None):
    '''
    Submit a job using farmoutAnalysisJobs --fwklite
    '''
    print "svfit standalone submit"
    #MELA necessary library 
    #os.system("cp  $CMSSW_BASE/src/ZZMatrixElement/MELA/data/$SCRAM_ARCH/libmcfm_705.so $CMSSW_BASE/lib/$SCRAM_ARCH")

#logger = logging.getLogger(__name__)
    args = parse_command_line(argv)
    jobName = args.jobName
    channel = "TauTau"
    period = 13
    dryrun = args.dryrun
    sampledir = args.sampledir
    sample_name = os.path.basename(sampledir)
    print "sample_name:",sample_name
    if sample_name == '' :
        print "SAMPLE_NAME not defined, check for trailing '/' on sampledir path"
        return
    if 'uwlogin' in socket.gethostname():
        sample_dir = '/data/%s/%s/%s' % (pwd.getpwuid(os.getuid())[0], jobName, sample_name)
    else:
        sample_dir = '/nfs_scratch/%s/%s/%s' % (pwd.getpwuid(os.getuid())[0], jobName, sample_name)
        # create submit dir
    submit_dir = '%s/submit' % (sample_dir)
    if os.path.exists(submit_dir):
        print('Submission directory exists for %s %s.' % (jobName, sample_name))
            
# create dag dir
    dag_dir = '%s/dags/dag' % (sample_dir)
    os.system('mkdir -p %s' % (os.path.dirname(dag_dir)))
    os.system('mkdir -p %s' % (dag_dir+'inputs'))

# output dir
    output_dir = '/store/user/%s/%s/%s/'\
        % (pwd.getpwuid(os.getuid())[0], jobName, sample_name)
    #output_dir = 'gsiftp://cms-lvs-gridftp.hep.wisc.edu:2811//hdfs/store/user/%s/%s/%s/'\
    #    % (pwd.getpwuid(os.getuid())[0], jobName, sample_name)

    # create file list
    filelist = ['%s/%s' % (sampledir, x) for x in os.listdir(sampledir)]
    numfiles = len(filelist)
    totalsize = sum([os.path.getsize(f) for f in filelist])
    averagesize = totalsize/numfiles
    #filesperjob = int(math.ceil(50000000./averagesize)) # average them to 50MB per job
    filesperjob = 1
    input_name = '%s/%s.txt' % (dag_dir+'inputs', sample_name)
    with open(input_name,'w') as file:
        for f in filelist:
            file.write('%s\n' % f.replace('/hdfs','gsiftp://cms-lvs-gridftp.hep.wisc.edu:2811//hdfs',1))
            #file.write('%s\n' % f.replace('/hdfs','',1))

# create bash script
    bash_name = '%s/%s_%i_%s.sh' % (dag_dir+'inputs', channel, period, sample_name)
#SVFitStandAlone outputFile="WZ.root" newOutputFile=1.0 newFile="none"
    bashScript = "#!/bin/bash\n value=$(<$INPUT)\n echo \"$value\"\n"
    bashScript += '$CMSSW_BASE/bin/$SCRAM_ARCH/FastMTTStandAlonePUATauDM inputfile=$value newFile=\'$OUTPUT\'' #% (channel, sample_name, period)
    if args.recoilType : recoilType = "recoilType="+args.recoilType
    else : recoilType = ''
    if args.doES : doES = "doES="+args.doES
    else : doES = ''
    if args.isWJets : isWJets = "isWJets="+args.isWJets
    else : isWJets = ''
    if args.metType : metType = "metType="+args.metType
    else : metType = ''
    bashScript += ' %s %s %s %s' % (recoilType, doES, isWJets, metType)
    bashScript += '\n'
    with open(bash_name,'w') as file:
        file.write(bashScript)
    os.system('chmod +x %s' % bash_name)
                
# create farmout command
    farmoutString = 'farmoutAnalysisJobs --site-requirements=\'OpSysAndVer == "SL6"\'  --vsize-limit=8000 --assume-input-files-exist --input-file-list=%s' % (input_name)
    farmoutString += ' --submit-dir=%s --output-dag-file=%s --output-dir=%s' % (submit_dir, dag_dir, output_dir)
#if period == 8:
#    farmoutString += ' --input-files-per-job=20 %s %s' % (jobName, bash_name)
#else:
#    farmoutString += ' --input-files-per-job=10 %s %s' % (jobName, bash_name)
    farmoutString += ' --input-files-per-job=%i %s %s' % (filesperjob, jobName, bash_name)
                
    if not args.dryrun:
        print('Submitting %s' % sample_name)
        os.system(farmoutString)
    else:
        print farmoutString
        
    return


if __name__ == '__main__':
    main()
