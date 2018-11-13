// Original setup from:
//https://raw.githubusercontent.com/lovedeepkaursaini/aHVV_HTT/master/anaHTT.C
// 04 Oct 2018
// to do list
// 1. add the extra mela variables ... currently tauCharge1 and tau1... map them correctly

#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
//#include "../interface/Mela.h"
//#include "../interface/TUtil.hh"
#include "ZZMatrixElement/MELA/interface/Mela.h"
#include "ZZMatrixElement/MELA/interface/TUtil.hh"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TKey.h"
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"


using namespace RooFit;
using namespace std;

void readdir(TDirectory *dir,optutl::CommandLineParser parser); 

//void MELA_HTT (TString InFile, TString OutFile)
int main (int argc, char* argv[])
{

    optutl::CommandLineParser parser ("Compute the MELA variables for flat tuple");
    parser.addOption("InFile",optutl::CommandLineParser::kString,"Input","");

    parser.parseArguments (argc, argv);

    TFile *f = new TFile(parser.stringValue("InFile").c_str(),"UPDATE");   

    readdir(f,parser);

    f->Close();

}


void readdir(TDirectory *dir,optutl::CommandLineParser parser) 
{
  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
	  TObject *obj = key->ReadObj();

	  if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
		  dir->cd(key->GetName());
		  TDirectory *subdir = gDirectory;
		  readdir(subdir,parser);
		  dirsav->cd();
	  }
      else if(obj->IsA()->InheritsFrom(TTree::Class())) {

          TTree *t = (TTree*)obj;

          //setting up MELA 
          int erg_tev=13;
          float mPOLE=125.6;
          float wPOLE=4.07e-3;
          TVar::VerbosityLevel verbosity = TVar::SILENT;
          Mela mela(erg_tev, mPOLE, verbosity);

          float ME_sm, ME_bsm, ME_bsm_mlt, KD_sm, KD_bsm, melaD0minus, ME_int, melaDCP,
                ME_sm_ggH, ME_bsm_ggH, ME_int_ggH,
                melaD0hplus, melaDint, melaDL1, melaDL1int, melaDL1Zg, melaDL1Zgint,
                melaD0minusggH, melaDCPggH,
                dPhi_jj, dPhiUnsigned_jj, dEta_jj,
                costhetastar, costheta1, costheta2, melaPhi, melaPhi1, Q2V1, Q2V2,
                sqrtQ2V1, sqrtQ2V2, avgSqrtQ2V12;
          
          float ME_sm_VBF, ME_sm_WH, ME_sm_ZH, ME_bkg1, ME_bkg2;

          Float_t         m_sv;
          Float_t         pt_sv;
          Float_t         eta_sv;
          Float_t         phi_sv;
          Int_t           njets;
          float jmass_1, jpt_1, jeta_1, jphi_1;
          float jmass_2, jpt_2, jeta_2, jphi_2;
          Float_t         pt_2;
          Float_t         phi_2;
          Float_t         eta_2;
          Float_t         m_2;
          Float_t         pt_1;
          Float_t         phi_1;
          Float_t         eta_1;
          Float_t         m_1;
    
          Float_t q_1;
          Float_t q_2;


          TBranch        *b_njets;   //!
          TBranch        *b_jpt_1;   //!
          TBranch        *b_jeta_1;   //!
          TBranch        *b_jphi_1;   //!
          TBranch        *b_jpt_2;   //!
          TBranch        *b_jeta_2;   //!
          TBranch        *b_jphi_2;   //!
          TBranch        *b_m_sv;   //!
          TBranch        *b_pt_sv;   //!
          TBranch        *b_eta_sv;   //!
          TBranch        *b_phi_sv;   //!
          TBranch        *b_pt_2;   //!
          TBranch        *b_phi_2;   //!
          TBranch        *b_eta_2;   //!
          TBranch        *b_m_2;   //!
          TBranch        *b_q_2;   //!
          TBranch        *b_pt_1;   //!
          TBranch        *b_phi_1;   //!
          TBranch        *b_eta_1;   //!
          TBranch        *b_m_1;   //!
          TBranch        *b_q_1;   //!

          t->SetBranchAddress("njets", &njets, &b_njets);
          t->SetBranchAddress("jpt_1", &jpt_1, &b_jpt_1);
          t->SetBranchAddress("jeta_1", &jeta_1, &b_jeta_1);
          t->SetBranchAddress("jphi_1", &jphi_1, &b_jphi_1);
          t->SetBranchAddress("jpt_2", &jpt_2, &b_jpt_2);
          t->SetBranchAddress("jeta_2", &jeta_2, &b_jeta_2);
          t->SetBranchAddress("jphi_2", &jphi_2, &b_jphi_2);
          t->SetBranchAddress("m_sv", &m_sv, &b_m_sv);
          t->SetBranchAddress("pt_sv", &pt_sv, &b_pt_sv);
          t->SetBranchAddress("eta_sv", &eta_sv, &b_eta_sv);
          t->SetBranchAddress("phi_sv", &phi_sv, &b_phi_sv);
          t->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
          t->SetBranchAddress("phi_1", &phi_1, &b_phi_1);
          t->SetBranchAddress("eta_1", &eta_1, &b_eta_1);
          t->SetBranchAddress("m_1", &m_1, &b_m_1);
          t->SetBranchAddress("q_1", &q_1, &b_q_1);
          t->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
          t->SetBranchAddress("phi_2", &phi_2, &b_phi_2);
          t->SetBranchAddress("eta_2", &eta_2, &b_eta_2);
          t->SetBranchAddress("m_2", &m_2, &b_m_2);
          t->SetBranchAddress("q_2", &q_2, &b_q_2);

          mela.setCandidateDecayMode(TVar::CandidateDecay_Stable);
          TBranch *bMelaD0minus        =  t->Branch("melaD0minus", &melaD0minus,"melaD0minus/F");
          TBranch *bMelaDCP            =  t->Branch("melaDCP", &melaDCP,"melaDCP/F");
          TBranch *bMelaD0hplus        =  t->Branch("melaD0hplus", &melaD0hplus,"melaD0hplus/F");
          TBranch *bMelaDint           =  t->Branch("melaDint", &melaDint,"melaDint/F");
          TBranch *bMelaDL1            =  t->Branch("melaDL1", &melaDL1,"melaDL1/F");
          TBranch *bMelaDL1int         =  t->Branch("melaDL1int", &melaDL1int,"melaDL1int/F");
          TBranch *bMelaDL1Zg          =  t->Branch("melaDL1Zg", &melaDL1Zg,"melaDL1Zg/F");
          TBranch *bMelaDL1Zgint       =  t->Branch("melaDL1Zgint", &melaDL1Zgint,"melaDL1Zgint/F");
          TBranch *bMelaD0minusggH     =  t->Branch("melaD0minusggH", &melaD0minusggH,"melaD0minusggH/F");
          TBranch *bMelaDCPggH         =  t->Branch("melaDCPggH", &melaDCPggH,"melaDCPggH/F");
          TBranch *bMelaDPhijj         =  t->Branch("melaDPhijj", &dPhi_jj,"melaDPhijj/F");
          TBranch *bMelaDPhiUnsignedjj =  t->Branch("melaDPhiUnsignedjj", &dPhiUnsigned_jj,"melaDPhiUnsignedjj/F");
          TBranch *bMelaDEtajj         =  t->Branch("melaDEtajj", &dEta_jj,"melaDEtajj/F");
          TBranch *bMelacosthetastar   =  t->Branch("melacosthetastar", &costhetastar,"melacosthetastar/F");
          TBranch *bMelacostheta1      =  t->Branch("melacostheta1", &costheta1,"melacostheta1/F");
          TBranch *bMelacostheta2      =  t->Branch("melacostheta2", &costheta2,"melacostheta2/F");
          TBranch *bMelaPhi            =  t->Branch("melaPhi", &melaPhi,"melaPhi/F");
          TBranch *bMelaPhi1           =  t->Branch("melaPhi1", &melaPhi1,"melaPhi1/F");
          TBranch *bMelaQ2V1           =  t->Branch("melaQ2V1", &Q2V1,"melaQ2V1/F");
          TBranch *bMelaQ2V2           =  t->Branch("melaQ2V2", &Q2V2,"melaQ2V2/F");
          TBranch *bMelaSqrtQ2V1       =  t->Branch("melaSqrtQ2V1", &sqrtQ2V1,"melaSqrtQ2V1/F");
          TBranch *bMelaSqrtQ2V2       =  t->Branch("melaSqrtQ2V2", &sqrtQ2V2,"melaSqrtQ2V2/F");
          TBranch *bMelaAvgSqrtQ2V12   =  t->Branch("melaAvgSqrtQ2V12", &avgSqrtQ2V12,"melaAvgSqrtQ2V12/F");
          //new mela vars
          TBranch *bME_bkg1            =  t->Branch("ME_bkg1", &ME_bkg1,"ME_bkg1/F");
          TBranch *bME_bkg2            =  t->Branch("ME_bkg2", &ME_bkg2,"ME_bkg2/F");
          TBranch *bME_sm_VBF            =  t->Branch("ME_sm_VBF", &ME_sm_VBF,"ME_sm_VBF/F");
          TBranch *bME_sm_WH            =  t->Branch("ME_sm_WH", &ME_sm_WH,"ME_sm_WH/F");
          TBranch *bME_sm_ZH            =  t->Branch("ME_sm_ZH", &ME_sm_ZH,"ME_sm_ZH/F");

          printf("Found tree -> computing MELA vars\n");

          for(Int_t i=0;i<t->GetEntries();++i)
          {

              if ( i % 100 == 0 ) std::cout << i << std::endl;
              //nb = tree->GetEntry(i);   
              //nbytes += nb;

              t->GetEntry(i);
              melaD0hplus = -9;
              melaDint = -9;
              melaDL1 = -9;
              melaDL1int = -9;
              melaDL1Zg = -9;
              melaDL1Zgint = -9;
              melaD0minus = -9;
              melaDCP = -9;
              melaD0minusggH = -9;
              melaDCPggH = -9;
              dPhi_jj = -9;
              dPhiUnsigned_jj = -9;
              dEta_jj = -19;
              costhetastar = -9;
              costheta1 = -9;
              costheta2 = -9;
              melaPhi = -9;
              melaPhi1 = -9;
              Q2V1 = -9;
              Q2V2 = -9;
              sqrtQ2V1 = -9;
              sqrtQ2V2 = -9;
              avgSqrtQ2V12 = -9;
              ME_bkg1 = -9;
              ME_sm_VBF = -9;

              if (njets>=2&&pt_sv>0.0){
                  if ( i % 100 == 0 ) std::cout << "Found entry with 2 jets ... mod 100" << "with njets "<<njets<<std::endl;
                  TLorentzVector jet1(0, 0, 1e-3, 1e-3), jet2(0, 0, 1e-3, 1e-3), higgs(0, 0, 0, 0),
                                 blank1(0, 0, 0, 0);
                  
                  TLorentzVector tau1, tau2;
                  tau1.SetPtEtaPhiM(pt_1, eta_1, phi_1, m_1);
                  tau2.SetPtEtaPhiM(pt_2, eta_2, phi_2, m_2);
            
                  jet1.SetPtEtaPhiM(jpt_1, jeta_1, jphi_1, 0);
                  jet2.SetPtEtaPhiM(jpt_2, jeta_2, jphi_2, 0);
                  // tau lepton 4-vectors
                  if (q_1*q_2 > 0) {
                      // For QCD estimation purpose, make the tauCharge2 opposite charge of tauCharge1 :/
                      q_2 = -q_1;
                  }
                    

                  SimpleParticleCollection_t daughters;
                  daughters.push_back(SimpleParticle_t(15*q_1, tau1)); 
                  daughters.push_back(SimpleParticle_t(15*q_2, tau2));

                  SimpleParticleCollection_t associated;
                  associated.push_back(SimpleParticle_t(0, jet1));
                  associated.push_back(SimpleParticle_t(0, jet2));

                  TLorentzVector pDaughters1, pDaughters2;
                  pDaughters1.SetPtEtaPhiM(pt_1, eta_1, phi_1, m_1);
                  pDaughters1.SetPtEtaPhiM(pt_2, eta_2, phi_2, m_2);


                  //new additions
                  // SM Higgs hypothesis ===========================================================
                  mela.setCandidateDecayMode(TVar::CandidateDecay_ff);
                  mela.setInputEvent(&daughters, &associated, (SimpleParticleCollection_t*)0, false);
                  mela.setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
                  mela.computeProdP(ME_sm_VBF, false);
                  std::cout<<"MELA SM VBF category signal discriminant HSM JJVBF:  "<<ME_sm_VBF<<std::endl;

                  //mela.computeVBFAngles(Q2V1, Q2V2, costheta1, costheta2, melaPhi, costhetastar, melaPhi1);

                  //get the ggH + 2jets hypothesis
                  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJQCD);
                  mela.selfDHggcoupl[0][gHIGGS_GG_2][0] = 1;
                  mela.computeProdP(ME_sm_ggH, false);

                  //get the WH + 2 jets hypothesis
                  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::Had_WH);
                  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0] = 1;
                  mela.computeProdP(ME_sm_WH, false);
                  std::cout<<"MELA SM WH + 2Jets :  "<<ME_sm_WH<<std::endl;

                  //get the ZH + 2 jets hypothesis
                  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::Had_ZH);
                  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0] = 1;
                  mela.computeProdP(ME_sm_ZH, false);
                  std::cout<<"MELA SM ZH + 2Jets :  "<<ME_sm_ZH<<std::endl;

                  // Z+2jets
                  mela.setProcess(TVar::bkgZJets, TVar::MCFM, TVar::JJQCD);
                  //mela.setProcess(TVar::bkgZJets, TVar::JHUGen, TVar::JJQCD);
                  mela.computeProdP(ME_bkg1, false);
                  std::cout<<"MELA Z + 2Jets :  "<<ME_bkg1<<std::endl;

                  associated.clear();
                  associated.push_back(SimpleParticle_t(0, jet2));
                  associated.push_back(SimpleParticle_t(0, jet1));
                  mela.setInputEvent(&daughters, &associated, (SimpleParticleCollection_t*)0, false);
                  mela.setProcess(TVar::bkgZJets, TVar::MCFM, TVar::JJQCD);
                  mela.computeProdP(ME_bkg2, false);
                  std::cout<<"MELA Z + 2Jets #2:  "<<ME_bkg2<<std::endl;

                  if (jet1.Pz() <= jet2.Pz()) {
                      dPhi_jj = jet1.DeltaPhi(jet2);
                  }
                  else {
                      dPhi_jj = jet2.DeltaPhi(jet1);
                  }
                  dPhiUnsigned_jj = jet1.DeltaPhi(jet2);
                  dEta_jj = jet1.Eta()-jet2.Eta();

                  // See: https://github.com/usarica/HiggsAnalysis-ZZMatrixElement/blob/newVH/MELA/interface/TUtil.hh#L106-L122
                  TUtil::computeVBFAngles( 
                          costhetastar, costheta1, costheta2, melaPhi, melaPhi1, Q2V1, Q2V2,
                          higgs, 25,
                          blank1, -9000,
                          blank1, -9000,
                          blank1, -9000,
                          jet1, 0,
                          jet2, 0
                          );

                  sqrtQ2V1 = TMath::Sqrt( Q2V1 );
                  sqrtQ2V2 = TMath::Sqrt( Q2V2 );
                  avgSqrtQ2V12 = (sqrtQ2V1 + sqrtQ2V2) / 2.;

              }
              
              bMelaD0minus       ->Fill();
              bMelaDCP           ->Fill();
              bMelaD0hplus       ->Fill();
              bMelaDint          ->Fill();
              bMelaDL1           ->Fill();
              bMelaDL1int        ->Fill();
              bMelaDL1Zg         ->Fill();
              bMelaDL1Zgint      ->Fill();
              bMelaD0minusggH    ->Fill();
              bMelaDCPggH        ->Fill();
              bMelaDPhijj        ->Fill();
              bMelaDPhiUnsignedjj->Fill();
              bMelaDEtajj        ->Fill();
              bMelacosthetastar  ->Fill();
              bMelacostheta1     ->Fill();
              bMelacostheta2     ->Fill();
              bMelaPhi           ->Fill();
              bMelaPhi1          ->Fill();
              bMelaQ2V1          ->Fill();
              bMelaQ2V2          ->Fill();
              bMelaSqrtQ2V1      ->Fill();
              bMelaSqrtQ2V2      ->Fill();
              bMelaAvgSqrtQ2V12  ->Fill();
              bME_bkg1  ->Fill();
              bME_bkg2  ->Fill();
              bME_sm_VBF  ->Fill();
              bME_sm_WH  ->Fill();
              bME_sm_ZH  ->Fill();
              mela.resetInputEvent();
          }
          //dir->Print();
          //gDirectory->WriteObject(t,"");
          gDirectory->ls();
          dir->WriteTObject(t,"","Overwrite");
		  //t->Write("",TObject::kOverwrite);
	  }//end else if object A
  }//end while key
}//end read directory
