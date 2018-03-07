{
   gROOT->ProcessLine(".L ../../ROOT/plotMacros/makePlotHThTh.C");
   
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_eta_1","diTauPlots/tauTau_eta_1.root","tt_inclusive",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_eta_2","diTauPlots/tauTau_eta_2.root","tt_inclusive",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_pt_1","diTauPlots/tauTau_pt_1.root","tt_inclusive",3,"p_{T} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_pt_2","diTauPlots/tauTau_pt_2.root","tt_inclusive",3,"p_{T} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);


   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_mvis","diTauPlots/tauTau_mvis.root","tt_inclusive",3,"m_{vis}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_njetspt20","diTauPlots/tauTau_njetspt20.root","tt_inclusive",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_mJJ","diTauPlots/tauTau_mJJ.root","tt_inclusive",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_ptJJ","diTauPlots/tauTau_ptJJ.root","tt_inclusive",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_met","diTauPlots/tauTau_met.root","tt_inclusive",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_fullPt","diTauPlots/tauTau_fullPt.root","tt_inclusive",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_isoMVARaw_1","diTauPlots/tauTau_isoMVARaw_1.root","tt_inclusive",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_isoMVARaw_2","diTauPlots/tauTau_isoMVARaw_2.root","tt_inclusive",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_isoDBRaw_1","diTauPlots/tauTau_isoDBRaw_1.root","tt_inclusive",3,"#Delta#beta iso #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_isoDBRaw_2","diTauPlots/tauTau_isoDBRaw_2.root","tt_inclusive",3,"#Delta#beta iso #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

}
 
