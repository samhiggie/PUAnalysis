#!/bin/sh

#nohup bash ./merge.sh >merge.log & 
#to see if finished running check 'top' and tail below
#tail -f merge.log

#2018_Oct_2017Data_ALL_data_tau_D_tautau-SUB_Data
#MAKE SURE /scratch/$USER/ is empty!!!
mkdir /scratch/$USER/ztt_unweighted_Nov10
cd /scratch/$USER/ztt_unweighted_Nov10
#2018_Oct_2017Data_ALL_data_tau_E_tautau-SUB_Data/
jobID='2018_Oct_2017Data_ALL_data_tau'


mergedata=0;
mergemc=1;
mergeW=0;
mergeZ=0;
mergehiggs=0;
#2018_Oct_2017Data_ALL_data_tau_F_tautau-SUB_Data/
if [ $mergedata -eq 1 ]
    then
    hadd -f tauDATA-B.root 	/hdfs/store/user/samuellh/${jobID}_B_tautau-SUB_Data/* &
    hadd -f tauDATA-C.root 	/hdfs/store/user/samuellh/${jobID}_C_tautau-SUB_Data/* &
    hadd -f tauDATA-D.root 	/hdfs/store/user/samuellh/${jobID}_D_tautau-SUB_Data/* &
    hadd -f tauDATA-E.root 	/hdfs/store/user/samuellh/${jobID}_E_tautau-SUB_Data/* &
    hadd -f tauDATA-F.root 	/hdfs/store/user/samuellh/${jobID}_F_tautau-SUB_Data/* &
    #hadd -f tauDATA-G.root 	/hdfs/store/user/samuellh/${jobID}_G_tautau-SUB_Data/* &
    #hadd -f tauDATA-H.root 	/hdfs/store/user/samuellh/${jobID}_H-*/* &

    wait;
    hadd -f tauDATA.root tauDATA-B.root tauDATA-C.root tauDATA-D.root tauDATA-E.root tauDATA-F.root
fi

jobID='2018_Oct_2017MC_ALL_v14_tautau'
#2018_Oct_2017MC_ggH_ggHtautau_125-SUB/
if [ $mergehiggs -eq 1 ]
    then #ggHtautau_125
    #hadd -f  ggH110.root /hdfs/store/user/samuellh/${jobID}_ggHtautau_110-SUB-TT/* &
    #hadd -f  ggH120.root /hdfs/store/user/samuellh/${jobID}_ggHtautau_120-SUB-TT/* &
#2018_Oct_2017MC_ALL_v14_tautau_ggH125_ext-SUB
    hadd -f  ggH125.root /hdfs/store/user/samuellh/${jobID}_ggH125_ext-SUB/* &
    #hadd -f  ggH130.root /hdfs/store/user/samuellh/${jobID}_ggHtautau_130-SUB-TT/* &
    #hadd -f  ggH140.root /hdfs/store/user/samuellh/${jobID}_ggHtautau_140-SUB-TT/* &
#2018_Oct_2017MC_ALL_v14_tautau_vbfH125-SUB/
    #hadd -f  vbfH120.root /hdfs/store/user/samuellh/${jobID}_vbfHtautau_110-SUB-TT/* &
    #hadd -f  vbfH120.root /hdfs/store/user/samuellh/${jobID}_vbfHtautau_120-SUB-TT/* &
    hadd -f  vbfH125.root /hdfs/store/user/samuellh/${jobID}_vbfH125-SUB/* &
    #hadd -f  vbfH130.root /hdfs/store/user/samuellh/${jobID}_vbfHtautau_130-SUB-TT/* &
    #hadd -f  vbfH130.root /hdfs/store/user/samuellh/${jobID}_vbfHtautau_140-SUB-TT/* &

    #hadd -f  WpH120.root /hdfs/store/user/samuellh/${jobID}_WpHtautau_120-SUB-TT/* &
#2018_Oct_2017MC_ALL_v14_tautau_WHplus-SUB
    hadd -f  WpH125.root /hdfs/store/user/samuellh/${jobID}_WHplus-SUB/* &
    #hadd -f  WpH130.root /hdfs/store/user/samuellh/${jobID}_WpHtautau_130-SUB-TT/* &

    #hadd -f  WmH120.root /hdfs/store/user/samuellh/${jobID}_WmHtautau_120-SUB-TT/* &
    hadd -f  WmH125.root /hdfs/store/user/samuellh/${jobID}_WHminus-SUB/* &
    #hadd -f  WmH130.root /hdfs/store/user/samuellh/${jobID}_WmHtautau_130-SUB-TT/* &

    #hadd -f  ZH120.root /hdfs/store/user/samuellh/${jobID}_ZHtautau_120-SUB-TT/* &
    hadd -f  ZH125.root /hdfs/store/user/samuellh/${jobID}_ZH-SUB/* &
    #hadd -f  ZH130.root /hdfs/store/user/samuellh/${jobID}_ZHtautau_130-SUB-TT/* &

    #hadd -f  ttH120.root /hdfs/store/user/samuellh/${jobID}_ttHtautau_120-SUB-TT/* &
    hadd -f  ttH125.root /hdfs/store/user/samuellh/${jobID}_ttH-SUB/* &
    #hadd -f  ttH130.root /hdfs/store/user/samuellh/${jobID}_ttHtautau_130-SUB-TT/* &
    wait;
#/hdfs/store/user/ojalvo/2016_Sep23_vbfHtautau_125-SUB-TT
fi 

if [ $mergeW -eq 1 ]
    then
#    hadd -f  WJetsMLM.root /hdfs/store/user/samuellh/${jobID}_WJets-SUB-TT/* & 
    hadd -f  W1Jets.root /hdfs/store/user/samuellh/${jobID}i_W1J_lnu-SUB/* & 
    hadd -f  W2Jets.root /hdfs/store/user/samuellh/${jobID}_W2J_lnu-SUB/* & 
    hadd -f  W3Jets.root /hdfs/store/user/samuellh/${jobID}_W3J_lnu-SUB/* & 
    hadd -f  W4Jets.root /hdfs/store/user/samuellh/${jobID}_W4J_lnu-SUB/* & 
    hadd -f  WJets_ext.root /hdfs/store/user/samuellh/${jobID}_WJ_lnu_ext-SUB/* & 
    hadd -f  WJets.root /hdfs/store/user/samuellh/${jobID}_WJ_lnu-SUB/* & 
    wait;
fi 

if [ $mergeZ -eq 1 ]
    then
    ##merge nominal and extension at the same time
    hadd -f  ZJets.root  /hdfs/store/user/samuellh/${jobID}_DYJ*-SUB/* & 
    hadd -f  Z1Jets.root /hdfs/store/user/samuellh/${jobID}_DY1*-SUB/* & 
    hadd -f  Z2Jets.root /hdfs/store/user/samuellh/${jobID}_DY2*-SUB/* & 
    hadd -f  Z3Jets.root /hdfs/store/user/samuellh/${jobID}_DY3*-SUB/* & 
    hadd -f  Z4Jets.root /hdfs/store/user/samuellh/${jobID}_DY4-SUB/* & 
    #hadd -f  ZJets_150.root /hdfs/store/user/samuellh/${jobID}_ZJets_150-SUB-TT/*  
    wait;
fi 

if [ $mergemc -eq 1 ]
    then

   #uncomment below for SM Backgorund sample 2016_Sep23_TT-SUB-TT
    #hadd -f   TT.root           /hdfs/store/user/samuellh/${jobID}_TT-SUB-TT/* & 
    hadd -f   TT_had.root 	/hdfs/store/user/samuellh/${jobID}_TT_had-SUB/*  
    hadd -f   TT_SL.root 	/hdfs/store/user/samuellh/${jobID}_TT_sl-SUB/*  
    hadd -f   TT_DL.root 	/hdfs/store/user/samuellh/${jobID}_TT_2l2nu-SUB/*  

    #hadd -f   WZ.root 	        /hdfs/store/user/samuellh/${jobID}_WZ-SUB-TT/* 
    hadd -f   WZTo1L3Nu.root    /hdfs/store/user/samuellh/${jobID}_WZ_1l3nu-SUB/* & 
    hadd -f   WZTo1L1Nu2Q.root  /hdfs/store/user/samuellh/${jobID}_WZ_lnu2q-SUB/* & 
    hadd -f   WZTo2L2Q.root     /hdfs/store/user/samuellh/${jobID}_WZ_2l2q-SUB/* & 
    hadd -f   WZTo3L1Nu.root    /hdfs/store/user/samuellh/${jobID}_WZ_3lnu-SUB/* & 
    #hadd -f   WZJTo3L1Nu.root    /hdfs/store/user/samuellh/${jobID}_WZJTo3L1Nu-SUB-TT/* & 

    hadd -f   tBar_tW.root 	/hdfs/store/user/samuellh/${jobID}_ST_tw_at-SUB/* &
    hadd -f   t_tW.root 	/hdfs/store/user/samuellh/${jobID}_ST_tW_t-SUB/* & 
    hadd -f   St_tBar.root 	/hdfs/store/user/samuellh/${jobID}_ST_t_at-SUB/* &
    hadd -f   St_t.root 	/hdfs/store/user/samuellh/${jobID}_ST_t_t-SUB/* & 

    #hadd -f   WW.root           /hdfs/store/user/samuellh/${jobID}_WW-SUB-TT/* & 
    hadd -f   WWTo1L1Nu2Q.root  /hdfs/store/user/samuellh/${jobID}_WW_lnu2q*-SUB/* & 
    hadd -f   WWTo4Q.root       /hdfs/store/user/samuellh/${jobID}_WW_4q-SUB/* & 
    hadd -f   WWTo2L2Nu.root    /hdfs/store/user/samuellh/${jobID}_WW_2l2nu-SUB/* & 

    #hadd -f   ZZ.root           /hdfs/store/user/samuellh/${jobID}_ZZ-SUB-TT/* & 
    hadd -f   ZZTo2L2Q.root     /hdfs/store/user/samuellh/${jobID}_ZZ_2l2q-SUB/* & 
    hadd -f   ZZTo2L2Nu.root    /hdfs/store/user/samuellh/${jobID}_ZZ_2l2nu-SUB/* & 
    hadd -f   ZZTo4L.root       /hdfs/store/user/samuellh/${jobID}_ZZ_4l*-SUB/* & 

    hadd -f   EWKWp2j.root      /hdfs/store/user/samuellh/${jobID}_EWKWPlus2j-SUB/* &
    hadd -f   EWKWm2j.root      /hdfs/store/user/samuellh/${jobID}_EWKWminus2j-SUB/* &
    hadd -f   EWKZ2l.root       /hdfs/store/user/samuellh/${jobID}_EWKZ2j_2l-SUB/* &
    hadd -f   EWKZ2Nu.root      /hdfs/store/user/samuellh/${jobID}_EWKZ2j_2nu-SUB/* &
    #hadd -f   VVTo2L2Nu.root       /hdfs/store/user/samuellh/${jobID}_VVTo2L2Nu*/* & 
    #hadd -f   WWW.root          /hdfs/store/user/samuellh/${jobID}_WWW-SUB-TT/* &
    #hadd -f   ZZZ.root          /hdfs/store/user/samuellh/${jobID}_ZZZ-SUB-TT/* &

    wait;
    #hadd     	--reuse-cache-files ZJets1050.root	/hdfs/store/user/samuellh/${jobID}_ZJets1050-SUB-MC 
    #hadd 	--reuse-cache-files WWTo2L2Nu.root 	/hdfs/store/user/samuellh/${jobID}_WWTo2L2Nu-SUB-MC 
    #hadd 	--reuse-cache-files WWTo4Q.root 	/hdfs/store/user/samuellh/${jobID}_WWTo4Q-SUB-MC 
    #hadd 	--reuse-cache-files WWToLNuQQ.root 	/hdfs/store/user/samuellh/${jobID}_WWToLNuQQ-SUB-MC 
    #hadd 	--reuse-cache-files ZZTo2L2Q.root 	/hdfs/store/user/samuellh/${jobID}_ZZTo2L2Q-SUB-MC 
    #hadd 	--reuse-cache-files ZZTo4Q.root 	/hdfs/store/user/samuellh/${jobID}_ZZTo4Q-SUB-MC 
    #nohup hadd 	--reuse-cache-files TT.root 	        /hdfs/store/user/samuellh/${jobID}_TT-SUB-MC  
    #nohup hadd 	--reuse-cache-files WJetsMLM.root 	/hdfs/store/user/samuellh/${jobID}_WJetsMLM-SUB-MC 
    #nohup hadd 	--reuse-cache-files t_s.root 	        /hdfs/store/user/samuellh/${jobID}_t_s-SUB-MC 
    #nohup hadd 	--reuse-cache-files t_s_Ext.root 	/hdfs/store/user/samuellh/${jobID}_t_Ext-SUB-MC 
fi

