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

void readdir(TDirectory *dir,optutl::CommandLineParser parser,TH1F* mchist,TH1F* datahist); 


int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets PileUp Event Weights in the ntuple");
   parser.addOption("dataset",optutl::CommandLineParser::kString,"dataset","dataset");
   parser.addOption("mcfile",optutl::CommandLineParser::kString,"data_pileup_pudistributions_mc_2017.root","data_pileup_pudistributions_mc_2017.root");
   parser.addOption("datafile",optutl::CommandLineParser::kString,"data_pileup_pudistributions_data_2017.root","data_pileup_pudistributions_data_2017.root");
   parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","PUWeight");

   
   parser.parseArguments (argc, argv);
   

 
   //TFile *p = new TFile(parser.stringValue("inputFile").c_str(),"READ");
   TFile *pm = new TFile(parser.stringValue("mcfile").c_str(),"READ");
   TFile *pd = new TFile(parser.stringValue("datafile").c_str(),"READ");
   TH1F* pileUpMC  = (TH1F*)pm->Get(parser.stringValue("dataset").c_str());
   TH1F* pileUpData  = (TH1F*)pd->Get("pileup");
   //float ev = evC->GetBinContent(1);
   
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");   
   
   readdir(f,parser,pileUpMC,pileUpData);

   f->Close();
   pm->Close();
   pd->Close();

} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser,TH1F* pileUpMC,TH1F* pileUpData) 
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
		  readdir(subdir,parser,pileUpMC,pileUpData);
		  dirsav->cd();
	  }
	  else if(obj->IsA()->InheritsFrom(TTree::Class())) {
		  float weight = parser.doubleValue("weight");
          //float weight;
          int npv;
          //TBranch *b_npv;
          float eventsMC;
          float sumOfWeightsMC;
          float eventsData;
          float sumOfWeightsData;
          int binMC;

          sumOfWeightsMC = pileUpMC->GetSumOfWeights();
          sumOfWeightsData = pileUpData->GetSumOfWeights();
		  TTree *t = (TTree*)obj;
          t->SetBranchAddress("npv", &npv);
		  TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
		  printf("Found tree -> weighting\n");
		  for(Int_t i=0;i<t->GetEntries();++i)
		  {
			  t->GetEntry(i);
			  //weight = parser.doubleValue("weight")/(ev);
              binMC = pileUpMC->FindBin(npv);
              eventsMC = (pileUpMC->GetBinContent(binMC))/sumOfWeightsMC;
              eventsData = (pileUpData->GetBinContent(binMC))/sumOfWeightsData;
              if(eventsMC>0){
			    weight = eventsData/eventsMC;
              }
              else{
                weight = 0.0;
              }
              if(i%100==0){
                  std::cout<<"Number of primary verticies "<<npv<<std::endl;
                  std::cout<<"Bin "<<binMC<<std::endl;
                  std::cout<<"Number of events in MC "<<eventsMC<<std::endl;
                  std::cout<<"Number of events in Data "<<eventsData<<std::endl;
                  std::cout<<"PUweight   "<<weight<<std::endl;
                }
			    newBranch->Fill();
		  }
		  t->Write("",TObject::kOverwrite);
	  }//end else if object A
  }//end while key
}//end read directory
