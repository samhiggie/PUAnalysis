
jobID="2018_Nov30"
jobIDMC="2018_Nov30_tautau"
svfitJobID="MELADec4"
##Note: These naming conventions should be fixed at the first submission step.
##      remove _tautau change SUB_Data + SUB_MC to SUB-TT-Data and SUB-TT-MC
                      
####DATA
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_data_tau_B_tautau-SUB_Data    --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_data_tau_C_tautau-SUB_Data    --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_data_tau_D_tautau-SUB_Data    --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_data_tau_E_tautau-SUB_Data    --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_data_tau_F_tautau-SUB_Data    --jobName ${svfitJobID}

##signal
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ggH125_ext-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_vbfH125-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ttH-SUB_MC                    --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WHminus-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WHplus-SUB_MC                 --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ZH-SUB_MC                     --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_VBFHiggs0L1_M-125-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_VBFHiggs0M_M-SUB_MC             --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_VBFHiggs0Mf05-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_VBFHiggs0PH-SUB_MC              --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_VBFHiggs0PHf05ph0-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0L1-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0L1fWH05ph0-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0M-SUB_MC                 --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0MfWH05ph0-SUB_MC         --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0PH-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0PHfWH05ph0-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_WHiggs0PM-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0L1-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0L1fZH05ph0-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0M-SUB_MC                 --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0MfZH05ph0-SUB_MC         --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0PH-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0PHfZH05ph0-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_ZHiggs0PM-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_GluGluH2JetsToTauTau_maxmix-SUB_MC         --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_GluGluH2JetsToTauTau_pseudoscalar-SUB_MC   --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobID}_GluGluH2JetsToTauTau_sm-SUB_MC             --jobName ${svfitJobID}

#singletop diboson
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_TT_2l2nu-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_TT_had-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_TT_sl-SUB_MC             --jobName ${svfitJobID}
                                                   
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ST_tW_t-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ST_t_at-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ST_t_t-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ST_tw_at-SUB_MC          --jobName ${svfitJobID}
                                                   
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WW_2l2nu-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WW_4q-SUB_MC             --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WW_lnu2q-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WW_lnu2q_ext-SUB_MC      --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WZ_1l3nu-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WZ_2l2q-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WZ_3lnu-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WZ_lnu2q-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ZZ_2l2nu-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ZZ_2l2q-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ZZ_4l-SUB_MC             --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_ZZ_4l_ext-SUB_MC         --jobName ${svfitJobID}
                                                   
###Typo here, fix if fix needed                                    
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}i_W1J_lnu-SUB_MC           --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_W2J_lnu-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_W3J_lnu-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_W4J_lnu-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WJ_lnu-SUB_MC             --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_WJ_lnu_ext-SUB_MC         --jobName ${svfitJobID}
                                                   
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_EWKWPlus2j-SUB_MC         --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_EWKWminus2j-SUB_MC        --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_EWKZ2j_2l-SUB_MC          --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_EWKZ2j_2nu-SUB_MC         --jobName ${svfitJobID}
                                                   
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY1-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY1_ext-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY2-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY2_ext-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY3-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY3_ext-SUB_MC            --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DY4-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DYJ-SUB_MC                --jobName ${svfitJobID}
python melaSubmitter.py -sd /hdfs/store/user/ojalvo/svFitDec2/${jobIDMC}_DYJ_ext-SUB_MC            --jobName ${svfitJobID}


