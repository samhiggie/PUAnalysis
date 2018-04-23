#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFileMerger.h"


std::vector<float> data;
std::vector<float> mc;

void readdir(TDirectory *dir,optutl::CommandLineParser parser,std::vector<float> ev,int type); 



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
  
   TFile *w1 = new TFile("WJetsHT200.root","UPDATE");
   TH1F* evC1  = (TH1F*)w1->Get(parser.stringValue("histoName").c_str());
   float evW1 = evC1->GetBinContent(1);
   w1->Close();   

   TFile *w2 = new TFile("WJetsHT400.root","UPDATE");
   TH1F* evC2  = (TH1F*)w2->Get(parser.stringValue("histoName").c_str());
   float evW2 = evC2->GetBinContent(1);
   w2->Close();

   TFile *w3 = new TFile("WJetsHT600.root","UPDATE");
   TH1F* evC3  = (TH1F*)w3->Get(parser.stringValue("histoName").c_str());
   float evW3 = evC3->GetBinContent(1);
   w3->Close();

   TFile *w4 = new TFile("WJetsHT800.root","UPDATE");
   TH1F* evC4  = (TH1F*)w4->Get(parser.stringValue("histoName").c_str());
   float evW4 = evC4->GetBinContent(1);
   w4->Close();

   TFile *w5 = new TFile("WJetsHT1200.root","UPDATE");
   TH1F* evC5  = (TH1F*)w5->Get(parser.stringValue("histoName").c_str());
   float evW5 = evC5->GetBinContent(1);
   w5->Close();
 
   TFile *w6 = new TFile("WJetsHT2500.root","UPDATE");
   TH1F* evC6  = (TH1F*)w6->Get(parser.stringValue("histoName").c_str());
   float evW6 = evC6->GetBinContent(1);
   w6->Close();
  
   TFile *w7 = new TFile("WJetsHTInf.root","UPDATE");
   TH1F* evC7  = (TH1F*)w7->Get(parser.stringValue("histoName").c_str());
   float evW7 = evC7->GetBinContent(1);
   w7->Close();
 
     
   printf("Found  %f W Events\n",evW);
   printf("Found  %f WJet HT200 Events\n",evW1);
   printf("Found  %f WJet HT400 Events\n",evW2);
   printf("Found  %f WJet HT600 Events\n",evW3);
   printf("Found  %f WJet HT800 Events\n",evW4);
   printf("Found  %f WJet HT1200 Events\n",evW5);
   printf("Found  %f WJet HT2500 Events\n",evW6);
   printf("Found  %f WJet HTInf Events\n",evW7);
  
   double LOtoNNLO=61526.7/50270;

   double WLo=evW/(LOtoNNLO*50270.0);
   double WLo1=evW1/(LOtoNNLO*1345);
   double WLo2=evW2/(LOtoNNLO*359.7);
   double WLo3=evW3/(LOtoNNLO*48.91);
   double WLo4=evW4/(LOtoNNLO*12.04);
   double WLo5=evW4/(LOtoNNLO*5.52);
   double WLo6=evW4/(LOtoNNLO*1.33);
   double WLo7=evW4/(LOtoNNLO*0.0322);

 
   std::vector<float> ev;
   ev.push_back(WLo);
   ev.push_back(WLo1);
   ev.push_back(WLo2);
   ev.push_back(WLo3);
   ev.push_back(WLo4);
   ev.push_back(WLo5);
   ev.push_back(WLo6);
   ev.push_back(WLo7);
   printf("Found  %f  Inclu Weight \n",1/ev[0]);
   printf("Found  %f WJet HT200 Weight\n",1/(ev[1]));
   printf("Found  %f WJet HT400 Weight\n",1/(ev[2]));
   printf("Found  %f WJet HT600 Weight\n",1/(ev[3]));
   printf("Found  %f WJet HT800 Weight\n",1/(ev[4]));
   printf("Found  %f WJet HT1200 Weight\n",1/(ev[5]));
   printf("Found  %f WJet HT2500 Weight\n",1/(ev[6]));
   printf("Found  %f WJet HTInf Weight\n",1/(ev[7]));
   

   TFile *f0 = new TFile("WJetsMLM.root","UPDATE");   
   readdir(f0,parser,ev,0);
   f0->Close();
   
   TFile *f1 = new TFile("WJetsHT200.root","UPDATE");   
   readdir(f1,parser,ev,1);
   f1->Close();
   
   TFile *f2 = new TFile("WJetsHT400.root","UPDATE");   
   readdir(f2,parser,ev,2);
   f2->Close();
   
   TFile *f3 = new TFile("WJetsHT600.root","UPDATE");   
   readdir(f3,parser,ev,3);
   f3->Close();
   
   TFile *f4 = new TFile("WJetsHT800.root","UPDATE");   
   readdir(f4,parser,ev,4);
   f4->Close();

   TFile *f5 = new TFile("WJetsHT1200.root","UPDATE");   
   readdir(f5,parser,ev,5);
   f5->Close();

   TFile *f6 = new TFile("WJetsHT2500.root","UPDATE");   
   readdir(f6,parser,ev,6);
   f6->Close();

   TFile *f7 = new TFile("WJetsHTInf.root","UPDATE");   
   readdir(f7,parser,ev,7);
   f7->Close();




  } 


void readdir(TDirectory *dir,optutl::CommandLineParser parser,std::vector<float> ev, int type) 
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
      readdir(subdir,parser,ev,type);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float weight;

      TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
      printf("Found tree -> weighting\n");
      float LHEProduct=0;
      t->SetBranchAddress("LHEProduct_ht",&LHEProduct); //GenHT 


      for(Int_t i=0;i<t->GetEntries();++i){
          t->GetEntry(i);

          if(type==0){ //only look inclsuive<100
              if (LHEProduct>100) weight = 0;
              else weight = parser.doubleValue("weight")/(ev[0]);
          }
          else if(type==1)
              weight = parser.doubleValue("weight")/(ev[1]);
          else if(type==2)
              weight = parser.doubleValue("weight")/(ev[2]);
          else if(type==3)
              weight = parser.doubleValue("weight")/(ev[3]);
          else if(type==4)
              weight = parser.doubleValue("weight")/(ev[4]);
          else if(type==5)
              weight = parser.doubleValue("weight")/(ev[5]);
          else if(type==6)
              weight = parser.doubleValue("weight")/(ev[6]);
          else if(type==7)
              weight = parser.doubleValue("weight")/(ev[7]);


          newBranch->Fill();
      }
      t->Write("",TObject::kOverwrite);
    }



  }

}
