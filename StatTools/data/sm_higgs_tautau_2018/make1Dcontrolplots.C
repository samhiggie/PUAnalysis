{
   gROOT->ProcessLine(".L ../../ROOT/plotMacros/makePlotHThTh_2018_ff.C");
   //gROOT->ProcessLine(".L ../../ROOT/plotMacros/makePlotHThTh_2018.C");
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_m_vis","2018_ttplots_ffnew_inc/tauTau_m_vis.root","tt_inc",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_met","2018_ttplots_ffnew_inc/tauTau_met.root","tt_inc",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_npv","2018_ttplots_ffnew_inc/tauTau_npv.root","tt_inc",3,"npv","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_pt_1","2018_ttplots_ffnew_inc/tauTau_pt_1.root","tt_inc",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_pt_2","2018_ttplots_ffnew_inc/tauTau_pt_2.root","tt_inc",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_eta_1","2018_ttplots_ffnew_inc/tauTau_eta_1.root","tt_inc",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_eta_2","2018_ttplots_ffnew_inc/tauTau_eta_2.root","tt_inc",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_pt_1","2018_ttplots_ffnew_inc/tauTau_pt_1.root","tt_inc",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_pt_2","2018_ttplots_ffnew_inc/tauTau_pt_2.root","tt_inc",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_eta_1","2018_ttplots_ffnew_inc/tauTau_eta_1.root","tt_inc",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_eta_2","2018_ttplots_ffnew_inc/tauTau_eta_2.root","tt_inc",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   

   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_njetspt20","2018_ttplots_ffnew_inc/tauTau_njetspt20.root","tt_inc",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_njets","2018_ttplots_ffnew_inc/tauTau_njets.root","tt_inc",3,"# Jets ","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_mJJ","2018_ttplots_ffnew_inc/tauTau_mJJ.root","tt_inc",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_ptJJ","2018_ttplots_ffnew_inc/tauTau_ptJJ.root","tt_inc",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_jpt_1","2018_ttplots_ffnew_inc/tauTau_jpt_1.root","tt_inc",3,"jpt_1","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_jpt_2","2018_ttplots_ffnew_inc/tauTau_jpt_2.root","tt_inc",3,"jpt_2","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);


   //makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_fullPt","2018_ttplots_ffnew_inc/tauTau_fullPt.root","tt_inc",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_iso_1","2018_ttplots_ffnew_inc/tauTau_iso_1.root","tt_inc",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_iso_2","2018_ttplots_ffnew_inc/tauTau_iso_2.root","tt_inc",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_gen_match_1","2018_ttplots_ffnew_inc/tauTau_gen_match_1.root","tt_inc",3,"gen_match MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_JEC_ff_2/diTau_gen_match_2","2018_ttplots_ffnew_inc/tauTau_gen_match_2.root","tt_inc",3,"gen_match MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
/*
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_m_vis","2018_svfit_ttplots_ffnew_vbf/tauTau_m_vis.root","tt_vbf",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_m_vis","2018_svfit_ttplots_ffnew_vbf/tauTau_m_vis.root","tt_vbf",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_m_vis","redo_ttplots_boosted/tauTau_m_vis.root","tt_boosted",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_m_vis","2018_svfit_ttplots_ffnew_0jet/tauTau_m_vis.root","tt_0jet",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_m_sv","2018_svfit_ttplots_ffnew_vbf/tauTau_m_sv.root","tt_vbf",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_m_sv","2018_ttplots_ffnew_inc/tauTau_m_sv.root","tt_inc",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_pt_1","2018_svfit_ttplots_ffnew_vbf/tauTau_pt_1.root","tt_vbf",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_pt_2","2018_svfit_ttplots_ffnew_vbf/tauTau_pt_2.root","tt_vbf",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_eta_1","2018_svfit_ttplots_ffnew_vbf/tauTau_eta_1.root","tt_vbf",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_eta_2","2018_svfit_ttplots_ffnew_vbf/tauTau_eta_2.root","tt_vbf",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_njetspt20","2018_svfit_ttplots_ffnew_vbf/tauTau_njetspt20.root","tt_vbf",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_njets","2018_svfit_ttplots_ffnew_vbf/tauTau_njets.root","tt_vbf",3,"# Jets ","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_mJJ","2018_svfit_ttplots_ffnew_vbf/tauTau_mJJ.root","tt_vbf",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_ptJJ","2018_svfit_ttplots_ffnew_vbf/tauTau_ptJJ.root","tt_vbf",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_jpt_1","2018_svfit_ttplots_ffnew_vbf/tauTau_jpt_1.root","tt_vbf",3,"jpt_1","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_jpt_2","2018_svfit_ttplots_ffnew_vbf/tauTau_jpt_2.root","tt_vbf",3,"jpt_2","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_met","2018_svfit_ttplots_ffnew_vbf/tauTau_met.root","tt_vbf",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_fullPt","2018_svfit_ttplots_ffnew_vbf/tauTau_fullPt.root","tt_vbf",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_iso_1","2018_svfit_ttplots_ffnew_vbf/tauTau_iso_1.root","tt_vbf",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_iso_2","2018_svfit_ttplots_ffnew_vbf/tauTau_iso_2.root","tt_vbf",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_gen_match_1","2018_svfit_ttplots_ffnew_vbf/tauTau_gen_match_1.root","tt_vbf",3,"gen_match MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_gen_match_2","2018_svfit_ttplots_ffnew_vbf/tauTau_gen_match_2.root","tt_vbf",3,"gen_match MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_Raw2017v2_1","2018_svfit_ttplots_ffnew_vbf/tauTau_Raw2017v2_1.root","tt_vbf",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_idRaw2017v2_2","2018_svfit_ttplots_ffnew_vbf/tauTau_idRaw2017v2_2.root","tt_vbf",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_Tight2017v2_1","2018_svfit_ttplots_ffnew_vbf/tauTau_Tight2017v2_1.root","tt_vbf",3,"new  Tight2017v2_1 #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_idTight2017v2_2","2018_svfit_ttplots_ffnew_vbf/tauTau_idTight2017v2_2.root","tt_vbf",3,"new idTight2017v2_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_Med2017v2_1","2018_svfit_ttplots_ffnew_vbf/tauTau_Med2017v2_1.root","tt_vbf",3,"new  Med2017v2_1 #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_idMed2017v2_2","2018_svfit_ttplots_ffnew_vbf/tauTau_idMed2017v2_2.root","tt_vbf",3,"new idMed2017v2_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoTight_1","2018_svfit_ttplots_ffnew_vbf/tauTau_isoTight_1.root","tt_vbf",3,"new isoTight_1 Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoTight_2","2018_svfit_ttplots_ffnew_vbf/tauTau_isoTight_2.root","tt_vbf",3,"new isoTight_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoMed_1","2018_svfit_ttplots_ffnew_vbf/tauTau_isoMed_1.root","tt_vbf",3,"new isoMed_1 Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoMed_2","2018_svfit_ttplots_ffnew_vbf/tauTau_isoMed_2.root","tt_vbf",3,"new isoMed_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoLoose_1","2018_svfit_ttplots_ffnew_vbf/tauTau_isoLoose_1.root","tt_vbf",3,"new isoLoose_1 Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoLoose_2","2018_svfit_ttplots_ffnew_vbf/tauTau_isoLoose_2.root","tt_vbf",3,"new isoLoose_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
*/
////////////////////////////////////////////////////////

   makeDiTauStack("~/public_html/HTT/tauMass/diTau_m_1_10","2018_ttplots_ffnew_inc_decay10/tauTau_m_1.root","tt_inc",3,"mass_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/tauMass/diTau_m_1_0", "2018_ttplots_ffnew_inc_decay0/tauTau_m_1.root","tt_inc",3,"mass_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/tauMass/diTau_m_1_1", "2018_ttplots_ffnew_inc_decay1/tauTau_m_1.root","tt_inc",3,"mass_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/tauMass/diTau_m_2","2018_ttplots_ffnew_inc/tauTau_m_2.root","tt_inc",3,"mass_{t} #tau_{2}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_pt_1","2018_ttplots_ffnew_inc/tauTau_pt_1.root","tt_inc",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_pt_2","2018_ttplots_ffnew_inc/tauTau_pt_2.root","tt_inc",3,"p_{t} #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_eta_1","2018_ttplots_ffnew_inc/tauTau_eta_1.root","tt_inc",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_eta_2","2018_ttplots_ffnew_inc/tauTau_eta_2.root","tt_inc",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////

   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_njetspt20","2018_ttplots_ffnew_inc/tauTau_njetspt20.root","tt_inc",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_njets","2018_ttplots_ffnew_inc/tauTau_njets.root","tt_inc",3,"# Jets","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_mJJ","2018_ttplots_ffnew_inc/tauTau_mJJ.root","tt_inc",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_ptJJ","2018_ttplots_ffnew_inc/tauTau_ptJJ.root","tt_inc",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_jpt_1","2018_ttplots_ffnew_inc/tauTau_jpt_1.root","tt_inc",3,"jpt_1","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_jpt_2","2018_ttplots_ffnew_inc/tauTau_jpt_2.root","tt_inc",3,"jpt_2","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_met","2018_ttplots_ffnew_inc/tauTau_met.root","tt_inc",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   ///////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_fullPt","2018_ttplots_ffnew_inc/tauTau_fullPt.root","tt_inc",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_iso_1","2018_ttplots_ffnew_inc/tauTau_iso_1.root","tt_inc",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   /////makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_isoTight_1","2018_ttplots_ffnew_inc/tauTau_isoTight_1.root","tt_inc",3,"iso Tight #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_isoMed_1","2018_ttplots_ffnew_inc/tauTau_isoMed_1.root","tt_inc",3,"iso Med #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_iso_2","2018_ttplots_ffnew_inc/tauTau_iso_2.root","tt_inc",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_isoDBRaw_1","2018_ttplots_ffnew_inc/tauTau_isoDBRaw_1.root","tt_inc",3,"#Delta#beta iso #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_inc/diTau_isoDBRaw_2","2018_ttplots_ffnew_inc/tauTau_isoDBRaw_2.root","tt_inc",3,"#Delta#beta iso #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
////////////////////////////////////////////////////////
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_Raw2017v2_1","redo_ttplots_iso/tauTau_Raw2017v2_1.root","tt_inc",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_idRaw2017v2_2","redo_ttplots_iso/tauTau_idRaw2017v2_2.root","tt_inc",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_Tight2017v2_1","redo_ttplots_iso/tauTau_Tight2017v2_1.root","tt_inc",3,"new  Tight2017v2_1 #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_idTight2017v2_2","redo_ttplots_iso/tauTau_idTight2017v2_2.root","tt_inc",3,"new idTight2017v2_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_Med2017v2_1","redo_ttplots_iso/tauTau_Med2017v2_1.root","tt_inc",3,"new  Med2017v2_1 #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_idMed2017v2_2","redo_ttplots_iso/tauTau_idMed2017v2_2.root","tt_inc",3,"new idMed2017v2_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoTight_1","redo_ttplots_iso/tauTau_isoTight_1.root","tt_inc",3,"new isoTight_1 Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoTight_2","redo_ttplots_iso/tauTau_isoTight_2.root","tt_inc",3,"new isoTight_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoMed_1","redo_ttplots_iso/tauTau_isoMed_1.root","tt_inc",3,"new isoMed_1 Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoMed_2","redo_ttplots_iso/tauTau_isoMed_2.root","tt_inc",3,"new isoMed_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoLoose_1","redo_ttplots_iso/tauTau_isoLoose_1.root","tt_inc",3,"new isoLoose_1 Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoLoose_2","redo_ttplots_iso/tauTau_isoLoose_2.root","tt_inc",3,"new isoLoose_2 Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoDBRaw_1","2018_svfit_ttplots_ffnew_vbf/tauTau_isoDBRaw_1.root","tt_vbf",3,"#Delta#beta iso #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_vbf/diTau_isoDBRaw_2","2018_svfit_ttplots_ffnew_vbf/tauTau_isoDBRaw_2.root","tt_vbf",3,"#Delta#beta iso #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
/*
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_m_sv","redo_ttplots_boosted/tauTau_m_sv.root","tt_boosted",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

    makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_eta_1","redo_ttplots_boosted/tauTau_eta_1.root","tt_boosted",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_eta_2","redo_ttplots_boosted/tauTau_eta_2.root","tt_boosted",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   

   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_njetspt20","redo_ttplots_boosted/tauTau_njetspt20.root","tt_boosted",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_njets","redo_ttplots_boosted/tauTau_njets.root","tt_boosted",3,"# Jets","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_mJJ","redo_ttplots_boosted/tauTau_mJJ.root","tt_boosted",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_ptJJ","redo_ttplots_boosted/tauTau_ptJJ.root","tt_boosted",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_jpt_1","redo_ttplots_boosted/tauTau_jpt_1.root","tt_boosted",3,"jpt_1","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_jpt_2","redo_ttplots_boosted/tauTau_jpt_2.root","tt_boosted",3,"jpt_2","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_met","redo_ttplots_boosted/tauTau_met.root","tt_boosted",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_fullPt","redo_ttplots_boosted/tauTau_fullPt.root","tt_boosted",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_iso_1","redo_ttplots_boosted/tauTau_iso_1.root","tt_boosted",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_iso_2","redo_ttplots_boosted/tauTau_iso_2.root","tt_boosted",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_gen_match_1","redo_ttplots_boosted/tauTau_gen_match_1.root","tt_boosted",3,"gen_match MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_gen_match_2","redo_ttplots_boosted/tauTau_gen_match_2.root","tt_boosted",3,"gen_match MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_isoDBRaw_1","redo_ttplots_boosted/tauTau_isoDBRaw_1.root","tt_boosted",3,"#Delta#beta iso #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_boosted/diTau_isoDBRaw_2","redo_ttplots_boosted/tauTau_isoDBRaw_2.root","tt_boosted",3,"#Delta#beta iso #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_iso_1","redo_ttplots_iso/tauTau_iso_1.root","tt_inc",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_iso_2","redo_ttplots_iso/tauTau_iso_2.root","tt_inc",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

*/


   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_m_sv","2018_svfit_ttplots_ffnew_0jet/tauTau_m_sv.root","tt_0jet",3,"m(#tau#tau)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);


   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_eta_1","2018_svfit_ttplots_ffnew_0jet/tauTau_eta_1.root","tt_0jet",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_eta_2","2018_svfit_ttplots_ffnew_0jet/tauTau_eta_2.root","tt_0jet",3,"#eta #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_pt_1","2018_svfit_ttplots_ffnew_0jet/tauTau_pt_1.root","tt_0jet",3,"pt #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_pt_2","2018_svfit_ttplots_ffnew_0jet/tauTau_pt_2.root","tt_0jet",3,"pt #tau_{1}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_njetspt20","2018_svfit_ttplots_ffnew_0jet/tauTau_njetspt20.root","tt_0jet",3,"# Jets p_{T}>20 GeV","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_njets","2018_svfit_ttplots_ffnew_0jet/tauTau_njets.root","tt_0jet",3,"# Jets","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_mJJ","2018_svfit_ttplots_ffnew_0jet/tauTau_mJJ.root","tt_0jet",3,"m_{JJ}","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_ptJJ","2018_svfit_ttplots_ffnew_0jet/tauTau_ptJJ.root","tt_0jet",3,"p_{T}(JJ)","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_jpt_1","2018_svfit_ttplots_ffnew_0jet/tauTau_jpt_1.root","tt_0jet",3,"jpt_1","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_jpt_2","2018_svfit_ttplots_ffnew_0jet/tauTau_jpt_2.root","tt_0jet",3,"jpt_2","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_met","2018_svfit_ttplots_ffnew_0jet/tauTau_met.root","tt_0jet",3,"met","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_fullPt","2018_svfit_ttplots_ffnew_0jet/tauTau_fullPt.root","tt_0jet",3,"p_{T}({#tau#tau})","GeV",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_njets","2018_svfit_ttplots_ffnew_0jet/tauTau_njets.root","tt_inc",3,"njets","number",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_iso_1","2018_svfit_ttplots_ffnew_0jet/tauTau_iso_1.root","tt_inc",3,"iso MVA Raw #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_iso_2","2018_svfit_ttplots_ffnew_0jet/tauTau_iso_2.root","tt_inc",3,"iso MVA Raw #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoTight_1","redo_ttplots_iso/tauTau_isoTight_1.root","tt_inc",3,"isoTight #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoTight_2","redo_ttplots_iso/tauTau_isoTight_2.root","tt_inc",3,"isoTight #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_gen_match_1","redo_ttplots_iso/tauTau_gen_match_1.root","tt_inc",3,"gen_match #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_gen_match_2","redo_ttplots_iso/tauTau_gen_match_2.root","tt_inc",3,"gen_match #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoVTight_1","redo_ttplots_iso/tauTau_isoVTight_1.root","tt_inc",3,"isoVTight #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoVTight_2","redo_ttplots_iso/tauTau_isoVTight_2.root","tt_inc",3,"isoVTight #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoMed_1","redo_ttplots_iso/tauTau_isoMed_1.root","tt_inc",3,"isoMed #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoMed_2","redo_ttplots_iso/tauTau_isoMed_2.root","tt_inc",3,"isoMed #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoLoose_1","redo_ttplots_iso/tauTau_isoLoose_1.root","tt_inc",3,"isoLoose #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoLoose_2","redo_ttplots_iso/tauTau_isoLoose_2.root","tt_inc",3,"isoLoose #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoVLoose_1","redo_ttplots_iso/tauTau_isoVLoose_1.root","tt_inc",3,"isoVLoose #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/redo_Control_2017_iso/diTau_isoVLoose_2","redo_ttplots_iso/tauTau_isoVLoose_2.root","tt_inc",3,"isoVLoose #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);

   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_isoDBRaw_1","2018_svfit_ttplots_ffnew_0jet/tauTau_isoDBRaw_1.root","tt_0jet",3,"#Delta#beta iso #tau_{1}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
   //makeDiTauStack("~/public_html/HTT/2018_controlplots_ffnew_0jet/diTau_isoDBRaw_2","2018_svfit_ttplots_ffnew_0jet/tauTau_isoDBRaw_2.root","tt_0jet",3,"#Delta#beta iso #tau_{2}","",false,"#tau_{h}#tau_{h}","Golden",false,false,true);
}
 
