#To submit jobs on 2018 premerged ntuples... MAKE SURE IT RUNS LOCALLY FIRST 
#protip, try the first commented out line on the command line to make sure things are functional 
 
jobName="FastMTT_2018"
##Note: These naming conventions should be fixed at the first submission step.
##      remove _tautau change SUB_Data + SUB_MC to SUB-TT-Data and SUB-TT-MC

                      
####DATA
#python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/VBFHToTauTau_M125_13TeV_powheg_pythia8/*/*/* --jobName $jobname  -es 
#python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_W1Jets                                -es   -iswj                       
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WminusHToTauTau_M125_13TeV_powheg_pythia8/*/*/* --jobName ${jobName}_WmH                                    -es                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_WW4Q                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/*/*/* --jobName ${jobName}_WZ1L3Nu                                 -es                         
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/*/*/* --jobName ${jobName}_WZ2L2Q                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WZJJToLNu_EWK_QCD_TuneCP5_13TeV-madgraph-pythia8/*/*/* --jobName ${jobName}_WZJJLNu                             -es                             
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_WJetsLNu                                 -es   -iswj                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WW_TuneCP5_13TeV-pythia8/*/*/* --jobName ${jobName}_WW                                                     -es     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_WW2L2Nu                               -es                           
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_W2JetsLNu                                -es   -iswj                       
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_WWLNuQQ                               -es                           
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WplusHToTauTau_M125_13TeV_powheg_pythia8/*/*/* --jobName ${jobName}_WpH                                     -es                     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/*/*/* --jobName ${jobName}_ZZ2L2Nu                                       -es                   
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ZZ_TuneCP5_13TeV-pythia8/*/*/* --jobName ${jobName}_ZZ                                                     -es     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/*/*/* --jobName ${jobName}_ST-t-at -es                                                         
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/*/*/* --jobName ${jobName}_ZZ2L2Q                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_DY3J                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_ttH                                -es                          
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_DY4J                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_TT-had                                    -es                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WZ_TuneCP5_13TeV-pythia8/*/*/* --jobName ${jobName}_WZ                                                     -es     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/GluGluHToTauTau_M125_13TeV_powheg_pythia8/*/*/* --jobName ${jobName}_ggH125                                    -es                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_TT_2L2Nu                                       -es                   
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_ST_tW_top                    -es                                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_DY2J                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_DY1J                           -es                               
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/*/*/* --jobName ${jobName}_ZZ4L                                          -es                
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/EWKWPlus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8/*/*/* --jobName ${jobName}_EWKWp2J                     -es                                     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/EWKWMinus2Jets_WToLNu_M-50_TuneCP5_13TeV-madgraph-pythia8/*/*/* --jobName ${jobName}_EWKWm2J                    -es                                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_W3JetsLNu                                -es    -iswj                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/EWKZ2Jets_ZToNuNu_TuneCP5_PSweights_13TeV-madgraph-pythia8/*/*/* --jobName ${jobName}_EWKZ2JetsZNuNu                   -es                                       
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_TTSML                                -es                          
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/*/*/* --jobName ${jobName}_WZ3LNu                                  -es                        
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/*/*/* --jobName ${jobName}_ST_tW_at                -es                                          
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ZHToTauTau_M125_13TeV_powheg_pythia8/*/*/* --jobName ${jobName}_ZH125                                         -es                 
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_DYJets                            -es                              
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/*/*/* --jobName ${jobName}_ST_t     -es                                                     
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/*/*/* --jobName ${jobName}_W4JetsLnu                                -es    -iswj                      
python fastmttSubmitter.py -s -sd /hdfs/store/user/shigginb/2019_June_15_2018_tt/EWKZ2Jets_ZToLL_M-50_TuneCP5_PSweights_13TeV-madgraph-pythia8/*/*/* --jobName ${jobName}_EWKZ2JetsZLL                -es                                          
