#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include <iostream>

using std::cout;
using std::endl;

void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev); 


int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("histoName",optutl::CommandLineParser::kString,"Counter Histogram Name","EventSummary");
   parser.addOption("sumHistoName",optutl::CommandLineParser::kString,"Sum Histogram Name","EventSummary");
   parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__WEIGHT__");

   
   parser.parseArguments (argc, argv);
   

 
   TFile *g = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");

   TH1F* evC  = (TH1F*)g->Get(parser.stringValue("histoName").c_str());
   float ev = evC->GetBinContent(1);
   
   TH1F* sumC  = (TH1F*)g->Get(parser.stringValue("sumHistoName").c_str());
   float sumPos = sumC->GetBinContent(2);
   float sumNeg = sumC->GetBinContent(1);

   float evGen =sumPos-sumNeg;
   
   g->Close();
   
   printf("Found  %f Events Counted\n",ev);
   printf("Found  %f Positive NLO Weights Counted\n",sumPos);
   printf("Found  %f Negative NLO Weights Counted\n",sumNeg);
   printf("Weighting by  %f Events\n",evGen);
   
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");   
   
   readdir(f,parser,evGen);

   f->Close();

} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev) 
{
  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
	  printf("Found key=%s \n",key->GetName());
	  TString keyname = key->GetName();
	  if (keyname=="CircJetID_puv2"||keyname=="sumweights"){
		  printf("Skipping key %s . Not weighting. \n",key->GetName());
		  continue;
	  }

	  TObject *obj = key->ReadObj();

	  if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
		  dir->cd(key->GetName());
		  TDirectory *subdir = gDirectory;
		  readdir(subdir,parser,ev);
		  dirsav->cd();
	  }
	  else if(obj->IsA()->InheritsFrom(TTree::Class())) {
		  float weight = parser.doubleValue("weight")/(ev);

		  TTree *t = (TTree*)obj;
		  TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
		  printf("Found tree -> weighting\n");
		  for(Int_t i=0;i<t->GetEntries();++i)
		  {
			  t->GetEntry(i);
			  weight = parser.doubleValue("weight")/(ev);
			  newBranch->Fill();
		  }
		  t->Write("",TObject::kOverwrite);
	  }//end else if object A
  }//end while key
}//end read directory
