#include "../../ROOT/plotMacros/makePlot2018.C"


void makeTemplatePlotsMuTau(){
   makeLTauStack("~/www/ltau_2018_mutau/muTau_m_sv","muTauPlots/muTau_m_sv.root","mt_inclusive",3,"M(#tau_{#mu}#tau_{h})","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_pt_1","muTauPlots/muTau_pt_1.root","mt_inclusive",3,"#tau P_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_m_vis","muTauPlots/muTau_m_vis.root","mt_inclusive",3,"m_vis","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_1","muTauPlots/muTau_eta_1.root","mt_inclusive",3,"#eta_{#mu}","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_jeta_1","muTauPlots/muTau_jeta_1.root","mt_inclusive",3,"Leading jet #eta","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_jeta_1_pt50","muTauPlots/muTau_jeta_1_pt50.root","mt_inclusive",3,"Leading jet #eta p_{T}> 50 GeV","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_jeta_2","muTauPlots/muTau_jeta_2.root","mt_inclusive",3,"Sub-Leading jet #eta","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_m_2","muTauPlots/muTau_m_2.root","mt_inclusive",3,"M_{#tau}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_jpt_1","muTauPlots/muTau_jpt_1.root","mt_inclusive",3,"Leading jet p_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_jpt_2","muTauPlots/muTau_jpt_2.root","mt_inclusive",3,"Sub-Leading jet p_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_met","muTauPlots/muTau_met.root","mt_inclusive",3,"ME_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_mt_1_nocut","muTauPlots/muTau_mt_1.root","mt_inclusive",3,"no cut m_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_pt_2","muTauPlots/muTau_pt_2.root","mt_inclusive",3,"#tau P_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_2","muTauPlots/muTau_eta_2.root","mt_inclusive",3,"#eta_{#tau}","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_mjj","muTauPlots/muTau_mjj.root","mt_inclusive",3,"M_{JJ}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_njetspt20","muTauPlots/muTau_njetspt20.root","mt_inclusive",3,"Number Jets p_{T}>20","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_njets","muTauPlots/muTau_njets.root","mt_inclusive",3,"Number Jets p_{T}>30","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_npvs","muTauPlots/muTau_npv.root","mt_inclusive",3,"PVs","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
/*

   //makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_1_30","muTauPlots/muTau_eta_1_30.root","mt_inclusive",3,"#eta_{#mu} taupt>30","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);

   //makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_2_30","muTauPlots/muTau_eta_2_30.root","mt_inclusive",3,"#eta_{#tau} pt>30","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_npvs_noweight","muTauPlots/muTau_npv_noweight.root","mt_inclusive",3,"visible mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_0jet_m_sv","muTauPlots/htt_mt.inputs-sm-13TeV-m_sv-0jet.root","mt_0jet",3,"SVFit Mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_0jet_m_vis","muTauPlots/htt_mt.inputs-sm-13TeV-m_vis-0jet.root","mt_0jet",3,"Visible Mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_incl_mt1","muTauPlots/htt_mt.inputs-sm-13TeV-mt_1-incl.root","mt_0jet",3,"Transverse Mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_incl_met","muTauPlots/htt_mt.inputs-sm-13TeV-met-incl.root","mt_0jet",3,"MET","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,false);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_npvs","muTauPlots/muTau_npv.root","mt_inclusive",3,"vertices","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_npvs_noweight","muTauPlots/muTau_npv_noweight.root","mt_inclusive",3,"visible mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_m_sv","muTauPlots/muTau_m_sv.root","mt_inclusive",3,"SVfit mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_m_vis_0jet","muTauPlots/muTau_m_vis_0jet.root","mt_inclusive",3,"visible mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_m_sv_0jet","muTauPlots/muTau_m_sv_0jet.root","mt_inclusive",3,"SVfit mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_mtRecoil_1","muTauPlots/muTau_mtRecoil_1.root","mt_inclusive",3,"m_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_npv","muTauPlots/muTau_npv.root","mt_inclusive",3,"npv","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_OldMVAIso","muTauPlots/muTau_OldMVAIso.root","mt_inclusive",3,"Raw MVAIsolation","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tauIso","muTauPlots/muTau_tauIso.root","mt_inclusive",3,"Raw Tau Isolation","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_puCorrPtSum_2","muTauPlots/muTau_puCorrPtSum_2.root","mt_inclusive",3,"puCorrPtSum_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_neutralIsoPtSum_2","muTauPlots/muTau_neutralIsoPtSum_2.root","mt_inclusive",3,"neutralIsoPtSum_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_chargedIsoPtSum_2","muTauPlots/muTau_chargedIsoPtSum_2.root","mt_inclusive",3,"chargedIsoPtSum_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_chargedIsoPtSumdR03_2","muTauPlots/muTau_chargedIsoPtSumdR03_2.root","mt_inclusive",3,"chargedIsoPtSumdR03_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_n_photons_total","muTauPlots/muTau_n_photons_total.root","mt_inclusive",3,"n_photons_total","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_nIsoGamma","muTauPlots/muTau_nIsoGamma.root","mt_inclusive",3,"n Isolated Gamma","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_nIsoNeutral","muTauPlots/muTau_nIsoNeutral.root","mt_inclusive",3,"n Isolated Neutral","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_photonSig","muTauPlots/muTau_photonSig.root","mt_inclusive",3,"n_photons_total-nIsoGamma","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_footprintCorrection_2","muTauPlots/muTau_footprintCorrection_2.root","mt_inclusive",3,"footprintCorrection_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tau_pt_weighted_dr_signal","muTauPlots/muTau_tau_pt_weighted_dr_signal.root","mt_inclusive",3,"tau_pt_weighted_dr_signal","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tau_pt_weighted_dr_iso","muTauPlots/muTau_tau_pt_weighted_dr_iso.root","mt_inclusive",3,"tau_pt_weighted_dr_iso","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tau_pt_weighted_dphi_strip","muTauPlots/muTau_tau_pt_weighted_dphi_strip.root","mt_inclusive",3,"tau_pt_weighted_dphi_strip","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tau_pt_weighted_deta_strip","muTauPlots/muTau_tau_pt_weighted_deta_strip.root","mt_inclusive",3,"tau_pt_weighted_deta_strip","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_photonPtSumOutsideSignalCone_2","muTauPlots/muTau_photonPtSumOutsideSignalCone_2.root","mt_inclusive",3,"photonPtSumOutsideSignalCone_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_photonPtSumOutsideSignalConedR03_2","muTauPlots/muTau_photonPtSumOutsideSignalConedR03_2.root","mt_inclusive",3,"photonPtSumOutsideSignalConedR03_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_neutralIsoPtSumWeight_2","muTauPlots/muTau_neutralIsoPtSumWeight_2.root","mt_inclusive",3,"neutralIsoPtSumWeight_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true ,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_neutralIsoPtSumdR03_2","muTauPlots/muTau_neutralIsoPtSumdR03_2.root","mt_inclusive",3,"neutralIsoPtSumdR03_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_sumChargedHadronPt04_1","muTauPlots/muTau_sumChargedHadronPt04_1.root","mt_inclusive",3,"sumChargedHadronPt04_1","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_sumChargedHadronPt03_1","muTauPlots/muTau_sumChargedHadronPt03_1.root","mt_inclusive",3,"sumChargedHadronPt03_1","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_sumNeutralHadronPt04_1","muTauPlots/muTau_sumNeutralHadronPt04_1.root","mt_inclusive",3,"sumNeutralHadronPt04_1","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_sumNeutralHadronPt03_1","muTauPlots/muTau_sumNeutralHadronPt03_1.root","mt_inclusive",3,"sumNeutralHadronPt03_1","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_sumPhotonPt04_1","muTauPlots/muTau_sumPhotonPt04_1.root","mt_inclusive",3,"sumPhotonPt04_1","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_sumPUPt04_1","muTauPlots/muTau_sumPUPt04_1.root","mt_inclusive",3,"sumPUPt04_1","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_mt_1","muTauPlots/muTau_pfmt_1.root","mt_inclusive",3,"m_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_mt_1_nocut","muTauPlots/muTau_mt_1_nocut.root","mt_inclusive",3,"no cut m_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);

   makeLTauStack("~/www/ltau_2018_mutau/muTau_phi_1","muTauPlots/muTau_phi_1.root","mt_inclusive",3,"#mu #phi","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_phi_2","muTauPlots/muTau_phi_2.root","mt_inclusive",3,"#tau #phi","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_mt_2","muTauPlots/muTau_mt_2.root","mt_inclusive",3,"#mu +MET m_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_mt","muTauPlots/muTau_mt.root","mt_inclusive",3,"Total m_{T}","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_iso_1","muTauPlots/muTau_iso_1.root","mt_inclusive",3,"Isolation #mu DR=0.4","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_pt_1","muTauPlots/muTau_pt_1.root","mt_inclusive",3,"#mu P_{T} ","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_pt_1_vbf","muTauPlots/muTau_pt_1_vbf.root","mt_inclusive",3,"#mu P_{T} ","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_1","muTauPlots/muTau_eta_1.root","mt_inclusive",3,"#eta_{#mu}","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_1_30","muTauPlots/muTau_eta_1_30.root","mt_inclusive",3,"#eta_{#mu} taupt>30","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_2","muTauPlots/muTau_eta_2.root","mt_inclusive",3,"#eta_{#tau}","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_eta_2_30","muTauPlots/muTau_eta_2_30.root","mt_inclusive",3,"#eta_{#tau} pt>30","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_m_vis","muTauPlots/muTau_m_vis.root","mt_inclusive",3,"visible mass","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_pt","muTauPlots/muTau_pt.root","mt_inclusive",3,"di-tau Pt","GeV",false,"#tau_{#mu}#tau_{h}","Golden",true,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_q_1","muTauPlots/muTau_q_1.root","mt_inclusive",3,"q_{#mu}","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_q_2","muTauPlots/muTau_q_2.root","mt_inclusive",3,"q_{#tau}","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_nCands","muTauPlots/muTau_nCands.root","mt_inclusive",3,"nCands","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tauDecayMode","muTauPlots/muTau_tauDecayMode.root","mt_inclusive",3,"#tau decay mode","",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_dxy_2","muTauPlots/muTau_dxy_2.root","mt_inclusive",3,"dxy_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_dxySig_2","muTauPlots/muTau_dxySig_2.root","mt_inclusive",3,"dxySig_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_flightLength_2","muTauPlots/muTau_flightLength_2.root","mt_inclusive",3,"flightLength_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   //makeLTauStack("~/www/ltau_2018_mutau/muTau_flightLengthSig_2","muTauPlots/muTau_flightLengthSig_2.root","mt_inclusive",3,"flightLengthSig_2","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);
   makeLTauStack("~/www/ltau_2018_mutau/muTau_tauNIsoTracks","muTauPlots/muTau_tauNIsoTracks.root","mt_inclusive",3,"Number Isolated Tracks","GeV",false,"#tau_{#mu}#tau_{h}","Golden",false,false,true);


*/
}
