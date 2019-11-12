#include <string>
#include <vector>
#include <limits>

#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TCut.h"
#include "TSystem.h"
#include "TFileMerger.h"

#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"

//global variables 
TFile *histfile = new TFile("FakeFactorHistograms.root","RECREATE");

void makeHistograms(TString inputPath, std::string channel_, TString luminosity);
std::vector<float> getFFractions(float m_vis_val, float njets_val);
std::pair<int,int> findBin(std::string histname,float m_vis,float njets);
void copyFiles( optutl::CommandLineParser parser, TFile* fOld, TFile* fNew) ;
void readdir(TDirectory *dir, optutl::CommandLineParser parser,  char TreeToUse[]) ;
void CopyFile(const char *fname, optutl::CommandLineParser parser);
void CopyDir(TDirectory *source,optutl::CommandLineParser parser);


int main (int argc, char* argv[]) 
{
    optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
    parser.addOption("inputDirectory",optutl::CommandLineParser::kString,"Where input files are located - must include data,TT,WJets,Zjets, and Diboson");
 
    parser.parseArguments (argc, argv);

    std::cout << "Input commands:" 
        << "\n -- input file: " << parser.stringValue("inputDirectory");


    char TreeToUse[80]="first";

    TFile *fProduce;//= new TFile(parser.stringValue("newFile").c_str(),"UPDATE");
    
    //Drawing the histograms for the FF method
    //std::string channel = "diTau";
    std::string channel = "muTau";
    //std::string inputPath = "/hdfs/store/user/samuellh/HTT_2018_Oct23_corr_skimmed/";
    TString inputPath = "/scratch/samuellh/muTau_2019/";
    if(parser.stringValue("inputDirectory")>0){
        inputPath = parser.stringValue("inputDirectory").c_str();
    }
    makeHistograms(inputPath,channel,"59740.0");//last number is lumi in pb
    

    TFile *fw = new TFile(inputPath+"WJETS.root","UPDATE");
    readdir(fw, parser,  TreeToUse);
    fw->Close();
    delete fw;
    
    TFile *fz = new TFile(inputPath+"ZJETS.root","UPDATE");
    readdir(fz, parser,  TreeToUse);
    fz->Close();
    delete fz;

    
    TFile *ft = new TFile(inputPath+"TT.root","UPDATE");
    readdir(ft, parser,  TreeToUse);
    ft->Close();
    delete ft;

    
    TFile *fd = new TFile(inputPath+"DiBoson.root","UPDATE");
    readdir(fd, parser,  TreeToUse);
    fd->Close();
    delete fd;

    

    TFile *f = new TFile(inputPath+"muDATA.root","UPDATE");
    readdir(f, parser,  TreeToUse);
    f->Close();
    delete f;
    
    //closing histogram file
    histfile->Close();
    std::cout<<"Closed histogram file"<<std::endl;

    return 0;  
} 


void readdir(TDirectory *dir, optutl::CommandLineParser parser,  char TreeToUse[]) 
{
    using namespace std;
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
            readdir(subdir, parser,  TreeToUse);

            dirsav->cd();
        }
        else if(obj->IsA()->InheritsFrom(TTree::Class())) {
            // check  if this tree was already processed
            channel = "tt";
            TTree *t = (TTree*)obj;

            //creating fakefactor object
            //TString ff_file_name = "/afs/hep.wisc.edu/home/samuellh/WorkingArea/CPstuff/Iso_2017/src/HTTutilities/Jet2TauFakes/data/SM2017/tight/vloose/tt/fakeFactors.root";
            TString ff_file_name = "/afs/hep.wisc.edu/home/samuellh/WorkingArea/CPstuff/Iso_2017/src/HTTutilities/Jet2TauFakes/data/SM2017/tight/vloose/mt/fakeFactors.root";
            TFile* ff_file = TFile::Open(ff_file_name);
            FakeFactor* ff = (FakeFactor*)ff_file->Get("ff_comb");
            //const std::vector<std::string>& inputNames = ff->inputs();
            std::vector<string> inputNames( ff->inputs() ) ;
            if (ff_file==0) std::cout<<"Error in FF file"<<std::endl;
            
            
            //adding the variables necessary to calculate weight
            Float_t pt_1, pt_2, tau_pt, mt, decayMode_2, m_vis, iso_1,isoTight_2;
            Int_t njets;
            TBranch *b_pt_1, *b_pt_2, *b_tau_pt, *b_mt, *b_decayMode_2, *b_njets, *b_m_vis, *b_iso_1, *b_isoTight_2;
            std::vector<double> variables( inputNames.size() );

            //loop over events in data file (global variable) 
            //TFile *f = new TFile(dataFile_.c_str());
            //if(f==0) printf("Not file Found\n");
            //get the nominal tree first
            //if(t==0) printf("Not Tree Found in file %s\n",file.c_str());
            //setting branch addresses
            t->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
            t->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
            t->SetBranchAddress("njets", &njets, &b_njets);
            t->SetBranchAddress("m_vis", &m_vis, &b_m_vis);
            t->SetBranchAddress("mt", &mt, &b_mt);
            t->SetBranchAddress("decayMode_2", &decayMode_2, &b_decayMode_2);
            t->SetBranchAddress("iso_1", &iso_1, &b_iso_1);
            t->SetBranchAddress("byTightIsolationMVArun2v1DBoldDMwLT_2", &isoTight_2, &b_isoTight_2);
    

            //new fake factor weight
            double ff_nom = 0.0;
            double frac_qcd = 0.0;
            double frac_w = 0.0;
            double frac_tt = 0.0;
            //double fakefactor;
            std::vector<float> fractions(3);
            TBranch *nBFF_1 = t->Branch("ff_nom",&ff_nom,"ff_nom/D");
            TBranch *nfr_1 = t->Branch("frac_qcd",&frac_qcd,"frac_qcd/D");
            TBranch *nfr_2 = t->Branch("frac_w",&frac_w,"frac_w/D");
            TBranch *nfr_3 = t->Branch("frac_tt",&frac_tt,"frac_tt/D");

            //TBranch *nBff_qcd_syst_up            trimmedtree->Branch("ff_qcd_syst_up"              ,      &ff_qcd_syst_up               ,"ff_qcd_syst_up/F"             );
            //TBranch *nBff_qcd_dm0_njet0_stat_up  trimmedtree->Branch("ff_qcd_dm0_njet0_stat_up"    ,      &ff_qcd_dm0_njet0_stat_up     ,"ff_qcd_dm0_njet0_stat_up/F"   );
            //TBranch *nBff_qcd_dm0_njet1_stat_up  trimmedtree->Branch("ff_qcd_dm0_njet1_stat_up"    ,      &ff_qcd_dm0_njet1_stat_up     ,"ff_qcd_dm0_njet1_stat_up/F"   );
            //TBranch *nBff_w_syst_up              trimmedtree->Branch("ff_w_syst_up"                ,          &ff_w_syst_up             ,"ff_w_syst_up/F"               );
            //TBranch *nBff_w_dm0_njet0_stat_up    trimmedtree->Branch("ff_w_dm0_njet0_stat_up"      ,      &ff_w_dm0_njet0_stat_up       ,"ff_w_dm0_njet0_stat_up/F"     );
            //TBranch *nBff_w_dm0_njet1_stat_up    trimmedtree->Branch("ff_w_dm0_njet1_stat_up"      ,      &ff_w_dm0_njet1_stat_up       ,"ff_w_dm0_njet1_stat_up/F"     );
            //TBranch *nBff_tt_syst_up             trimmedtree->Branch("ff_tt_syst_up"               ,      &ff_tt_syst_up                ,"ff_tt_syst_up/F"              );
            //TBranch *nBff_tt_dm0_njet0_stat_up   trimmedtree->Branch("ff_tt_dm0_njet0_stat_up"     ,      &ff_tt_dm0_njet0_stat_up      ,"ff_tt_dm0_njet0_stat_up/F"    );
            //TBranch *nBff_tt_dm0_njet1_stat_up   trimmedtree->Branch("ff_tt_dm0_njet1_stat_up"     ,      &ff_tt_dm0_njet1_stat_up      ,"ff_tt_dm0_njet1_stat_up/F"    );
            //TBranch *nBff_qcd_syst_down          trimmedtree->Branch("ff_qcd_syst_down"            ,      &ff_qcd_syst_down             ,"ff_qcd_syst_down/F"           );
            //TBranch *nBff_qcd_dm0_njet0_stat_down trimmedtree->Branch("ff_qcd_dm0_njet0_stat_down"  ,         &ff_qcd_dm0_njet0_stat_down,"ff_qcd_dm0_njet0_stat_down/F" );
            //TBranch *nBff_qcd_dm0_njet1_stat_down trimmedtree->Branch("ff_qcd_dm0_njet1_stat_down"  ,         &ff_qcd_dm0_njet1_stat_down,"ff_qcd_dm0_njet1_stat_down/F" );
            //TBranch *nBff_w_syst_down            trimmedtree->Branch("ff_w_syst_down"              ,      &ff_w_syst_down               ,"ff_w_syst_down/F"             );
            //TBranch *nBff_w_dm0_njet0_stat_down  trimmedtree->Branch("ff_w_dm0_njet0_stat_down"    ,      &ff_w_dm0_njet0_stat_down     ,"ff_w_dm0_njet0_stat_down/F"   );
            //TBranch *nBff_w_dm0_njet1_stat_down  trimmedtree->Branch("ff_w_dm0_njet1_stat_down"    ,      &ff_w_dm0_njet1_stat_down     ,"ff_w_dm0_njet1_stat_down/F"   );
            //TBranch *nBff_tt_syst_down           trimmedtree->Branch("ff_tt_syst_down"             ,      &ff_tt_syst_down              ,"ff_tt_syst_down/F"            );
            //TBranch *nBff_tt_dm0_njet0_stat_down trimmedtree->Branch("ff_tt_dm0_njet0_stat_down"   ,      &ff_tt_dm0_njet0_stat_down    ,"ff_tt_dm0_njet0_stat_down/F"  );
            //TBranch *nBff_tt_dm0_njet1_stat_down trimmedtree->Branch("ff_tt_dm0_njet1_stat_down"   ,      &ff_tt_dm0_njet1_stat_down    ,"ff_tt_dm0_njet1_stat_down/F"  );
            //dir->cd();





            //looping over data events 
            for(int i=0;i<t->GetEntries();i++ ){
                t->GetEntry(i);
                if(i%1000==0) std::cout<<"working on entry   "<<i<<std::endl;

                //initializing variables for FF ... 
                //std::cout<<"Initializing vectors ... "<<std::endl;
                fractions[0] = (float) 0.0;
                fractions[1] = (float) 0.0;
                fractions[2] = (float) 0.0;

                variables[0] = (double) 0.0; 
                variables[1] = (double) 0.0;
                variables[2] = (double) 0.0;
                variables[3] = (double) 0.0;
                variables[4] = (double) 0.0;
                variables[5] = (double) 0.0;
                variables[6] = (double) 0.0;
                variables[7] = (double) 0.0;
                variables[8] = (double) 0.0;

                ff_nom = 0.0;//normalizing to 1 so that I can multiply 1 and 2 later in the histogramming step

                if( isoTight_2<0.5){
                    
                    //std::cout<<"Tau 1 is not isolated ... "<<std::endl;
                    variables[0] = (double) pt_2;
                    variables[1] = (double) decayMode_2; //pt of non-fake tau candidate
                    variables[2] = (double) njets;
                    variables[3] = (double) m_vis;
                    variables[4] = (double) mt;
                    variables[5] = (double) iso_1;
                    fractions  = getFFractions((float)m_vis,(float) njets);
                    std::cout<<"fractions qcd  "<<fractions[3]<<std::endl;
                    //variables[5] = (double) fractions[3];//frac_qcd;
                    frac_qcd = (double) fractions[3];//frac_qcd;
                    variables[6] = frac_qcd;//frac_qcd;
                    //variables[6] = (double) fractions[0];//frac_w;
                    frac_w = (double) fractions[0];//frac_w;
                    variables[7] = frac_w;//frac_w;
                    //variables[7] = (double) fractions[1];//frac_tt;
                    frac_tt = (double) fractions[1];//frac_tt;
                    variables[8] = frac_tt;
                    ff_nom = ff->value(variables);
                    //ff_qcd_syst_up = ff->value(variables,"ff_qcd_syst")

                }
                
                
                //filling histogram with weight(not done)
                //renormalizeHistogram(filelabel_+prefix,"fakefactor",ff_nom*0.5 + ff_nom_2*0.5 );
                //wrong! Need to save both branches... 
                //fakefactor = ff_nom*0.5 + ff_nom_2*0.5; 
                nBFF_1->Fill();
                nfr_1->Fill();
                nfr_2->Fill();
                nfr_3->Fill();

            }//end data event loop
            std::cout<<"closing up"<<std::endl;
            dir->cd();
            t->Write("",TObject::kOverwrite);
            delete ff;
            ff_file->Close();
            delete t;
            std::cout<<"Closed and deleted objects in target file"<<std::endl;
        }
    }
}

void makeHistograms(TString path,std::string channel_,TString luminosity){
    //using namespace ROOT;
    //TString path = "/hdfs/store/user/samuellh/HTT_2018_Oct23_corr/";
    //TString path = inputPath.c_str();
    //making the cut string
    //may need to take the other permutations of these... for example 1 leg is gen matched 5 or less and the other is 6. 
    //ffSample->Draw("variable","cuts*fraction*Weight")

    //TFile *fwjets  = new TFile(wjets.c_str());
    TFile *fwjets  = new TFile(path+"WJETS.root");
    if(fwjets==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *twjets= (TTree*)fwjets->Get((channel_+"EventTree/eventTree").c_str());
    //this m_vis is a place holder ... can be any varibale ...
    
    //if(twjets==0) printf("Not Tree Found in file %s\n",wjets.c_str());
    //TFile *fzjets  = new TFile(zjets.c_str());
    TFile *fzjets  = new TFile(path+"ZJETS.root");
    if(fzjets==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *tzjets= (TTree*)fzjets->Get((channel_+"EventTree/eventTree").c_str());
    //if(tzjets==0) printf("Not Tree Found in file %s\n",zjets.c_str());
    //TFile *fdiboson  = new TFile(diboson.c_str());
    TFile *fdiboson  = new TFile(path+"DiBoson.root");
    if(fdiboson==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *tdiboson= (TTree*)fdiboson->Get((channel_+"EventTree/eventTree").c_str());
    //if(tdiboson==0) printf("Not Tree Found in file %s\n",diboson.c_str());
    //TFile *fttbar  = new TFile(ttbar.c_str());
    TFile *fttbar  = new TFile(path+"TT.root");
    if(fttbar==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *tttbar= (TTree*)fttbar->Get((channel_+"EventTree/eventTree").c_str());
    //if(tttbar==0) printf("Not Tree Found in file %s\n",ttbar.c_str());
    //TFile *fdata  = new TFile(data.c_str());
    TFile *fdata  = new TFile(path+"muDATA.root");
    if(fdata==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *tdata= (TTree*)fdata->Get((channel_+"EventTree/eventTree").c_str());
    //if(tdata==0) printf("Not Tree Found in file %s\n",data.c_str());
    
    
    histfile->cd(); 


    //pre-defined binning for the FF method 
    std::vector<float> m_vis{0,50,80,100,110,120,130,150,170,200,250,1000};
    std::vector<float> njets{-0.5,0.5,1.5,15};
    // must plot the variable in these bins???? or just 2D ... this is where the discussion breaks down... 
    //filling the histograms and finding the number of entries for each bin ... 
    //TH1D *hwjets = twjets->Draw(var,AR2);
    //TH3D *3hwjets = twjets->Draw(var+":"+m_vis+":"+njets, AR2+"weight");

    TH2D *hW   = new TH2D("W","W",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);
    TH2D *hZJ   = new TH2D("ZJ","ZJ",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]); 
    TH2D *hVVJ = new TH2D("VVJ","VVJ",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);
    TH2D *hVVT = new TH2D("VVT","VVT",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);
    TH2D *hTTJ   = new TH2D("TTJ","TTJ",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);
    TH2D *hTTT   = new TH2D("TTT","TTT",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);
    TH2D *hZTT   = new TH2D("ZTT","ZTT",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);
    TH2D *hdata    = new TH2D("data","data",m_vis.size()-1,&m_vis[0],njets.size()-1,&njets[0]);

    //TH2D *hW   = new TH2D("W","W",12,0.0,1000.0,4,-0.5,15);
    //TH2D *hZJ   = new TH2D("ZJ","ZJ",12,0.0,1000.0,4,-0.5,15); 
    //TH2D *hVVJ = new TH2D("VVJ","VVJ",12,0.0,1000.0,4,-0.5,15);
    //TH2D *hVVT = new TH2D("VVT","VVT",12,0.0,1000.0,4,-0.5,15);
    //TH2D *hTTJ   = new TH2D("TTJ","TTJ",12,0.0,1000.0,4,-0.5,15);
    //TH2D *hTTT   = new TH2D("TTT","TTT",12,0.0,1000.0,4,-0.5,15);
    //TH2D *hZTT   = new TH2D("ZTT","ZTT",12,0.0,1000.0,4,-0.5,15);
    //TH2D *hdata    = new TH2D("data","data",12,0.0,1000.0,4,-0.5,15);

    //The MC samples are split in events where the tau is faked by a jet (gen_match == 6: ZJ, TTJ, W, VVJ) and the remaining part (gen_match <= 5: ZTT, TTT, VVT )
    //TCut preselection = "isoTight_1>0.5&&isoTight_2>0.5&&abs(eta_1)<2.1&&abs(eta_2)<2.1&&againstMuonTight3_1>0&&againstMuonTight3_2>0&&againstElectronVLooseMVA6_1>0&&againstElectronVLooseMVA6_2>0&&npv>0&&diLeptons==0&&extraelec_veto==0&&extramuon_veto==0";
    TString preselection = "pt_1>21&&pt_2>30&&npv>0&&id_m_medium_1>0&&tightMuons<=1&&tightElectrons==0&&diLeptons==0&&againstMuonTight3_2>0&&againstElectronVLooseMVA6_2>0&&";
    TString preselectionIso = "pt_1>21&&pt_2>30&&npv>0&&id_m_medium_1>0&&iso_1<0.15&&byTightIsolationMVArun2v1DBoldDMwLT_2>0.5&&tightMuons<=1&&tightElectrons==0&&diLeptons==0&&againstMuonTight3_2>0&&againstElectronVLooseMVA6_2>0&&";
    TString ApplicationRegion = "byVLooseIsolationMVArun2v1DBoldDMwLT_2>0.5&&byTightIsolationMVArun2v1DBoldDMwLT_2<0.5&&";
    TString ApplicationRegiondata = "byVLooseIsolationMVArun2v1DBoldDMwLT_2>0.5&&byTightIsolationMVArun2v1DBoldDMwLT_2<0.5";
    TString SignalRegion = "byTightIsolationMVArun2v1DBoldDMwLT_2>0.5&&";
    TString weight_ ="__WEIGHT__*GENWEIGHT*puweight*"+luminosity;

    //TCut trueSelection = "gen_match_2<=5";
    //TCut fakeSelection = "gen_match_2==6";
    TString trueSelection = "gen_match_2==5";
    TString trueLSelection = "gen_match_2<5";
    TString fakeSelection = "gen_match_2==6";

    twjets->Draw("njets:m_vis>>W", "("+preselection+ApplicationRegion+fakeSelection+")*"+weight_)     ;// TH2D *hW = gDirectory->Get("hW");
    tzjets->Draw("njets:m_vis>>ZJ", "("+preselection+ApplicationRegion+fakeSelection+")*"+weight_)    ;// TH2D *hZJ = gDirectory->Get("hZJ");
    tdiboson->Draw("njets:m_vis>>VVJ", "("+preselection+ApplicationRegion+fakeSelection+")*"+weight_) ;// TH2D *hVVJ = gDirectory->Get("hVVJ");
    tdiboson->Draw("njets:m_vis>>VVT", "("+preselection+ApplicationRegion+trueSelection+")*"+weight_) ;// TH2D *hVVT = gDirectory->Get("hVVT");
    tttbar->Draw("njets:m_vis>>TTJ", "("+preselection+ApplicationRegion+fakeSelection+")*"+weight_)   ;// TH2D *hTTJ = gDirectory->Get("hTTJ");
    tttbar->Draw("njets:m_vis>>TTT", "("+preselection+ApplicationRegion+trueSelection+")*"+weight_)   ;// TH2D *hTTT = gDirectory->Get("hTTT");
    //tttbar->Draw("njets:m_vis>>ZTT", "("+preselection+ApplicationRegion+trueSelection+")*"+weight_)   ;// TH2D *hZTT = gDirectory->Get("hZTT");
    tzjets->Draw("njets:m_vis>>ZTT", "("+preselection+ApplicationRegion+trueSelection+")*"+weight_)   ;// TH2D *hZTT = gDirectory->Get("hZTT");
    tdata->Draw("njets:m_vis>>data",preselection+ApplicationRegiondata)        ;// TH2D *hdata = gDirectory->Get("hdata");
    std::cout<<"Events in data"<<hdata->GetEntries()<<std::endl;
     

    histfile->Write((hW   )->GetName(),TObject::kOverwrite);
    histfile->Write((hZJ  )->GetName(),TObject::kOverwrite);
    histfile->Write((hVVJ )->GetName(),TObject::kOverwrite);
    histfile->Write((hVVT )->GetName(),TObject::kOverwrite);
    histfile->Write((hTTJ )->GetName(),TObject::kOverwrite);
    histfile->Write((hTTT )->GetName(),TObject::kOverwrite);
    histfile->Write((hZTT )->GetName(),TObject::kOverwrite);
    histfile->Write((hdata)->GetName(),TObject::kOverwrite);
    
    fzjets->Close();
    fwjets->Close();
    fdiboson->Close();
    fttbar->Close();
    fdata->Close();
    
    return;

}



std::vector<float> getFFractions(float m_vis_val, float njets_val) {
    
    //travel to histogram file no directory structure ... histos should be there
    histfile->cd();
    std::vector<float> fractions;

    //Calculating the Fractions  
    std::pair<int,int> thebins;
    thebins=findBin("W",m_vis_val,njets_val);
    //std::cout<<"Found the bin!"<<std::endl;
    //std::cout<<"The bins!  "<<thebins.first<<"    "<<thebins.second<<std::endl;
    
     
    float W    = ((TH2D*) histfile->Get("W"   ))->GetBinContent(thebins.first,thebins.second); 
    float ZJ   = ((TH2D*) histfile->Get("ZJ"  ))->GetBinContent(thebins.first,thebins.second);
    float VVJ  = ((TH2D*) histfile->Get("VVJ" ))->GetBinContent(thebins.first,thebins.second);
    float VVT  = ((TH2D*) histfile->Get("VVT" ))->GetBinContent(thebins.first,thebins.second);
    float TTT  = ((TH2D*) histfile->Get("TTT" ))->GetBinContent(thebins.first,thebins.second);
    float TTJ  = ((TH2D*) histfile->Get("TTJ" ))->GetBinContent(thebins.first,thebins.second);
    float ZTT  = ((TH2D*) histfile->Get("TTJ" ))->GetBinContent(thebins.first,thebins.second);
    float data = ((TH2D*) histfile->Get("data"))->GetBinContent(thebins.first,thebins.second);
    std::cout<<"W    events :"<<W   <<std::endl;
    std::cout<<"ZJ   events :"<<ZJ  <<std::endl;
    std::cout<<"VVJ  events :"<<VVJ <<std::endl;
    std::cout<<"VVT  events :"<<VVT <<std::endl;
    std::cout<<"TTT  events :"<<TTT <<std::endl;
    std::cout<<"TTJ  events :"<<TTJ <<std::endl;
    std::cout<<"ZTT  events :"<<ZTT <<std::endl;
    std::cout<<"data events :"<<data<<std::endl;
    
    float frac_w = (W + ZJ + VVJ) / data;
    float frac_tt = TTJ / data;
    float frac_real = (ZTT + TTT + VVT) / data;
    float frac_qcd = 1. - (frac_w + frac_tt + frac_real);
    float total = frac_w + frac_tt + frac_qcd;
    frac_w = frac_w/total;
    frac_tt = frac_tt/total;
    frac_qcd = frac_qcd/total;
    std::cout<<"frac_qcd:   "<<frac_qcd<<std::endl;
    std::cout<<"frac_w:   "<<frac_w<<std::endl;
    std::cout<<"frac_tt:   "<<frac_tt<<std::endl;
    std::cout<<"frac_real:   "<<frac_real<<std::endl;
    fractions.push_back(frac_w);
    fractions.push_back(frac_tt);
    fractions.push_back(frac_real);
    fractions.push_back(frac_qcd);

    
    return fractions; 
}


//Find the bin!!!
std::pair<int,int> findBin(std::string histname,float m_vis,float njets){
    
    histfile->cd();     
    TH2D * h = (TH2D*) histfile->Get(histname.c_str());
    //std::cout<<"entries in find bin histo "<<h->GetEntries()<<std::endl;
    TAxis *X = h->GetXaxis();   
    TAxis *Y = h->GetYaxis();   
    int binx = X->FindBin(m_vis);
    int biny = Y->FindBin(njets);
    std::pair<int,int> binpair = std::make_pair(binx,biny);

    return binpair;
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
  using namespace ROOT;
  //prepare files to be copied
  if(gSystem->AccessPathName(parser.stringValue("inputFile").c_str())) {
    gSystem->CopyFile("hsimple.root", parser.stringValue("inputFile").c_str());
  }

  fNew->cd();
  CopyFile(parser.stringValue("inputFile").c_str(),parser);
  fNew->ls();
  fNew->Close();

}
