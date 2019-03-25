#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TMath.h"
#include "TFileMerger.h"



void readdir(TDirectory *dir,optutl::CommandLineParser parser,TH2D* hist); 



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("histoName",optutl::CommandLineParser::kString,"Counter Histogram Name","EventSummary");
   parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__ZWEIGHT__");

   
   parser.parseArguments (argc, argv);
   
   
 
   //TFile *fZpt    = new TFile("zpt_weights_2016.root","UPDATE");
   TFile *fZpt    = new TFile("htt_scalefactors_2017_v2.root","UPDATE");
   TH2D* hZpt = 0;
   if(fZpt!=0 && fZpt->IsOpen()) {
     hZpt = (TH2D*)fZpt->Get("zptmass_histo");;
     printf("ENABLING Z WEIGHTING USING HISTOGRAM\n");
   }
   else{
     printf("ERROR!!! WEIGHT FILE NOT FOUND!!! EXITING!!!\n");
     return 0;
   }
 
 
   TFile *f0 = new TFile("ZJETS.root","UPDATE");   
   readdir(f0,parser,hZpt);
   f0->Close();

   if(fZpt!=0 && fZpt->IsOpen())
     fZpt->Close();


} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser, TH2D* hist) 
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
			readdir(subdir,parser,hist);
			dirsav->cd();
		}
		else if(obj->IsA()->InheritsFrom(TTree::Class())) {
			TTree *t = (TTree*)obj;
			float weight;
			float weight2;
			float weight3;
			float weight4;

			TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
			TBranch *newBranch2 = t->Branch("highTauEffi",&weight2,"highTauEffi/F");
			TBranch *newBranch3 = t->Branch("EleTauFake",&weight3,"EleTauFake/F");
			TBranch *newBranch4 = t->Branch("MuTauFake",&weight4,"MuTauFake/F");
			
			int mLL=0;
			float genPx=0;
			float genPy=0;
			float genTauPt=0;
			float TauEta=0;


			t->SetBranchAddress("LHEProduct_mll",&mLL); //InvMass
			t->SetBranchAddress("genpX",&genPx); //genPx
			t->SetBranchAddress("genpY",&genPy); //genPy
			t->SetBranchAddress("genPt2",&genTauPt); //genPy
			t->SetBranchAddress("eta_2",&TauEta); //genPy


			printf("Found tree -> weighting\n");
			for(Int_t i=0;i<t->GetEntries();++i){
				t->GetEntry(i);
				float genPt = TMath::Sqrt(genPx*genPx+genPy*genPy);
				//printf("Found genPt -> %f,\n",genPt);
                weight =  1.0;
                weight = hist->GetBinContent(hist->GetXaxis()->FindBin(mLL),hist->GetYaxis()->FindBin(genPt));
				//printf("Found Zweight -> %f,\n",weight);
				weight2 = 0.2 * genTauPt/1000.; 
                if (std::abs(TauEta)<1.460)  weight3=1.8;
                else  weight3=1.3;
                
                if (std::abs(TauEta)<1.2)  weight4=1.28;
                else if (std::abs(TauEta)<1.7)  weight4=2.6;
                else if (std::abs(TauEta)<2.3)  weight4=2.1;

				newBranch->Fill();
				newBranch2->Fill();
				newBranch3->Fill();
				newBranch4->Fill();
			}
			t->Write("",TObject::kOverwrite);
		}



	}

}
