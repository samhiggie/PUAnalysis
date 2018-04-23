#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFileMerger.h"


std::vector<float> data;
std::vector<float> mc;

void readdir(TDirectory *dir,optutl::CommandLineParser parser,std::vector<float> ev); 



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("histoName",optutl::CommandLineParser::kString,"Counter Histogram Name","EventSummary");
   parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__WEIGHT__");

   
   parser.parseArguments (argc, argv);
   

   

 
   TFile *w = new TFile("WJetsMLM.root","UPDATE");

   TH1F* evC  = (TH1F*)w->Get(parser.stringValue("histoName").c_str());
   float evW = evC->GetBinContent(1);
   
   w->Close();
  
   TFile *w1 = new TFile("W1Jets.root","UPDATE");

   TH1F* evC1  = (TH1F*)w1->Get(parser.stringValue("histoName").c_str());
   float evW1 = evC1->GetBinContent(1);
   
   w1->Close();   

   TFile *w2 = new TFile("W2Jets.root","UPDATE");

   TH1F* evC2  = (TH1F*)w2->Get(parser.stringValue("histoName").c_str());
   float evW2 = evC2->GetBinContent(1);
   
   w2->Close();

   TFile *w3 = new TFile("W3Jets.root","UPDATE");

   TH1F* evC3  = (TH1F*)w3->Get(parser.stringValue("histoName").c_str());
   float evW3 = evC3->GetBinContent(1);
   
   w3->Close();

   TFile *w4 = new TFile("W4Jets.root","UPDATE");

   TH1F* evC4  = (TH1F*)w4->Get(parser.stringValue("histoName").c_str());
   float evW4 = evC4->GetBinContent(1);
   
   w4->Close();
 
     
   printf("Found  %f W Events\n",evW);
   printf("Found  %f W+1Jet Events\n",evW1);
   printf("Found  %f W+2Jet Events\n",evW2);
   printf("Found  %f W+3Jet Events\n",evW3);
   printf("Found  %f W+4Jet Events\n",evW4);
  
   double LOtoNNLO=61526.7/50380;

   double WLo=evW/(LOtoNNLO*50380.0);
   double WLo1=evW1/(LOtoNNLO*9644.5);
   double WLo2=evW2/(LOtoNNLO*3144.5);
   double WLo3=evW3/(LOtoNNLO*954.8);
   double WLo4=evW4/(LOtoNNLO*485.6);

 
   std::vector<float> ev;
   ev.push_back(WLo);
   ev.push_back(WLo1);
   ev.push_back(WLo2);
   ev.push_back(WLo3);
   ev.push_back(WLo4);
   printf("Found  %f  0 Jet Weight \n",1/ev[0]);
   printf("Found  %f W+1Jet Weight\n",1/(ev[0]+ev[1]));
   printf("Found  %f W+2Jet Weight\n",1/(ev[0]+ev[2]));
   printf("Found  %f W+3Jet Weight\n",1/(ev[0]+ev[3]));
   printf("Found  %f W+4Jet Weight\n",1/(ev[0]+ev[4]));
   

   TFile *f0 = new TFile("WJetsMLM.root","UPDATE");   
   readdir(f0,parser,ev);
   f0->Close();
   
   TFile *f1 = new TFile("W1Jets.root","UPDATE");   
   readdir(f1,parser,ev);
   f1->Close();
   
   TFile *f2 = new TFile("W2Jets.root","UPDATE");   
   readdir(f2,parser,ev);
   f2->Close();
   
   TFile *f3 = new TFile("W3Jets.root","UPDATE");   
   readdir(f3,parser,ev);
   f3->Close();
   
   TFile *f4 = new TFile("W4Jets.root","UPDATE");   
   readdir(f4,parser,ev);
   f4->Close();

  } 


void readdir(TDirectory *dir,optutl::CommandLineParser parser,std::vector<float> ev) 
{
  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    printf("Found key=%s \n",key->GetName());
    TObject *obj = key->ReadObj();

    if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      readdir(subdir,parser,ev);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float weight;

      TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
      int LHEProduct=0;
      t->SetBranchAddress("LHEProduct_njet",&LHEProduct); //NJets

      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i){
	  t->GetEntry(i);

	  if(LHEProduct==0)
	  	weight = parser.doubleValue("weight")/(ev[0]);
	  else if(LHEProduct==1)
	  	weight = parser.doubleValue("weight")/(ev[0]+ev[1]);
	  else if(LHEProduct==2)
	  	weight = parser.doubleValue("weight")/(ev[0]+ev[2]);
	  else if(LHEProduct==3)
	  	weight = parser.doubleValue("weight")/(ev[0]+ev[3]);
	  else if(LHEProduct==4)
	  	weight = parser.doubleValue("weight")/(ev[0]+ev[4]);
	  	
	  newBranch->Fill();
	}
      t->Write("",TObject::kOverwrite);
    }



  }

}
