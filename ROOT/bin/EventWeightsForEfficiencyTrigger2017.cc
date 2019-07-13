#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
//#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h"
#include "PUAnalysis/TauTriggerSFs2017/interface/TauTriggerSFs2017.h"
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include <math.h> 
#include "TMath.h" 
#include <limits>


double efficiency(double m, double m0, double sigma, double alpha, double n, double norm)
 { 
   //std::cout<<"efficiency m: "<<m<<" m0: "<<m0<<" sigma: "<<sigma<<" alpha: "<<alpha<<" n: "<<n<<" norm: "<<norm<<std::endl;

   const double sqrtPiOver2 = 1.2533141373;
   const double sqrt2 = 1.4142135624;

   double sig = fabs((double) sigma);
   
   double t = (m - m0)/sig;
   
   if (alpha < 0)
     t = -t;

   double absAlpha = fabs(alpha / sig);
   double a = TMath::Power(n/absAlpha,n)*exp(-0.5*absAlpha*absAlpha);
   double b = absAlpha - n/absAlpha;
   double arg = absAlpha / sqrt2 ;

   //   if (a>=std::numeric_limits<double>::max()) return -1. ;

   double ApproxErf ;

   if (arg > 5.) ApproxErf = 1 ;
   else if (arg < -5.) ApproxErf = -1 ;
   else ApproxErf = TMath::Erf(arg) ;

   double leftArea = (1 + ApproxErf) * sqrtPiOver2 ;
   double rightArea = ( a * 1/TMath::Power(absAlpha - b,n-1)) / (n - 1);
   double area = leftArea + rightArea;

   if ( t <= absAlpha ){
     arg = t / sqrt2 ;
     if (arg > 5.) ApproxErf = 1 ;
     else if (arg < -5.) ApproxErf = -1 ;
     else ApproxErf = TMath::Erf(arg) ;
     return norm * (1 + ApproxErf) * sqrtPiOver2 / area ;
   }
   else{
     return norm * (leftArea +  a * (1/TMath::Power(t-b,n-1) - 1/TMath::Power(absAlpha - b,n-1)) / (1 - n)) / area ;
   }
 }


void readdir(TDirectory *dir,optutl::CommandLineParser parser,char TreeToUse[]); 



int main (int argc, char* argv[]) 
{

   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__CORR__");
   parser.parseArguments (argc, argv);
   std::cout<<std::endl;
   std::cout<<"weighting file: "<<parser.stringValue("outputFile").c_str() <<std::endl;   

   char TreeToUse[80]="first" ;
   
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");
   readdir(f,parser,TreeToUse);
   f->Close();

} 


void readdir(TDirectory *dir, optutl::CommandLineParser parser, char TreeToUse[]) 
{
  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  char stringA[80]="first";
  
  while ((key = (TKey*)next())) {
  
	printf("Found key=%s \n",key->GetName());
	if(!strcmp(stringA,TreeToUse)) sprintf(TreeToUse,"%s",key->GetName());
	printf("Strings %s %s \n",TreeToUse,stringA);
	TObject *obj = key->ReadObj();

    if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      readdir(subdir,parser,TreeToUse);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float weight_1 = 1.0;
      float weight_2 = 1.0;
      float weight = 1.0;
      float zPtWeight;
      float XSecLumiWeight;
      //float svFit;
      //float Higgs_Pt;
      //float m_sv;
      //float pt_sv;

      TBranch *newBranch     = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
      TBranch *newBranchLeg1 = t->Branch("trigweight_1",&weight_1,"trigweight_1/F");
      TBranch *newBranchLeg2 = t->Branch("trigweight_2",&weight_2,"trigweight_2/F");
      TBranch *newBranchZPt   = t->Branch("zPtWeight",&zPtWeight,"zPtWeight/F");
      TBranch *newBranchZXsec = t->Branch("XSecLumiWeight",&XSecLumiWeight,"XSecLumiWeight/F");
      //TBranch *newBranchm_sv  = t->Branch("m_sv",&svFit,"m_sv/F");
      //TBranch *newBranchpt_sv = t->Branch("pt_sv",&Higgs_Pt,"pt_sv/F");

      float pt1;
      float eta1;
      float phi1;
      float isoLoose1;
      float isoVLoose1;
      float isoMed1;
      float isoTight1;
      float isoVTight1;
      float pt2;
      float eta2;
      float phi2;
      float isoVLoose2;
      float isoLoose2;
      float isoMed2;
      float isoTight2;
      float isoVTight2;
      float gen_match_1;
      float gen_match_2;

      t->SetBranchAddress("pt_1",&pt1);
      t->SetBranchAddress("eta_1",&eta1);
      t->SetBranchAddress("phi_1",&phi1);
      t->SetBranchAddress("isoVLoose_1",&isoVLoose1);
      t->SetBranchAddress("isoLoose_1",&isoLoose1);
      t->SetBranchAddress("isoMed_1",&isoMed1);
      t->SetBranchAddress("isoTight_1",&isoTight1);
      t->SetBranchAddress("isoVTight_1",&isoVTight1);
      //t->SetBranchAddress("svFit",&svFit);
      //t->SetBranchAddress("Higgs_Pt",&Higgs_Pt);
      

      t->SetBranchAddress("pt_2",&pt2);
      t->SetBranchAddress("eta_2",&eta2);
      t->SetBranchAddress("phi_2",&phi2);
      t->SetBranchAddress("isoVLoose_2",&isoVLoose2);
      t->SetBranchAddress("isoLoose_2",&isoLoose2);
      t->SetBranchAddress("isoMed_2",&isoMed2);
      t->SetBranchAddress("isoTight_2",&isoTight2);
      t->SetBranchAddress("isoVTight_2",&isoVTight2);

      t->SetBranchAddress("__WEIGHT__",&XSecLumiWeight);
      //t->SetBranchAddress("__ZWEIGHT__",&zPtWeight);

      t->SetBranchAddress("gen_match_1",&gen_match_1);
      t->SetBranchAddress("gen_match_2",&gen_match_2);

      int n = 0;
      
      // Short alias for this namespace
      namespace pt = boost::property_tree;

      // Create a root
      pt::ptree root;
      pt::ptree rootFakes;

      std::string cmssw = std::getenv("CMSSW_BASE");
      std::cout<<"cmssw area: "<<cmssw<<std::endl;

      // first read in the json file 
      //pt::read_json("/data/ojalvo/Htt_80X/CMSSW_8_0_20/src/UWAnalysis/ROOT/bin/triggerJSONs/triggerSF/di-tau/real_taus_binned.json", root);
      //pt::read_json("/data/ojalvo/Htt_80X/CMSSW_8_0_20/src/UWAnalysis/ROOT/bin/triggerJSONs/triggerSF/di-tau/same_sign_binned.json", rootFakes);
      std::string inFile = cmssw+"/src/PUAnalysis/TauTriggerSFs2017/data/tauTriggerEfficiencies2017.root";
      std::string inFileNew = cmssw+"/src/PUAnalysis/TauTriggerSFs2017/data/tauTriggerEfficiencies2017_New.root";

      TauTriggerSFs2017 tauTriggerSFsVTight(inFileNew, inFile, "vtight", "MVA");
      TauTriggerSFs2017 tauTriggerSFsTight(inFileNew,  inFile, "tight", "MVA");
      TauTriggerSFs2017 tauTriggerSFsMedium(inFileNew, inFile, "medium", "MVA");
      TauTriggerSFs2017 tauTriggerSFsLoose(inFileNew,  inFile, "loose", "MVA");
      TauTriggerSFs2017 tauTriggerSFsVLoose(inFileNew, inFile, "vloose", "MVA");
      //diTau_tight_MC
      //
      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i)
	{
	  t->GetEntry(i);
	  weight_1=1.0;
	  weight_2=1.0;
	  weight = 1.0;

	  if(isoVTight1 > 0.5)//iso v tight
	    weight_1 = tauTriggerSFsVTight.getDiTauScaleFactor(pt1, eta1, phi1);
	  else if(isoTight1 > 0.5)
	    weight_1 = tauTriggerSFsTight.getDiTauScaleFactor(pt1, eta1, phi1);
	  else if(isoMed1 > 0.5)
	    weight_1 = tauTriggerSFsMedium.getDiTauScaleFactor(pt1, eta1, phi1);
	  else if(isoLoose1 > 0.5)
	    weight_1 = tauTriggerSFsLoose.getDiTauScaleFactor(pt1, eta1, phi1);
	  else if(isoVLoose1 > 0.5)
	    weight_1 = tauTriggerSFsVLoose.getDiTauScaleFactor(pt1, eta1, phi1);

	  if(isoVTight2 > 0.5)//iso v tight
	    weight_2 = tauTriggerSFsVTight.getDiTauScaleFactor(pt2, eta2, phi2);
	  else if(isoTight2 > 0.5)
	    weight_2 = tauTriggerSFsTight.getDiTauScaleFactor(pt2, eta2, phi2);
	  else if(isoMed2 > 0.5)
	    weight_2 = tauTriggerSFsMedium.getDiTauScaleFactor(pt2, eta2, phi2);
	  else if(isoLoose2 > 0.5)
	    weight_2 = tauTriggerSFsLoose.getDiTauScaleFactor(pt2, eta2, phi2);
	  else if(isoVLoose2 > 0.5)
	    weight_2 = tauTriggerSFsVLoose.getDiTauScaleFactor(pt2, eta2, phi2);

	  weight = weight_1*weight_2;
	  dirsav->cd();

	  //if(weight>1 || weight_1 > 1 || weight_2 > 1 || weight==0){
	  //if(n<20){
	  //std::cout<<"something looks fishy...  weight: "<<weight<<" weight_1: "<<weight_1<<" weight_2: "<<weight_2<<std::endl;
	  //n++;
	  //}

	  //if(n>20)
	  //exit(0);
	  newBranch->Fill();     
	  newBranchLeg1->Fill(); 
	  newBranchLeg2->Fill(); 
	  newBranchZPt->Fill();  
	  newBranchZXsec->Fill();
	  newBranch->Fill();
	  //newBranchm_sv->Fill();
	  //newBranchpt_sv->Fill();
	}

	t->Write("",TObject::kOverwrite);
	strcpy(TreeToUse,stringA) ;
    }
  }
}


/*
//VTightIso
        "m_{0}": 38.63953827612661, 
        "sigma":  7.389378523494392, 
        "alpha": 11.190558467918098, 
        "n":      1.6373712046498128
        "norm":   0.818539785184176, 
38.6395, 7.3893, 11.1905, 1.6373, 0.8185,
 */

/*
//NoIso
        "m_{0}": 44.61974911191058, 
        "sigma":  8.823024805816253, 
        "alpha": 11.841403541663073, 
        "n":      1.2807865720447276
        "norm":   0.9999999986555769, 
44.6197, 8.8230, 11.8414, 1.2807, 0.9999
 */
