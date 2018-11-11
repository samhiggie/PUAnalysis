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
   

   

 
   //TFile *w = new TFile("ZJets.root","UPDATE");
   TFile *w = new TFile("ZJets.root","UPDATE");

   TH1F* evC  = (TH1F*)w->Get(parser.stringValue("histoName").c_str());
   float evW = evC->GetBinContent(1);
   
   w->Close();
  
   TFile *w1 = new TFile("Z1Jets.root","UPDATE");
   TH1F* evC1  = (TH1F*)w1->Get(parser.stringValue("histoName").c_str());
   float evW1 = evC1->GetBinContent(1);
   w1->Close();   

   TFile *w2 = new TFile("Z2Jets.root","UPDATE");

   TH1F* evC2  = (TH1F*)w2->Get(parser.stringValue("histoName").c_str());
   float evW2 = evC2->GetBinContent(1);
   
   w2->Close();

   TFile *w3 = new TFile("Z3Jets.root","UPDATE");

   TH1F* evC3  = (TH1F*)w3->Get(parser.stringValue("histoName").c_str());
   float evW3 = evC3->GetBinContent(1);
   
   w3->Close();
   
   TFile *w4 = new TFile("Z4Jets.root","UPDATE");

   TH1F* evC4  = (TH1F*)w4->Get(parser.stringValue("histoName").c_str());
   float evW4 = evC4->GetBinContent(1);
   w4->Close();
   
   //TFile *w5 = new TFile("ZJets_150.root","UPDATE");

   //TH1F* evC5  = (TH1F*)w5->Get(parser.stringValue("histoName").c_str());
   //float evW5 = evC5->GetBinContent(1);
   
   //w5->Close();
     
   printf("Found  %f Z Events\n",evW);
   printf("Found  %f Z+1Jet Events\n",evW1);
   printf("Found  %f Z+2Jet Events\n",evW2);
   printf("Found  %f Z+3Jet Events\n",evW3);
   printf("Found  %f Z+4Jet Events\n",evW4);
   //printf("Found  %f Z >150GeV Jet Events\n",evW5);
  
   double LOtoNNLO=6225.42/5343.0;

   double DYLo=evW/(LOtoNNLO*5343.0);
   double DYLo1=evW1/(LOtoNNLO*877.8);
   double DYLo2=evW2/(LOtoNNLO*304.4);
   double DYLo3=evW3/(LOtoNNLO*111.5);
   double DYLo4=evW4/(LOtoNNLO*44.03);
   //double DYLo5=evW5/(LOtoNNLO*6.7);
 
   std::vector<float> ev;
   ev.push_back(DYLo);
   ev.push_back(DYLo1);
   ev.push_back(DYLo2);
   ev.push_back(DYLo3);
   ev.push_back(DYLo4);
   //ev.push_back(DYLo5);
   
   TFile *f0 = new TFile("ZJets.root","UPDATE");   
   //TFile *f0 = new TFile("ZJets.root","UPDATE");   
   readdir(f0,parser,ev);
   f0->Close();
   
   TFile *f1 = new TFile("Z1Jets.root","UPDATE");   
   readdir(f1,parser,ev);
   f1->Close();
   
   TFile *f2 = new TFile("Z2Jets.root","UPDATE");   
   readdir(f2,parser,ev);
   f2->Close();
   
   TFile *f3 = new TFile("Z3Jets.root","UPDATE");   
   readdir(f3,parser,ev);
   f3->Close();
   
   //TFile *f4 = new TFile("Z4Jets.root","UPDATE");   
   //readdir(f4,parser,ev);
   //f4->Close();
 
   //TFile *f5 = new TFile("ZJets_150.root","UPDATE");   
   //readdir(f5,parser,ev);
   //f5->Close();

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
      int mLL=0;
      t->SetBranchAddress("LHEProduct_njet",&LHEProduct); //NJets
      t->SetBranchAddress("LHEProduct_mll",&mLL); //InvMass

      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i){
	      t->GetEntry(i);
	      if (mLL<150){
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
		      else 
			      weight = parser.doubleValue("weight")/(ev[0]);
	      }
	      else if (mLL>150){
		      if(LHEProduct==0)
			      weight = parser.doubleValue("weight")/(ev[0]+ev[5]);
		      else if(LHEProduct==1)
			      weight = parser.doubleValue("weight")/(ev[0]+ev[1]+ev[5]);
		      else if(LHEProduct==2)
			      weight = parser.doubleValue("weight")/(ev[0]+ev[2]+ev[5]);
		      else if(LHEProduct==3)
			      weight = parser.doubleValue("weight")/(ev[0]+ev[3]+ev[5]);
		      else if(LHEProduct==4)
			      weight = parser.doubleValue("weight")/(ev[0]+ev[4]+ev[5]);
		      else
			      weight = parser.doubleValue("weight")/(ev[0]+ev[5]);

	      }

	      newBranch->Fill();
      }
      t->Write("",TObject::kOverwrite);
    }



  }

}
