// Author: Rene Brun

#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

//Example of script showing how to copy all objects (including directories)
//from a source file.
//For each input file, a new directory is created in the current directory
//with the name of the source file.
//After execution of:
// root > .x copyFiles.C
//the file result.root will contain 4 subdirectories:
// "tot100.root", "hsimple.root", "hs1.root","hs2.root"

void CopyDir(TDirectory *source) {
  //copy all objects and subdirs of directory source as a subdir of the current directory
  source->ls();
  TDirectory *savdir = gDirectory;
  TKey *key;
  TIter nextkey(source->GetListOfKeys());
  
  int len = strlen(source->GetName());
  const char *last_five = &source->GetName()[len-5];


  TDirectory *adir;
  //check to see if we're at the top level .root directory, if yes, then do not create this directory.
  if(strcmp(last_five,".root")!=0){
    //std::cout<<"-----------------last_five not equal to .root, last_five:  "<<last_five<<std::endl;
    adir = savdir->mkdir(source->GetName());
    adir->cd();
  }
  else{
    adir=savdir;
  }

  //loop on all entries of this directory
  
  while ((key = (TKey*)nextkey())) {
    
    const char *classname = key->GetClassName();
    TClass *cl = gROOT->GetClass(classname);
    if (!cl) continue;
    if (cl->InheritsFrom(TDirectory::Class())) {
      source->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      adir->cd();
      CopyDir(subdir);
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
void CopyFile(const char *fname) {
  //Copy all objects and subdirs of file fname as a subdir of the current directory
  TDirectory *target = gDirectory;
  TFile *f = TFile::Open(fname);
  if (!f || f->IsZombie()) {
    printf("Cannot copy file: %s\n",fname);
    target->cd();
    return;
  }
  target->cd();
  CopyDir(f);
  delete f;
  target->cd();
}
void copyFiles() {
  //prepare files to be copied

  //main function copying 4 files as subdirectories of a new file

  //resulting directory
  TFile *f = new TFile("htt_tt.inputs-sm-13TeV-2D.root","recreate");
  //input directory
  CopyFile("tauTautt_0jet_m_vis.root");
  CopyFile("tauTautt_boosted_msv_fullPt.root");
  CopyFile("tauTautt_vbf_msv_mjj.root");
  //put as many input directories as you like, we simply grab the contents and put them into results.root
  //CopyFile("htt_et.inputs-sm-13TeV-m_vis.root");

  f->ls();
  delete f;
}
//
  
 
  
 

