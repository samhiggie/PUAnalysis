#To submit jobs on 2018 premerged ntuples... MAKE SURE IT RUNS LOCALLY FIRST 
#protip, try the first commented out line on the command line to make sure things are functional 
 
jobName="FastMTT2018"
##Note: These naming conventions should be fixed at the first submission step.
##      remove _tautau change SUB_Data + SUB_MC to SUB-TT-Data and SUB-TT-MC

                      
####DATA
#python svFitSubmitterFast.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/VBFHToTauTau_M125_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname  -es 
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName ${jobname}_W1Jets                                -es   -iswj                       
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WminusHToTauTau_M125_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname                                    -es                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/*/*/*/ --jobName $jobname                                 -es                         
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/*/*/*/ --jobName $jobname                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WZJJToLNu_EWK_QCD_TuneCP5_13TeV-madgraph-pythia8/*/*/*/ --jobName $jobname                             -es                             
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                                 -es   -iswj                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WW_TuneCP5_13TeV-pythia8/*/*/*/ --jobName $jobname                                                     -es     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                               -es                           
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                                -es   -iswj                       
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                               -es                           
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WplusHToTauTau_M125_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname                                     -es                     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname                                       -es                   
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ZZ_TuneCP5_13TeV-pythia8/*/*/*/ --jobName $jobname                                                     -es     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/*/*/*/ --jobName $jobname -es                                                         
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/*/*/*/ --jobName $jobname                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                                -es                          
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                                    -es                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WZ_TuneCP5_13TeV-pythia8/*/*/*/ --jobName $jobname                                                     -es     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/GluGluHToTauTau_M125_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname                                    -es                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                                       -es                   
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                    -es                                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname                                          -es                
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/EWKWPlus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8/*/*/*/ --jobName $jobname                     -es                                     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/EWKWMinus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8/*/*/*/ --jobName $jobname                    -es                                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                                -es    -iswj                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/EWKZ2Jets_ZToNuNu_TuneCP5_PSweights_13TeV-madgraph-pythia8/*/*/*/ --jobName $jobname                   -es                                       
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                                -es                          
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/*/*/*/ --jobName $jobname                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/*/*/*/ --jobName $jobname                -es                                          
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ZHToTauTau_M125_13TeV_powheg_pythia8/*/*/*/ --jobName $jobname                                         -es                 
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                            -es                              
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/*/*/*/ --jobName $jobname     -es                                                     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/*/ --jobName $jobname                                -es    -iswj                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2018_MC_tt/EWKZ2Jets_ZToLL_M-50_TuneCP5_PSweights_13TeV-madgraph-pythia8/*/*/*/ --jobName $jobname                -es                                          
