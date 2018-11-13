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

def get_parser(desc):
    parser = argparse.ArgumentParser(description=desc)
    return parser

def parse_command_line(argv):
    parser = get_parser("Run the desired analyzer on FSA n-tuples")

    parser.add_argument('-s','--submit',action='store_true',help='Submit jobs to condor')
    parser.add_argument('-dr','--dryrun',action='store_true',help='Create jobs but dont submit')
    parser.add_argument('-t','--test',action='store_true',help='Do a test (output test.root)')
    parser.add_argument('-jn','--jobName',nargs='?',type=str,const='',help='Job Name for condor submission')
    parser.add_argument('-d','--customDir',nargs='?',type=str,const='',help='Custom input directory')
    parser.add_argument('-sd','--sampledir',nargs='?',type=str,const='',help='The Sample Input directory')
    parser.add_argument('-ms','--metShift',nargs='?',type=str,const='',help='Shift the met')
    args = parser.parse_args(argv)

    return args

print "MELA submit"


def main(argv=None):
    '''
    Submit a job using farmoutAnalysisJobs --fwklite
    '''
    # jobs will fail if you do not copy $CMSSW_BASE/src/ZZMatrixElement/MELA/data/$SCRAM_ARCH/libmcfm_705.so to $CMSSW_BASE/lib/$SCRAM_ARCH
    os.system("cp  $CMSSW_BASE/src/ZZMatrixElement/MELA/data/$SCRAM_ARCH/libmcfm_705.so $CMSSW_BASE/lib/$SCRAM_ARCH")

    print "mela standalone submit"
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
            file.write('%s\n' % f.replace('/hdfs','',1))

# create bash script
    bash_name = '%s/%s_%i_%s.sh' % (dag_dir+'inputs', channel, period, sample_name)
    bashScript = "#!/bin/bash\n value=$(<$INPUT)\n echo \"$value\"\n"
    bashScript += '$CMSSW_BASE/bin/$SCRAM_ARCH/produceMELABranches inputFile=$value newFile=\'$OUTPUT\'' #% (channel, sample_name, period)
    bashScript += '\n'
    with open(bash_name,'w') as file:
        file.write(bashScript)
    os.system('chmod +x %s' % bash_name)
                
# create farmout command
    farmoutString = 'farmoutAnalysisJobs --infer-cmssw-path --fwklite --input-file-list=%s' % (input_name)
    farmoutString += ' --submit-dir=%s --output-dag-file=%s --output-dir=%s' % (submit_dir, dag_dir, output_dir)
    farmoutString += ' --input-files-per-job=%i %s %s' % (filesperjob, jobName, bash_name)
                
    if not args.dryrun:
        print('Submitting %s' % sample_name)
        os.system(farmoutString)
    else:
        print farmoutString
        
    return


if __name__ == '__main__':
    main()
