{
   gROOT->ProcessLine(".L ../../ROOT/plotMacros/makePlotHThTh.C");

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_mvis","diTauPlots/tauTau_m_vis.root","tt_inclusive",3,"m_{vis}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT/diTau_2017/diTau_pt_1","diTauPlots/tauTau_pt_1.root","tt_inclusive",3,"p_{T} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT/diTau_2017/diTau_pt_2","diTauPlots/tauTau_pt_2.root","tt_inclusive",3,"p_{T} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //void makeDiTauStack(TString name,TString file,TString dir,int s,TString labelX,TString units = "GeV",bool left=false,TString channel = "",TString json = "Golden",bool log = false,bool dndm=false,bool doRatio = false)   
   //makeDiTauStack("~/www/HTT/diTau_2017/diTau_m_vis","diTauDatacards-2D-moriond/tauTautt_vbf_msv.root","tt_vbf",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

    makeDiTauStack("~/www/HTT/diTau_2017/diTau_eta_1","diTauPlots/tauTau_eta_1.root","tt_inclusive",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT/diTau_2017/diTau_eta_2","diTauPlots/tauTau_eta_2.root","tt_inclusive",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_njetspt20","diTauPlots/tauTau_njetspt20.root","tt_inclusive",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_mJJ","diTauPlots/tauTau_mJJ.root","tt_inclusive",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_ptJJ","diTauPlots/tauTau_ptJJ.root","tt_inclusive",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_met","diTauPlots/tauTau_met.root","tt_inclusive",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_fullPt","diTauPlots/tauTau_fullPt.root","tt_inclusive",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT/diTau_2017/diTau_isoMVARaw_1","diTauPlots/tauTau_isoMVARaw_1.root","tt_inclusive",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT/diTau_2017/diTau_isoMVARaw_2","diTauPlots/tauTau_isoMVARaw_2.root","tt_inclusive",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT/diTau_2017/diTau_isoDBRaw_1","diTauPlots/tauTau_isoDBRaw_1.root","tt_inclusive",3,"#Delta#beta iso #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT/diTau_2017/diTau_isoDBRaw_2","diTauPlots/tauTau_isoDBRaw_2.root","tt_inclusive",3,"#Delta#beta iso #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

}
 
