#!/bin/sh
olddirname='ztt_unweighted_Apr7_svFit'
newdirname='ztt_weighted_Apr7_svFit'
mkdir /scratch/$USER/$newdirname
cd /scratch/$USER/$newdirname

weight=0;
weightH=1;
weightW=0;
weightZ=0;

#cp /scratch/$USER/$olddirname/tauDATA.root /scratch/$USER/$newdirname/.

if [ $weightH -eq 1 ]
    then

    for dir in ggH120.root ggH125.root ggH130.root vbfH120.root vbfH125.root vbfH130.root ttH120.root ttH125.root ttH130.root WpH120.root WpH125.root WpH130.root WmH120.root WmH125.root WmH130.root ZH120.root ZH125.root ZH130.root  
    do 
	cp /scratch/$USER/$olddirname/$dir /scratch/$USER/$newdirname/. &
    done 
    wait;
    echo 'weight higgs'
    EventWeightsIterativeGen outputFile='ggH120.root'     weight=3.644956       histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='ggH125.root'     weight=3.045965       histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='ggH130.root'     weight=2.451271       histoName='TT/results' sumHistoName='sumweights/genWeights' &
								 	   
    EventWeightsIterativeGen outputFile='vbfH120.root'    weight=0.274663       histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='vbfH125.root'    weight=0.2371314      histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='vbfH130.root'    weight=0.1967617      histoName='TT/results' sumHistoName='sumweights/genWeights' &
								 	   
    EventWeightsIterativeGen outputFile='WpH120.root'     weight=0.0546185      histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='WpH125.root'     weight=0.04304355     histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='WpH130.root'     weight=0.03270345     histoName='TT/results' sumHistoName='sumweights/genWeights' &
								 	   
    EventWeightsIterativeGen outputFile='WmH120.root'     weight=0.0546185      histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='WmH125.root'     weight=0.04304355     histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='WmH130.root'     weight=0.03270345     histoName='TT/results' sumHistoName='sumweights/genWeights' &
								 	   
    EventWeightsIterativeGen outputFile='ZH120.root'      weight=0.0693812      histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='ZH125.root'      weight=0.0554268      histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='ZH130.root'      weight=0.042739       histoName='TT/results' sumHistoName='sumweights/genWeights' &
								 	   
    EventWeightsIterativeGen outputFile='ttH120.root'     weight=0.040128       histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='ttH125.root'     weight=0.0320424      histoName='TT/results' sumHistoName='sumweights/genWeights' &
    EventWeightsIterativeGen outputFile='ttH130.root'     weight=0.024743       histoName='TT/results' sumHistoName='sumweights/genWeights' &
    wait;
fi

if [ $weightZ -eq 1 ]
    then
    for dir in ZJets_ext1.root Z1Jets.root Z2Jets.root Z3Jets.root Z4Jets.root
    do 
	cp /scratch/$USER/$olddirname/$dir /scratch/$USER/$newdirname/.
    done 
    #make sure Zpt root file is around!!!
    cp /scratch/ojalvo/zpt_weights_2016.root /scratch/$USER/$newdirname/.
    EventWeightsIterativeZJets    weight=1    histoName='TT/results' 
    hadd -f ZJETS.root ZJets_ext1.root Z1Jets.root Z2Jets.root Z3Jets.root Z4Jets.root
     
fi

if [ $weightW -eq 1 ]
    then
    for dir in WJets.root WJetsMLM.root W1Jets.root W2Jets.root W3Jets.root W4Jets.root
    do 
	cp /scratch/$USER/$olddirname/$dir /scratch/$USER/$newdirname/. &
    done 
    wait;
    EventWeightsIterativeGen outputFile='WJetsMLM.root'      weight=61526.7   histoName='TT/results' sumHistoName='sumweights/genWeights'
    EventWeightsIterativeWJets    weight=1    histoName='TT/results' 
    #hadd WJETS.root WJetsMLM.root W1Jets.root W2Jets.root W3Jets.root W4Jets.root
    hadd -f WJETS.root W1Jets.root W2Jets.root W3Jets.root W4Jets.root
 
fi



if [ $weight -eq 1 ]
    then

#removed from copy list:
#WZTo2L2Q.root
    for dir in TT.root WZTo1L3Nu.root WZTo1L1Nu2Q.root WZTo3L1Nu.root WZTo3L1Nu.root WZJTo3L1Nu.root tBar_tW.root t_tW.root St_tBar.root St_t.root WWTo1L1Nu2Q.root ZZTo2L2Q.root ZZTo4L.root VVTo2L2Nu.root WWW.root ZZZ.root 
    do 
	cp /scratch/$USER/$olddirname/$dir /scratch/$USER/$newdirname/.
    done

    #echo 'Weight TT'
    #EventWeightsIterativeGen outputFile='TT.root'  weight=831.76     histoName='TT/results' sumHistoName='sumweights/genWeights'
    #EventWeightsIterativeTT has top pt reweighting
    echo 'Weight TT'
    EventWeightsIterativeTT  outputFile='TT.root'             weight=831.76     histoName='TT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight WZ 1L3Nu'
    EventWeightsIterativeGen outputFile='WZTo1L3Nu.root'      weight=3.05   histoName='TT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight WZ 1L1NuQQ'
    EventWeightsIterativeGen outputFile='WZTo1L1Nu2Q.root'      weight=10.71   histoName='TT/results' sumHistoName='sumweights/genWeights' &
    #echo 'Weight WZ 2L2Q'
    #EventWeightsIterativeGen outputFile='WZTo2L2Q.root'      weight=5.595   histoName='TT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight WZ 3L1Nu'
    EventWeightsIterativeGen outputFile='WZTo3L1Nu.root'      weight=4.42965   histoName='TT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight WZJ To 2L1Nu'
    EventWeightsIterativeGen outputFile='WZJTo3L1Nu.root'      weight=4.708   histoName='TT/results' sumHistoName='sumweights/genWeights' &


    echo 'Weight tBar_tW'
    EventWeightsIterativeGen outputFile='tBar_tW.root'      weight=35.6    histoName='TT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight t_tW'
    EventWeightsIterativeGen outputFile='t_tW.root'         weight=35.6    histoName='TT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight St_antitop'
    EventWeightsIterativeGen outputFile='St_tBar.root'      weight=80.95    histoName='TT/results' sumHistoName='sumweights/genWeights' & #80.59 pb * 3*.108
    echo 'Weight St_top'
    EventWeightsIterativeGen outputFile='St_t.root'         weight=136.02    histoName='TT/results' sumHistoName='sumweights/genWeights' & #136 * 3*.108

    echo 'Weight WW to 1L1Nu QQ'
    EventWeightsIterativeGen outputFile='WWTo1L1Nu2Q.root'  weight=49.997    histoName='TT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight ZZ 2L2Q'
    EventWeightsIterativeGen outputFile='ZZTo2L2Q.root'     weight=3.22  histoName='TT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight ZZTo4L'
    EventWeightsIterativeGen outputFile='ZZTo4L.root'       weight=1.3816  histoName='TT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight VV to 2L2Nu'
    EventWeightsIterativeGen outputFile='VVTo2L2Nu.root'    weight=11.95    histoName='TT/results' sumHistoName='sumweights/genWeights' &

    echo 'Weight TriBoson WWW'
    EventWeightsIterativeGen outputFile='WWW.root'          weight=0.2086     histoName='TT/results' sumHistoName='sumweights/genWeights' &
    echo 'Weight TriBoson ZZZ'
    EventWeightsIterativeGen outputFile='ZZZ.root'          weight=0.01398      histoName='TT/results' sumHistoName='sumweights/genWeights' &

    #EventWeightsIterativeGen outputFile='WZJTo1L3Nu.root'      weight=4.708   histoName='TT/results' sumHistoName='sumweights/genWeights' &
#add m_ll>30

    #echo 'Weight WW to L1Nu QQ'
    #EventWeightsIterativeGen outputFile='WWToLNuQQ.root'     weight=49.997    histoName='TT/results' sumHistoName='sumweights/genWeights' &
    #EventWeightsIterativeGen outputFile='WWTo2L2Q.root'     weight=49.997    histoName='TT/results' sumHistoName='sumweights/genWeights' &

    wait;

    hadd -f DiBoson.root WWTo*root WZTo*root ZZTo*.root St_*.root t*tW.root VVTo*root WWW.root ZZZ.root
fi


#now doing some cleanup
mv St_t* ../unneededZTT/.
mv WWTo2L2Q.root ../unneededZTT/.
mv Z*Jets.root ../unneededZTT/.
mv W*Jets.root ../unneededZTT/.
mv WJetsMLM.root ../unneededZTT/.
mv ZJets_* ../unneededZTT/.
mv WZ*.root ../unneededZTT/.
mv t* ../unneededZTT/.
mv ZZ*.root ../unneededZTT/.
mv WWW.root ../unneededZTT/.
mv ZZZ.root ../unneededZTT/.
mv VVTo2L2Nu.root ../unneededZTT/.


