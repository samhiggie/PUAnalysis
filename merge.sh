#!/bin/sh

#nohup bash ./merge.sh >merge.log & 
#to see if finished running check 'top' and tail below
#tail -f merge.log

#MAKE SURE /scratch/$USER/ is empty!!!
mkdir /nfs_scratch/$USER/ztt_unweighted11
cd /nfs_scratch/$USER/ztt_unweighted11


mergedata=1;
mergemc=0;
mergeqcd=0;
mergeW=0;
mergehiggs=0;

#TAU2016B_Jul21-SUB-TT-JSON/
#TAU2016C_Jul21-SUB-TT-JSON/
#TAU2016E_Jul21-SUB-TT-JSON/
#TAU2016F_Jul21-SUB-TT-JSON/

if [ $mergedata -eq 1 ]
    then
    /cms/sw/farmout/mergeFiles 	--reuse-cache-files tauDATA-B.root 	/hdfs/store/user/$USER/TAU2016B_Jul21-SUB-TT-JSON
    /cms/sw/farmout/mergeFiles 	--reuse-cache-files tauDATA-C.root 	/hdfs/store/user/$USER/TAU2016C_Jul21-SUB-TT-JSON
    /cms/sw/farmout/mergeFiles 	--reuse-cache-files tauDATA-D.root 	/hdfs/store/user/$USER/TAU2016D_Jul21-SUB-TT-JSON
    /cms/sw/farmout/mergeFiles 	--reuse-cache-files tauDATA-E.root 	/hdfs/store/user/$USER/TAU2016E_Jul21-SUB-TT-JSON
    hadd -f tauDATA.root tauDATA-*root
fi

if [ $mergeqcd -eq 1 ]
    then
    #/cms/sw/farmout/mergeFiles 		--reuse-cache-files muQCD.root /hdfs/store/user/$USER/25ns_muQCD-SUB-MC 
    #/cms/sw/farmout/mergeFiles 		--reuse-cache-files emQCD.root /hdfs/store/user/$USER/25ns_emQCD-SUB-MC 
    /cms/sw/farmout/mergeFiles --reuse-cache-files QCDBCtoE_30.root /hdfs/store/user/$USER/25ns_QCDBCtoE_30-SUB-MC  
    /cms/sw/farmout/mergeFiles --reuse-cache-files QCDBCtoE_80.root /hdfs/store/user/$USER/25ns_QCDBCtoE_80-SUB-MC  
    /cms/sw/farmout/mergeFiles --reuse-cache-files QCDBCtoE_170.root /hdfs/store/user/$USER/25ns_QCDBCtoE_170-SUB-MC  
    /cms/sw/farmout/mergeFiles --reuse-cache-files QCDBCtoE_250.root /hdfs/store/user/$USER/25ns_QCDBCtoE_250-SUB-MC  
fi 

if [ $mergehiggs -eq 1 ]
    then
    /cms/sw/farmout/mergeFiles --reuse-cache-files ggH.root /hdfs/store/user/$USER/25ns_ggHtautau-SUB-MC 
    /cms/sw/farmout/mergeFiles --reuse-cache-files vbfH.root /hdfs/store/user/$USER/25ns_vbfHtautau-SUB-MC 
fi 

if [ $mergeW -eq 1 ]
    then
    /cms/sw/farmout/mergeFiles --reuse-cache-files WJetsHT100.root /hdfs/store/user/$USER/25ns_WJetsHT100-SUB-MC 
    /cms/sw/farmout/mergeFiles --reuse-cache-files WJetsHT200.root /hdfs/store/user/$USER/25ns_WJetsHT200-SUB-MC 
    /cms/sw/farmout/mergeFiles --reuse-cache-files WJetsHT400.root /hdfs/store/user/$USER/25ns_WJetsHT400-SUB-MC 
    /cms/sw/farmout/mergeFiles --reuse-cache-files WJetsHT600.root /hdfs/store/user/$USER/25ns_WJetsHT600-SUB-MC 
fi 


#2016_80X_St_t_antitop-SUB-TT/
#2016_80X_tBar_tW-SUB-TT/
#2016_80X_TT-SUB-TT/
#2016_80X_t_tW-SUB-TT/
#2016_80X_WJets_amc-SUB-TT/
#2016_80X_WW-SUB-TT/
#2016_80X_WWTo2L2Q-SUB-TT/
#2016_80X_WZ-SUB-TT/
#2016_80X_WZTo1L1Nu2Q-SUB-TT/
#2016_80X_WZTo1L3Nu-SUB-TT/
#2016_80X_Z1Jets-SUB-TT/
#2016_80X_Z2Jets-SUB-TT/
#2016_80X_Z3Jets-SUB-TT/
#2016_80X_Z4Jets-SUB-TT/
#2016_80X_ZJets_150-SUB-TT/
#2016_80X_ZJets-SUB-TT/
#2016_80X_ZZ-SUB-TT/
#2016_80X_ZZTo2L2Q-SUB-TT/
#2016_80X_ZZTo4L-SUB-TT/

jobID='2016_80X'
if [ $mergemc -eq 1 ]
    then
    #uncomment below for SM Backgorund sample
    /cms/sw/farmout/mergeFiles  	--reuse-cache-files tBar.root 	        /hdfs/store/user/$USER/${jobID}_tBar_tW-SUB-MC
    /cms/sw/farmout/mergeFiles  	--reuse-cache-files TTJets.root         /hdfs/store/user/$USER/${jobID}_TTJets-SUB-MC 
    /cms/sw/farmout/mergeFiles  	--reuse-cache-files t.root 	        /hdfs/store/user/$USER/${jobID}_t_tW-SUB-MC 
    /cms/sw/farmout/mergeFiles  	--reuse-cache-files WJets.root 	        /hdfs/store/user/$USER/${jobID}_WJets-SUB-MC 
    /cms/sw/farmout/mergeFiles 		--reuse-cache-files WW.root     	/hdfs/store/user/$USER/${jobID}_WW-SUB-MC 
    /cms/sw/farmout/mergeFiles  	--reuse-cache-files WZ.root 	        /hdfs/store/user/$USER/${jobID}_WZJets-SUB-MC
    /cms/sw/farmout/mergeFiles 		--reuse-cache-files ZJets.root	        /hdfs/store/user/$USER/${jobID}_ZJets-SUB-MC 
    #/cms/sw/farmout/mergeFiles        	--reuse-cache-files ZJets1050.root	/hdfs/store/user/$USER/${jobID}_ZJets1050-SUB-MC 
    /cms/sw/farmout/mergeFiles 		--reuse-cache-files ZZ.root             /hdfs/store/user/$USER/${jobID}_ZZ-SUB-MC 

    #/cms/sw/farmout/mergeFiles 	--reuse-cache-files WWTo2L2Nu.root 	/hdfs/store/user/$USER/${jobID}_WWTo2L2Nu-SUB-MC 
    #/cms/sw/farmout/mergeFiles 	--reuse-cache-files WWTo4Q.root 	/hdfs/store/user/$USER/${jobID}_WWTo4Q-SUB-MC 
    #/cms/sw/farmout/mergeFiles 	--reuse-cache-files WWToLNuQQ.root 	/hdfs/store/user/$USER/${jobID}_WWToLNuQQ-SUB-MC 
    #/cms/sw/farmout/mergeFiles 	--reuse-cache-files ZZTo2L2Q.root 	/hdfs/store/user/$USER/${jobID}_ZZTo2L2Q-SUB-MC 
    #/cms/sw/farmout/mergeFiles 	--reuse-cache-files ZZTo4Q.root 	/hdfs/store/user/$USER/${jobID}_ZZTo4Q-SUB-MC 
    #nohup /cms/sw/farmout/mergeFiles 	--reuse-cache-files TT.root 	        /hdfs/store/user/$USER/${jobID}_TT-SUB-MC & 
    #nohup /cms/sw/farmout/mergeFiles 	--reuse-cache-files WJetsMLM.root 	/hdfs/store/user/$USER/${jobID}_WJetsMLM-SUB-MC &
    #nohup /cms/sw/farmout/mergeFiles 	--reuse-cache-files t_s.root 	        /hdfs/store/user/$USER/${jobID}_t_s-SUB-MC &
    #nohup /cms/sw/farmout/mergeFiles 	--reuse-cache-files t_s_Ext.root 	/hdfs/store/user/$USER/${jobID}_t_Ext-SUB-MC &
fi

