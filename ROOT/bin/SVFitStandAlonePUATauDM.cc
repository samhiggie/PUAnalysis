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

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"

#include "HTT-utilities/RecoilCorrections/interface/RecoilCorrector.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

//If recoilType 0 then don't do recoil
//              FIXME amc@nlo is not ready yet!!! 1 then aMC@NLO DY and W+Jets MC samples
//                1 is not longer an option
//              2 MG5 DY and W+Jets MC samples or Higgs MC samples
//
//If doES       0 does not apply any ES shifts
//              1 applies ES shifts to TT channel, no effect on other channels
//
//If isWJets    0 no shift in number of jets used for recoil corrections
//              1 shifts njets + 1 for recoil corrections
//
//If metType    1 use mvamet
//        -1 use pf met

ClassicSVfit svfitAlgorithm;
bool tylerCode = false;

void copyFiles( optutl::CommandLineParser parser, TFile* fOld, TFile* fNew) ;
void readdir(TDirectory *dir, optutl::CommandLineParser parser,  char TreeToUse[], int recoilType, int doES, int isWJets, int metType, double tesSize) ;
void CopyFile(const char *fname, optutl::CommandLineParser parser);
void CopyDir(TDirectory *source,optutl::CommandLineParser parser);

void runSVFit(std::vector<classic_svFit::MeasuredTauLepton> & measuredTauLeptons,
              double measuredMETx, double measuredMETy,
              TMatrixD &covMET, float num, float &svFitMass, float& svFitPt, float &svFitEta,
              float &svFitPhi, float &svFitMET, float &svFitTransverseMass,
              TLorentzVector& tau1, TLorentzVector& tau2);

int main (int argc, char* argv[]) 
{
  optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
  parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__svFit__");
  parser.addOption("newFile",optutl::CommandLineParser::kString,"newFile","newFile.root");
  parser.addOption("inputFile",optutl::CommandLineParser::kString,"input File");
  parser.addOption("newOutputFile",optutl::CommandLineParser::kDouble,"New Output File",0.0);
  parser.addOption("recoilType",optutl::CommandLineParser::kDouble,"recoilType",0.0);
  parser.addOption("doES",optutl::CommandLineParser::kDouble,"doES",0.0);
  parser.addOption("isWJets",optutl::CommandLineParser::kDouble,"isWJets",0.0);
  parser.addOption("metType",optutl::CommandLineParser::kDouble,"metType",-1.0); // 1 = mvamet, -1 = pf met
  parser.addOption("tesSize",optutl::CommandLineParser::kDouble,"tesSize",0.012); // Default TES = 1.2%
  parser.addOption("numEvents",optutl::CommandLineParser::kInteger,"numEvents",-1);
  parser.parseArguments (argc, argv);
  
  std::cout << "EXTRA COMMANDS:"
	    << "\n --- numEvents: " << parser.integerValue("numEvents")
	    << "\n --- recoilType: " << parser.doubleValue("recoilType")
	    << "\n --- doES: " << parser.doubleValue("doES")
	    << "\n --- isWJets: " << parser.doubleValue("isWJets")
	    << "\n --- metType: " << parser.doubleValue("metType")
	    << "\n --- tesSize: " << parser.doubleValue("tesSize") << std::endl;
  
  // Make sure a proper Met Type is chosen
  assert (parser.doubleValue("metType") == 1.0 || parser.doubleValue("metType") == -1.0);
  
  // No DiTauMass constraint
  svfitAlgorithm.setDiTauMassConstraint(-1.0);
  
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
    readdir(fProduce,parser,TreeToUse,parser.doubleValue("recoilType"),parser.doubleValue("doES"),
            parser.doubleValue("isWJets"),parser.doubleValue("metType"),parser.doubleValue("tesSize"));
    
    fProduce->Close();
    f->Close();
  }
  else{
    TFile *f = new TFile(parser.stringValue("inputFile").c_str(),"UPDATE");
    readdir(f,parser,TreeToUse,parser.doubleValue("recoilType"),parser.doubleValue("doES"),
            parser.doubleValue("isWJets"),parser.doubleValue("metType"),parser.doubleValue("tesSize"));
    f->Close();
  }
  
  
} 


void readdir(TDirectory *dir, optutl::CommandLineParser parser, char TreeToUse[], int recoilType, int doES, int isWJets, int metType, double tesSize) 
{
  
  TLorentzVector tau1, tau2;
  // up systematics
  TLorentzVector tau1_up, tau1_DM0_up, tau1_DM1_up, tau1_DM10_up, tau1_UncMet_up, tau1_ClusteredMet_up;
  TLorentzVector tau2_up, tau2_DM0_up, tau2_DM1_up, tau2_DM10_up, tau2_UncMet_up, tau2_ClusteredMet_up;
  // down systematics
  TLorentzVector tau1_down, tau1_DM0_down, tau1_DM1_down, tau1_DM10_down, tau1_UncMet_down, tau1_ClusteredMet_down;
  TLorentzVector tau2_down, tau2_DM0_down, tau2_DM1_down, tau2_DM10_down, tau2_UncMet_down, tau2_ClusteredMet_down;
  
  std::string recoilFileName = "$CMSSW_BASE/src/HTT-utilities/RecoilCorrections/data/TypeI-PFMet_Run2016BtoH.root";
  if(recoilType == 1) { //amc@nlo
    std::cout << "Alexei no long specified MG vs. AMC@NLO, so use recoilType = 2" << std::endl;
    return; }
  if(recoilType == 2 && metType == 1) { // mva met (Alexei no long specified MG vs. AMC@NLO)
    std::cout << "Alexei does not provide full 2016 data recoil corrections for Mva Met\n\n" << std::endl;
    std::cout << "Using ICHEP Mva Met corrections\n\n" << std::endl;
    recoilFileName = "$CMSSW_BASE/src/HTT-utilities/RecoilCorrections/data/MvaMET_2016BCD.root";}
  if(recoilType == 2 && metType == -1) { // pf met (Alexei no long specified MG vs. AMC@NLO)
    recoilFileName = "$CMSSW_BASE/src/HTT-utilities/RecoilCorrections/data/TypeI-PFMet_Run2016BtoH.root";}
  
  classic_svFit::MeasuredTauLepton::kDecayType decayType1 = classic_svFit::MeasuredTauLepton::kUndefinedDecayType;
  classic_svFit::MeasuredTauLepton::kDecayType decayType2 = classic_svFit::MeasuredTauLepton::kUndefinedDecayType; 
  
  // Both masses should depend on decay mode and particle?
  float mass1;
  float mass2;
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
      readdir(subdir,parser,TreeToUse,parser.doubleValue("recoilType"),parser.doubleValue("doES"),
	      parser.doubleValue("isWJets"),parser.doubleValue("metType"),parser.doubleValue("tesSize"));
      
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
	decayType1 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
	decayType2 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
	mass1 = 0.13957;
	mass2 = 0.13957;
	channel = "tt";
	std::cout << "Identified channel tt and using kappa = 5" << std::endl;
	svfitAlgorithm.addLogM_fixed(true, 5);
      } 
      else if ( std::string(key->GetName()).find("em") != std::string::npos )  {
	std::cout<< "EMu sample" <<std::endl;
	decayType1 = classic_svFit::MeasuredTauLepton::kTauToElecDecay;
	decayType2 = classic_svFit::MeasuredTauLepton::kTauToMuDecay;
	mass1 = 0.00051100;
	mass2 = 0.105658;
	channel = "em";
	std::cout << "Identified channel em and using kappa = 3" << std::endl;
	svfitAlgorithm.addLogM_fixed(true, 3);
      }
      else if ( std::string(key->GetName()).find("eleTauEvent") != std::string::npos ) {
	std::cout<<"eleTauTree"<<std::endl;
	decayType1 = classic_svFit::MeasuredTauLepton::kTauToElecDecay;
	decayType2 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
	mass1 = 0.00051100;
	mass2 = 0;
	channel = "et";
	std::cout << "Identified channel et and using kappa = 4" << std::endl;
	svfitAlgorithm.addLogM_fixed(true, 4);
      } 
      //else if ( std::string(key->GetName()).find("muTauEvent") != std::string::npos ) {
      else if ( std::string(key->GetName()).find("eventTree") != std::string::npos ) {
	//std::cout << "muTauEvent" << std::endl;
	decayType1 = classic_svFit::MeasuredTauLepton::kTauToMuDecay;
	decayType2 = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
	mass1 = 0.105658;
	mass2 = 0;
	channel = "mt";
	std::cout << "Identified channel mt and using kappa = 4" << std::endl;
	svfitAlgorithm.addLogM_fixed(true, 4);
      } else {
	std::cout<<"Tree "<< key->GetName() <<" does not match ... Skipping!!"<<std::endl;
	return;
      }
      
      TTree *t = (TTree*)obj;
      float svFitMass = -10;
      float svFitPt = -10;
      float svFitEta = -10;
      float svFitPhi = -10;
      float svFitMET = -10;
      float svFitTransverseMass = -10;

      float metcorr_ex = -10; // corrected met px (float)
      float metcorr_ey = -10;  // corrected met py (float)
      float metcorrUncUp_ex = -10; // corrUncUpected met px (float)
      float metcorrUncUp_ey = -10;  // corrUncUpected met py (float)
      float metcorrUncDown_ex = -10; // corrUncDownected met px (float)
      float metcorrUncDown_ey = -10;  // corrUncDownected met py (float)
      float metcorrClusteredUp_ex = -10; // corrClusteredUpected met px (float)
      float metcorrClusteredUp_ey = -10;  // corrClusteredUpected met py (float)
      float metcorrClusteredDown_ex = -10; // corrClusteredDownected met px (float)
      float metcorrClusteredDown_ey = -10;  // corrClusteredDownected met py (float)

      // For saving
      float metcor = -10; // corrected metcor
      float metcorphi = -10; // corrected metcorphi
      float metcorClusteredDown = -10;   
      float metcorphiClusteredDown = -10;
      float metcorClusteredUp = -10;     
      float metcorphiClusteredUp = -10;  
      float metcorUncDown = -10;         
      float metcorphiUncDown = -10;      
      float metcorUncUp = -10;           
      float metcorphiUncUp = -10;        

      //TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&svFitMass,(parser.stringValue("branch")+"/F").c_str());
      TBranch *newBranch1 = t->Branch("m_sv", &svFitMass, "m_sv/F");
      TBranch *newBranch2 = t->Branch("pt_sv", &svFitPt, "pt_sv/F");
      TBranch *newBranch3 = t->Branch("eta_sv", &svFitEta, "eta_sv/F");
      TBranch *newBranch4 = t->Branch("phi_sv", &svFitPhi, "phi_sv/F");
      TBranch *newBranch5 = t->Branch("met_sv", &svFitMET, "met_sv/F");
      TBranch *newBranch6 = t->Branch("mt_sv", &svFitTransverseMass, "mt_sv/F");

      TBranch *newBranch7 = t->Branch("metcorr_ex", &metcorr_ex, "metcorr_ex/F");
      TBranch *newBranch8 = t->Branch("metcorr_ey", &metcorr_ey, "metcorr_ey/F");
      TBranch *newBranch9 = t->Branch("metcor", &metcor, "metcor/F");
      TBranch *newBranch10 = t->Branch("metcorphi", &metcorphi, "metcorphi/F");

      // If doing ES shifts, we need extra ouput branches
      //
      float svFitMass_UP = -10;
      float svFitPt_UP = -10;
      float svFitEta_UP = -10;
      float svFitPhi_UP = -10;
      float svFitMET_UP = -10;
      float svFitTransverseMass_UP = -10;
      float svFitMass_DOWN = -10;
      float svFitPt_DOWN = -10;
      float svFitEta_DOWN = -10;
      float svFitPhi_DOWN = -10;
      float svFitMET_DOWN = -10;
      float svFitTransverseMass_DOWN = -10;

      float svFitMass_DM0_UP = -10;
      float svFitPt_DM0_UP = -10;
      float svFitEta_DM0_UP = -10;
      float svFitPhi_DM0_UP = -10;
      float svFitMET_DM0_UP = -10;
      float svFitTransverseMass_DM0_UP = -10;
      float svFitMass_DM0_DOWN = -10;
      float svFitPt_DM0_DOWN = -10;
      float svFitEta_DM0_DOWN = -10;
      float svFitPhi_DM0_DOWN = -10;
      float svFitMET_DM0_DOWN = -10;
      float svFitTransverseMass_DM0_DOWN = -10;

      float svFitMass_DM1_UP = -10;
      float svFitPt_DM1_UP = -10;
      float svFitEta_DM1_UP = -10;
      float svFitPhi_DM1_UP = -10;
      float svFitMET_DM1_UP = -10;
      float svFitTransverseMass_DM1_UP = -10;
      float svFitMass_DM1_DOWN = -10;
      float svFitPt_DM1_DOWN = -10;
      float svFitEta_DM1_DOWN = -10;
      float svFitPhi_DM1_DOWN = -10;
      float svFitMET_DM1_DOWN = -10;
      float svFitTransverseMass_DM1_DOWN = -10;

      float svFitMass_DM10_UP = -10;
      float svFitPt_DM10_UP = -10;
      float svFitEta_DM10_UP = -10;
      float svFitPhi_DM10_UP = -10;
      float svFitMET_DM10_UP = -10;
      float svFitTransverseMass_DM10_UP = -10;
      float svFitMass_DM10_DOWN = -10;
      float svFitPt_DM10_DOWN = -10;
      float svFitEta_DM10_DOWN = -10;
      float svFitPhi_DM10_DOWN = -10;
      float svFitMET_DM10_DOWN = -10;
      float svFitTransverseMass_DM10_DOWN = -10;

      float svFitMass_UncMet_UP = -10;
      float svFitPt_UncMet_UP = -10;
      float svFitEta_UncMet_UP = -10;
      float svFitPhi_UncMet_UP = -10;
      float svFitMET_UncMet_UP = -10;
      float svFitTransverseMass_UncMet_UP = -10;
      float svFitMass_UncMet_DOWN = -10;
      float svFitPt_UncMet_DOWN = -10;
      float svFitEta_UncMet_DOWN = -10;
      float svFitPhi_UncMet_DOWN = -10;
      float svFitMET_UncMet_DOWN = -10;
      float svFitTransverseMass_UncMet_DOWN = -10;

      float svFitMass_ClusteredMet_UP = -10;
      float svFitPt_ClusteredMet_UP = -10;
      float svFitEta_ClusteredMet_UP = -10;
      float svFitPhi_ClusteredMet_UP = -10;
      float svFitMET_ClusteredMet_UP = -10;
      float svFitTransverseMass_ClusteredMet_UP = -10;
      float svFitMass_ClusteredMet_DOWN = -10;
      float svFitPt_ClusteredMet_DOWN = -10;
      float svFitEta_ClusteredMet_DOWN = -10;
      float svFitPhi_ClusteredMet_DOWN = -10;
      float svFitMET_ClusteredMet_DOWN = -10;
      float svFitTransverseMass_ClusteredMet_DOWN = -10;
      
      // tau leptons                                                                                                  
      // nominal ========================
      float tau1_pt  = -10;
      float tau1_eta = -10;
      float tau1_phi = -10;
      float tau1_m   = -10;
      float tau2_pt  = -10;
      float tau2_eta = -10;
      float tau2_phi = -10;
      float tau2_m   = -10;
      // up (whatever it is) ============
      float tau1_pt_UP  = -10;
      float tau1_eta_UP = -10;
      float tau1_phi_UP = -10;
      float tau1_m_UP   = -10;
      float tau2_pt_UP  = -10;
      float tau2_eta_UP = -10;
      float tau2_phi_UP = -10;
      float tau2_m_UP   = -10;
      // down 
      float tau1_pt_DOWN  = -10;
      float tau1_eta_DOWN = -10;
      float tau1_phi_DOWN = -10;
      float tau1_m_DOWN   = -10;
      float tau2_pt_DOWN  = -10;
      float tau2_eta_DOWN = -10;
      float tau2_phi_DOWN = -10;
      float tau2_m_DOWN   = -10;
      // up DM0 =========================
      float tau1_pt_DM0_UP  = -10;
      float tau1_eta_DM0_UP = -10;
      float tau1_phi_DM0_UP = -10;
      float tau1_m_DM0_UP   = -10;
      float tau2_pt_DM0_UP  = -10;
      float tau2_eta_DM0_UP = -10;
      float tau2_phi_DM0_UP = -10;
      float tau2_m_DM0_UP   = -10;
      // down 
      float tau1_pt_DM0_DOWN  = -10;
      float tau1_eta_DM0_DOWN = -10;
      float tau1_phi_DM0_DOWN = -10;
      float tau1_m_DM0_DOWN   = -10;
      float tau2_pt_DM0_DOWN  = -10;
      float tau2_eta_DM0_DOWN = -10;
      float tau2_phi_DM0_DOWN = -10;
      float tau2_m_DM0_DOWN   = -10;
      // up DM1 =========================
      float tau1_pt_DM1_UP  = -10;
      float tau1_eta_DM1_UP = -10;
      float tau1_phi_DM1_UP = -10;
      float tau1_m_DM1_UP   = -10;
      float tau2_pt_DM1_UP  = -10;
      float tau2_eta_DM1_UP = -10;
      float tau2_phi_DM1_UP = -10;
      float tau2_m_DM1_UP   = -10;
      // down 
      float tau1_pt_DM1_DOWN  = -10;
      float tau1_eta_DM1_DOWN = -10;
      float tau1_phi_DM1_DOWN = -10;
      float tau1_m_DM1_DOWN   = -10;
      float tau2_pt_DM1_DOWN  = -10;
      float tau2_eta_DM1_DOWN = -10;
      float tau2_phi_DM1_DOWN = -10;
      float tau2_m_DM1_DOWN   = -10;
      // up DM10 =========================
      float tau1_pt_DM10_UP  = -10;
      float tau1_eta_DM10_UP = -10;
      float tau1_phi_DM10_UP = -10;
      float tau1_m_DM10_UP   = -10;
      float tau2_pt_DM10_UP  = -10;
      float tau2_eta_DM10_UP = -10;
      float tau2_phi_DM10_UP = -10;
      float tau2_m_DM10_UP   = -10;
      // down 
      float tau1_pt_DM10_DOWN  = -10;
      float tau1_eta_DM10_DOWN = -10;
      float tau1_phi_DM10_DOWN = -10;
      float tau1_m_DM10_DOWN   = -10;
      float tau2_pt_DM10_DOWN  = -10;
      float tau2_eta_DM10_DOWN = -10;
      float tau2_phi_DM10_DOWN = -10;
      float tau2_m_DM10_DOWN   = -10;
      // up UncMet ========================= 
      float tau1_pt_UncMet_UP  = -10;
      float tau1_eta_UncMet_UP = -10;
      float tau1_phi_UncMet_UP = -10;
      float tau1_m_UncMet_UP   = -10;
      float tau2_pt_UncMet_UP  = -10;
      float tau2_eta_UncMet_UP = -10;
      float tau2_phi_UncMet_UP = -10;
      float tau2_m_UncMet_UP   = -10;
      // down 
      float tau1_pt_UncMet_DOWN  = -10;
      float tau1_eta_UncMet_DOWN = -10;
      float tau1_phi_UncMet_DOWN = -10;
      float tau1_m_UncMet_DOWN   = -10;
      float tau2_pt_UncMet_DOWN  = -10;
      float tau2_eta_UncMet_DOWN = -10;
      float tau2_phi_UncMet_DOWN = -10;
      float tau2_m_UncMet_DOWN   = -10;
      // up ClusteredMet ========================= 
      float tau1_pt_ClusteredMet_UP  = -10;
      float tau1_eta_ClusteredMet_UP = -10;
      float tau1_phi_ClusteredMet_UP = -10;
      float tau1_m_ClusteredMet_UP   = -10;
      float tau2_pt_ClusteredMet_UP  = -10;
      float tau2_eta_ClusteredMet_UP = -10;
      float tau2_phi_ClusteredMet_UP = -10;
      float tau2_m_ClusteredMet_UP   = -10;
      // down 
      float tau1_pt_ClusteredMet_DOWN  = -10;
      float tau1_eta_ClusteredMet_DOWN = -10;
      float tau1_phi_ClusteredMet_DOWN = -10;
      float tau1_m_ClusteredMet_DOWN   = -10;
      float tau2_pt_ClusteredMet_DOWN  = -10;
      float tau2_eta_ClusteredMet_DOWN = -10;
      float tau2_phi_ClusteredMet_DOWN = -10;
      float tau2_m_ClusteredMet_DOWN   = -10;
                                                                                  
      TBranch *newBranch11 = t->Branch("m_sv_UP", &svFitMass_UP, "m_sv_UP/F");
      TBranch *newBranch12 = t->Branch("pt_sv_UP", &svFitPt_UP, "pt_sv_UP/F");
      TBranch *newBranch13 = t->Branch("eta_sv_UP", &svFitEta_UP, "eta_sv_UP/F");
      TBranch *newBranch14 = t->Branch("phi_sv_UP", &svFitPhi_UP, "phi_sv_UP/F");
      TBranch *newBranch15 = t->Branch("met_sv_UP", &svFitMET_UP, "met_sv_UP/F");
      TBranch *newBranch16 = t->Branch("mt_sv_UP", &svFitTransverseMass_UP, "mt_sv_UP/F");

      TBranch *newBranch17 = t->Branch("m_sv_DOWN", &svFitMass_DOWN, "m_sv_DOWN/F");
      TBranch *newBranch18 = t->Branch("pt_sv_DOWN", &svFitPt_DOWN, "pt_sv_DOWN/F");
      TBranch *newBranch19 = t->Branch("eta_sv_DOWN", &svFitEta_DOWN, "eta_sv_DOWN/F");
      TBranch *newBranch20 = t->Branch("phi_sv_DOWN", &svFitPhi_DOWN, "phi_sv_DOWN/F");
      TBranch *newBranch21 = t->Branch("met_sv_DOWN", &svFitMET_DOWN, "met_sv_DOWN/F");
      TBranch *newBranch22 = t->Branch("mt_sv_DOWN", &svFitTransverseMass_DOWN, "mt_sv_DOWN/F");

      TBranch *newBranch23 = t->Branch("m_sv_DM0_UP", &svFitMass_DM0_UP, "m_sv_DM0_UP/F");
      TBranch *newBranch24 = t->Branch("pt_sv_DM0_UP", &svFitPt_DM0_UP, "pt_sv_DM0_UP/F");
      TBranch *newBranch25 = t->Branch("eta_sv_DM0_UP", &svFitEta_DM0_UP, "eta_sv_DM0_UP/F");
      TBranch *newBranch26 = t->Branch("phi_sv_DM0_UP", &svFitPhi_DM0_UP, "phi_sv_DM0_UP/F");
      TBranch *newBranch27 = t->Branch("met_sv_DM0_UP", &svFitMET_DM0_UP, "met_sv_DM0_UP/F");
      TBranch *newBranch28 = t->Branch("mt_sv_DM0_UP", &svFitTransverseMass_DM0_UP, "mt_sv_DM0_UP/F");

      TBranch *newBranch29 = t->Branch("m_sv_DM0_DOWN", &svFitMass_DM0_DOWN, "m_sv_DM0_DOWN/F");
      TBranch *newBranch30 = t->Branch("pt_sv_DM0_DOWN", &svFitPt_DM0_DOWN, "pt_sv_DM0_DOWN/F");
      TBranch *newBranch31 = t->Branch("eta_sv_DM0_DOWN", &svFitEta_DM0_DOWN, "eta_sv_DM0_DOWN/F");
      TBranch *newBranch32 = t->Branch("phi_sv_DM0_DOWN", &svFitPhi_DM0_DOWN, "phi_sv_DM0_DOWN/F");
      TBranch *newBranch33 = t->Branch("met_sv_DM0_DOWN", &svFitMET_DM0_DOWN, "met_sv_DM0_DOWN/F");
      TBranch *newBranch34 = t->Branch("mt_sv_DM0_DOWN", &svFitTransverseMass_DM0_DOWN, "mt_sv_DM0_DOWN/F");

      TBranch *newBranch35 = t->Branch("m_sv_DM1_UP", &svFitMass_DM1_UP, "m_sv_DM1_UP/F");
      TBranch *newBranch36 = t->Branch("pt_sv_DM1_UP", &svFitPt_DM1_UP, "pt_sv_DM1_UP/F");
      TBranch *newBranch37 = t->Branch("eta_sv_DM1_UP", &svFitEta_DM1_UP, "eta_sv_DM1_UP/F");
      TBranch *newBranch38 = t->Branch("phi_sv_DM1_UP", &svFitPhi_DM1_UP, "phi_sv_DM1_UP/F");
      TBranch *newBranch39 = t->Branch("met_sv_DM1_UP", &svFitMET_DM1_UP, "met_sv_DM1_UP/F");
      TBranch *newBranch40 = t->Branch("mt_sv_DM1_UP", &svFitTransverseMass_DM1_UP, "mt_sv_DM1_UP/F");

      TBranch *newBranch41 = t->Branch("m_sv_DM1_DOWN", &svFitMass_DM1_DOWN, "m_sv_DM1_DOWN/F");
      TBranch *newBranch42 = t->Branch("pt_sv_DM1_DOWN", &svFitPt_DM1_DOWN, "pt_sv_DM1_DOWN/F");
      TBranch *newBranch43 = t->Branch("eta_sv_DM1_DOWN", &svFitEta_DM1_DOWN, "eta_sv_DM1_DOWN/F");
      TBranch *newBranch44 = t->Branch("phi_sv_DM1_DOWN", &svFitPhi_DM1_DOWN, "phi_sv_DM1_DOWN/F");
      TBranch *newBranch45 = t->Branch("met_sv_DM1_DOWN", &svFitMET_DM1_DOWN, "met_sv_DM1_DOWN/F");
      TBranch *newBranch46 = t->Branch("mt_sv_DM1_DOWN", &svFitTransverseMass_DM1_DOWN, "mt_sv_DM1_DOWN/F");

      TBranch *newBranch47 = t->Branch("m_sv_DM10_UP", &svFitMass_DM10_UP, "m_sv_DM10_UP/F");
      TBranch *newBranch48 = t->Branch("pt_sv_DM10_UP", &svFitPt_DM10_UP, "pt_sv_DM10_UP/F");
      TBranch *newBranch49 = t->Branch("eta_sv_DM10_UP", &svFitEta_DM10_UP, "eta_sv_DM10_UP/F");
      TBranch *newBranch50 = t->Branch("phi_sv_DM10_UP", &svFitPhi_DM10_UP, "phi_sv_DM10_UP/F");
      TBranch *newBranch51 = t->Branch("met_sv_DM10_UP", &svFitMET_DM10_UP, "met_sv_DM10_UP/F");
      TBranch *newBranch52 = t->Branch("mt_sv_DM10_UP", &svFitTransverseMass_DM10_UP, "mt_sv_DM10_UP/F");

      TBranch *newBranch53 = t->Branch("m_sv_DM10_DOWN", &svFitMass_DM10_DOWN, "m_sv_DM10_DOWN/F");
      TBranch *newBranch54 = t->Branch("pt_sv_DM10_DOWN", &svFitPt_DM10_DOWN, "pt_sv_DM10_DOWN/F");
      TBranch *newBranch55 = t->Branch("eta_sv_DM10_DOWN", &svFitEta_DM10_DOWN, "eta_sv_DM10_DOWN/F");
      TBranch *newBranch56 = t->Branch("phi_sv_DM10_DOWN", &svFitPhi_DM10_DOWN, "phi_sv_DM10_DOWN/F");
      TBranch *newBranch57 = t->Branch("met_sv_DM10_DOWN", &svFitMET_DM10_DOWN, "met_sv_DM10_DOWN/F");
      TBranch *newBranch58 = t->Branch("mt_sv_DM10_DOWN", &svFitTransverseMass_DM10_DOWN, "mt_sv_DM10_DOWN/F");

      TBranch *newBranch59 = t->Branch("m_sv_UncMet_UP", &svFitMass_UncMet_UP, "m_sv_UncMet_UP/F");
      TBranch *newBranch60 = t->Branch("pt_sv_UncMet_UP", &svFitPt_UncMet_UP, "pt_sv_UncMet_UP/F");
      TBranch *newBranch61 = t->Branch("eta_sv_UncMet_UP", &svFitEta_UncMet_UP, "eta_sv_UncMet_UP/F");
      TBranch *newBranch62 = t->Branch("phi_sv_UncMet_UP", &svFitPhi_UncMet_UP, "phi_sv_UncMet_UP/F");
      TBranch *newBranch63 = t->Branch("met_sv_UncMet_UP", &svFitMET_UncMet_UP, "met_sv_UncMet_UP/F");
      TBranch *newBranch64 = t->Branch("mt_sv_UncMet_UP", &svFitTransverseMass_UncMet_UP, "mt_sv_UncMet_UP/F");

      TBranch *newBranch65 = t->Branch("m_sv_UncMet_DOWN", &svFitMass_UncMet_DOWN, "m_sv_UncMet_DOWN/F");
      TBranch *newBranch66 = t->Branch("pt_sv_UncMet_DOWN", &svFitPt_UncMet_DOWN, "pt_sv_UncMet_DOWN/F");
      TBranch *newBranch67 = t->Branch("eta_sv_UncMet_DOWN", &svFitEta_UncMet_DOWN, "eta_sv_UncMet_DOWN/F");
      TBranch *newBranch68 = t->Branch("phi_sv_UncMet_DOWN", &svFitPhi_UncMet_DOWN, "phi_sv_UncMet_DOWN/F");
      TBranch *newBranch69 = t->Branch("met_sv_UncMet_DOWN", &svFitMET_UncMet_DOWN, "met_sv_UncMet_DOWN/F");
      TBranch *newBranch70 = t->Branch("mt_sv_UncMet_DOWN", &svFitTransverseMass_UncMet_DOWN, "mt_sv_UncMet_DOWN/F");

      TBranch *newBranch71 = t->Branch("m_sv_ClusteredMet_UP", &svFitMass_ClusteredMet_UP, "m_sv_ClusteredMet_UP/F");
      TBranch *newBranch72 = t->Branch("pt_sv_ClusteredMet_UP", &svFitPt_ClusteredMet_UP, "pt_sv_ClusteredMet_UP/F");
      TBranch *newBranch73 = t->Branch("eta_sv_ClusteredMet_UP", &svFitEta_ClusteredMet_UP, "eta_sv_ClusteredMet_UP/F");
      TBranch *newBranch74 = t->Branch("phi_sv_ClusteredMet_UP", &svFitPhi_ClusteredMet_UP, "phi_sv_ClusteredMet_UP/F");
      TBranch *newBranch75 = t->Branch("met_sv_ClusteredMet_UP", &svFitMET_ClusteredMet_UP, "met_sv_ClusteredMet_UP/F");
      TBranch *newBranch76 = t->Branch("mt_sv_ClusteredMet_UP", &svFitTransverseMass_ClusteredMet_UP, "mt_sv_ClusteredMet_UP/F");

      TBranch *newBranch77 = t->Branch("m_sv_ClusteredMet_DOWN", &svFitMass_ClusteredMet_DOWN, "m_sv_ClusteredMet_DOWN/F");
      TBranch *newBranch78 = t->Branch("pt_sv_ClusteredMet_DOWN", &svFitPt_ClusteredMet_DOWN, "pt_sv_ClusteredMet_DOWN/F");
      TBranch *newBranch79 = t->Branch("eta_sv_ClusteredMet_DOWN", &svFitEta_ClusteredMet_DOWN, "eta_sv_ClusteredMet_DOWN/F");
      TBranch *newBranch80 = t->Branch("phi_sv_ClusteredMet_DOWN", &svFitPhi_ClusteredMet_DOWN, "phi_sv_ClusteredMet_DOWN/F");
      TBranch *newBranch81 = t->Branch("met_sv_ClusteredMet_DOWN", &svFitMET_ClusteredMet_DOWN, "met_sv_ClusteredMet_DOWN/F");
      TBranch *newBranch82 = t->Branch("mt_sv_ClusteredMet_DOWN", &svFitTransverseMass_ClusteredMet_DOWN, "mt_sv_ClusteredMet_DOWN/F");
    
      TBranch *newBranch83 = t->Branch("metcorClusteredDown",    &metcorClusteredDown,   "metcorClusteredDown/F");
      TBranch *newBranch84 = t->Branch("metcorphiClusteredDown", &metcorphiClusteredDown,"metcorphiClusteredDown/F");
      TBranch *newBranch85 = t->Branch("metcorClusteredUp",      &metcorClusteredUp,     "metcorClusteredUp/F");
      TBranch *newBranch86 = t->Branch("metcorphiClusteredUp",   &metcorphiClusteredUp,  "metcorphiClusteredUp/F");
      TBranch *newBranch87 = t->Branch("metcorUncDown",          &metcorUncDown,         "metcorUncDown/F");
      TBranch *newBranch89 = t->Branch("metcorphiUncDown",       &metcorphiUncDown,      "metcorphiUncDown/F");
      TBranch *newBranch90 = t->Branch("metcorUncUp",            &metcorUncUp,           "metcorUncUp/F");
      TBranch *newBranch91 = t->Branch("metcorphiUncUp",         &metcorphiUncUp,        "metcorphiUncUp/F");
    
      // adding tau-related branches
      std::vector<TBranch*> tau4VectorBranches;
      tau4VectorBranches.push_back(t->Branch("tau1_pt",  &tau1_pt,  "tau1_pt/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta", &tau1_eta, "tau1_eta/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi", &tau1_phi, "tau1_phi/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m",   &tau1_m,   "tau1_m/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt",  &tau2_pt,  "tau2_pt/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta", &tau2_eta, "tau2_eta/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi", &tau2_phi, "tau2_phi/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m",   &tau2_m,   "tau2_m/F"));
      // up
      tau4VectorBranches.push_back(t->Branch("tau1_pt_UP",  &tau1_pt_UP,  "tau1_pt_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_UP", &tau1_eta_UP, "tau1_eta_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_UP", &tau1_phi_UP, "tau1_phi_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_UP",   &tau1_m_UP,   "tau1_m_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_UP",  &tau2_pt_UP,  "tau2_pt_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_UP", &tau2_eta_UP, "tau2_eta_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_UP", &tau2_phi_UP, "tau2_phi_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_UP",   &tau2_m_UP,   "tau2_m_UP/F"));
      // down
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DOWN",  &tau1_pt_DOWN,  "tau1_pt_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DOWN", &tau1_eta_DOWN, "tau1_eta_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DOWN", &tau1_phi_DOWN, "tau1_phi_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DOWN",   &tau1_m_DOWN,   "tau1_m_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DOWN",  &tau2_pt_DOWN,  "tau2_pt_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DOWN", &tau2_eta_DOWN, "tau2_eta_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DOWN", &tau2_phi_DOWN, "tau2_phi_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DOWN",   &tau2_m_DOWN,   "tau2_m_DOWN/F"));
      // up DM0
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DM0_UP",  &tau1_pt_DM0_UP,  "tau1_pt_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DM0_UP", &tau1_eta_DM0_UP, "tau1_eta_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DM0_UP", &tau1_phi_DM0_UP, "tau1_phi_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DM0_UP",   &tau1_m_DM0_UP,   "tau1_m_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DM0_UP",  &tau2_pt_DM0_UP,  "tau2_pt_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DM0_UP", &tau2_eta_DM0_UP, "tau2_eta_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DM0_UP", &tau2_phi_DM0_UP, "tau2_phi_DM0_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DM0_UP",   &tau2_m_DM0_UP,   "tau2_m_DM0_UP/F"));
      // down
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DM0_DOWN",  &tau1_pt_DM0_DOWN,  "tau1_pt_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DM0_DOWN", &tau1_eta_DM0_DOWN, "tau1_eta_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DM0_DOWN", &tau1_phi_DM0_DOWN, "tau1_phi_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DM0_DOWN",   &tau1_m_DM0_DOWN,   "tau1_m_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DM0_DOWN",  &tau2_pt_DM0_DOWN,  "tau2_pt_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DM0_DOWN", &tau2_eta_DM0_DOWN, "tau2_eta_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DM0_DOWN", &tau2_phi_DM0_DOWN, "tau2_phi_DM0_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DM0_DOWN",   &tau2_m_DM0_DOWN,   "tau2_m_DM0_DOWN/F"));
      // up DM1
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DM1_UP",  &tau1_pt_DM1_UP,  "tau1_pt_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DM1_UP", &tau1_eta_DM1_UP, "tau1_eta_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DM1_UP", &tau1_phi_DM1_UP, "tau1_phi_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DM1_UP",   &tau1_m_DM1_UP,   "tau1_m_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DM1_UP",  &tau2_pt_DM1_UP,  "tau2_pt_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DM1_UP", &tau2_eta_DM1_UP, "tau2_eta_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DM1_UP", &tau2_phi_DM1_UP, "tau2_phi_DM1_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DM1_UP",   &tau2_m_DM1_UP,   "tau2_m_DM1_UP/F"));
      // down
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DM1_DOWN",  &tau1_pt_DM1_DOWN,  "tau1_pt_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DM1_DOWN", &tau1_eta_DM1_DOWN, "tau1_eta_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DM1_DOWN", &tau1_phi_DM1_DOWN, "tau1_phi_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DM1_DOWN",   &tau1_m_DM1_DOWN,   "tau1_m_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DM1_DOWN",  &tau2_pt_DM1_DOWN,  "tau2_pt_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DM1_DOWN", &tau2_eta_DM1_DOWN, "tau2_eta_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DM1_DOWN", &tau2_phi_DM1_DOWN, "tau2_phi_DM1_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DM1_DOWN",   &tau2_m_DM1_DOWN,   "tau2_m_DM1_DOWN/F"));
      // up DM10
    
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DM10_UP",  &tau1_pt_DM10_UP,  "tau1_pt_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DM10_UP", &tau1_eta_DM10_UP, "tau1_eta_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DM10_UP", &tau1_phi_DM10_UP, "tau1_phi_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DM10_UP",   &tau1_m_DM10_UP,   "tau1_m_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DM10_UP",  &tau2_pt_DM10_UP,  "tau2_pt_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DM10_UP", &tau2_eta_DM10_UP, "tau2_eta_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DM10_UP", &tau2_phi_DM10_UP, "tau2_phi_DM10_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DM10_UP",   &tau2_m_DM10_UP,   "tau2_m_DM10_UP/F"));
      // down
      tau4VectorBranches.push_back(t->Branch("tau1_pt_DM10_DOWN",  &tau1_pt_DM10_DOWN,  "tau1_pt_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_DM10_DOWN", &tau1_eta_DM10_DOWN, "tau1_eta_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_DM10_DOWN", &tau1_phi_DM10_DOWN, "tau1_phi_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_DM10_DOWN",   &tau1_m_DM10_DOWN,   "tau1_m_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_DM10_DOWN",  &tau2_pt_DM10_DOWN,  "tau2_pt_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_DM10_DOWN", &tau2_eta_DM10_DOWN, "tau2_eta_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_DM10_DOWN", &tau2_phi_DM10_DOWN, "tau2_phi_DM10_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_DM10_DOWN",   &tau2_m_DM10_DOWN,   "tau2_m_DM10_DOWN/F"));
      // up UncMet
      tau4VectorBranches.push_back(t->Branch("tau1_pt_UncMet_UP",  &tau1_pt_UncMet_UP,  "tau1_pt_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_UncMet_UP", &tau1_eta_UncMet_UP, "tau1_eta_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_UncMet_UP", &tau1_phi_UncMet_UP, "tau1_phi_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_UncMet_UP",   &tau1_m_UncMet_UP,   "tau1_m_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_UncMet_UP",  &tau2_pt_UncMet_UP,  "tau2_pt_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_UncMet_UP", &tau2_eta_UncMet_UP, "tau2_eta_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_UncMet_UP", &tau2_phi_UncMet_UP, "tau2_phi_UncMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_UncMet_UP",   &tau2_m_UncMet_UP,   "tau2_m_UncMet_UP/F"));
      // down
      tau4VectorBranches.push_back(t->Branch("tau1_pt_UncMet_DOWN",  &tau1_pt_UncMet_DOWN,  "tau1_pt_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_UncMet_DOWN", &tau1_eta_UncMet_DOWN, "tau1_eta_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_UncMet_DOWN", &tau1_phi_UncMet_DOWN, "tau1_phi_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_UncMet_DOWN",   &tau1_m_UncMet_DOWN,   "tau1_m_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_UncMet_DOWN",  &tau2_pt_UncMet_DOWN,  "tau2_pt_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_UncMet_DOWN", &tau2_eta_UncMet_DOWN, "tau2_eta_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_UncMet_DOWN", &tau2_phi_UncMet_DOWN, "tau2_phi_UncMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_UncMet_DOWN",   &tau2_m_UncMet_DOWN,   "tau2_m_UncMet_DOWN/F"));
      // up ClusteredMet
      tau4VectorBranches.push_back(t->Branch("tau1_pt_ClusteredMet_UP",  &tau1_pt_ClusteredMet_UP,  "tau1_pt_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_ClusteredMet_UP", &tau1_eta_ClusteredMet_UP, "tau1_eta_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_ClusteredMet_UP", &tau1_phi_ClusteredMet_UP, "tau1_phi_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_ClusteredMet_UP",   &tau1_m_ClusteredMet_UP,   "tau1_m_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_ClusteredMet_UP",  &tau2_pt_ClusteredMet_UP,  "tau2_pt_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_ClusteredMet_UP", &tau2_eta_ClusteredMet_UP, "tau2_eta_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_ClusteredMet_UP", &tau2_phi_ClusteredMet_UP, "tau2_phi_ClusteredMet_UP/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_ClusteredMet_UP",   &tau2_m_ClusteredMet_UP,   "tau2_m_ClusteredMet_UP/F"));
      // down
      tau4VectorBranches.push_back(t->Branch("tau1_pt_ClusteredMet_DOWN",  &tau1_pt_ClusteredMet_DOWN,  "tau1_pt_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_eta_ClusteredMet_DOWN", &tau1_eta_ClusteredMet_DOWN, "tau1_eta_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_phi_ClusteredMet_DOWN", &tau1_phi_ClusteredMet_DOWN, "tau1_phi_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau1_m_ClusteredMet_DOWN",   &tau1_m_ClusteredMet_DOWN,   "tau1_m_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_pt_ClusteredMet_DOWN",  &tau2_pt_ClusteredMet_DOWN,  "tau2_pt_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_eta_ClusteredMet_DOWN", &tau2_eta_ClusteredMet_DOWN, "tau2_eta_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_phi_ClusteredMet_DOWN", &tau2_phi_ClusteredMet_DOWN, "tau2_phi_ClusteredMet_DOWN/F"));
      tau4VectorBranches.push_back(t->Branch("tau2_m_ClusteredMet_DOWN",   &tau2_m_ClusteredMet_DOWN,   "tau2_m_ClusteredMet_DOWN/F"));
      std::cout << "That's a lot of tau 4-vector branches! N = " << tau4VectorBranches.size() << std::endl;
    
      unsigned long long evt;
      int run, lumi;
      float pt1;
      float eta1;
      float phi1;
      float gen_match_1;
      float pt2;
      float eta2;
      float phi2;
      float m2;
      float gen_match_2;
      float decayMode=-999.;
      float decayMode2;
      float mvaCovMatrix00;
      float mvaCovMatrix10;
      float mvaCovMatrix01;
      float mvaCovMatrix11;
      float pfCovMatrix00;
      float pfCovMatrix10;
      float pfCovMatrix01;
      float pfCovMatrix11;
      //float mvamet_ex, // uncorrected mva met px (float)
      //  mvamet_ey, // uncorrected mva met py (float)
      float  genPx=-999.    , // generator Z/W/Higgs px (float)
        genPy =-999.   , // generator Z/W/Higgs py (float)
        visPx =-999.   , // generator visible Z/W/Higgs px (float)
        visPy =-999.   ; // generator visible Z/W/Higgs py (float)

      int njets =-999.   ;  // number of jets (hadronic jet multiplicity) (int)

      // define MET
      double measuredMETx = 0.;
      double measuredMETy = 0.;
      float mvamet;
      float mvametphi;
      float pfmet;
      float pfmetphi;
      TLorentzVector TMet(0,0,0,0);
      // define MET covariance
      TMatrixD covMET(2, 2);

      // MET Uncertainties
      float uncMetPtUp;
      float uncMetPtDown;
      float uncMetPhiUp;
      float uncMetPhiDown;
      float clusteredMetPtUp;
      float clusteredMetPtDown;
      float clusteredMetPhiUp;
      float clusteredMetPhiDown;
      double uncMetUpMETx = 0.;
      double uncMetUpMETy = 0.;
      double uncMetDownMETx = 0.;
      double uncMetDownMETy = 0.;
      double clusteredMetUpMETx = 0.;
      double clusteredMetUpMETy = 0.;
      double clusteredMetDownMETx = 0.;
      double clusteredMetDownMETy = 0.;
      
      //ele/mu variables
      TBranch *pt1branch;
      
      t->SetBranchAddress("evt",&evt);
      t->SetBranchAddress("run",&run);
      t->SetBranchAddress("lumi",&lumi);
      if(channel=="tt" && tylerCode ) {
        t->SetBranchAddress("t1Pt",&pt1,&pt1branch);
        t->SetBranchAddress("t1Eta",&eta1);
        t->SetBranchAddress("t1Phi",&phi1);
        t->SetBranchAddress("t1Mass",&mass1);
        t->SetBranchAddress("t1ZTTGenMatching",&gen_match_1);
        t->SetBranchAddress("t2Pt",&pt2);
        t->SetBranchAddress("t2Eta",&eta2);
        t->SetBranchAddress("t2Phi",&phi2);
        t->SetBranchAddress("t2Mass",&mass2);
        t->SetBranchAddress("t2ZTTGenMatching",&gen_match_2);
        t->SetBranchAddress("t1DecayMode",&decayMode);
        t->SetBranchAddress("t2DecayMode",&decayMode2);
        t->SetBranchAddress("t1_t2_MvaMetCovMatrix00",&mvaCovMatrix00);
        t->SetBranchAddress("t1_t2_MvaMetCovMatrix01",&mvaCovMatrix01);
        t->SetBranchAddress("t1_t2_MvaMetCovMatrix10",&mvaCovMatrix10);
        t->SetBranchAddress("t1_t2_MvaMetCovMatrix11",&mvaCovMatrix11);
        t->SetBranchAddress("t1_t2_MvaMet",&mvamet);
        t->SetBranchAddress("t1_t2_MvaMetPhi",&mvametphi);
        t->SetBranchAddress("jetVeto30", &njets);
        t->SetBranchAddress("type1_pfMetEt",&pfmet);
        t->SetBranchAddress("type1_pfMetPhi",&pfmetphi);
      }
      else {
        t->SetBranchAddress("pt_1",&pt1,&pt1branch);
        t->SetBranchAddress("eta_1",&eta1);
        t->SetBranchAddress("phi_1",&phi1);
        t->SetBranchAddress("pt_2",&pt2);
        t->SetBranchAddress("eta_2",&eta2);
        t->SetBranchAddress("phi_2",&phi2);
        t->SetBranchAddress("m_2",&m2);
        //t->SetBranchAddress("l1_decayMode",&decayMode);
        //t->SetBranchAddress("l2_decayMode",&decayMode2);
        t->SetBranchAddress("decayMode_1",&decayMode);
        t->SetBranchAddress("decayMode_2",&decayMode2);
        //t->SetBranchAddress("mvacov00",&mvaCovMatrix00);
        //t->SetBranchAddress("mvacov01",&mvaCovMatrix01);
        //t->SetBranchAddress("mvacov10",&mvaCovMatrix10);
        //t->SetBranchAddress("mvacov11",&mvaCovMatrix11);
        t->SetBranchAddress("metcov00",&mvaCovMatrix00);
        t->SetBranchAddress("metcov01",&mvaCovMatrix01);
        t->SetBranchAddress("metcov10",&mvaCovMatrix10);
        t->SetBranchAddress("metcov11",&mvaCovMatrix11);
        //t->SetBranchAddress("mvamet",&mvamet);
        //t->SetBranchAddress("met",&mvamet);
        //t->SetBranchAddress("mvametphi",&mvametphi);
        //t->SetBranchAddress("metphi",&mvametphi);
        t->SetBranchAddress("njets", &njets);
        t->SetBranchAddress("met",&pfmet);
        t->SetBranchAddress("metphi",&pfmetphi);
      }
      // Recoil variables below
      t->SetBranchAddress( "genpX", &genPx);
      t->SetBranchAddress( "genpY", &genPy);
      t->SetBranchAddress( "vispX", &visPx);
      t->SetBranchAddress( "vispY", &visPy);
      // FOR PF MET ANALYSIS
      //t->SetBranchAddress("metcov00",&pfCovMatrix00);
      //t->SetBranchAddress("metcov01",&pfCovMatrix01);
      //t->SetBranchAddress("metcov10",&pfCovMatrix10);
      //t->SetBranchAddress("metcov11",&pfCovMatrix11);
      t->SetBranchAddress("metcov00",&pfCovMatrix00);
      t->SetBranchAddress("metcov01",&pfCovMatrix01);
      t->SetBranchAddress("metcov10",&pfCovMatrix10);
      t->SetBranchAddress("metcov11",&pfCovMatrix11);
      // Met Unc
      t->SetBranchAddress("type1_pfMet_shiftedPt_UnclusteredEnUp",&uncMetPtUp);
      t->SetBranchAddress("type1_pfMet_shiftedPt_UnclusteredEnDown",&uncMetPtDown);
      t->SetBranchAddress("type1_pfMet_shiftedPhi_UnclusteredEnUp",&uncMetPhiUp);
      t->SetBranchAddress("type1_pfMet_shiftedPhi_UnclusteredEnDown",&uncMetPhiDown);
      t->SetBranchAddress("type1_pfMet_shiftedPt_JetEnUp",&clusteredMetPtUp);
      t->SetBranchAddress("type1_pfMet_shiftedPt_JetEnDown",&clusteredMetPtDown);
      t->SetBranchAddress("type1_pfMet_shiftedPhi_JetEnUp",&clusteredMetPhiUp);
      t->SetBranchAddress("type1_pfMet_shiftedPhi_JetEnDown",&clusteredMetPhiDown);

      // use this RooT file when running on aMC@NLO DY and W+Jets MC samples
      RecoilCorrector* recoilCorrector = new RecoilCorrector(recoilFileName);
      if (metType == 1) std::cout<<"MetType: MvaMet"<<std::endl;
      if (metType == -1) std::cout<<"MetType: PF Met"<<std::endl;
      std::cout<<"recoiltype "<<recoilType<<" recoilFileName "<<recoilFileName<<std::endl;
      
      printf("Found tree -> weighting\n");
    
      double tesUP = 1.0 + tesSize;
      double tesDOWN = 1.0 - tesSize;

      int nevents = t->GetEntries();
      if ( parser.integerValue("numEvents") != -1 ) nevents = parser.integerValue("numEvents");
      for(Int_t i=0;i<nevents;++i){
	t->GetEntry(i);

         //Recoil Correction time
         // Correct WJets recoil for faked lepton / extra jet
         int recoilNJets;
         if(isWJets) {
            recoilNJets = njets + 1;
            std::cout << " - njets: " << njets << " recoilNJets: " << recoilNJets << std::endl;
         }
         else recoilNJets = njets;

         // Using PF Met or Mva Met?
         if (metType == 1) { // 1 = Mva Met
             TMet.SetPtEtaPhiM(mvamet,0,mvametphi,0);
             measuredMETx = mvamet*TMath::Cos(mvametphi);
             measuredMETy = mvamet*TMath::Sin(mvametphi);

             covMET[0][0] =  mvaCovMatrix00;
             covMET[1][0] =  mvaCovMatrix10;
             covMET[0][1] =  mvaCovMatrix01;
             covMET[1][1] =  mvaCovMatrix11;
         } // mva met
         if (metType == -1) { // -1 = PF Met
             TMet.SetPtEtaPhiM(pfmet,0,pfmetphi,0);
             measuredMETx = pfmet*TMath::Cos(pfmetphi);
             measuredMETy = pfmet*TMath::Sin(pfmetphi);
             // Shifted METs
             uncMetUpMETx         = uncMetPtUp*TMath::Cos(uncMetPhiUp);
             uncMetUpMETy         = uncMetPtUp*TMath::Sin(uncMetPhiUp);
             uncMetDownMETx       = uncMetPtDown*TMath::Cos(uncMetPhiDown);
             uncMetDownMETy       = uncMetPtDown*TMath::Sin(uncMetPhiDown);
             clusteredMetUpMETx   = clusteredMetPtUp*TMath::Cos(clusteredMetPhiUp);
             clusteredMetUpMETy   = clusteredMetPtUp*TMath::Sin(clusteredMetPhiUp);
             clusteredMetDownMETx = clusteredMetPtDown*TMath::Cos(clusteredMetPhiDown);
             clusteredMetDownMETy = clusteredMetPtDown*TMath::Sin(clusteredMetPhiDown);

             covMET[0][0] =  pfCovMatrix00;
             covMET[1][0] =  pfCovMatrix10;
             covMET[0][1] =  pfCovMatrix01;
             covMET[1][1] =  pfCovMatrix11;
         } // pf met

         // Do recoil corrections if requested
         if(recoilType != 0){
            // Alexie shows that corrections via quantile mapping provide best results
            // for mva met and pf met, so
            // use that as the defaul.  People can switch if they want below
            //
            // RecoilCorrector::Correct == Quantile Mapping
            // RecoilCorrector::CorrectByMeanResolution == By Mean Res

            //recoilCorrector->Correct(
            recoilCorrector->CorrectByMeanResolution( // This method is faster (Alexei)
                              measuredMETx, // uncorrected mva met px (float)
                              measuredMETy, // uncorrected mva met py (float)
                              genPx, // generator Z/W/Higgs px (float)
                              genPy, // generator Z/W/Higgs py (float)
                              visPx, // generator visible Z/W/Higgs px (float)
                              visPy, // generator visible Z/W/Higgs py (float)
                              recoilNJets,  // number of jets (hadronic jet multiplicity) (int)
                              metcorr_ex, // corrected met px (float)
                              metcorr_ey  // corrected met py (float)
                              );
            // Shifted MET unc Up
            recoilCorrector->CorrectByMeanResolution( // This method is faster (Alexei)
                              uncMetUpMETx, // uncorrected mva met px (float)
                              uncMetUpMETy, // uncorrected mva met py (float)
                              genPx, // generator Z/W/Higgs px (float)
                              genPy, // generator Z/W/Higgs py (float)
                              visPx, // generator visible Z/W/Higgs px (float)
                              visPy, // generator visible Z/W/Higgs py (float)
                              recoilNJets,  // number of jets (hadronic jet multiplicity) (int)
                              metcorrUncUp_ex, // corrected met px (float)
                              metcorrUncUp_ey  // corrected met py (float)
                              );
            // Shifted MET unc Down
            recoilCorrector->CorrectByMeanResolution( // This method is faster (Alexei)
                              uncMetDownMETx, // uncorrected mva met px (float)
                              uncMetDownMETy, // uncorrected mva met py (float)
                              genPx, // generator Z/W/Higgs px (float)
                              genPy, // generator Z/W/Higgs py (float)
                              visPx, // generator visible Z/W/Higgs px (float)
                              visPy, // generator visible Z/W/Higgs py (float)
                              recoilNJets,  // number of jets (hadronic jet multiplicity) (int)
                              metcorrUncDown_ex, // corrected met px (float)
                              metcorrUncDown_ey  // corrected met py (float)
                              );
            // Shifted MET clustered Up
            recoilCorrector->CorrectByMeanResolution( // This method is faster (Alexei)
                              clusteredMetUpMETx, // uncorrected mva met px (float)
                              clusteredMetUpMETy, // uncorrected mva met py (float)
                              genPx, // generator Z/W/Higgs px (float)
                              genPy, // generator Z/W/Higgs py (float)
                              visPx, // generator visible Z/W/Higgs px (float)
                              visPy, // generator visible Z/W/Higgs py (float)
                              recoilNJets,  // number of jets (hadronic jet multiplicity) (int)
                              metcorrClusteredUp_ex, // corrected met px (float)
                              metcorrClusteredUp_ey  // corrected met py (float)
                              );
            // Shifted MET clustered Down
            recoilCorrector->CorrectByMeanResolution( // This method is faster (Alexei)
                              clusteredMetDownMETx, // uncorrected mva met px (float)
                              clusteredMetDownMETy, // uncorrected mva met py (float)
                              genPx, // generator Z/W/Higgs px (float)
                              genPy, // generator Z/W/Higgs py (float)
                              visPx, // generator visible Z/W/Higgs px (float)
                              visPy, // generator visible Z/W/Higgs py (float)
                              recoilNJets,  // number of jets (hadronic jet multiplicity) (int)
                              metcorrClusteredDown_ex, // corrected met px (float)
                              metcorrClusteredDown_ey  // corrected met py (float)
                              );
           std::cout << " - MEASURED:  met_ex: " << measuredMETx << "  met_ey: " << measuredMETy << std::endl;
           std::cout << " - CORRECTED: met_ex: " << metcorr_ex << "  met_ey: " << metcorr_ey << std::endl;
        }
        else{
           metcorr_ex = measuredMETx;
           metcorr_ey = measuredMETy;
           metcorrUncUp_ex = uncMetUpMETx;
           metcorrUncUp_ey = uncMetUpMETy;
           metcorrUncDown_ex = uncMetDownMETx;
           metcorrUncDown_ey = uncMetDownMETy;
           metcorrClusteredUp_ex = clusteredMetUpMETx;
           metcorrClusteredUp_ey = clusteredMetUpMETy;
           metcorrClusteredDown_ex = clusteredMetDownMETx;
           metcorrClusteredDown_ey = clusteredMetDownMETy;
        }

        metcor = TMath::Sqrt( metcorr_ex*metcorr_ex + metcorr_ey*metcorr_ey);
        metcorphi = TMath::ATan2( metcorr_ey, metcorr_ex );
        std::cout << " - metcor "<<metcor<<" metcorphi "<<metcorphi<<std::endl;

        // Corrected MET values for saving
        // Will be re-corrected with TEC if running tautau channel
        metcorClusteredDown = TMath::Sqrt( metcorrClusteredDown_ex*metcorrClusteredDown_ex + metcorrClusteredDown_ey*metcorrClusteredDown_ey);
        metcorphiClusteredDown = TMath::ATan2( metcorrClusteredDown_ey, metcorrClusteredDown_ex );

        metcorClusteredUp = TMath::Sqrt( metcorrClusteredUp_ex*metcorrClusteredUp_ex + metcorrClusteredUp_ey*metcorrClusteredUp_ey);
        metcorphiClusteredUp = TMath::ATan2( metcorrClusteredUp_ey, metcorrClusteredUp_ex );

        metcorUncDown = TMath::Sqrt( metcorrUncDown_ex*metcorrUncDown_ex + metcorrUncDown_ey*metcorrUncDown_ey);
        metcorphiUncDown = TMath::ATan2( metcorrUncDown_ey, metcorrUncDown_ex );

        metcorUncUp = TMath::Sqrt( metcorrUncUp_ex*metcorrUncUp_ex + metcorrUncUp_ey*metcorrUncUp_ey);
        metcorphiUncUp = TMath::ATan2( metcorrUncUp_ey, metcorrUncUp_ex );

      if(channel=="mt"||channel=="et"){

         float shiftTau=1.0;
         if (gen_match_2==5 && decayMode2==0) shiftTau=0.982;
         if (gen_match_2==5 && decayMode2==1) shiftTau=1.010;
         if (gen_match_2==5 && decayMode2==10) shiftTau=1.004;
         pt2 = pt2 * shiftTau;
         double dx2, dy2;
         dx2 = pt2 * TMath::Cos( phi2 ) * (( 1. / shiftTau ) - 1.);
         dy2 = pt2 * TMath::Sin( phi2 ) * (( 1. / shiftTau ) - 1.);
         metcorr_ex = metcorr_ex + dx2;
         metcorr_ey = metcorr_ey + dy2;

         mass2 = m2;
         std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
         measuredTauLeptons.push_back(
           classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1,  phi1, mass1));
        
        measuredTauLeptons.push_back(
           classic_svFit::MeasuredTauLepton(decayType2,  pt2, eta2, phi2,  mass2, decayMode2)); 
        std::cout<< "evt: "<<evt<<" run: "<<run<<" lumi: "<<lumi<< " pt1 " << pt1 << " mass1 " << mass1 << " pt2: "<< pt2<< " mass2: "<< mass2 <<std::endl;        
        //modified
        runSVFit(measuredTauLeptons, 
		 metcorr_ex, metcorr_ey, covMET, 0, 
		 svFitMass, svFitPt, svFitEta, svFitPhi, svFitMET, svFitTransverseMass, tau1, tau2);
        std::cout<<"finished runningSVFit"<<std::endl;

        if(doES) {

          if (gen_match_2<=5){
             float ES_UP_scale=1.0; // this value is for jet -> tau fakes
             if (gen_match_2<5) ES_UP_scale=1.01; // for gen matched ele/muon
             if (gen_match_2==5) ES_UP_scale=tesUP; // for real taus
             double pt2_UP;
             pt2_UP = pt2 * ES_UP_scale;
             double metcorr_ex_UP, metcorr_ey_UP;
             double dx2_UP, dy2_UP;
             dx2_UP = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_UP_scale ) - 1.);
             dy2_UP = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_UP_scale ) - 1.);
             metcorr_ex_UP = metcorr_ex + dx2_UP;
             metcorr_ey_UP = metcorr_ey + dy2_UP;
             
             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
             measuredTauLeptonsUP.push_back(
              classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1,  phi1, mass1));
             measuredTauLeptonsUP.push_back(
              classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));

             runSVFit(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, 0, svFitMass_UP, svFitPt_UP, svFitEta_UP, svFitPhi_UP, svFitMET_UP, svFitTransverseMass_UP, tau1_up, tau2_up);
      }
      else {
          svFitMass_UP=svFitMass;
          svFitPt_UP=svFitPt;
          svFitEta_UP=svFitEta;
          svFitPhi_UP=svFitPhi;
          svFitMET_UP=svFitMET;
          svFitTransverseMass_UP=svFitTransverseMass;
	  tau1_up = tau1;
	  tau2_up = tau2;
      }

          // Second ES Down, x 0.97
          if (gen_match_2<=5){
             float ES_DOWN_scale=1.0; // jet
             if (gen_match_2==5) ES_DOWN_scale=tesDOWN; // tau
             if (gen_match_2<5) ES_DOWN_scale=0.990;  // elec/mu
             double pt2_DOWN;
             pt2_DOWN = pt2 * ES_DOWN_scale;
             double metcorr_ex_DOWN, metcorr_ey_DOWN;
             double dx2_DOWN, dy2_DOWN;
             dx2_DOWN = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_DOWN_scale ) - 1.);
             dy2_DOWN = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_DOWN_scale ) - 1.);
             metcorr_ex_DOWN = metcorr_ex + dx2_DOWN;
             metcorr_ey_DOWN = metcorr_ey + dy2_DOWN;

             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;          
             measuredTauLeptonsDOWN.push_back(
              classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1,  phi1, mass1));
             measuredTauLeptonsDOWN.push_back(
              classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));

             runSVFit(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, 0, svFitMass_DOWN, svFitPt_DOWN, svFitEta_DOWN, svFitPhi_DOWN, svFitMET_DOWN, svFitTransverseMass_DOWN, tau1_down, tau2_down);
      }
      else {
              svFitMass_DOWN=svFitMass;
              svFitPt_DOWN=svFitPt;
              svFitEta_DOWN=svFitEta;
              svFitPhi_DOWN=svFitPhi;
              svFitMET_DOWN=svFitMET;
              svFitTransverseMass_DOWN=svFitTransverseMass;
	      tau1_down = tau1;
	      tau2_down = tau2;
          }
        } // end doES
      } // eTau / muTau

      else if(channel=="em"){
        // define lepton four vectors
        std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
        measuredTauLeptons.push_back(
         classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1,  phi1, mass1));
        measuredTauLeptons.push_back(
         classic_svFit::MeasuredTauLepton(decayType2,  pt2, eta2, phi2, mass2));

        std::cout<< "evt: "<<evt<<" run: "<<run<<" lumi: "<<lumi<< " pt1 " << pt1 << " mass1 " << mass1 << " pt2: "<< pt2<< " mass2: "<< mass2 <<std::endl;        
        runSVFit(measuredTauLeptons, metcorr_ex, metcorr_ey, covMET, 0, svFitMass, svFitPt, svFitEta, svFitPhi, svFitMET, svFitTransverseMass, tau1, tau2);
        std::cout<<"finished running non-EES SVFit in EMu"<<std::endl;
        if(doES) {

          // Only shift Electrons
          // 1% shift in barrel and 2.5% shift in endcap
          // applied to electrons in emu channel
          float etaBarrelEndcap  = 1.479;
          float ES_UP_scale;
          if (abs(eta1) < etaBarrelEndcap) ES_UP_scale = 1.01;
          else ES_UP_scale = 1.025;
          double pt1_UP = pt1 * ES_UP_scale;
          std::cout << "E eta: " << eta1 << " ees SF: " << ES_UP_scale << std::endl;
          double metcorr_ex_UP, metcorr_ey_UP;
          double dx1_UP, dy1_UP;
          dx1_UP = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_UP_scale ) - 1.);
          dy1_UP = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_UP_scale ) - 1.);
          metcorr_ex_UP = metcorr_ex + dx1_UP;
          metcorr_ey_UP = metcorr_ey + dy1_UP;
          std::cout << "px1 " << pt1 * TMath::Cos( phi1 ) << "  met px1 cor " << dx1_UP <<std::endl;
          std::cout << "py1 " << pt1 * TMath::Sin( phi1 ) << "  met py1 cor " << dy1_UP <<std::endl;
          std::cout << "pt1 " << pt1 << "  pt1_up " << pt1_UP <<std::endl;
          std::cout << "metcor_ex " << metcorr_ex << " ees: " << metcorr_ex_UP << std::endl;
          std::cout << "metcor_ey " << metcorr_ey << " ees: " << metcorr_ey_UP << std::endl;
          
          std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
          measuredTauLeptonsUP.push_back(
           classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1));
          measuredTauLeptonsUP.push_back(
           classic_svFit::MeasuredTauLepton(decayType2,  pt2, eta2, phi2, mass2));

          std::cout<< "evt: "<<evt<<" run: "<<run<<" lumi: "<<lumi<< " pt1 " << pt1_UP << " mass1 " << mass1 << " pt2: "<< pt2 << " mass2: "<< mass2 <<std::endl;        
          runSVFit(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, 0, svFitMass_UP, svFitPt_UP, svFitEta_UP, svFitPhi_UP, svFitMET_UP, svFitTransverseMass_UP, tau1_up, tau2_up);
          std::cout<<"finished runningSVFit in EMu EES Up"<<std::endl;


          // EES Down
          float ES_DOWN_scale;
          if (abs(eta1) < etaBarrelEndcap) ES_DOWN_scale = 0.99;
          else ES_DOWN_scale = 0.975;
          std::cout << "E eta: " << eta1 << " ees SF: " << ES_DOWN_scale << std::endl;
          double pt1_DOWN;
          pt1_DOWN = pt1 * ES_DOWN_scale;
          double metcorr_ex_DOWN, metcorr_ey_DOWN;
          double dx1_DOWN, dy1_DOWN;
          dx1_DOWN = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_DOWN_scale ) - 1.);
          dy1_DOWN = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_DOWN_scale ) - 1.);
          metcorr_ex_DOWN = metcorr_ex + dx1_DOWN;
          metcorr_ey_DOWN = metcorr_ey + dy1_DOWN;
          std::cout << "px1 " << pt1 * TMath::Cos( phi1 ) << "  met px1 cor " << dx1_DOWN <<std::endl;
          std::cout << "py1 " << pt1 * TMath::Sin( phi1 ) << "  met py1 cor " << dy1_DOWN <<std::endl;
          std::cout << "metcor_ex " << metcorr_ex << " ees: " << metcorr_ex_DOWN << std::endl;
          std::cout << "metcor_ey " << metcorr_ey << " ees: " << metcorr_ey_DOWN << std::endl;

          std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;
          measuredTauLeptonsDOWN.push_back(
           classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1));
          measuredTauLeptonsDOWN.push_back(
           classic_svFit::MeasuredTauLepton(decayType2,  pt2, eta2, phi2,  mass2));

          runSVFit(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, 0, svFitMass_DOWN, svFitPt_DOWN, svFitEta_DOWN, svFitPhi_DOWN, svFitMET_DOWN, svFitTransverseMass_DOWN, tau1_down, tau2_down);


        } // end doES
      } // eMu



      else if(channel=="tt"){

         float shiftTau1=1.0;
         float shiftTau2=1.0;
         if (gen_match_1==5 && decayMode==0) shiftTau1=0.982;
         if (gen_match_1==5 && decayMode==1) shiftTau1=1.010;
         if (gen_match_1==5 && decayMode==10) shiftTau1=1.004;
         if (gen_match_2==5 && decayMode2==0) shiftTau2=0.982;
         if (gen_match_2==5 && decayMode2==1) shiftTau2=1.010;
         if (gen_match_2==5 && decayMode2==10) shiftTau2=1.004;
         pt1 = pt1 * shiftTau1;
         pt2 = pt2 * shiftTau2;
         double dx1, dy1;
         double dx2, dy2;
         dx1 = pt1 * TMath::Cos( phi1 ) * (( 1. / shiftTau1 ) - 1.);
         dy1 = pt1 * TMath::Sin( phi1 ) * (( 1. / shiftTau1 ) - 1.);
         dx2 = pt2 * TMath::Cos( phi2 ) * (( 1. / shiftTau2 ) - 1.);
         dy2 = pt2 * TMath::Sin( phi2 ) * (( 1. / shiftTau2 ) - 1.);
         metcorr_ex = metcorr_ex + dx1;
         metcorr_ey = metcorr_ey + dy1;
         metcorr_ex = metcorr_ex + dx2;
         metcorr_ey = metcorr_ey + dy2;

        // define lepton four vectors
        std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
        // Add Tau of higest Pt first
        if (pt1 > pt2) {
          measuredTauLeptons.push_back(
           classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1,  phi1, mass1, decayMode));
        
          measuredTauLeptons.push_back(
           classic_svFit::MeasuredTauLepton(decayType2,  pt2, eta2, phi2,  mass2, decayMode2));
        }
        else {
          measuredTauLeptons.push_back(
           classic_svFit::MeasuredTauLepton(decayType2,  pt2, eta2, phi2,  mass2, decayMode2));

          measuredTauLeptons.push_back(
           classic_svFit::MeasuredTauLepton(decayType1, pt1, eta1,  phi1, mass1, decayMode));
        }

        std::cout<< "evt: "<<evt<<" run: "<<run<<" lumi: "<<lumi<< " pt1 " << pt1 << " mass1 " << mass1 << " pt2: "<< pt2<< " mass2: "<< mass2 <<std::endl;        
        runSVFit(measuredTauLeptons, metcorr_ex, metcorr_ey, covMET, 0, svFitMass, svFitPt, svFitEta, svFitPhi, svFitMET, svFitTransverseMass, tau1, tau2);
        std::cout<<"finished running non-TES SVFit in TT"<<std::endl;


        //*****************************************************
        // MET SYSTEMATICS
        // Taus Pt have been corrected (TEC)
        // All 4 mets have recoil corrections already applied
        // Still need TEC propagated to shifted, recoil corrected
        // METs
        //*****************************************************

        std::cout << "MET Unclustered Energy Up   ---  ";
        metcorrUncUp_ex = metcorrUncUp_ex + dx1 + dx2;
        metcorrUncUp_ey = metcorrUncUp_ey + dy1 + dy2;
        runSVFit(measuredTauLeptons, metcorrUncUp_ex, metcorrUncUp_ey, covMET, 0, svFitMass_UncMet_UP, svFitPt_UncMet_UP, svFitEta_UncMet_UP, svFitPhi_UncMet_UP, svFitMET_UncMet_UP, svFitTransverseMass_UncMet_UP, tau1_UncMet_up, tau2_UncMet_up);
        std::cout << "MET Unclustered Energy Down ---  ";
        metcorrUncDown_ex = metcorrUncDown_ex + dx1 + dx2;
        metcorrUncDown_ey = metcorrUncDown_ey + dy1 + dy2;
        runSVFit(measuredTauLeptons, metcorrUncDown_ex, metcorrUncDown_ey, covMET, 0, svFitMass_UncMet_DOWN, svFitPt_UncMet_DOWN, svFitEta_UncMet_DOWN, svFitPhi_UncMet_DOWN, svFitMET_UncMet_DOWN, svFitTransverseMass_UncMet_DOWN, tau1_UncMet_down, tau2_UncMet_down);
        std::cout << "MET Clustered Energy Up     ---  ";
        metcorrClusteredUp_ex = metcorrClusteredUp_ex + dx1 + dx2;
        metcorrClusteredUp_ey = metcorrClusteredUp_ey + dy1 + dy2;
        runSVFit(measuredTauLeptons, metcorrClusteredUp_ex, metcorrClusteredUp_ey, covMET, 0, svFitMass_ClusteredMet_UP, svFitPt_ClusteredMet_UP, svFitEta_ClusteredMet_UP, svFitPhi_ClusteredMet_UP, svFitMET_ClusteredMet_UP, svFitTransverseMass_ClusteredMet_UP, tau1_ClusteredMet_up, tau2_ClusteredMet_up);
        std::cout << "MET Clustered Energy Down   ---  ";
        metcorrClusteredDown_ex = metcorrClusteredDown_ex + dx1 + dx2;
        metcorrClusteredDown_ey = metcorrClusteredDown_ey + dy1 + dy2;
        runSVFit(measuredTauLeptons, metcorrClusteredDown_ex, metcorrClusteredDown_ey, covMET, 0, svFitMass_ClusteredMet_DOWN, svFitPt_ClusteredMet_DOWN, svFitEta_ClusteredMet_DOWN, svFitPhi_ClusteredMet_DOWN, svFitMET_ClusteredMet_DOWN, svFitTransverseMass_ClusteredMet_DOWN, tau1_ClusteredMet_down, tau2_ClusteredMet_down);
        std::cout<< "Shifted MET Summary:\nmetcorr_ex " << metcorr_ex << "\n --- metcorrUncUp_ex " << metcorrUncUp_ex << " metcorrUncDown_ex " << metcorrUncDown_ex
        << " metcorrClusteredUp_ex " << metcorrClusteredUp_ex << " metcorrClusteredDown_ex " << metcorrClusteredDown_ex << std::endl;
        std::cout<< "metcorr_ey " << metcorr_ey << "\n --- metcorrUncUp_ey " << metcorrUncUp_ey << " metcorrUncDown_ey " << metcorrUncDown_ey
        << " metcorrClusteredUp_ey " << metcorrClusteredUp_ey << " metcorrClusteredDown_ey " << metcorrClusteredDown_ey << std::endl;


        // Corrected MET values for saving
        metcor = TMath::Sqrt( metcorr_ex*metcorr_ex + metcorr_ey*metcorr_ey);
        metcorphi = TMath::ATan2( metcorr_ey, metcorr_ex );
        metcorClusteredDown = TMath::Sqrt( metcorrClusteredDown_ex*metcorrClusteredDown_ex + metcorrClusteredDown_ey*metcorrClusteredDown_ey);
        metcorphiClusteredDown = TMath::ATan2( metcorrClusteredDown_ey, metcorrClusteredDown_ex );
        metcorClusteredUp = TMath::Sqrt( metcorrClusteredUp_ex*metcorrClusteredUp_ex + metcorrClusteredUp_ey*metcorrClusteredUp_ey);
        metcorphiClusteredUp = TMath::ATan2( metcorrClusteredUp_ey, metcorrClusteredUp_ex );
        metcorUncDown = TMath::Sqrt( metcorrUncDown_ex*metcorrUncDown_ex + metcorrUncDown_ey*metcorrUncDown_ey);
        metcorphiUncDown = TMath::ATan2( metcorrUncDown_ey, metcorrUncDown_ex );
        metcorUncUp = TMath::Sqrt( metcorrUncUp_ex*metcorrUncUp_ex + metcorrUncUp_ey*metcorrUncUp_ey);
        metcorphiUncUp = TMath::ATan2( metcorrUncUp_ey, metcorrUncUp_ex );

        if(doES) {

      //***************************************************************************
      //********************* Two taus shifted up *********************************
      //***************************************************************************
      
      if (gen_match_2==5 or gen_match_1==5){
             std::cout << "Two UP    ---  ";
             float ES_UP_scale1 = 1.0;
             float ES_UP_scale2 = 1.0;
             if(gen_match_1==5) ES_UP_scale1 = tesUP;
             if(gen_match_2==5) ES_UP_scale2 = tesUP;
             std::cout << "TES values: gen1: " << gen_match_1 << "   dm_1: " << decayMode;
             std::cout << "   tes1: " << ES_UP_scale1;
             std::cout << "   gen2: " << gen_match_2 << "   dm_2: " << decayMode2;
             std::cout << "   tes2: " << ES_UP_scale2 << std::endl;
             double pt1_UP, pt2_UP;
             pt1_UP = pt1 * ES_UP_scale1;
             pt2_UP = pt2 * ES_UP_scale2;
             double metcorr_ex_UP, metcorr_ey_UP;
             double dx1_UP, dy1_UP, dx2_UP, dy2_UP;
             dx1_UP = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dy1_UP = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dx2_UP = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             dy2_UP = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             metcorr_ex_UP = metcorr_ex + dx1_UP + dx2_UP;
             metcorr_ey_UP = metcorr_ey + dy1_UP + dy2_UP;
             
             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
             
             // Add Tau of higest Pt first
             if (pt1 > pt2) {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
             
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));

               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, 0, svFitMass_UP, svFitPt_UP, svFitEta_UP, svFitPhi_UP, svFitMET_UP, svFitTransverseMass_UP, tau1_up, tau2_up);
          }
          else {
              svFitMass_UP=svFitMass;
              svFitPt_UP=svFitPt;
              svFitEta_UP=svFitEta;
              svFitPhi_UP=svFitPhi;
              svFitMET_UP=svFitMET;
              svFitTransverseMass_UP=svFitTransverseMass;
	      tau1_up = tau1;
	      tau2_up = tau2;
          }

          //***************************************************************************
          //********************** Tau DM0 shifted up *********************************
          //***************************************************************************

          if ((gen_match_2==5 && decayMode2==0) or (gen_match_1==5 && decayMode==0)){
             std::cout << "DM0 UP    ---  ";
             float ES_UP_scale1 = 1.0;
             float ES_UP_scale2 = 1.0;
             if(gen_match_1==5 && decayMode==0) ES_UP_scale1 = tesUP;
             if(gen_match_2==5 && decayMode2==0) ES_UP_scale2 = tesUP;
             double pt1_UP, pt2_UP;
             pt1_UP = pt1 * ES_UP_scale1;
             pt2_UP = pt2 * ES_UP_scale2;
             double metcorr_ex_UP, metcorr_ey_UP;
             double dx1_UP, dy1_UP, dx2_UP, dy2_UP;
             dx1_UP = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dy1_UP = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dx2_UP = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             dy2_UP = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             metcorr_ex_UP = metcorr_ex + dx1_UP + dx2_UP;
             metcorr_ey_UP = metcorr_ey + dy1_UP + dy2_UP;
          
             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
             // Add Tau of higest Pt first
             if (pt1 > pt2) {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, 0, svFitMass_DM0_UP, svFitPt_DM0_UP, svFitEta_DM0_UP, svFitPhi_DM0_UP, svFitMET_DM0_UP, svFitTransverseMass_DM0_UP, tau1_DM0_up, tau2_DM0_down);
          }
          else {
              svFitMass_DM0_UP=svFitMass;
              svFitPt_DM0_UP=svFitPt;
              svFitEta_DM0_UP=svFitEta;
              svFitPhi_DM0_UP=svFitPhi;
              svFitMET_DM0_UP=svFitMET;
              svFitTransverseMass_DM0_UP=svFitTransverseMass;
	      tau1_DM0_up = tau1;
	      tau2_DM0_down = tau2;
          }

          //***************************************************************************
          //********************** Tau DM1 shifted up *********************************
          //***************************************************************************

          if ((decayMode==1 && gen_match_1==5) or (decayMode2==1 && gen_match_2==5)){
             std::cout << "DM1 UP    ---  ";
             float ES_UP_scale1 = 1.0;
             float ES_UP_scale2 = 1.0;
             if (decayMode==1 && gen_match_1==5) ES_UP_scale1 = tesUP;
             if (decayMode2==1 && gen_match_2==5) ES_UP_scale2 = tesUP;
             double pt1_UP, pt2_UP;
             pt1_UP = pt1 * ES_UP_scale1;
             pt2_UP = pt2 * ES_UP_scale2;
             double metcorr_ex_UP, metcorr_ey_UP;
             double dx1_UP, dy1_UP, dx2_UP, dy2_UP;
             dx1_UP = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dy1_UP = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dx2_UP = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             dy2_UP = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             metcorr_ex_UP = metcorr_ex + dx1_UP + dx2_UP;
             metcorr_ey_UP = metcorr_ey + dy1_UP + dy2_UP;
             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
             // Add Tau of higest Pt first
             if (pt1 > pt2) {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, 0, svFitMass_DM1_UP, svFitPt_DM1_UP, svFitEta_DM1_UP, svFitPhi_DM1_UP, svFitMET_DM1_UP, svFitTransverseMass_DM1_UP, tau1_DM1_up, tau2_DM1_up);
          }
          else {
              svFitMass_DM1_UP=svFitMass;
              svFitPt_DM1_UP=svFitPt;
              svFitEta_DM1_UP=svFitEta;
              svFitPhi_DM1_UP=svFitPhi;
              svFitMET_DM1_UP=svFitMET;
              svFitTransverseMass_DM1_UP=svFitTransverseMass;
	      tau1_DM1_up = tau1;
	      tau2_DM1_up = tau2;
          }

          //***************************************************************************
          //********************* Tau DM10 shifted up *********************************
          //***************************************************************************

          if ((decayMode2==10 && gen_match_2==5) or (decayMode==10 && gen_match_1==5)){
             std::cout << "DM10 UP    ---  ";
             float ES_UP_scale1 = 1.0;
             float ES_UP_scale2 = 1.0;
             if(decayMode==10 && gen_match_1==5) ES_UP_scale1 = tesUP;
             if(decayMode2==10 && gen_match_2==5) ES_UP_scale2 = tesUP;
             double pt1_UP, pt2_UP;
             pt1_UP = pt1 * ES_UP_scale1;
             pt2_UP = pt2 * ES_UP_scale2;
             double metcorr_ex_UP, metcorr_ey_UP;
             double dx1_UP, dy1_UP, dx2_UP, dy2_UP;
             dx1_UP = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dy1_UP = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_UP_scale1 ) - 1.);
             dx2_UP = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             dy2_UP = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_UP_scale2 ) - 1.);
             metcorr_ex_UP = metcorr_ex + dx1_UP + dx2_UP;
             metcorr_ey_UP = metcorr_ey + dy1_UP + dy2_UP;
          
             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
          
             // Add Tau of higest Pt first
             if (pt1 > pt2) {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_UP, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsUP.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_UP, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, 0, svFitMass_DM10_UP, svFitPt_DM10_UP, svFitEta_DM10_UP, svFitPhi_DM10_UP, svFitMET_DM10_UP, svFitTransverseMass_DM10_UP, tau1_DM10_up, tau2_DM10_up);
          }
          else {
              svFitMass_DM10_UP=svFitMass;
              svFitPt_DM10_UP=svFitPt;
              svFitEta_DM10_UP=svFitEta;
              svFitPhi_DM10_UP=svFitPhi;
              svFitMET_DM10_UP=svFitMET;
              svFitTransverseMass_DM10_UP=svFitTransverseMass;
	      tau1_DM10_up = tau1;
	      tau2_DM10_up = tau2;
          }

      //*****************************************************
      //************* Two taus shifted down *****************
      //*****************************************************

          if (gen_match_1==5 or gen_match_2==5){
             std::cout << "Two DOWN  ---  ";
             float ES_DOWN_scale1 = 1.0;
             float ES_DOWN_scale2 = 1.0;
             if (gen_match_1==5) ES_DOWN_scale1 = tesDOWN;
             if (gen_match_2==5) ES_DOWN_scale2 = tesDOWN;
             double pt1_DOWN, pt2_DOWN;
             pt1_DOWN = pt1 * ES_DOWN_scale1;
             pt2_DOWN = pt2 * ES_DOWN_scale2;
             double metcorr_ex_DOWN, metcorr_ey_DOWN;
             double dx1_DOWN, dy1_DOWN, dx2_DOWN, dy2_DOWN;
             dx1_DOWN = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dy1_DOWN = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dx2_DOWN = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             dy2_DOWN = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             metcorr_ex_DOWN = metcorr_ex + dx1_DOWN + dx2_DOWN;
             metcorr_ey_DOWN = metcorr_ey + dy1_DOWN + dy2_DOWN;

             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;
             
             if (pt1 > pt2) {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, 0, svFitMass_DOWN, svFitPt_DOWN, svFitEta_DOWN, svFitPhi_DOWN, svFitMET_DOWN, svFitTransverseMass_DOWN, tau1_down, tau2_down);
          }
          else {
              svFitMass_DOWN=svFitMass;
              svFitPt_DOWN=svFitPt;
              svFitEta_DOWN=svFitEta;
              svFitPhi_DOWN=svFitPhi;
              svFitMET_DOWN=svFitMET;
              svFitTransverseMass_DOWN=svFitTransverseMass;
	      tau1_down = tau1;
	      tau2_down = tau2;
          }

          //*****************************************************
          //************* Tau DM0 shifted down  *****************
          //*****************************************************

          if ((decayMode==0 && gen_match_1==5) or (decayMode2==0 && gen_match_2==5)){
             std::cout << "DM0 DOWN  ---  ";
             float ES_DOWN_scale1 = 1.0;
             float ES_DOWN_scale2 = 1.0;
             if (decayMode==0 && gen_match_1==5) ES_DOWN_scale1 = tesDOWN;
             if (decayMode2==0 && gen_match_2==5) ES_DOWN_scale2 = tesDOWN;
             double pt1_DOWN, pt2_DOWN;
             pt1_DOWN = pt1 * ES_DOWN_scale1;
             pt2_DOWN = pt2 * ES_DOWN_scale2;
             double metcorr_ex_DOWN, metcorr_ey_DOWN;
             double dx1_DOWN, dy1_DOWN, dx2_DOWN, dy2_DOWN;
             dx1_DOWN = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dy1_DOWN = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dx2_DOWN = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             dy2_DOWN = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             metcorr_ex_DOWN = metcorr_ex + dx1_DOWN + dx2_DOWN;
             metcorr_ey_DOWN = metcorr_ey + dy1_DOWN + dy2_DOWN;

             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;
             if (pt1 > pt2) {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, 0, svFitMass_DM0_DOWN, svFitPt_DM0_DOWN, svFitEta_DM0_DOWN, svFitPhi_DM0_DOWN, svFitMET_DM0_DOWN, svFitTransverseMass_DM0_DOWN, tau1_DM0_down, tau2_DM0_down);
          }
          else {
              svFitMass_DM0_DOWN=svFitMass;
              svFitPt_DM0_DOWN=svFitPt;
              svFitEta_DM0_DOWN=svFitEta;
              svFitPhi_DM0_DOWN=svFitPhi;
              svFitMET_DM0_DOWN=svFitMET;
              svFitTransverseMass_DM0_DOWN=svFitTransverseMass;
	      tau1_DM0_down = tau1;
	      tau2_DM0_down = tau2;
          }

          //*****************************************************
          //************** Tau DM1 shifted down *****************
          //*****************************************************

          if ((decayMode==1 && gen_match_1==5) or (decayMode2==1 && gen_match_2==5)){
             std::cout << "DM1 DOWN  ---  ";
             float ES_DOWN_scale1 = 1.0;
             float ES_DOWN_scale2 = 1.0;
             if (decayMode==1 && gen_match_1==5) ES_DOWN_scale1 = tesDOWN;
             if (decayMode2==1 && gen_match_2==5) ES_DOWN_scale2 = tesDOWN;
             double pt1_DOWN, pt2_DOWN;
             pt1_DOWN = pt1 * ES_DOWN_scale1;
             pt2_DOWN = pt2 * ES_DOWN_scale2;
             double metcorr_ex_DOWN, metcorr_ey_DOWN;
             double dx1_DOWN, dy1_DOWN, dx2_DOWN, dy2_DOWN;
             dx1_DOWN = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dy1_DOWN = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dx2_DOWN = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             dy2_DOWN = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             metcorr_ex_DOWN = metcorr_ex + dx1_DOWN + dx2_DOWN;
             metcorr_ey_DOWN = metcorr_ey + dy1_DOWN + dy2_DOWN;

             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;

             if (pt1 > pt2) {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, 0, svFitMass_DM1_DOWN, svFitPt_DM1_DOWN, svFitEta_DM1_DOWN, svFitPhi_DM1_DOWN, svFitMET_DM1_DOWN, svFitTransverseMass_DM1_DOWN, tau1_DM1_down, tau2_DM1_down);
          }
          else {
              svFitMass_DM1_DOWN=svFitMass;
              svFitPt_DM1_DOWN=svFitPt;
              svFitEta_DM1_DOWN=svFitEta;
              svFitPhi_DM1_DOWN=svFitPhi;
              svFitMET_DM1_DOWN=svFitMET;
              svFitTransverseMass_DM1_DOWN=svFitTransverseMass;
	      tau1_DM1_down =  tau1;
	      tau2_DM1_down =  tau2;
          }

          //*****************************************************
          //************* Tau DM10 shifted down *****************
          //*****************************************************

          if ((decayMode==10 && gen_match_1==5) or (decayMode2==10 && gen_match_2==5)){
             std::cout << "DM10 DOWN  ---  ";
             float ES_DOWN_scale1 = 1.0;
             float ES_DOWN_scale2 = 1.0;
             if (decayMode==10 && gen_match_1==5) ES_DOWN_scale1 = tesDOWN;
             if (decayMode2==10 && gen_match_2==5) ES_DOWN_scale2 = tesDOWN;
             double pt1_DOWN, pt2_DOWN;
             pt1_DOWN = pt1 * ES_DOWN_scale1;
             pt2_DOWN = pt2 * ES_DOWN_scale2;
             double metcorr_ex_DOWN, metcorr_ey_DOWN;
             double dx1_DOWN, dy1_DOWN, dx2_DOWN, dy2_DOWN;
             dx1_DOWN = pt1 * TMath::Cos( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dy1_DOWN = pt1 * TMath::Sin( phi1 ) * (( 1. / ES_DOWN_scale1 ) - 1.);
             dx2_DOWN = pt2 * TMath::Cos( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             dy2_DOWN = pt2 * TMath::Sin( phi2 ) * (( 1. / ES_DOWN_scale2 ) - 1.);
             metcorr_ex_DOWN = metcorr_ex + dx1_DOWN + dx2_DOWN;
             metcorr_ey_DOWN = metcorr_ey + dy1_DOWN + dy2_DOWN;

             std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;
             if (pt1 > pt2) {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
             }
             else {
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType2,  pt2_DOWN, eta2, phi2,  mass2, decayMode2));
               measuredTauLeptonsDOWN.push_back(
                classic_svFit::MeasuredTauLepton(decayType1, pt1_DOWN, eta1,  phi1, mass1, decayMode));
             }

             runSVFit(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, 0, svFitMass_DM10_DOWN, svFitPt_DM10_DOWN, svFitEta_DM10_DOWN, svFitPhi_DM10_DOWN, svFitMET_DM10_DOWN, svFitTransverseMass_DM10_DOWN, tau1_DM10_down, tau2_DM10_down);
          }
          else {
              svFitMass_DM10_DOWN=svFitMass;
              svFitPt_DM10_DOWN=svFitPt;
              svFitEta_DM10_DOWN=svFitEta;
              svFitPhi_DM10_DOWN=svFitPhi;
              svFitMET_DM10_DOWN=svFitMET;
              svFitTransverseMass_DM10_DOWN=svFitTransverseMass;
	      tau1_DM10_down = tau1;
	      tau2_DM10_down = tau2;
          }
        }// Do ES (TT)

      } // Double Hadronic (TT)

      else {
        svFitMass = -100;
        svFitPt = -100;
        svFitEta = -100;
        svFitPhi = -100;
        svFitMET = -100;
        svFitTransverseMass = -100;
	tau1.SetPtEtaPhiM(0,0,0,0);
	tau2.SetPtEtaPhiM(0,0,0,0); 
      }
      // fill the tau 4-vector parameters for branch-filling
      tau1_pt  = tau1.Pt();
      tau1_eta = tau1.Eta();
      tau1_phi = tau1.Phi();
      tau1_m   = tau1.M();
      tau2_pt  = tau2.Pt();
      tau2_eta = tau2.Eta();
      tau2_phi = tau2.Phi();
      tau2_m   = tau2.M();
      // up
      tau1_pt_UP  = tau1_up.Pt();
      tau1_eta_UP = tau1_up.Eta();
      tau1_phi_UP = tau1_up.Phi();
      tau1_m_UP   = tau1_up.M();
      tau2_pt_UP  = tau2_up.Pt();
      tau2_eta_UP = tau2_up.Eta();
      tau2_phi_UP = tau2_up.Phi();
      tau2_m_UP   = tau2_up.M();
      // down
      tau1_pt_DOWN  = tau1_down.Pt();
      tau1_eta_DOWN = tau1_down.Eta();
      tau1_phi_DOWN = tau1_down.Phi();
      tau1_m_DOWN   = tau1_down.M();
      tau2_pt_DOWN  = tau2_down.Pt();
      tau2_eta_DOWN = tau2_down.Eta();
      tau2_phi_DOWN = tau2_down.Phi();
      tau2_m_DOWN   = tau2_down.M();
      // DM0 up
      tau1_pt_DM0_UP  = tau1_DM0_up.Pt();
      tau1_eta_DM0_UP = tau1_DM0_up.Eta();
      tau1_phi_DM0_UP = tau1_DM0_up.Phi();
      tau1_m_DM0_UP   = tau1_DM0_up.M();
      tau2_pt_DM0_UP  = tau2_DM0_up.Pt();
      tau2_eta_DM0_UP = tau2_DM0_up.Eta();
      tau2_phi_DM0_UP = tau2_DM0_up.Phi();
      tau2_m_DM0_UP   = tau2_DM0_up.M();
      // down
      tau1_pt_DM0_DOWN  = tau1_DM0_down.Pt();
      tau1_eta_DM0_DOWN = tau1_DM0_down.Eta();
      tau1_phi_DM0_DOWN = tau1_DM0_down.Phi();
      tau1_m_DM0_DOWN   = tau1_DM0_down.M();
      tau2_pt_DM0_DOWN  = tau2_DM0_down.Pt();
      tau2_eta_DM0_DOWN = tau2_DM0_down.Eta();
      tau2_phi_DM0_DOWN = tau2_DM0_down.Phi();
      tau2_m_DM0_DOWN   = tau2_DM0_down.M();
      // DM1 up
      tau1_pt_DM1_UP  = tau1_DM1_up.Pt();
      tau1_eta_DM1_UP = tau1_DM1_up.Eta();
      tau1_phi_DM1_UP = tau1_DM1_up.Phi();
      tau1_m_DM1_UP   = tau1_DM1_up.M();
      tau2_pt_DM1_UP  = tau2_DM1_up.Pt();
      tau2_eta_DM1_UP = tau2_DM1_up.Eta();
      tau2_phi_DM1_UP = tau2_DM1_up.Phi();
      tau2_m_DM1_UP   = tau2_DM1_up.M();
      // down
      tau1_pt_DM1_DOWN  = tau1_DM1_down.Pt();
      tau1_eta_DM1_DOWN = tau1_DM1_down.Eta();
      tau1_phi_DM1_DOWN = tau1_DM1_down.Phi();
      tau1_m_DM1_DOWN   = tau1_DM1_down.M();
      tau2_pt_DM1_DOWN  = tau2_DM1_down.Pt();
      tau2_eta_DM1_DOWN = tau2_DM1_down.Eta();
      tau2_phi_DM1_DOWN = tau2_DM1_down.Phi();
      tau2_m_DM1_DOWN   = tau2_DM1_down.M();
      // DM10 up
      tau1_pt_DM10_UP  = tau1_DM10_up.Pt();
      tau1_eta_DM10_UP = tau1_DM10_up.Eta();
      tau1_phi_DM10_UP = tau1_DM10_up.Phi();
      tau1_m_DM10_UP   = tau1_DM10_up.M();
      tau2_pt_DM10_UP  = tau2_DM10_up.Pt();
      tau2_eta_DM10_UP = tau2_DM10_up.Eta();
      tau2_phi_DM10_UP = tau2_DM10_up.Phi();
      tau2_m_DM10_UP   = tau2_DM10_up.M();
      // down
      tau1_pt_DM10_DOWN  = tau1_DM10_down.Pt();
      tau1_eta_DM10_DOWN = tau1_DM10_down.Eta();
      tau1_phi_DM10_DOWN = tau1_DM10_down.Phi();
      tau1_m_DM10_DOWN   = tau1_DM10_down.M();
      tau2_pt_DM10_DOWN  = tau2_DM10_down.Pt();
      tau2_eta_DM10_DOWN = tau2_DM10_down.Eta();
      tau2_phi_DM10_DOWN = tau2_DM10_down.Phi();
      tau2_m_DM10_DOWN   = tau2_DM10_down.M();
      // UncMet up
      tau1_pt_UncMet_UP  = tau1_UncMet_up.Pt();
      tau1_eta_UncMet_UP = tau1_UncMet_up.Eta();
      tau1_phi_UncMet_UP = tau1_UncMet_up.Phi();
      tau1_m_UncMet_UP   = tau1_UncMet_up.M();
      tau2_pt_UncMet_UP  = tau2_UncMet_up.Pt();
      tau2_eta_UncMet_UP = tau2_UncMet_up.Eta();
      tau2_phi_UncMet_UP = tau2_UncMet_up.Phi();
      tau2_m_UncMet_UP   = tau2_UncMet_up.M();
      // down
      tau1_pt_UncMet_DOWN  = tau1_UncMet_down.Pt();
      tau1_eta_UncMet_DOWN = tau1_UncMet_down.Eta();
      tau1_phi_UncMet_DOWN = tau1_UncMet_down.Phi();
      tau1_m_UncMet_DOWN   = tau1_UncMet_down.M();
      tau2_pt_UncMet_DOWN  = tau2_UncMet_down.Pt();
      tau2_eta_UncMet_DOWN = tau2_UncMet_down.Eta();
      tau2_phi_UncMet_DOWN = tau2_UncMet_down.Phi();
      tau2_m_UncMet_DOWN   = tau2_UncMet_down.M();
      // UnclusteredMet up
      tau1_pt_ClusteredMet_UP  = tau1_ClusteredMet_up.Pt();
      tau1_eta_ClusteredMet_UP = tau1_ClusteredMet_up.Eta();
      tau1_phi_ClusteredMet_UP = tau1_ClusteredMet_up.Phi();
      tau1_m_ClusteredMet_UP   = tau1_ClusteredMet_up.M();
      tau2_pt_ClusteredMet_UP  = tau2_ClusteredMet_up.Pt();
      tau2_eta_ClusteredMet_UP = tau2_ClusteredMet_up.Eta();
      tau2_phi_ClusteredMet_UP = tau2_ClusteredMet_up.Phi();
      tau2_m_ClusteredMet_UP   = tau2_ClusteredMet_up.M();
      // down
      tau1_pt_ClusteredMet_DOWN  = tau1_ClusteredMet_down.Pt();
      tau1_eta_ClusteredMet_DOWN = tau1_ClusteredMet_down.Eta();
      tau1_phi_ClusteredMet_DOWN = tau1_ClusteredMet_down.Phi();
      tau1_m_ClusteredMet_DOWN   = tau1_ClusteredMet_down.M();
      tau2_pt_ClusteredMet_DOWN  = tau2_ClusteredMet_down.Pt();
      tau2_eta_ClusteredMet_DOWN = tau2_ClusteredMet_down.Eta();
      tau2_phi_ClusteredMet_DOWN = tau2_ClusteredMet_down.Phi();
      tau2_m_ClusteredMet_DOWN   = tau2_ClusteredMet_down.M();

      
      std::cout << "\n\n" << std::endl;
      //std::cout << "\n\nex: " << metcorr_ex << "   ey: " << metcorr_ey <<  " phi: " << metcorphi<<"\n"<<std::endl; 
      newBranch1->Fill();
      newBranch2->Fill();
      newBranch3->Fill();
      newBranch4->Fill();
      newBranch5->Fill();
      newBranch6->Fill();
      newBranch7->Fill();
      newBranch8->Fill();
      newBranch9->Fill();
      newBranch10->Fill();

      newBranch11->Fill();
      newBranch12->Fill();
      newBranch13->Fill();
      newBranch14->Fill();
      newBranch15->Fill();
      newBranch16->Fill();
      newBranch17->Fill();
      newBranch18->Fill();
      newBranch19->Fill();
      newBranch20->Fill();
      newBranch21->Fill();
      newBranch22->Fill();

      newBranch23->Fill();
      newBranch24->Fill();
      newBranch25->Fill();
      newBranch26->Fill();
      newBranch27->Fill();
      newBranch28->Fill();
      newBranch29->Fill();
      newBranch30->Fill();
      newBranch31->Fill();
      newBranch32->Fill();
      newBranch33->Fill();
      newBranch34->Fill();

      newBranch35->Fill();
      newBranch36->Fill();
      newBranch37->Fill();
      newBranch38->Fill();
      newBranch39->Fill();
      newBranch40->Fill();
      newBranch41->Fill();
      newBranch42->Fill();
      newBranch43->Fill();
      newBranch44->Fill();
      newBranch45->Fill();
      newBranch46->Fill();

      newBranch47->Fill();
      newBranch48->Fill();
      newBranch49->Fill();
      newBranch50->Fill();
      newBranch51->Fill();
      newBranch52->Fill();
      newBranch53->Fill();
      newBranch54->Fill();
      newBranch55->Fill();
      newBranch56->Fill();
      newBranch57->Fill();
      newBranch58->Fill();

      newBranch59->Fill();
      newBranch60->Fill();
      newBranch61->Fill();
      newBranch62->Fill();
      newBranch63->Fill();
      newBranch64->Fill();
      newBranch65->Fill();
      newBranch66->Fill();
      newBranch67->Fill();
      newBranch68->Fill();
      newBranch69->Fill();
      newBranch70->Fill();

      newBranch71->Fill();
      newBranch72->Fill();
      newBranch73->Fill();
      newBranch74->Fill();
      newBranch75->Fill();
      newBranch76->Fill();
      newBranch77->Fill();
      newBranch78->Fill();
      newBranch79->Fill();
      newBranch80->Fill();
      newBranch81->Fill();
      newBranch82->Fill();

      newBranch83->Fill();
      newBranch84->Fill();
      newBranch85->Fill();
      newBranch86->Fill();
      newBranch87->Fill();
      newBranch89->Fill();
      newBranch90->Fill();
      newBranch91->Fill();

      for(unsigned int i = 0; i != tau4VectorBranches.size(); ++i)
	(tau4VectorBranches[i])->Fill();
      
      }
      dir->cd();
      t->Write("",TObject::kOverwrite);
      delete  t;
    } // if the iterator of the key is a TTree
  }
}

void runSVFit(std::vector<classic_svFit::MeasuredTauLepton> & measuredTauLeptons, 
	      double measuredMETx, double measuredMETy, TMatrixD &covMET, float num, 
	      float &svFitMass, float& svFitPt, float &svFitEta, float &svFitPhi, float &svFitMET, float &svFitTransverseMass, 
	      TLorentzVector& tau1, TLorentzVector& tau2){

  svfitAlgorithm.integrate(measuredTauLeptons, measuredMETx, measuredMETy, covMET);
  if ( svfitAlgorithm.isValidSolution()) {

    svFitMass = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->getMass();
    svFitPt = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->getPt();
    svFitEta = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->getEta();
    svFitPhi = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->getPhi();
    svFitTransverseMass = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->getTransverseMass();

    classic_svFit::HistogramAdapterTau* h_tau1 = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->tau1();
    classic_svFit::HistogramAdapterTau* h_tau2 = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->tau2();
    const classic_svFit::LorentzVector tau1_p4 = h_tau1->getP4();
    const classic_svFit::LorentzVector tau2_p4 = h_tau2->getP4();
    tau1.SetPtEtaPhiM(tau1_p4.Pt(), tau1_p4.Eta(), tau1_p4.Phi(), tau1_p4.M());
    tau2.SetPtEtaPhiM(tau2_p4.Pt(), tau2_p4.Eta(), tau2_p4.Phi(), tau2_p4.M());

    const classic_svFit::LorentzVector ditau = static_cast<classic_svFit::HistogramAdapterDiTau*>(svfitAlgorithm.getHistogramAdapter())->getP4();
    svFitMET = (ditau - (measuredTauLeptons[0].p4() + measuredTauLeptons[1].p4())).Pt();

    //TLorentzVector testTau1, testTau2;
    //testTau1.SetPtEtaPhiM(measuredTauLeptons[0].p4().Pt(), measuredTauLeptons[0].p4().Eta(), measuredTauLeptons[0].p4().Phi(), measuredTauLeptons[0].p4().M());
    //testTau2.SetPtEtaPhiM(measuredTauLeptons[1].p4().Pt(), measuredTauLeptons[1].p4().Eta(), measuredTauLeptons[1].p4().Phi(), measuredTauLeptons[1].p4().M());

    //TLorentzVector ditau;
    //ditau.SetPtEtaPhiM(svFitPt, svFitEta, svFitPhi, svFitMass);
  }

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

