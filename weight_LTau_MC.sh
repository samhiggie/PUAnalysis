#!/bin/sh

jobID=2018_Jun25
mkdir /nfs_scratch/$USER/${jobID}_weighted/
cp /nfs_scratch/$USER/${jobID}_unweighted/* /nfs_scratch/$USER/${jobID}_weighted/.
cd /nfs_scratch/$USER/${jobID}_weighted/

#echo "copying...."
#mkdir /nfs_scratch/$USER/${jobID}_weighted/
#cp /scratch/ojalvo/2017_Ntuples/rename/* /nfs_scratch/$USER/${jobID}_weighted/.
#cd /nfs_scratch/$USER/${jobID}_weighted/.

#echo "finishded copying...."

weight=0;
weightEWK=0;
weightTriBoson=0;
weightTT=0;
weightH=0;
weightW=1;
weightZ=1;
weightZPt=0;


#hadd  DiBoson.root WWTo*root WZTo*root ZZTo*.root St_*.root t*tW.root VVTo*root 
#hadd  EWKZ.root EWKZ*root

if [ $weightH -eq 1 ]
    then
    echo 'weight higgs to 1 pb'
    #EventWeightsIterativeHiggs outputFile='ggH110.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeHiggs outputFile='ggH120.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeHiggs outputFile='ggH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeHiggs outputFile='ggH130.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeHiggs outputFile='ggH140.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    EventWeightsIterativeGen outputFile='ggH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    EventWeightsIterativeGen outputFile='vbfH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'

    #EventWeightsIterativeGen outputFile='vbfH110.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='vbfH120.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='vbfH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='vbfH130.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='vbfH140.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'

    #EventWeightsIterativeGen outputFile='vbfHWW125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='ggHWW125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #*0.215*0.324*0.324

    #EventWeightsIterativeGen outputFile='ZH110.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='ZH120.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='ZH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='ZH130.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='ZH140.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'

    #EventWeightsIterativeGen outputFile='WpH110.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WpH120.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WpH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WpH130.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WpH140.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'

    #EventWeightsIterativeGen outputFile='WmH110.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WmH120.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WmH125.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WmH130.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeGen outputFile='WmH140.root'     weight=1    histoName='MT/results' sumHistoName='sumweights/genWeights'
fi


if [ $weightZPt -eq 1 ]
    then
    nohup EventWeightsIterativeZPt  outputFile='ZJETS.root'  weight=1    histoName='MT/results' 
    #EventWeightsIterativeZPt  outputFile='EWKZ.root'    histoName='MT/results' 
fi

if [ $weightZ -eq 1 ]
    then
    nohup EventWeightsIterativeZJets    weight=1    histoName='MT/results' 
    hadd -f ZJETS.root ZJets.root Z1Jets.root Z2Jets.root Z3Jets.root
fi

if [ $weightW -eq 1 ]
    then

    nohup EventWeightsIterativeWJets    weight=1    histoName='MT/results'  
    hadd -f WJETS.root WJetsMLM.root W1Jets.root W2Jets.root W3Jets.root W4Jets.root
fi


if [ $weightTT -eq 1 ]
    then
    echo 'Weight TT'
    nohup EventWeightsIterativeTT outputFile='TT.root'  weight=831.76     histoName='MT/results' sumHistoName='sumweights/genWeights' 
    #EventWeightsIterativeTT has top pt reweighting
fi

if [ $weight -eq 1 ]
    then
    echo 'Weight WW'
    nohup EventWeightsIterativeGen outputFile='WW.root'      weight=63.21  histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight WZ'
    nohup EventWeightsIterativeGen outputFile='WZ.root'      weight=22.82  histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight ZZ'
    nohup EventWeightsIterativeGen outputFile='ZZ.root'      weight=10.32  histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight t_tW'
    nohup EventWeightsIterativeGen outputFile='t_tW.root'        weight=38.09    histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight tBar_tW'
    nohup EventWeightsIterativeGen outputFile='tBar_tW.root'     weight=38.09    histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight St_antitop'
    nohup EventWeightsIterativeGen outputFile='St_antitop.root'  weight=26.23  histoName='MT/results' sumHistoName='sumweights/genWeights' & #80.59 pb * 3*.108
    echo 'Weight St_top'
    nohup EventWeightsIterativeGen outputFile='St_top.root'      weight=44.07  histoName='MT/results' sumHistoName='sumweights/genWeights' & #136 * 3*.108
    wait;
    nohup EventWeightsIterativeGen outputFile='TT2L2Nu.root'    weight=87.31     histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='TTHadronic.root' weight=380.1     histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='TTSemiLep.root'  weight=364.4     histoName='MT/results' sumHistoName='sumweights/genWeights' &
    wait;

    hadd -f DiBoson.root WW.root WZ.root ZZ.root tBar_tW.root t_tW.root St_antitop.root St_top.root
    hadd -f TT.root TT2L2Nu.root TTHadronic.root TTSemiLep.root

fi

if [ $weightEWK -eq 1 ]
    then
    echo 'Weight EWK'

    #echo 'Weight WAMC'
    echo 'Weight ZZ'
    nohup EventWeightsIterativeGen outputFile='ZZTo2L2Q.root'      weight=3.22  histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='ZZTo4L.root'      weight=1.212  histoName='MT/results' sumHistoName='sumweights/genWeights'

    echo 'Weight WZ 1L1NuQQ'
    nohup EventWeightsIterativeGen outputFile='WZTo1L1Nu2Q.root' weight=10.71   histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight WZ 2L2Q'
    nohup EventWeightsIterativeGen outputFile='WZTo2L2Q.root'    weight=5.595   histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight WZ 1L3Nu'
    nohup EventWeightsIterativeGen outputFile='WZTo1L3Nu.root'   weight=3.05   histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='WZTo3L1Nu.root'   weight=4.708   histoName='MT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight WW to L1Nu QQ'
    nohup EventWeightsIterativeGen outputFile='WWTo1L1Nu2Q.root' weight=49.997     histoName='MT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight VV to 2L2Nu'
    nohup  EventWeightsIterativeGen outputFile='VVTo2L2Nu.root'  weight=11.95    histoName='MT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight t_tW'
    nohup EventWeightsIterativeGen outputFile='t_tW.root'        weight=35.6    histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight tBar_tW'
    nohup EventWeightsIterativeGen outputFile='tBar_tW.root'     weight=35.6    histoName='MT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight St_antitop'
    nohup EventWeightsIterativeGen outputFile='St_antitop.root'  weight=26.23  histoName='MT/results' sumHistoName='sumweights/genWeights' & #80.59 pb * 3*.108
    echo 'Weight St_top'
    nohup EventWeightsIterativeGen outputFile='St_top.root'      weight=44.07  histoName='MT/results' sumHistoName='sumweights/genWeights' & #136 * 3*.108

    EventWeightsIterativeGen outputFile='EWKZ2JetLL.root'        weight=3.987    histoName='MT/results' sumHistoName='sumweights/genWeights' 
    EventWeightsIterativeGen outputFile='EWKZ2JetNuNu.root'      weight=10.01    histoName='MT/results' sumHistoName='sumweights/genWeights' 
    EventWeightsIterativeGen outputFile='EWKminus2jet.root'      weight=20.25    histoName='MT/results' sumHistoName='sumweights/genWeights' 
    EventWeightsIterativeGen outputFile='EWKplus2jet.root'       weight=25.62    histoName='MT/results' sumHistoName='sumweights/genWeights' 
fi

if [ $weightTriBoson -eq 1 ]
    then
    echo 'Weight Triboson'
    nohup EventWeightsIterativeGen outputFile='WWW.root'  weight=0.2086    histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='WWZ.root'  weight=0.1651    histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='WZZ.root'  weight=0.05565   histoName='MT/results' sumHistoName='sumweights/genWeights' &
    nohup EventWeightsIterativeGen outputFile='ZZZ.root'  weight=0.01398   histoName='MT/results' sumHistoName='sumweights/genWeights' &
fi



