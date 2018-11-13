#!!!!RUN merge.sh prior!!!!!
#Script to merge all the samples and apply weights... 
#
#Meant for the crab formatted jobs... which makes the directories in the eos automatically... 


#Script to merge the root files
#Run in directory that contains the names of all the samples...

#for d in */;
#do
#    echo Merging Root Files
#    echo in directory "$d"
#    cd "$d"/.
#    dname=${PWD##*/}
#    echo NewFile "$dname.root"
#    hadd -k "$dname.root" */*/*/*.root
#    cd ..
#done



echo make sure to run merge.sh to generate the root files from the analysis level 

cp /eos/uscms/store/user/samuellh/VBF/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8.root DY0Jets.root 
cp /eos/uscms/store/user/samuellh/VBF/DYToLL-M-50_1J_14TeV-madgraphMLM-pythia8/DYToLL-M-50_1J_14TeV-madgraphMLM-pythia8.root DY1Jets.root 
cp /eos/uscms/store/user/samuellh/VBF/DYToLL-M-50_2J_14TeV-madgraphMLM-pythia8/DYToLL-M-50_2J_14TeV-madgraphMLM-pythia8.root DY2Jets.root 
cp /eos/uscms/store/user/samuellh/VBF/DYToLL-M-50_3J_14TeV-madgraphMLM-pythia8/DYToLL-M-50_3J_14TeV-madgraphMLM-pythia8.root DY3Jets.root 

#Need special reweighting for Z+jets, then we hadd to single file later!!
EventWeightsIterativeZJets ZeroJets='DY0Jets.root'  OneJets='DY1Jets.root' TwoJets='DY2Jets.root'     histoName='TT/results'

#We need to add glugluHtautau... I think I need to redo jobs find these files:
#/GluGluHToTauTau_M125_14TeV_powheg_pythia8/PhaseIITDRFall17MiniAOD-PU200_93X_upgrade2023_realistic_v2-v2/MINIAODSIM
cp   /eos/uscms/store/user/samuellh/VBF/GluGluHToTauTau_M125_14TeV_powheg_pythia8/GluGluHToTauTau_M125_14TeV_powheg_pythia8.root  ggH125.root  
                                                                                                                                                           
                                                                                                                                                           
cp  /eos/uscms/store/user/samuellh/VBF/QCD_Flat_Pt-15to7000_TuneCUETP8M1_14TeV_pythia8/QCD_Flat_Pt-15to7000_TuneCUETP8M1_14TeV_pythia8.root    QCD.root    
                                                                                                                                                           
                                                                                                                                                           
cp   /eos/uscms/store/user/samuellh/VBF/TT_TuneCUETP8M2T4_14TeV-powheg-pythia8/TT_TuneCUETP8M2T4_14TeV-powheg-pythia8.root    ttBar.root  
                                                                                                                                                           
                                                                                                                                                           
cp   /eos/uscms/store/user/samuellh/VBF/VBFHToTauTau_M125_14TeV_powheg_pythia8/VBFHToTauTau_M125_14TeV_powheg_pythia8.root       vbfH125.root

hadd -f DYJets.root DY0Jets.root DY1Jets.root DY2Jets.root


EventWeightsIterative outputFile='ggH125.root'     weight=1       histoName='TT/results'
EventWeightsIterative outputFile='vbfH125.root'    weight=1      histoName='TT/results' 
EventWeightsIterative outputFile='ttBar.root'      weight=864.5     histoName='TT/results' 
#EventWeightsIterative outputFile='DYJets.root'     weight=5139.0     histoName='TT/results' 
#EventWeightsIterative outputFile='QCD.root'     weight=335469     histoName='TT/results' 
EventWeightsIterative outputFile='QCD.root'     weight=2207000000     histoName='TT/results' 
