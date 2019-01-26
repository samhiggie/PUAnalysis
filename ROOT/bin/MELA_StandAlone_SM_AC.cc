#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include <math.h> 
#include "TMath.h" 
#include <limits>
#include "TSystem.h"
#include <vector>
#include <string>

#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "HTT-utilities/RecoilCorrections/interface/RecoilCorrector.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"


#include "ZZMatrixElement/MELA/interface/Mela.h"
#include "ZZMatrixElement/MELA/interface/TUtil.hh"


using namespace std;
Mela mela(13.0, 125.6, TVar::ERROR);

void copyFiles( optutl::CommandLineParser parser, TFile* fOld, TFile* fNew) ;
void readdir(TDirectory *dir, optutl::CommandLineParser parser,  char TreeToUse[], bool trueTau = true) ;
void CopyFile(const char *fname, optutl::CommandLineParser parser);
void CopyDir(TDirectory *source,optutl::CommandLineParser parser);


void calculateME(
                 float m_sv,float pt_sv,float eta_sv,float phi_sv,
                 float pt_1,float phi_1,float eta_1,float m_1,float q_1,float pt_2,float phi_2,float eta_2,float m_2,float q_2,int njets,float jpt_1,float jeta_1,float jphi_1,float jpt_2,float jeta_2,float jphi_2,
                 TLorentzVector tau1, TLorentzVector tau2, TLorentzVector jet1, TLorentzVector jet2,
                 int tauCharge1, int tauCharge2,
                 float& ME_sm_VBF, float& ME_sm_ggH, float& ME_sm_WH, float& ME_sm_ZH,
                 float& ME_bkg1, float& ME_bkg2,

                 float& ME_sm, float& ME_bsm, float& ME_bsm_mlt, float& KD_sm, float& KD_bsm, float& melaD0minus, float& ME_int, float& melaDCP, float& ME_bsm_ggH, float& ME_int_ggH, 
                 float& melaD0hplus, float& melaDint, float& melaDL1, float& melaDL1int, float& melaDL1Zg, float& melaDL1Zgint, 
                 float& melaD0minusggH, float& melaDCPggH, 
                 float&  melaDPhijj, float& melaDPhiUnsignedjj, float& melaDEtajj,
                 float& Q2V1, float& Q2V2, float& costheta1, float& costheta2, float& Phi, float& costhetastar, float& Phi1);
int main (int argc, char* argv[]) 
{
  optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
  parser.addOption("newFile",optutl::CommandLineParser::kString,"newFile","newFile.root");
  parser.addOption("newOutputFile",optutl::CommandLineParser::kDouble,"New Output File",0.0);
  parser.addOption("inputFile",optutl::CommandLineParser::kString,"input File");
  parser.addOption("trueTau",optutl::CommandLineParser::kBool,"use true 4-vectors of tau leptons",true);
  parser.parseArguments (argc, argv);
  
  std::cout << "Input commands:" 
        << "\n -- input file: " << parser.stringValue("inputFile")
        << "\n -- output file: " << parser.stringValue("newFile")
        << "\n -- use true tau 4-vectors (1 - yes, 0 - no): " << parser.boolValue("trueTau") << std::endl;
  
  
  char TreeToUse[80]="first";
  
  TFile *fProduce;//= new TFile(parser.stringValue("newFile").c_str(),"UPDATE");
  
  if(parser.doubleValue("newOutputFile")>0){
    TFile *f = new TFile(parser.stringValue("inputFile").c_str(),"READ");
    std::cout<<"Creating new outputfile"<<std::endl;
    std::string newFileName = parser.stringValue("newFile");
    
    fProduce = new TFile(newFileName.c_str(),"RECREATE");
    copyFiles(parser, f, fProduce);//new TFile(parser.stringValue("inputFile").c_str()+"SVFit","UPDATE");
    fProduce = new TFile(newFileName.c_str(),"UPDATE");
    std::cout<<"listing the directories================="<<std::endl;
    fProduce->ls();
    
    readdir(fProduce, parser,  TreeToUse, parser.boolValue("trueTau"));
    fProduce->Close();
    f->Close();
  }
  else{
    TFile *f = new TFile(parser.stringValue("inputFile").c_str(),"UPDATE");
    readdir(f, parser,  TreeToUse, parser.boolValue("trueTau"));
    f->Close();
  }
  
  return 0;  
} 


void readdir(TDirectory *dir, optutl::CommandLineParser parser,  char TreeToUse[], bool trueTau)
{
  
  std::cout << "Starting!!!" << std::endl;
  std::cout << "TreeToUse: " << TreeToUse << std::endl;
  char stringA[80]="first";
  std::string channel = "x";

  TDirectory *dirsav = gDirectory;
  TKey *key;
  dir->cd();      

  std::vector<TString> processedNames;
  
  TIter next(dir->GetListOfKeys());
  while ((key = (TKey*)next())) {
    printf("Found key=%s \n",key->GetName());
    
    TObject *obj = key->ReadObj();
    if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
      std::cout << "This is a directory, diving in!" << std::endl;
      // zero the processedNames vector, to allow processing trees with duplicate names in separate directories
      processedNames.clear();

      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      sprintf(TreeToUse,"%s",key->GetName());
      readdir(subdir, parser,  TreeToUse, trueTau);
      
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      // check  if this tree was already processed
      std::vector<TString>::const_iterator it = find(processedNames.begin(), processedNames.end(), key->GetName());
      if ( it != processedNames.end() ) {
    std::cout << "This tree was already processed, skipping..." <<  std::endl;
        continue;
      }
      std::cout << "This is the tree! Start processing" << std::endl;
      processedNames.push_back(key->GetName());
      
      // Identify the process
      if ( std::string(key->GetName()).find("eventTree") != std::string::npos )  {
        channel = "tt";
    std::cout << "Identified channel tt" << std::endl;
      } 
      else if ( std::string(key->GetName()).find("em") != std::string::npos )  {
    channel = "em";
    std::cout << "Identified channel em" << std::endl;
      }
      else if ( std::string(key->GetName()).find("et") != std::string::npos ) {
        channel = "et";
    std::cout << "Identified channel et" << std::endl;
      } 
      else if ( std::string(key->GetName()).find("mutau") != std::string::npos ) {
        channel = "mt";
    std::cout << "Identified channel mt" << std::endl;
      } else {
    std::cout<<"Tree "<< key->GetName() <<" does not match ... Skipping!!"<<std::endl;
        return;
      }

      TTree* tree = (TTree*)obj;
      // mela SM analysis
      float ME_sm_VBF, ME_sm_ggH, ME_sm_WH, ME_sm_ZH, ME_bkg, ME_bkg1, ME_bkg2;
      float mela_Dbkg_VBF, mela_Dbkg_ggH, mela_Dbkg_WH, mela_Dbkg_ZH;

      // mela AC analysis 
      float ME_sm, ME_bsm, ME_bsm_mlt, KD_sm, KD_bsm, melaD0minus, ME_int, melaDCP,
            ME_bsm_ggH, ME_int_ggH,
            melaD0hplus, melaDint, melaDL1, melaDL1int, melaDL1Zg, melaDL1Zgint,
            melaD0minusggH, melaDCPggH,
            melaDPhijj, melaDPhiUnsignedjj, melaDEtajj;
      // angles
      float Q2V1,Q2V2;
      float costheta1,costheta2;
      float Phi;
      float costhetastar;
      float Phi1;
      // taus kinematics
      Float_t pt_1, eta_1, phi_1, m_1, q_1;
      Float_t pt_2, eta_2, phi_2, m_2, q_2;
      //parent kinematics
      Float_t         m_sv;
      Float_t         pt_sv;
      Float_t         eta_sv;
      Float_t         phi_sv;
      // jets kinematics
      Int_t   njets;
      Float_t jpt_1, jpt_2; 
      Float_t jeta_1, jphi_1; 
      Float_t jeta_2, jphi_2; 

      
      TBranch        *b_m_sv;   //!
      TBranch        *b_pt_sv;   //!
      TBranch        *b_eta_sv;   //!
      TBranch        *b_phi_sv;   //!
      TBranch *b_q_1;
      TBranch *b_q_2;
      TBranch *b_pt_1;   //!
      TBranch *b_phi_1;   //!
      TBranch *b_eta_1;   //!
      TBranch *b_m_1;   //!
      TBranch *b_pt_2;   //!
      TBranch *b_phi_2;   //!
      TBranch *b_eta_2;   //!
      TBranch *b_m_2;   //!
      TBranch *b_njets;   //!
      TBranch *b_jpt_1;   //!
      TBranch *b_jeta_1;   //!
      TBranch *b_jphi_1;   //!
      TBranch *b_jpt_2;   //!
      TBranch *b_jeta_2;   //!
      TBranch *b_jphi_2;   //!


      tree->SetBranchAddress("m_sv", &m_sv, &b_m_sv);
      tree->SetBranchAddress("pt_sv", &pt_sv, &b_pt_sv);
      tree->SetBranchAddress("eta_sv", &eta_sv, &b_eta_sv);
      tree->SetBranchAddress("phi_sv", &phi_sv, &b_phi_sv);
      tree->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
      tree->SetBranchAddress("phi_1", &phi_1, &b_phi_1);
      tree->SetBranchAddress("eta_1", &eta_1, &b_eta_1);
      tree->SetBranchAddress("m_1", &m_1, &b_m_1);
      tree->SetBranchAddress("q_1", &q_1, &b_q_1);
      tree->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
      tree->SetBranchAddress("phi_2", &phi_2, &b_phi_2);
      tree->SetBranchAddress("eta_2", &eta_2, &b_eta_2);
      tree->SetBranchAddress("m_2", &m_2, &b_m_2);
      tree->SetBranchAddress("q_2", &q_2, &b_q_2);
      tree->SetBranchAddress("njets", &njets, &b_njets);
      tree->SetBranchAddress("jpt_1", &jpt_1, &b_jpt_1);
      tree->SetBranchAddress("jeta_1", &jeta_1, &b_jeta_1);
      tree->SetBranchAddress("jphi_1", &jphi_1, &b_jphi_1);
      tree->SetBranchAddress("jpt_2", &jpt_2, &b_jpt_2);
      tree->SetBranchAddress("jeta_2", &jeta_2, &b_jeta_2);
      tree->SetBranchAddress("jphi_2", &jphi_2, &b_jphi_2);



      // new branches that will need to be filled
      std::string Dbkg_VBF_unc = "Dbkg_VBF";
      std::string Dbkg_ggH_unc = "Dbkg_ggH";
      std::string Dbkg_WH_unc = "Dbkg_WH";
      std::string Dbkg_ZH_unc = "Dbkg_ZH";

      std::string ME_sm_VBF_unc = "ME_sm_VBF";
      std::string ME_sm_ggH_unc = "ME_sm_ggH";
      std::string ME_sm_WH_unc = "ME_sm_WH";
      std::string ME_sm_ZH_unc = "ME_sm_ZH";
      std::string ME_bkg_unc = "ME_bkg";
      std::string ME_bkg1_unc = "ME_bkg1";
      std::string ME_bkg2_unc = "ME_bkg2";

      std::string Q2V1_unc = "Q2V1";
      std::string Q2V2_unc = "Q2V2";
      std::string costheta1_unc = "costheta1";
      std::string costheta2_unc = "costheta2";
      std::string Phi_unc = "Phi";
      std::string costhetastar_unc = "costhetastar";
      std::string Phi1_unc = "Phi1";

      std::string mjj_unc = "mjj";
     

      std::string ME_sm_unc          =    "ME_sm"      ;
      std::string ME_bsm_unc         =    "ME_bsm"     ;         
      std::string ME_bsm_mlt_unc     =    "ME_bsm_mlt" ;             
      std::string KD_sm_unc          =    "KD_sm"      ;       
      std::string KD_bsm_unc         =    "KD_bsm"     ;         
      std::string ME_int_unc         =    "ME_int"     ;        
      std::string ME_bsm_ggH_unc     =    "ME_bsm_ggH" ;             
      std::string ME_int_ggH_unc     =    "ME_int_ggH" ;             

      std::string melaD0minus_unc        =  "melaD0minus"       ;
      std::string melaDCP_unc            =  "melaDCP"           ;
      std::string melaD0hplus_unc        =  "melaD0hplus"       ;
      std::string melaDint_unc           =  "melaDint"          ;
      std::string melaDL1_unc            =  "melaDL1"           ;
      std::string melaDL1int_unc         =  "melaDL1int"        ;
      std::string melaDL1Zg_unc          =  "melaDL1Zg"         ;
      std::string melaDL1Zgint_unc       =  "melaDL1Zgint"      ;
      std::string melaD0minusggH_unc     =  "melaD0minusggH"    ;
      std::string melaDCPggH_unc         =  "melaDCPggH"        ;
      std::string melaDPhijj_unc         =  "melaDPhijj"        ;
      std::string melaDPhiUnsignedjj_unc =  "melaDPhiUnsignedjj"; 
      std::string melaDEtajj_unc         =  "melaDEtajj"        ;  


 
      vector<TBranch*> newBranches;
      newBranches.push_back(tree->Branch(Dbkg_VBF_unc.c_str(), &mela_Dbkg_VBF));
      newBranches.push_back(tree->Branch(Dbkg_ggH_unc.c_str(), &mela_Dbkg_ggH));
      newBranches.push_back(tree->Branch(Dbkg_WH_unc.c_str(), &mela_Dbkg_WH));
      newBranches.push_back(tree->Branch(Dbkg_ZH_unc.c_str(), &mela_Dbkg_ZH));
      // ME
      newBranches.push_back(tree->Branch(ME_sm_VBF_unc.c_str(), &ME_sm_VBF));
      newBranches.push_back(tree->Branch(ME_sm_ggH_unc.c_str(), &ME_sm_ggH));
      newBranches.push_back(tree->Branch(ME_sm_WH_unc.c_str(), &ME_sm_WH));
      newBranches.push_back(tree->Branch(ME_sm_ZH_unc.c_str(), &ME_sm_ZH));
      newBranches.push_back(tree->Branch(ME_bkg_unc.c_str(), &ME_bkg));
      newBranches.push_back(tree->Branch(ME_bkg1_unc.c_str(), &ME_bkg1));
      newBranches.push_back(tree->Branch(ME_bkg2_unc.c_str(), &ME_bkg2));
      //AC

      newBranches.push_back(tree->Branch(ME_sm_unc.c_str()         , &ME_sm      ));
      newBranches.push_back(tree->Branch(ME_bsm_unc.c_str()        , &ME_bsm     ));         
      newBranches.push_back(tree->Branch(ME_bsm_mlt_unc.c_str()    , &ME_bsm_mlt ));             
      newBranches.push_back(tree->Branch(KD_sm_unc.c_str()         , &KD_sm      ));       
      newBranches.push_back(tree->Branch(KD_bsm_unc.c_str()        , &KD_bsm     ));         
      newBranches.push_back(tree->Branch(ME_int_unc.c_str()        , &ME_int     ));        
      newBranches.push_back(tree->Branch(ME_bsm_ggH_unc.c_str()    , &ME_bsm_ggH ));             
      newBranches.push_back(tree->Branch(ME_int_ggH_unc.c_str()    , &ME_int_ggH ));             

      newBranches.push_back(tree->Branch(melaD0minus_unc.c_str()        ,  &melaD0minus       ));
      newBranches.push_back(tree->Branch(melaDCP_unc.c_str()            ,  &melaDCP           ));
      newBranches.push_back(tree->Branch(melaD0hplus_unc.c_str()        ,  &melaD0hplus       ));
      newBranches.push_back(tree->Branch(melaDint_unc.c_str()           ,  &melaDint          ));
      newBranches.push_back(tree->Branch(melaDL1_unc.c_str()            ,  &melaDL1           ));
      newBranches.push_back(tree->Branch(melaDL1int_unc.c_str()         ,  &melaDL1int        ));
      newBranches.push_back(tree->Branch(melaDL1Zg_unc.c_str()          ,  &melaDL1Zg         ));
      newBranches.push_back(tree->Branch(melaDL1Zgint_unc.c_str()       ,  &melaDL1Zgint      ));
      newBranches.push_back(tree->Branch(melaD0minusggH_unc.c_str()     ,  &melaD0minusggH    ));
      newBranches.push_back(tree->Branch(melaDCPggH_unc.c_str()         ,  &melaDCPggH        ));
      newBranches.push_back(tree->Branch(melaDPhijj_unc.c_str()         ,  &melaDPhijj        ));
      newBranches.push_back(tree->Branch(melaDPhiUnsignedjj_unc.c_str() ,  &melaDPhiUnsignedjj)); 
      newBranches.push_back(tree->Branch(melaDEtajj_unc.c_str()         ,  &melaDEtajj        ));  

      // angles
      newBranches.push_back(tree->Branch(Q2V1_unc.c_str(), &Q2V1));
      newBranches.push_back(tree->Branch(Q2V2_unc.c_str(), &Q2V2));
      newBranches.push_back(tree->Branch(costheta1_unc.c_str(), &costheta1));
      newBranches.push_back(tree->Branch(costheta2_unc.c_str(), &costheta2));
      newBranches.push_back(tree->Branch(Phi_unc.c_str(), &Phi));
      newBranches.push_back(tree->Branch(costhetastar_unc.c_str(), &costhetastar));
      newBranches.push_back(tree->Branch(Phi1_unc.c_str(), &Phi1));

      float mjj = 0;
      newBranches.push_back(tree->Branch(mjj_unc.c_str(), &mjj));

      Long64_t nentries = tree->GetEntries();

      Long64_t nbytes = 0, nb = 0;
      for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if ( jentry % 100000 == 0 ) std::cout << jentry << std::endl;
    nb = tree->GetEntry(jentry);   nbytes += nb;
    
    // initialize
    mjj = 0;
    ME_sm_VBF = -100; // ME for SM process VBF H->tt
    ME_sm_ggH = -100; // ME for ggH + 2 jets
    ME_sm_WH  = -100; // ME for WH (W->jj)
    ME_sm_ZH  = -100; // ME for ZH (Z->jj)
    
    ME_bkg1 = -100;   // ME for Z+2jets with leading jet being first, trailing second
    ME_bkg2 = -100;   // ME for Z+2jets with trailing jet being first, leading second
    ME_bkg  = -100;   // Sum of the two above (what we need to use)
    
    mela_Dbkg_VBF = -100; // ME_sm_VBF / (ME_sm_VBF + ME_bkg) <- normalized probability to separate H->tt and Z->tt
    mela_Dbkg_ggH = -100; // same for ggH and Ztt
    mela_Dbkg_WH  = -100; // same for WH and Ztt
    mela_Dbkg_ZH  = -100; // same for ZH and Ztt

    //Anomalous Couplings 
    

    ME_sm = -100;
    ME_bsm = -100;
    ME_bsm_mlt = -100;
    KD_sm = -100;
    KD_bsm = -100;
    ME_int = -100;
    ME_bsm_ggH = -100;
    ME_int_ggH = -100;
 
    melaD0hplus = -100;
    melaDint = -100;
    melaDL1 = -100;
    melaDL1int = -100;
    melaDL1Zg = -100;
    melaDL1Zgint = -100;
    melaD0minus = -100;
    melaDCP = -100;
    melaD0minusggH = -100;
    melaDCPggH = -100;
    melaDPhijj = -100;
    melaDPhiUnsignedjj = -100;
    melaDEtajj = -100;

    // angles inputs to MELA
    Q2V1 = -100;
    Q2V2 = -100;
    costheta1    = -100;
    costheta2    = -100;
    Phi          = -100;
    costhetastar = -100;
    Phi1         = -100;
    

    if (njets>=2){
      TLorentzVector tau1, tau2;
      tau1.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
      tau2.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
      
      // jet 4-vectors
      TLorentzVector jet1(0, 0, 1e-3, 1e-3), jet2(0, 0, 1e-3, 1e-3), higgs(0, 0, 0, 0), blank1(0, 0, 0, 0);
      jet1.SetPtEtaPhiM(jpt_1, jeta_1, jphi_1, 0);
      jet2.SetPtEtaPhiM(jpt_2, jeta_2, jphi_2, 0);
      mjj = (jet1 +  jet2).M();
        
      // tau lepton 4-vectors
      TLorentzVector pDaughters1, pDaughters2;
      
      TLorentzVector visTau1, visTau2;
      visTau1.SetPtEtaPhiM(pt_1, eta_1, phi_1, m_1);
      visTau2.SetPtEtaPhiM(pt_2, eta_2, phi_2, m_2);
        
      if ( !trueTau ) {
        pDaughters1 = visTau1;
        pDaughters2 = visTau2;
      } else {
        pDaughters1 = tau1;
        pDaughters2 = tau2;
      }
      
      
      
      // Determine the signs of the tau leptons      
      int tauCharge1 = q_1;
      int tauCharge2 = q_2;
      
      if ( tau1.DeltaR(visTau1) > tau1.DeltaR(visTau2) )
        tauCharge1 = q_2;
      if ( tau2.DeltaR(visTau2) > tau2.DeltaR(visTau1) ) 
        tauCharge2 = q_1;
      
      calculateME(
              m_sv,pt_sv,eta_sv,phi_sv,
              pt_1,phi_1,eta_1,m_1,q_1,pt_2,phi_2,eta_2,m_2,q_2,njets,jpt_1,jeta_1,jphi_1,jpt_2,jeta_2,jphi_2,                
              pDaughters1, pDaughters2, jet1, jet2, tauCharge1, tauCharge2,
              ME_sm_VBF, ME_sm_ggH, ME_sm_WH, ME_sm_ZH,
              ME_bkg1, ME_bkg2,
              ME_sm,  ME_bsm,  ME_bsm_mlt,  KD_sm,  KD_bsm,  melaD0minus,  ME_int,  melaDCP,  ME_bsm_ggH,  ME_int_ggH, 
              melaD0hplus,  melaDint,  melaDL1,  melaDL1int,  melaDL1Zg,  melaDL1Zgint, 
              melaD0minusggH,  melaDCPggH, 
              melaDPhijj,  melaDPhiUnsignedjj,  melaDEtajj,
              Q2V1, Q2V2, costheta1, costheta2, Phi, costhetastar, Phi1);
      
      
      ME_bkg = ME_bkg1 + ME_bkg2;
      
      mela_Dbkg_VBF = ME_sm_VBF / ( ME_sm_VBF + ME_bkg);
      mela_Dbkg_ggH = ME_sm_ggH / ( ME_sm_ggH + ME_bkg);
      mela_Dbkg_WH  = ME_sm_WH / ( ME_sm_WH + ME_bkg);
      mela_Dbkg_ZH  = ME_sm_ZH / ( ME_sm_ZH + ME_bkg);
    }
    // Fill new branches
    for(auto branchToFill : newBranches) branchToFill->Fill();
    } // loop over events
      
      dir->cd();
      tree->Write("", TObject::kOverwrite);
      delete tree; 
      
    }
  }
}

void calculateME(
                 float m_sv,float pt_sv,float eta_sv,float phi_sv,
                 float pt_1,float phi_1,float eta_1,float m_1,float q_1,float pt_2,float phi_2,float eta_2,float m_2,float q_2,int njets,float jpt_1,float jeta_1,float jphi_1,float jpt_2,float jeta_2,float jphi_2,
                 TLorentzVector tau1, TLorentzVector tau2, TLorentzVector jet1, TLorentzVector jet2,
                 int tauCharge1, int tauCharge2,
                 float& ME_sm_VBF, float& ME_sm_ggH, float& ME_sm_WH, float& ME_sm_ZH,
                 float& ME_bkg1, float& ME_bkg2,

                 float& ME_sm, float& ME_bsm, float& ME_bsm_mlt, float& KD_sm, float& KD_bsm, float& melaD0minus, float& ME_int, float& melaDCP, float& ME_bsm_ggH, float& ME_int_ggH, 
                 float& melaD0hplus, float& melaDint, float& melaDL1, float& melaDL1int, float& melaDL1Zg, float& melaDL1Zgint, 
                 float& melaD0minusggH, float& melaDCPggH, 
                 float&  melaDPhijj, float& melaDPhiUnsignedjj, float& melaDEtajj,
                 float& Q2V1, float& Q2V2, float& costheta1, float& costheta2, float& Phi, float& costhetastar, float& Phi1) {
  
  /*
  std::cout << "Input " << std::endl;
  std::cout << "\t tau1: " << tau1.Pt() << "\t" << tau1.Eta() << "\t" << tau1.Phi() << "\t" << tau1.M() << std::endl;
  std::cout << "\t tau2: " << tau2.Pt() << "\t" << tau2.Eta() << "\t" << tau2.Phi() << "\t" << tau2.M() << std::endl;
  std::cout << "\t jet1: " << jet1.Pt() << "\t" << jet1.Eta() << "\t" << jet1.Phi() << "\t" << jet1.M() << std::endl;
  std::cout << "\t jet2: " << jet2.Pt() << "\t" << jet2.Eta() << "\t" << jet2.Phi() << "\t" << jet2.M() << std::endl;
  std::cout << "And charges: " << tauCharge1 << "\t" << tauCharge2 << std::endl;
  std::cout << std::endl;
  */

  // tau lepton 4-vectors
  if (tauCharge1*tauCharge2 > 0) {
    // For QCD estimation purpose, make the tauCharge2 opposite charge of tauCharge1 :/
    tauCharge2 = -tauCharge1;
  }

  SimpleParticleCollection_t daughters;
  daughters.push_back(SimpleParticle_t(15*tauCharge1, tau1)); 
  daughters.push_back(SimpleParticle_t(15*tauCharge2, tau2));

  SimpleParticleCollection_t associated;
  associated.push_back(SimpleParticle_t(0, jet1));
  associated.push_back(SimpleParticle_t(0, jet2));
  
  // SM Higgs hypothesis ===========================================================
  mela.setCandidateDecayMode(TVar::CandidateDecay_ff);
  mela.setInputEvent(&daughters, &associated, (SimpleParticleCollection_t*)0, false);
  mela.setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
  mela.computeProdP(ME_sm_VBF, false);

  mela.computeVBFAngles(Q2V1, Q2V2, costheta1, costheta2, Phi, costhetastar, Phi1);
  
  //get the ggH + 2jets hypothesis
  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJQCD);
  mela.selfDHggcoupl[0][gHIGGS_GG_2][0] = 1;
  mela.computeProdP(ME_sm_ggH, false);
  
  //get the WH + 2 jets hypothesis
  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::Had_WH);
  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0] = 1;
  mela.computeProdP(ME_sm_WH, false);
  
  //get the ZH + 2 jets hypothesis
  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::Had_ZH);
  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0] = 1;
  mela.computeProdP(ME_sm_ZH, false);
  
  // Z+2jets
  mela.setProcess(TVar::bkgZJets, TVar::MCFM, TVar::JJQCD);
  mela.computeProdP(ME_bkg1, false);
  
  associated.clear();
  associated.push_back(SimpleParticle_t(0, jet2));
  associated.push_back(SimpleParticle_t(0, jet1));
  mela.setInputEvent(&daughters, &associated, (SimpleParticleCollection_t*)0, false);
  mela.setProcess(TVar::bkgZJets, TVar::MCFM, TVar::JJQCD);
  mela.computeProdP(ME_bkg2, false);


  // AC analysis 
  TLorentzVector higgs(0, 0, 0, 0),
                 blank1(0, 0, 0, 0);
  jet1.SetPtEtaPhiM(jpt_1, jeta_1, jphi_1, 0);
  jet2.SetPtEtaPhiM(jpt_2, jeta_2, jphi_2, 0);
  higgs.SetPtEtaPhiM(pt_sv, eta_sv, phi_sv, m_sv);
  TVector3 boostH = higgs.BoostVector();

  associated.clear();
  associated.push_back(SimpleParticle_t(0, jet1));
  associated.push_back(SimpleParticle_t(0, jet2));

  TLorentzVector pDaughters1, pDaughters2;
  pDaughters1.SetPtEtaPhiM(pt_1, eta_1, phi_1, m_1);
  pDaughters1.SetPtEtaPhiM(pt_2, eta_2, phi_2, m_2);

  SimpleParticleCollection_t daughters_ZZ;
  daughters_ZZ.push_back(SimpleParticle_t(25, higgs));
  // daughters_ZZ.push_back(SimpleParticle_t(13, pDaughters1));
  // daughters_ZZ.push_back(SimpleParticle_t(15, pDaughters2));
  mela.setInputEvent(&daughters_ZZ, &associated, (SimpleParticleCollection_t*)0, false);
  //get ME scalar
  mela.setProcess(TVar::HSMHiggs, TVar::JHUGen, TVar::JJVBF);
  mela.computeProdP(ME_sm, false);

  //get ME bsm
  mela.setProcess(TVar::H0minus, TVar::JHUGen, TVar::JJVBF);
  mela.computeProdP(ME_bsm, false);
  ME_bsm_mlt = ME_bsm*pow(0.297979, 2);

  //compute D_BSM (eq.5 of HIG-17-011)
  KD_bsm = ME_sm / (ME_sm + ME_bsm);
  melaD0minus = ME_sm / (ME_sm + ME_bsm_mlt);


  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_VV_4][0]=1;
  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0]=1;
  mela.computeProdP(ME_int, false);

  //define D_CP
  melaDCP = (0.297979*(ME_int-(ME_sm + ME_bsm)))/(ME_sm + (pow(0.297979, 2)*ME_bsm));

  // New from Heshy: 22, Nov 2017
  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_VV_2][0]=1;
  mela.computeProdP(ME_bsm, false);
  ME_bsm_mlt = ME_bsm*pow(0.271899, 2);
  melaD0hplus = ME_sm / (ME_sm + ME_bsm_mlt);

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_VV_2][0]=1;
  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0]=1;
  mela.computeProdP(ME_int, false);
  melaDint = (0.271899*(ME_int-(ME_sm + ME_bsm)))/(ME_sm + (pow(0.271899, 2)*ME_bsm));


  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_VV_1_PRIME2][0]=1;
  mela.computeProdP(ME_bsm, false);
  ME_bsm_mlt = ME_bsm*pow(2156.43, 2);
  melaDL1 = ME_sm / (ME_sm + ME_bsm_mlt);

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_VV_1_PRIME2][0]=1;
  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0]=1;
  mela.computeProdP(ME_int, false);
  melaDL1int = (2156.43*(ME_int-(ME_sm + ME_bsm)))/(ME_sm + (pow(2156.43, 2)*ME_bsm));

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_ZA_1_PRIME2][0]=1;
  mela.computeProdP(ME_bsm, false);
  ME_bsm_mlt = ME_bsm*pow(4091.0, 2);
  melaDL1Zg = ME_sm / (ME_sm + ME_bsm_mlt);

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJVBF);
  mela.selfDHzzcoupl[0][gHIGGS_ZA_1_PRIME2][0]=1;
  mela.selfDHzzcoupl[0][gHIGGS_VV_1][0]=1;
  mela.computeProdP(ME_int, false);
  melaDL1Zgint = (4091.0*(ME_int-(ME_sm + ME_bsm)))/(ME_sm + (pow(4091.0, 2)*ME_bsm));

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJQCD);
  mela.selfDHggcoupl[0][gHIGGS_GG_2][0]=1;
  mela.computeProdP(ME_sm_ggH, false);

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJQCD);
  mela.selfDHggcoupl[0][gHIGGS_GG_4][0]=1;
  mela.computeProdP(ME_bsm_ggH, false);

  melaD0minusggH = ME_sm_ggH / (ME_sm_ggH + ME_bsm_ggH);

  mela.setProcess(TVar::SelfDefine_spin0, TVar::JHUGen, TVar::JJQCD);
  mela.selfDHggcoupl[0][gHIGGS_GG_2][0]=1;
  mela.selfDHggcoupl[0][gHIGGS_GG_4][0]=1;
  mela.computeProdP(ME_int_ggH, false);

  melaDCPggH = (ME_int_ggH-(ME_sm_ggH + ME_bsm_ggH))/(ME_sm_ggH + ME_bsm_ggH);



  if (jet1.Pz() <= jet2.Pz()) {
      melaDPhijj = jet1.DeltaPhi(jet2);
  }
  else {
      melaDPhijj = jet2.DeltaPhi(jet1);
  }
  melaDPhiUnsignedjj = jet1.DeltaPhi(jet2);
  melaDEtajj = jet1.Eta()-jet2.Eta();

  //reset the mela object 
  mela.resetInputEvent();
  return;
}

//Thank you Renee Brun :)
void CopyDir(TDirectory *source, optutl::CommandLineParser parser) {
  //copy all objects and subdirs of directory source as a subdir of the current directory
  TDirectory *savdir = gDirectory;
  TDirectory *adir = savdir; 
  if(source->GetName()!=parser.stringValue("inputFile")){
    adir = savdir->mkdir(source->GetName());
    std::cout<<"Source name is not outputfile name"<<std::endl;
    adir->cd();    
  }
  else{
    //adir = savdir->mkdir("input");
    adir->cd();    
  }

  //loop on all entries of this directory
  TKey *key;
  TIter nextkey(source->GetListOfKeys());
  while ((key = (TKey*)nextkey())) {
    const char *classname = key->GetClassName();
    TClass *cl = gROOT->GetClass(classname);
    if (!cl) continue;
    if (cl->InheritsFrom(TDirectory::Class())) {
      source->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      adir->cd();
      CopyDir(subdir,parser);
      adir->cd();
    } else if (cl->InheritsFrom(TTree::Class())) {
      TTree *T = (TTree*)source->Get(key->GetName());
      adir->cd();
      TTree *newT = T->CloneTree(-1,"fast");
      newT->Write();
    } else {
      source->cd();
      TObject *obj = key->ReadObj();
      adir->cd();
      obj->Write();
      delete obj;
    }
  }
  adir->SaveSelf(kTRUE);
  savdir->cd();
}
void CopyFile(const char *fname, optutl::CommandLineParser parser) {
  //Copy all objects and subdirs of file fname as a subdir of the current directory
  TDirectory *target = gDirectory;
  TFile *f = TFile::Open(fname);
  if (!f || f->IsZombie()) {
    printf("Cannot copy file: %s\n",fname);
    target->cd();
    return;
  }
  target->cd();
  CopyDir(f,parser);
  delete f;
  target->cd();
}
void copyFiles( optutl::CommandLineParser parser, TFile* fOld, TFile* fNew) 
{
  //prepare files to be copied
  if(gSystem->AccessPathName(parser.stringValue("inputFile").c_str())) {
    gSystem->CopyFile("hsimple.root", parser.stringValue("inputFile").c_str());
  }

  fNew->cd();
  CopyFile(parser.stringValue("inputFile").c_str(),parser);
  fNew->ls();
  fNew->Close();

}

