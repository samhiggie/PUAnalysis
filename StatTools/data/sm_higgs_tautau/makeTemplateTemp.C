{
   gROOT->ProcessLine(".L ../../ROOT/plotMacros/makePlotHThTh.C");
   
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_eta_1","diTauPlots/tauTau_eta_1.root","tt_inclusive",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/www/HTT_CP/diTau_2016/diTau_eta_2","diTauPlots/tauTau_eta_2.root","tt_inclusive",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   
}
