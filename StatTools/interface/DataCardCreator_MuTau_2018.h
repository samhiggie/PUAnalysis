#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TCut.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include <math.h>
#include <boost/algorithm/string.hpp>
#include "PUAnalysis/DataFormats/interface/TH1Keys.h"
#include <TEfficiency.h>
#include <TMath.h>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
//#include "FineBins.h"
#include "HTTutilities/Jet2TauFakes/interface/FakeFactor.h"


using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::pair;
using std::make_pair;

struct BkgOutput {
    float DATA;
    float W, dW;
    float QCD, dQCD;
    float ZLFT, dZLFT;
    float ZJFT, dZJFT;
    float TOP, dTOP;
    float TTT, dTTT;
    float TTJ, dTTJ;
    float TTL, dTTL;
    float VV, dVV;
    float VVT, dVVT;
    float VVL, dVVL;
    float VVJ, dVVJ;
    float ZTT, dZTT;

    BkgOutput(){};

    BkgOutput(float i) {
        // This assumes that a-d are all of the same type and all in order
        std::fill(&DATA, &dZTT+1, i);
    }

};



class DataCardCreatorHTT {
    public:

        DataCardCreatorHTT(optutl::CommandLineParser parser) {
            channel_  = parser.stringValue("channel");
            shifts_   = parser.stringVector("shifts");
			doJEC_    = parser.doubleValue("doJEC");//addme
            energy_   = parser.stringValue("energy");
            samesign_ = parser.doubleValue("samesign");

			nominalSelection_ = parser.stringValue("nominalselection");

            std::string name_=channel_;
            if (channel_=="eleTau") filelabel_="et";
            if (channel_=="muTau") filelabel_="mt";


            //create the name you need to add to the histograms 
            //in the root file 
            for(unsigned int i=0;i<shifts_.size();++i) {
                std::string shiftL = shifts_.at(i);
                shiftL.resize(1);
                boost::to_lower(shiftL);
                std::cout<<"shiftL: "<<shiftL<<std::endl;
                std::string chan = "mt";
                if(channel_=="eleTau") chan = "et";
                //if (shifts_[i]=="Tau") shiftsPostFix_.push_back("TES");
                shiftsPostFix_.push_back("CMS_scale_"+shiftL+"_"+chan+"_"+energy_);
            }

            //read input files
            zttFile_   = parser.stringValue("zttFile");
            zllFile_   = parser.stringValue("zllFile");
            wFile_     = parser.stringValue("wFile");
            vvFile_    = parser.stringValue("vvFile");
            topFile_   = parser.stringValue("topFile");
            qcdFile_   = parser.stringValue("qcdFile");
            dataFile_  = parser.stringValue("dataFile");

            //read control and signal regions
            preSelection_ = parser.stringValue("preselection");

            signalSelection_      = parser.stringValue("signalselection");
            wSelection_           = parser.stringValue("wselection");
            relaxedSelection_     = parser.stringValue("relaxedSelection");
            trigSelection_        = parser.stringValue("trigSelection");
            trigSelectionData_    = parser.stringValue("trigSelectionData");
            blinding_             = parser.stringValue("blinding");
            charge_               = parser.stringValue("charge");

            if (samesign_) charge_="abs(charge)==2";


            ZTT1PRONG_        = "tauDecayMode==0"; //Zttyield
            ZTT1PRONG1PI0_        = "tauDecayMode==1"; //Zttyield
            ZTT3PRONG_        = "tauDecayMode==10"; //Zttyield

            ZTT_genTauSel_        = "gen_match_2==5"; //Zttyield
            muTau_genTauSel_        = "gen_match_1 ==2 && gen_match_2==5"; //Zttyield
            ZLFT_genLSel_         = "gen_match_2<5";
            ZJFT_genLReject_      = "gen_match_2==6";
            ZLL_genLLSel_        = "(gen_match_2<5||gen_match_2==6)"; //Zttyield

            //
            if(samesign_>0)
                osSignalSelection_    = signalSelection_+"&&abs(charge)==2";
            else
                osSignalSelection_    = signalSelection_+"&&charge==0";

            ssSignalSelection_    = signalSelection_+"&&abs(charge)==2";
            if(samesign_>0)
                osWSelection_         = wSelection_+"&&abs(charge)==2";
            else
                osWSelection_         = wSelection_+"&&charge==0";

            ssWSelection_         = wSelection_+"&&abs(charge)==2";
            verbose_              = parser.integerValue("verbose");

            //read systematic uncertainties 
            luminosity_    = parser.doubleValue("luminosity");
            luminosityErr_ = parser.doubleValue("luminosityErr");
            muID_          = parser.doubleValue("muID");
            muIDErr_       = parser.doubleValue("muIDErr");
            bID_           = parser.doubleValue("bID");
            bIDErr_        = parser.doubleValue("bIDErr");
            bMisID_        = parser.doubleValue("bMisID");
            bMisIDErr_     = parser.doubleValue("bMisIDErr");
            eleID_         = parser.doubleValue("eleID");
            eleIDErr_      = parser.doubleValue("eleIDErr");
            tauID_         = parser.doubleValue("tauID");
            tauIDHigh_     = parser.doubleValue("tauIDHigh");
            tauIDErr_      = parser.doubleValue("tauIDErr");
            zttScale_      = parser.doubleValue("zttScale");
            zttScaleErr_   = parser.doubleValue("zttScaleErr");
			vvScale_       = parser.doubleValue("VVScale");

            //read the basic varibale you will put in the histogram
            variable_      = parser.stringValue("variable");

            //read the event weight for MC and embedded
            weight_        = parser.stringValue("weight");
            Zweight_       = parser.stringValue("Zweight");
            TTweight_      = parser.stringValue("TTweight");
            embWeight_     = parser.stringValue("embWeight");

            //define the histogram binning
            bins_ = parser.integerValue("bins");
            max_  = parser.doubleValue("max");
            min_  = parser.doubleValue("min");


            //Define background uncertainty Errors
            topErr_     = parser.doubleValue("topErr");
            qcdErr_     = parser.doubleValue("qcdErr");
            vvErr_      = parser.doubleValue("vvErr");
            zlftErr_    = parser.doubleValue("zlftErr");
            //zlftFactor_ = parser.stringValue("zlftFactor");
            zlftFactor_ = parser.doubleValue("zlftFactor");

            zjftErr_      = parser.doubleValue("zjftErr");
            wFactorErr_   = parser.doubleValue("wFactorErr");
            qcdFactor_    = parser.doubleValue("qcdFactor");
            qcdFactorErr_ = parser.doubleValue("qcdFactorErr");
            bFactorZ_     = parser.doubleValue("bFactorZ");
            bFactorZErr_  = parser.doubleValue("bFactorZErr");
            bFactorW_     = parser.doubleValue("bFactorW");
            bFactorWErr_  = parser.doubleValue("bFactorWErr");

            dir_ = parser.stringValue("dir");

            scaleUp_ = parser.doubleValue("scaleUp");

            fout_ = new TFile(parser.stringValue("outputfile").c_str(),"RECREATE");

        }


        void makeHiggsShape(std::string preselection, std::string categoryselection, std::string prefix) {

            std::pair<float,float> tmp;
            float legCorr=1.0;

            if(muID_!=0&&eleID_!=0) {legCorr*=muID_*eleID_;}
            if(muID_!=0&&eleID_==0) {legCorr*=muID_*tauID_;}
            if(muID_==0&&eleID_!=0) {legCorr*=eleID_*tauID_;}
            std::cout<<"Make Higgs Shape"<<std::endl;
            tmp= createHistogramAndShifts(dir_+"ggH125.root","ggH120",("("+preselection+"&&"+categoryselection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*47.38*0.0698,prefix);
            tmp= createHistogramAndShifts(dir_+"ggH125.root","ggH125",("("+preselection+"&&"+categoryselection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*44.14*0.0627,prefix);
            tmp= createHistogramAndShifts(dir_+"ggH125.root","ggH130",("("+preselection+"&&"+categoryselection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*41.23*0.0541,prefix);
            tmp= createHistogramAndShifts(dir_+"vbfH125.root","qqH120",("("+preselection+"&&"+categoryselection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*3.935*0.0698,prefix);
            tmp= createHistogramAndShifts(dir_+"vbfH125.root","qqH125",("("+preselection+"&&"+categoryselection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*3.782*0.0627,prefix);
            tmp= createHistogramAndShifts(dir_+"vbfH125.root","qqH130",("("+preselection+"&&"+categoryselection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*3.637*0.0541,prefix);
            std::cout<<"Made Higgs Shape"<<std::endl;
            //sam editions check!!
			string fullSelection     = preselection+"&&"+trigSelection_+"&&"+osSignalSelection_;
            if(doJEC_>0)
			  createJETSystematicsHiggsCustVar(fullSelection, luminosity_*legCorr, prefix);
            
        }


        /*-------------Create Histograms------------------*/

        BkgOutput runOSLSMT(std::string preSelection,std::string prefix,std::string zShape, float topExtrap) {
            std::cout<<"runOSLSMT"<<std::endl;

            BkgOutput output(0);    

            float leg1Corr=1.0;
            if(muID_!=0) leg1Corr*=muID_;
            if(eleID_!=0) leg1Corr*=eleID_;

            printf("Tau ID Scale Factor is %.3f \n",tauID_);

            std::cout<<"Create Data"<<std::endl;
            std::cout<<"      Data Selection: "<<preSelection<<"&&"<<osSignalSelection_<<std::endl;


            std::pair<float,float> dataY         = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+trigSelectionData_+"&&"+osSignalSelection_+"&&"+blinding_+")",scaleUp_,prefix);
            output.DATA = dataY.first;


            std::cout<<"Create Top"<<std::endl;
            std::cout<<"Create Top Sys"<<TTweight_<<std::endl;
            //Create ttbar
            std::pair<float,float> topYield      = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_+"*"+TTweight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);
            std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
            printf("      TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);
            output.TOP  = topInflYield.first;
            output.dTOP = topInflYield.second;

            std::cout<<"Create VV"<<std::endl;
            //Create Diboson
            std::pair<float,float> vvYield      = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            printf("      Diboson events before inflation = %f + %f \n",vvYield.first,vvYield.second);
            std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
            printf("      Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);
            output.VV  = vvInflYield.first;
            output.dVV = vvInflYield.second;


            std::cout<<"Create ZLFT"<<std::endl;
            //Create ZL and ZJ
            std::pair<float,float> zlftYield   = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZLFT_genLSel_+")*"+weight_),luminosity_*leg1Corr*zttScale_*zlftFactor_,prefix,false);
            //std::pair<float,float> zlftYield   = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&genTaus==0&&((abs(pdg2)==13&&genPt2>8)||(abs(pdg2)==11&&genPt2>8)))*"+weight_),luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix,false);
            std::pair<float,float> zlftInflYield  = inflateError(zlftYield,zlftErr_);
            printf("      Z (l->tau) in signal region = %f + %f \n",zlftInflYield.first,zlftInflYield.second);
            output.ZLFT  = zlftInflYield.first;
            output.dZLFT = zlftInflYield.second;


            std::cout<<"Create ZJFT"<<std::endl;
            std::pair<float,float> zjftYield      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZJFT_genLReject_+")*"+weight_),luminosity_*leg1Corr*zttScale_,prefix);    
            //std::pair<float,float> zjftYield      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&(!((genTaus==0&&abs(pdg2)==13&&genPt2>8)||(genTaus==0&&abs(pdg2)==11&&genPt2>8)||(genTaus>0&&genVisPt2>18))))*"+weight_),luminosity_*leg1Corr*zttScale_,prefix);    
            std::pair<float,float> zjftInflYield  = inflateError(zjftYield,zjftErr_);
            printf("      Z (j->tau) in signal region = %f + %f \n",zjftInflYield.first,zjftInflYield.second);
            output.ZJFT  = zjftInflYield.first;
            output.dZJFT = zjftInflYield.second;

            /*
               std::cout<<"Create ZLL"<<std::endl;
            //Create ZL and ZJ
            std::pair<float,float> zllYield   = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZLL_genLLSel_+")*"+weight_),luminosity_*leg1Corr*zllFactor_*zttScale_,prefix,false);
            //std::pair<float,float> zllYield   = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&genTaus==0&&((abs(pdg2)==13&&genPt2>8)||(abs(pdg2)==11&&genPt2>8)))*"+weight_),luminosity_*leg1Corr*zllFactor_*zttScale_,prefix,false);
            std::pair<float,float> zllInflYield  = inflateError(zllYield,zllErr_);
            printf("      Z (l->tau) in signal region = %f + %f \n",zllInflYield.first,zllInflYield.second);
            output.ZLL  = zllInflYield.first;
            output.dZLL = zllInflYield.second;
            */


            std::cout<<"Create ZTT"<<std::endl;
            //Create Z-->tautau
            if(!runZTT(preSelection, prefix, zShape, topExtrap, output)){
                std::cout<<"Error Creating Ztt"<<std::endl;
                return output;
            }


            //Create W 
            //In principle osSignalSelection should work as a dummy variable
            std::cout<<"Create W"<<std::endl;
            if(!runW(preSelection, prefix, zShape, topExtrap, output, "pt_1>-100", "pt_1>-100",wSelection_)){
                std::cout<<"Error Creating W"<<std::endl;
                return output;
            }

            std::cout<<"Create QCD"<<std::endl;
            //Create QCD
            if(!runQCD(preSelection, prefix, zShape, topExtrap, output, "pt_1>-100", relaxedSelection_)){ //pt_1>-100 is the category Selection
                std::cout<<"Error Creating QCD"<<std::endl;
                return output;
            }


            std::cout<<"=============Data Yields============="<<std::endl;
            std::cout<<"DATA: "<< output.DATA<<std::endl;
            std::cout<<std::endl;
            std::cout<<"BKGD Yields "<<std::endl;
            std::cout<<"QCD: "<< output.QCD<<std::endl;
            std::cout<<"W: "<< output.W<<std::endl;
            std::cout<<"TOP: "<< output.TOP<<std::endl;
            std::cout<<"VV: "<< output.VV<<std::endl;
            std::cout<<"ZLFT: "<< output.ZLFT<<std::endl;
            std::cout<<"ZJFT: "<< output.ZJFT<<std::endl;
            std::cout<<"ZTT: "<< output.ZTT<<std::endl;

            //TODO: Check that this outputs the correct values
            float background    = output.QCD  + output.W  + output.TOP  + output.VV  + output.ZLFT  + output.ZJFT  + output.ZTT;
            float backgroundErr = sqrt( pow(output.dQCD,2) + pow(output.dW,2) + pow(output.dTOP,2) + pow(output.dVV,2) + pow(output.dZLFT,2) + pow(output.dZJFT,2) + pow(output.dZTT,2));

            printf("BACKGROUND=%f +-%f \n",background,backgroundErr);


            float fullBackgroundErr = sqrt(pow(quadrature(output.VV,output.dVV,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)
                    +pow(quadrature(output.TOP,output.dTOP,muIDErr_,eleIDErr_,tauIDErr_),2)
                    +pow(quadrature(output.ZJFT,output.dZJFT,muIDErr_,eleIDErr_,zttScaleErr_),2)
                    +pow(quadrature(output.ZLFT,output.dZLFT,muIDErr_,eleIDErr_,zttScaleErr_),2)
                    +pow(output.dQCD,2)
                    +pow(output.dW,2)
                    +pow(quadrature(output.ZTT,output.dZTT,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2));

            printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,sqrt(pow(quadrature(output.VV,    output.dVV,   muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)
                        +pow(quadrature(output.TOP,  output.dTOP,  muIDErr_,eleIDErr_,tauIDErr_),2)
                        +pow(quadrature(output.ZJFT, output.dZJFT, muIDErr_,eleIDErr_,zttScaleErr_),2)
                        +pow(quadrature(output.ZLFT, output.dZLFT, muIDErr_,eleIDErr_,zttScaleErr_),2)
                        +pow(output.dQCD,2)
                        +pow(output.dW,2)
                        +pow(quadrature(output.ZTT,output.dZTT,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)));



            //create a histogram with the error for plotting reasons and only
            TH1F *err = new TH1F("BKGErr","",1,0,1);
            err->SetBinContent(1,fullBackgroundErr/background);
            fout_->cd((filelabel_+prefix).c_str());
            err->Write();

            return output;      
        }

        /*
         * Run the full extrapolation in the Btag category
         * Needed: BtagSF, categorySelection
         *
         */

        BkgOutput runFullExtrapBtag(std::string relaxedSelection, std::string wSel, std::string preSelection, std::string categorySelection_, std::string prefix, std::string zShape, float topExtrap, float zExtrap, float zExtrapErr, std::string bTagSF) {

            std::cout<<"======================"<<std::endl;
            std::cout<<"Run Full Extrapolation"<<std::endl;
            std::cout<<"categorySelection: "<<categorySelection_<<std::endl;
            //TODO: Fix this category seleciton business, should be more elegant
            std::string categorySelection = categorySelection_;
            std::string dummySelection_   = osSignalSelection_;

            weight_ = weight_+"*"+bTagSF;

            BkgOutput output;    

            float leg1Corr=1.0;
            if(muID_!=0) leg1Corr*=muID_;
            if(eleID_!=0) leg1Corr*=eleID_;

            printf("Tau ID Scale Factor is %.3f \n",tauID_);

            std::cout<<"Select DATA"<<std::endl;
            std::pair<float,float> dataY         = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+trigSelectionData_+"&&"+osSignalSelection_+"&&"+categorySelection+")",scaleUp_,prefix);
            output.DATA = dataY.first;
            std::cout<<"      DATA Yield: "<< output.DATA<<std::endl;
            std::cout<<"      DATA Selection: "<<preSelection<<"&&"<<trigSelectionData_<<"&&"<<osSignalSelection_<<"&&"<<categorySelection<<std::endl; 



            std::cout<<"Create DiBoson"<<std::endl;
            //Create Diboson
            std::pair<float,float> vvYield      = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VV before error inflation: "<<vvYield.first<<std::endl;
            std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
            printf("      Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);
            std::cout<<"      VV after error inflation: "<<vvInflYield.first<<std::endl;
            output.VV  = vvInflYield.first;
            output.dVV = vvInflYield.second;

            std::pair<float,float> vvtYield      = createHistogramAndShifts(vvFile_,"VVT",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZTT_genTauSel_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VVT before error inflation: "<<vvtYield.first<<std::endl;
            std::pair<float,float> vvtInflYield  = inflateError(vvtYield,vvtErr_);
            output.VVT  = vvtInflYield.first;
            output.dVVT = vvtInflYield.second;

            std::pair<float,float> vvjYield      = createHistogramAndShifts(vvFile_,"VVJ",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZJFT_genLReject_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VVJ before error inflation: "<<vvjYield.first<<std::endl;
            std::pair<float,float> vvjInflYield  = inflateError(vvjYield,vvjErr_);
            output.VVJ  = vvjInflYield.first;
            output.dVVJ = vvjInflYield.second;

            std::pair<float,float> vvlYield      = createHistogramAndShifts(vvFile_,"VVL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZLFT_genLSel_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VVL before error inflation: "<<vvlYield.first<<std::endl;
            std::pair<float,float> vvlInflYield  = inflateError(vvlYield,vvlErr_);
            output.VVL  = vvlInflYield.first;
            output.dVVL = vvlInflYield.second;

            //END PROGRAM FOR DEBUGGING VV DISTS.
            return output;
            //Create ZL and ZJ

            std::cout<<"Create ZLFT"<<std::endl;
            //ZL Yield
            std::pair<float,float> zlftYield   = createHistogramAndShifts(zllFile_,"ZLTmp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection_+"&&"+ZLFT_genLSel_+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_*zlftFactor_,prefix,false);
            //ZLShape
            //std::pair<float,float> zlftShape   = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+relaxedSelection+"&&"+ZLFT_genLSel_+")*"+weight_),luminosity_*leg1Corr*zlftFactor_*zttScale_*zlftFactor_,prefix,false);
            std::pair<float,float> zlftShape   = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZLFT_genLSel_+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_*zlftFactor_,prefix,false);
            std::pair<float,float> zlftShape1   = createHistogramAndShifts(zllFile_,"ZL_1prong",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZLFT_genLSel_+"&&tauDecayMode==0"+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_*zlftFactor_,prefix,false);
            std::pair<float,float> zlftShape2   = createHistogramAndShifts(zllFile_,"ZL_other",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZLFT_genLSel_+"&&tauDecayMode!=0"+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_*zlftFactor_,prefix,false);

            std::pair<float,float> zlftInflYield  = inflateError(zlftYield,zlftErr_);
            printf("      Z (l->tau) in signal region = %f + %f \n",zlftInflYield.first,zlftInflYield.second);

            renormalizeHistogram(filelabel_+prefix,"ZL",zlftInflYield.first);
            output.ZLFT  = zlftInflYield.first;
            output.dZLFT  = zlftInflYield.second;

            if(shifts_.size()>0&&channel_=="eleTau"){
                std::pair<float,float> zlShiftUp      = createHistogramShifted(zllFile_,"ZL_CMS_htt_ZLScale_etau_13TeVUp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection_+"&&abs(pdg2)==11&&"+ZLFT_genLSel_+")*"+weight_+"*"+Zweight_),"1.02",luminosity_*leg1Corr*zttScale_*zlftFactor_*zExtrap,prefix);
                std::pair<float,float> zlShiftDown     = createHistogramShifted(zllFile_,"ZL_CMS_htt_ZLScale_etau_13TeVDown",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection_+"&&abs(pdg2)==11&&"+ZLFT_genLSel_+")*"+weight_+"*"+Zweight_),"0.98",luminosity_*leg1Corr*zttScale_*zlftFactor_*zExtrap,prefix);
            }
            else if(shifts_.size()>0&&channel_=="muTau"){
                std::pair<float,float> zlShiftUp      = createHistogramShifted(zllFile_,"ZL_CMS_htt_ZLScale_mutau_13TeVUp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection_+"&&abs(pdg2)==13&&"+ZLFT_genLSel_+")*"+weight_+"*"+Zweight_),"1.02",luminosity_*leg1Corr*zttScale_*zlftFactor_*zExtrap,prefix);
                std::pair<float,float> zlShiftDown     = createHistogramShifted(zllFile_,"ZL_CMS_htt_ZLScale_mutau_13TeVDown",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection_+"&&abs(pdg2)==13&&"+ZLFT_genLSel_+")*"+weight_+"*"+Zweight_),"0.98",luminosity_*leg1Corr*zttScale_*zlftFactor_*zExtrap,prefix);
            }

            std::cout<<"Create ZJFT"<<std::endl;
            //ZJ Yield
            std::pair<float,float> zjftYield      = createHistogramAndShifts(zllFile_,"ZJTmp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection_+"&&"+ZJFT_genLReject_+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_,prefix);    

            //ZJ Shape
            //std::pair<float,float> zjftShape      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+relaxedSelection+"&&"+ZJFT_genLReject_+")*"+weight_),luminosity_*leg1Corr*zttScale_,prefix);    
            std::pair<float,float> zjftShape      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZJFT_genLReject_+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_,prefix);    
            std::pair<float,float> zjftShape1      = createHistogramAndShifts(zllFile_,"ZJ_1prong",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZJFT_genLReject_+"&&"+ZTT1PRONG_+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_,prefix);    
            std::pair<float,float> zjftShape2      = createHistogramAndShifts(zllFile_,"ZJ_other",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZJFT_genLReject_+"&&tauDecayMode!=0"+")*"+weight_+"*"+Zweight_),luminosity_*leg1Corr*zttScale_,prefix);    

            std::pair<float,float> zjftInflYield  = inflateError(zjftYield,zjftErr_);
            printf("      Z (j->tau) in signal region = %f + %f \n",zjftInflYield.first,zjftInflYield.second);
            renormalizeHistogram(filelabel_+prefix,"ZJ",zjftInflYield.first);
            output.ZJFT  = zjftInflYield.first;
            output.dZJFT = zjftInflYield.second;

            std::cout<<"Create ZTT"<<std::endl;
            //TODO: Check me, previous Btag ZTT shape correction had a special normalization method
            if(!runZTT(preSelection, prefix, zShape, topExtrap, output, categorySelection)){
                std::cout<<"Error Creating Ztt"<<std::endl;
                return output;
            }

            std::cout<<"Create TOP"<<std::endl;
            //Create ttbar
            //Last argument is a dummy argument
            if(!runTOP(preSelection, prefix, zShape, topExtrap, output, categorySelection, relaxedSelection)){
                std::cout<<"Error Creating TOP"<<std::endl;
                return output;
            }


            std::cout<<"Create W"<<std::endl;
            //Create W
            if(!runW(preSelection, prefix, zShape, topExtrap, output, categorySelection, relaxedSelection, wSel)){
                std::cout<<"Error Creating W"<<std::endl;
                return output;
            }

            std::cout<<"Running Fake Factor"<<std::endl;
            if(!runFF(preSelection, prefix, zShape, topExtrap, output, categorySelection, relaxedSelection)){
                std::cout<<"Error Creating FF"<<std::endl;
                return output;
            }

            std::cout<<"Create QCD"<<std::endl;
            //Create QCD
            if(!runQCD(preSelection, prefix, zShape, topExtrap, output, categorySelection, relaxedSelection)){
                std::cout<<"Error Creating QCD"<<std::endl;
                return output;
            }



            //adding the systematics!!
			string fullSelection     = preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_;

			if(doJEC_>0){
			  std::cout<<"creating met systematics backgrounds"<<std::endl;
			  //createMETSystematics(fullSelection,tauIDCorr, leg1Corr, topExtrap, prefix);
			  std::cout<<"creating jet systematics backgrounds"<<std::endl;
			  createJETSystematicsCustVar(fullSelection,tauID_, leg1Corr, topExtrap, prefix);

			}
            std::cout<<std::endl;
            std::cout<<"=============Data Yields============="<<std::endl;
            std::cout<<"DATA: "<< output.DATA<<std::endl;
            std::cout<<std::endl;


            std::cout<<std::endl;
            std::cout<<"BKGD Yields "<<std::endl;
            std::cout<<"QCD: "<< output.QCD<<std::endl;
            std::cout<<"W: "<< output.W<<std::endl;
            std::cout<<"TOP: "<< output.TOP<<std::endl;
            std::cout<<"VV: "<< output.VV<<std::endl;
            std::cout<<"ZLFT: "<< output.ZLFT<<std::endl;
            std::cout<<"ZJFT: "<< output.ZJFT<<std::endl;
            std::cout<<"ZTT: "<< output.ZTT<<std::endl;


            float background    = output.QCD  + output.W  + output.TOP  + output.VV  + output.ZLFT  + output.ZJFT  + output.ZTT;
            float backgroundErr = sqrt( pow(output.dQCD,2) + pow(output.dW,2) + pow(output.dTOP,2) + pow(output.dVV,2) + pow(output.dZLFT,2) + pow(output.dZJFT,2) + pow(output.dZTT,2));
            printf("BACKGROUND=%f +-%f \n",background,backgroundErr);

            ///LATEX->Here since we want it for the note add all errors , even those that will go separate in the datacard

            //printf("LATEX ------------------------------------\n");
            //printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", dataYield.first, dataYieldSdb.first, dataSSYield.first, dataSSYieldSdb.first);
            //printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", vvInflYield.first, quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_), vvInflYieldSdb.first, quadrature(vvInflYieldSdb.first,vvInflYieldSdb.second,muIDErr_,eleIDErr_,tauIDErr_));
            //printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topInflYield.first,quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_), topInflYieldSdb.first, quadrature(topInflYieldSdb.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_));
            //printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zjftInflYield.first, quadrature(zjftInflYield.first,zjftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_), zjftInflSSYield.first,quadrature(zjftInflSSYield.first,zjftInflSSYield.second,muIDErr_,eleIDErr_,zttScaleErr_));
            //printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zlftInflYield.first, quadrature(zlftInflYield.first,zlftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_),zlftInflSSYield.first,quadrature(zlftInflSSYield.first,zlftInflSSYield.second,muIDErr_,eleIDErr_,zttScaleErr_));
            //printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow.first, osWLow.second, osWHigh.first, osWHigh.second, ssWLow.first, ssWLow.second, dataSSYieldSdb.first, dataSSYieldSdb.second);
            //printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
            //printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zttYield.first,quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_));


            float fullBackgroundErr = sqrt(pow(quadrature(output.VV,output.dVV,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)
                    +pow(quadrature(output.TOP,output.dTOP,muIDErr_,eleIDErr_,tauIDErr_),2)
                    +pow(quadrature(output.ZJFT,output.dZJFT,muIDErr_,eleIDErr_,zttScaleErr_),2)
                    +pow(quadrature(output.ZLFT,output.dZLFT,muIDErr_,eleIDErr_,zttScaleErr_),2)
                    +pow(output.dQCD,2)
                    +pow(output.dW,2)
                    +pow(quadrature(output.ZTT,output.dZTT,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2));

            printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,sqrt(pow(quadrature(output.VV,    output.dVV,   muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)
                        +pow(quadrature(output.TOP,  output.dTOP,  muIDErr_,eleIDErr_,tauIDErr_),2)
                        +pow(quadrature(output.ZJFT, output.dZJFT, muIDErr_,eleIDErr_,zttScaleErr_),2)
                        +pow(quadrature(output.ZLFT, output.dZLFT, muIDErr_,eleIDErr_,zttScaleErr_),2)
                        +pow(output.dQCD,2)
                        +pow(output.dW,2)
                        +pow(quadrature(output.ZTT,output.dZTT,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)));



            //create a histogram with the error for plotting reasons and only
            TH1F *err = new TH1F("BKGErr","",1,0,1);
            err->SetBinContent(1,fullBackgroundErr/background);
            fout_->cd((filelabel_+prefix).c_str());
            err->Write();

            return output;

        }
    void createShiftsTES(string name, string inputFile, string inputSelections, string inputWeight, float scale, string prefix,  pair<float,float> nominalYield){

              //2018 
              std::string ptSelectionDM0Up_    = "(((pt_2*1.011)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*0.988)>40&&decaymode_2==10))&&(((pt_1*1.011)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*0.988)>50&&decaymode_1==10))";
              std::string ptSelectionDM0Down_  = "(((pt_2*0.989)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*0.988)>40&&decaymode_2==10))&&(((pt_1*0.989)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*0.988)>50&&decaymode_1==10))";
              std::string ptSelectionDM1Up_    = "(((pt_2*0.987)>40&&decaymode_2==0)||((pt_2*1.008)>40&&decaymode_2==1)||((pt_2*0.988)>40&&decaymode_2==10))&&(((pt_1*0.987)>50&&decaymode_1==0)||((pt_1*1.009)>50&&decaymode_1==1)||((pt_1*0.988)>50&&decaymode_1==10))";
              std::string ptSelectionDM1Down_  = "(((pt_2*0.987)>40&&decaymode_2==0)||((pt_2*0.992)>40&&decaymode_2==1)||((pt_2*0.988)>40&&decaymode_2==10))&&(((pt_1*0.987)>50&&decaymode_1==0)||((pt_1*0.992)>50&&decaymode_1==1)||((pt_1*0.988)>50&&decaymode_1==10))";
              std::string ptSelectionDM10Up_   = "(((pt_2*0.987)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.009)>40&&decaymode_2==10))&&(((pt_1*0.987)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.011)>50&&decaymode_1==10))";
              std::string ptSelectionDM10Down_ = "(((pt_2*0.987)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*0.991)>40&&decaymode_2==10))&&(((pt_1*0.987)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*0.991)>50&&decaymode_1==10))";
              //2017  not done
              //std::string ptselectiondm0up_    = "(((pt_2*1.01)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*1.01)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.000)>50&&decaymode_1==10))";
              //std::string ptselectiondm0down_  = "(((pt_2*0.99)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*0.99)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.000)>50&&decaymode_1==10))";
              //std::string ptselectiondm1up_    = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*1.009)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*1.009)>50&&decaymode_1==1)||((pt_1*1.000)>50&&decaymode_1==10))";
              //std::string ptselectiondm1down_  = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*0.991)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*0.991)>50&&decaymode_1==1)||((pt_1*0.989)>50&&decaymode_1==10))";
              //std::string ptselectiondm10up_   = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.011)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.011)>50&&decaymode_1==10))";
              //std::string ptselectiondm10down_ = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*0.989)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*0.989)>50&&decaymode_1==10))";

              ////2016 legacy 
              //std::string ptselectiondm0up_    = "(((pt_2*1.01)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*1.01)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.000)>50&&decaymode_1==10))";
              //std::string ptselectiondm0down_  = "(((pt_2*0.99)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*0.99)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.000)>50&&decaymode_1==10))";
              //std::string ptselectiondm1up_    = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*1.009)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*1.009)>50&&decaymode_1==1)||((pt_1*1.000)>50&&decaymode_1==10))";
              //std::string ptselectiondm1down_  = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*0.991)>40&&decaymode_2==1)||((pt_2*1.000)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*0.991)>50&&decaymode_1==1)||((pt_1*0.989)>50&&decaymode_1==10))";
              //std::string ptselectiondm10up_   = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*1.011)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*1.011)>50&&decaymode_1==10))";
              //std::string ptselectiondm10down_ = "(((pt_2*0.994)>40&&decaymode_2==0)||((pt_2*0.995)>40&&decaymode_2==1)||((pt_2*0.989)>40&&decaymode_2==10))&&(((pt_1*0.994)>50&&decaymode_1==0)||((pt_1*0.995)>50&&decaymode_1==1)||((pt_1*0.989)>50&&decaymode_1==10))";
              //2016
              //std::string ptselectiondm0up_    = "(((pt_2*0.988)>40&&decaymode_2==0)||((pt_2*1.010)>40&&decaymode_2==1)||((pt_2*1.004)>40&&decaymode_2==10))&&(((pt_1*0.988)>50&&decaymode_1==0)||((pt_1*1.010)>50&&decaymode_1==1)||((pt_1*1.004)>50&&decaymode_1==10))";
              //std::string ptselectiondm0down_  = "(((pt_2*0.976)>40&&decaymode_2==0)||((pt_2*1.010)>40&&decaymode_2==1)||((pt_2*1.004)>40&&decaymode_2==10))&&(((pt_1*0.976)>50&&decaymode_1==0)||((pt_1*1.010)>50&&decaymode_1==1)||((pt_1*1.004)>50&&decaymode_1==10))";
              //std::string ptselectiondm1up_    = "(((pt_2*0.982)>40&&decaymode_2==0)||((pt_2*1.016)>40&&decaymode_2==1)||((pt_2*1.004)>40&&decaymode_2==10))&&(((pt_1*0.982)>50&&decaymode_1==0)||((pt_1*1.016)>50&&decaymode_1==1)||((pt_1*1.004)>50&&decaymode_1==10))";
              //std::string ptselectiondm1down_  = "(((pt_2*0.982)>40&&decaymode_2==0)||((pt_2*1.004)>40&&decaymode_2==1)||((pt_2*1.004)>40&&decaymode_2==10))&&(((pt_1*0.982)>50&&decaymode_1==0)||((pt_1*1.004)>50&&decaymode_1==1)||((pt_1*1.004)>50&&decaymode_1==10))";
              //std::string ptselectiondm10up_   = "(((pt_2*0.982)>40&&decaymode_2==0)||((pt_2*1.010)>40&&decaymode_2==1)||((pt_2*1.010)>40&&decaymode_2==10))&&(((pt_1*0.982)>50&&decaymode_1==0)||((pt_1*1.010)>50&&decaymode_1==1)||((pt_1*1.010)>50&&decaymode_1==10))";
              //std::string ptselectiondm10down_ = "(((pt_2*0.982)>40&&decaymode_2==0)||((pt_2*1.010)>40&&decaymode_2==1)||((pt_2*0.998)>40&&decaymode_2==10))&&(((pt_1*0.982)>50&&decaymode_1==0)||((pt_1*1.010)>50&&decaymode_1==1)||((pt_1*0.998)>50&&decaymode_1==10))";

              std::pair<float,float> ZTT_DM0_UP  ;
              std::pair<float,float> ZTT_DM0_DOWN  ;
              std::pair<float,float> ZTT_DM1_UP    ;
              std::pair<float,float> ZTT_DM1_DOWN  ;
              std::pair<float,float> ZTT_DM10_UP   ;
              std::pair<float,float> ZTT_DM10_DOWN ;

              //std::cout<<"DM0Up Selection "<<"("+ptSelectionDM0Up_    +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight<<std::endl;
              ZTT_DM0_UP    = createHistogramAndShiftsCustomVar(variable_+"_DM0_UP"   , inputFile,name+"_CMS_scale_t_1prong_13TeVUp",         ("("+ptSelectionDM0Up_    +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight),scale,prefix);
              ZTT_DM0_DOWN  = createHistogramAndShiftsCustomVar(variable_+"_DM0_DOWN" , inputFile,name+"_CMS_scale_t_1prong_13TeVDown",       ("("+ptSelectionDM0Down_  +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight),scale,prefix);
              ZTT_DM1_UP    = createHistogramAndShiftsCustomVar(variable_+"_DM1_UP"   , inputFile,name+"_CMS_scale_t_1prong1pizero_13TeVUp",  ("("+ptSelectionDM1Up_    +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight),scale,prefix);
              ZTT_DM1_DOWN  = createHistogramAndShiftsCustomVar(variable_+"_DM1_DOWN" , inputFile,name+"_CMS_scale_t_1prong1pizero_13TeVDown",("("+ptSelectionDM1Down_  +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight),scale,prefix);
              ZTT_DM10_UP   = createHistogramAndShiftsCustomVar(variable_+"_DM10_UP"  ,inputFile,name+"_CMS_scale_t_3prong_13TeVUp",         ("("+ptSelectionDM10Up_   +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight),scale,prefix);
              ZTT_DM10_DOWN = createHistogramAndShiftsCustomVar(variable_+"_DM10_DOWN",inputFile,name+"_CMS_scale_t_3prong_13TeVDown",       ("("+ptSelectionDM10Down_ +"&&"+nominalSelection_+"&&"+inputSelections+")*"+inputWeight),scale,prefix);
              

              //a quick sanity check... 
              std::cout<<"ZTT_DM0 nominal "<< nominalYield.first <<" Up "<<ZTT_DM0_UP.first<<" Down "<<ZTT_DM0_DOWN.first<<std::endl;
              if((abs(nominalYield.first-ZTT_DM0_UP.first)/nominalYield.first)>0.2)
                std::cout<<"Difference between Nominal and Up is greater than 20% this might indicate a problem"<<std::endl;
              if((abs(nominalYield.first-ZTT_DM0_DOWN.first)/nominalYield.first)>0.2)
                std::cout<<"Difference between Nominal and Down is greater than 20% this might indicate a problem"<<std::endl;

            }

    		void createJETSystematicsCustVar(string inputSelections, float tauIDCorr, float leg1Corr, float topExtrap, string prefix){
		  std::vector<std::string> jetSysVec = {"Closure", "AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "TimePtEta", "Total","Eta0to5","Eta3to5","Eta0to3","EC2"};

		  //find and replace jet selection
		  for(auto jetSys : jetSysVec){
		    std::string newSelectionUp=inputSelections;
		    std::string newSelectionDown=inputSelections;
		    ReplaceStringInPlace(newSelectionUp,   "njets", "njet_"   +jetSys+"Up");
		    ReplaceStringInPlace(newSelectionUp,   "mjj"  , "vbfMass_"+jetSys+"Up");
		    ReplaceStringInPlace(newSelectionDown, "njets", "njet_"   +jetSys+"Down");
		    ReplaceStringInPlace(newSelectionDown, "mjj"  , "vbfMass_"+jetSys+"Down");

		    pair<float,float> topJetYieldJetUp   = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  topFile_, "TTJ_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);
		    pair<float,float> topJetYieldJetDown = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  topFile_, "TTJ_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);
		    									                                      
		    pair<float,float> topTauYieldJetUp   = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  topFile_, "TTT_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 		  
		    pair<float,float> topTauYieldJetDown = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  topFile_, "TTT_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 
		    									                                      
		    pair<float,float> vvtYieldJetUp      = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  vvFile_,  "VVT_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    pair<float,float> vvtYieldJetDown    = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  vvFile_,  "VVT_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    									                                      
		    pair<float,float> vvYieldJetUp       = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  vvFile_,  "VVJ_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    pair<float,float> vvYieldJetDown     = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  vvFile_,  "VVJ_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    									                                      
		    pair<float,float> WYieldJetUp        = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  wFile_,   "W_CMS_scale_j_" +jetSys+"_13TeVUp"     , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);
		    pair<float,float> WYieldJetDown      = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  wFile_,   "W_CMS_scale_j_" +jetSys+"_13TeVDown"   , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);
		    									                                      
		    pair<float,float> ZTTYieldJetUp      = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  zttFile_, "ZTT_CMS_scale_j_"   +jetSys+"_13TeVUp"     , ("("+newSelectionUp+  "&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		    pair<float,float> ZTTYieldJetDown    = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  zttFile_, "ZTT_CMS_scale_j_"   +jetSys+"_13TeVDown"   , ("("+newSelectionDown+"&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		    
		    pair<float,float> zlftYieldJetUp     = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  zllFile_, "ZL_CMS_scale_j_" +jetSys+"_13TeVUp"     , ("("+newSelectionUp+  "&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);
		    pair<float,float> zlftYieldJetDown   = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  zllFile_, "ZL_CMS_scale_j_" +jetSys+"_13TeVDown"   , ("("+newSelectionDown+"&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);
		    									                                     
		    pair<float,float> zjftYieldJetUp     = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Up"  ,  zllFile_, "ZJ_CMS_scale_j_" +jetSys+"_13TeVUp"    , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    
		    pair<float,float> zjftYieldJetDown   = createHistogramAndShiftsCustomVar(  variable_+"_"+jetSys+"Down",  zllFile_, "ZJ_CMS_scale_j_" +jetSys+"_13TeVDown"  , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    

		  }
		}

		void createJETSystematicsHiggsCustVar(string inputSelections, float scale, string prefix){

		  std::vector<std::string> jetSysVec = {"Closure", "AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "TimePtEta", "Total","Eta0to5","Eta3to5","Eta0to3","EC2"};

		  for(auto jetSys : jetSysVec){

		    std::string newSelectionUp=inputSelections;
		    std::string newSelectionDown=inputSelections;
		    ReplaceStringInPlace(newSelectionUp,   "njets", "njet_"   +jetSys+"Up");
		    ReplaceStringInPlace(newSelectionUp,   "mjj"  , "vbfMass_"+jetSys+"Up");
		    ReplaceStringInPlace(newSelectionDown, "njets", "njet_"   +jetSys+"Down");
		    ReplaceStringInPlace(newSelectionDown, "mjj"  , "vbfMass_"+jetSys+"Down");
		    
		    pair<float,float> ggH125JetUp   = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Up"  ,  dir_+"ggH125.root" ,"ggH125_CMS_scale_j_"+jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> ggH125JetDown = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Down",  dir_+"ggH125.root" ,"ggH125_CMS_scale_j_"+jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> qqH125JetUp   = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Up"  ,  dir_+"vbfH125.root","qqH125_CMS_scale_j_" +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> qqH125JetDown = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Down",  dir_+"vbfH125.root","qqH125_CMS_scale_j_" +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		   /* 
		    pair<float,float> ZH125JetUp    = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Up"  ,  dir_+"ZH125.root"  ,"ZH125_CMS_scale_j_"  +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> ZH125JetDown  = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Down",  dir_+"ZH125.root"  ,"ZH125_CMS_scale_j_"  +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> WmH125JetUp   = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Up"  ,  dir_+"WmH125.root"  ,"WmH125_CMS_scale_j_"  +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> WmH125JetDown = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Down",  dir_+"WmH125.root"  ,"WmH125_CMS_scale_j_"  +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);

		    pair<float,float> WpH125JetUp   = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Up"  ,  dir_+"WpH125.root"  ,"WpH125_CMS_scale_j_"  +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> WpH125JetDown = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Down",  dir_+"WpH125.root"  ,"WpH125_CMS_scale_j_"  +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> ttH125JetUp   = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Up"  ,  dir_+"ttH125.root" ,"ttH125_CMS_scale_j_" +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> ttH125JetDown = createHistogramAndShiftsCustomVar(variable_+"_"+jetSys+"Down",  dir_+"ttH125.root" ,"ttH125_CMS_scale_j_" +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
            */
		  }
		}
		void createJETSystematics(string inputSelections, float tauIDCorr, float leg1Corr, float topExtrap, string prefix){
		  std::vector<std::string> jetSysVec = {"Closure", "AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "TimePtEta", "Total","Eta0to5","Eta3to5","Eta0to3","EC2"};

		  //find and replace jet selection
		  for(auto jetSys : jetSysVec){
		    std::string newSelectionUp=inputSelections;
		    std::string newSelectionDown=inputSelections;
		    ReplaceStringInPlace(newSelectionUp,   "njets", "njet_"   +jetSys+"Up");
		    ReplaceStringInPlace(newSelectionUp,   "mjj"  , "vbfMass_"+jetSys+"Up");
		    ReplaceStringInPlace(newSelectionDown, "njets", "njet_"   +jetSys+"Down");
		    ReplaceStringInPlace(newSelectionDown, "mjj"  , "vbfMass_"+jetSys+"Down");

		    pair<float,float> topJetYieldJetUp   = createHistogramAndShifts(  topFile_, "TTJ_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);
		    pair<float,float> topJetYieldJetDown = createHistogramAndShifts(  topFile_, "TTJ_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);
		    
		    pair<float,float> topTauYieldJetUp   = createHistogramAndShifts(  topFile_, "TTT_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 		  
		    pair<float,float> topTauYieldJetDown = createHistogramAndShifts(  topFile_, "TTT_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 
		    
		    pair<float,float> vvtYieldJetUp      = createHistogramAndShifts(  vvFile_,  "VVT_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    pair<float,float> vvtYieldJetDown    = createHistogramAndShifts(  vvFile_,  "VVT_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    
		    pair<float,float> vvYieldJetUp       = createHistogramAndShifts(  vvFile_,  "VVJ_CMS_scale_j_" +jetSys+"_13TeVUp"   , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    pair<float,float> vvYieldJetDown     = createHistogramAndShifts(  vvFile_,  "VVJ_CMS_scale_j_" +jetSys+"_13TeVDown" , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		    
		    pair<float,float> WYieldJetUp        = createHistogramAndShifts(  wFile_,   "W_CMS_scale_j_" +jetSys+"_13TeVUp"     , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);
		    pair<float,float> WYieldJetDown      = createHistogramAndShifts(  wFile_,   "W_CMS_scale_j_" +jetSys+"_13TeVDown"   , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);
		    
		    pair<float,float> ZTTYieldJetUp      = createHistogramAndShifts(  zttFile_, "ZTT_CMS_scale_j_"   +jetSys+"_13TeVUp"     , ("("+newSelectionUp+  "&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		    pair<float,float> ZTTYieldJetDown    = createHistogramAndShifts(  zttFile_, "ZTT_CMS_scale_j_"   +jetSys+"_13TeVDown"   , ("("+newSelectionDown+"&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		    
		    pair<float,float> zlftYieldJetUp     = createHistogramAndShifts(  zllFile_, "ZL_CMS_scale_j_"    +jetSys+"_13TeVUp"     , ("("+newSelectionUp+  "&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);
		    pair<float,float> zlftYieldJetDown   = createHistogramAndShifts(  zllFile_, "ZL_CMS_scale_j_"    +jetSys+"_13TeVDown"   , ("("+newSelectionDown+"&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);
		    
		    pair<float,float> zjftYieldJetUp     = createHistogramAndShifts(  zllFile_, "ZJ_CMS_scale_j_" +jetSys+"_13TeVUp"    , ("("+newSelectionUp+  "&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    
		    pair<float,float> zjftYieldJetDown   = createHistogramAndShifts(  zllFile_, "ZJ_CMS_scale_j_" +jetSys+"_13TeVDown"  , ("("+newSelectionDown+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    

		  }
		}

		void createJETSystematicsHiggs(string inputSelections, float scale, string prefix){
		  std::vector<std::string> jetSysVec = {"Closure", "AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "TimePtEta", "Total","Eta0to5","Eta3to5","Eta0to3","EC2"};
		  for(auto jetSys : jetSysVec){

		    std::string newSelectionUp=inputSelections;
		    std::string newSelectionDown=inputSelections;
		    ReplaceStringInPlace(newSelectionUp,   "njets", "njet_"   +jetSys+"Up");
		    ReplaceStringInPlace(newSelectionUp,   "mjj"  , "vbfMass_"+jetSys+"Up");
		    ReplaceStringInPlace(newSelectionDown, "njets", "njet_"   +jetSys+"Down");
		    ReplaceStringInPlace(newSelectionDown, "mjj"  , "vbfMass_"+jetSys+"Down");
		    
		    pair<float,float> ggH125JetUp   = createHistogramAndShifts(  dir_+"ggH125.root" ,"ggH125_CMS_scale_j_"+jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> ggH125JetDown = createHistogramAndShifts(  dir_+"ggH125.root" ,"ggH125_CMS_scale_j_"+jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> qqH125JetUp   = createHistogramAndShifts(  dir_+"vbfH125.root","qqH125_CMS_scale_j_" +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> qqH125JetDown = createHistogramAndShifts(  dir_+"vbfH125.root","qqH125_CMS_scale_j_" +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> ZH125JetUp    = createHistogramAndShifts(  dir_+"ZH125.root"  ,"ZH125_CMS_scale_j_"  +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> ZH125JetDown  = createHistogramAndShifts(  dir_+"ZH125.root"  ,"ZH125_CMS_scale_j_"  +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> WmH125JetUp   = createHistogramAndShifts(  dir_+"WmH125.root"  ,"WmH125_CMS_scale_j_"  +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> WmH125JetDown = createHistogramAndShifts(  dir_+"WmH125.root"  ,"WmH125_CMS_scale_j_"  +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);

		    pair<float,float> WpH125JetUp   = createHistogramAndShifts(  dir_+"WpH125.root"  ,"WpH125_CMS_scale_j_"  +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> WpH125JetDown = createHistogramAndShifts(  dir_+"WpH125.root"  ,"WpH125_CMS_scale_j_"  +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		    
		    pair<float,float> ttH125JetUp   = createHistogramAndShifts(  dir_+"ttH125.root" ,"ttH125_CMS_scale_j_" +jetSys+"_13TeVUp"  ,newSelectionUp,scale,prefix);
		    pair<float,float> ttH125JetDown = createHistogramAndShifts(  dir_+"ttH125.root" ,"ttH125_CMS_scale_j_" +jetSys+"_13TeVDown",newSelectionDown,scale,prefix);
		  }
		}

		void createMETSystematics(string inputSelections, float tauIDCorr, float leg1Corr, float topExtrap, string prefix){
		  //m_sv:mjj
		  std::string var1_UP_   = "m_sv_UncMet_UP";
		  std::string var1_DOWN_ = "m_sv_UncMet_DOWN";

		  pair<float,float> zjftYieldUncUp     = createHistogramAndShiftsCustomVar(var1_UP_  ,zllFile_, "ZJ_CMS_scale_met_unclustered_13TeVUp"   , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    
		  pair<float,float> zjftYieldUncDown   = createHistogramAndShiftsCustomVar(var1_DOWN_,zllFile_, "ZJ_CMS_scale_met_unclustered_13TeVDown" , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    
											                           
		  pair<float,float> topJetYieldUncUp   = createHistogramAndShiftsCustomVar(var1_UP_  ,topFile_, "TTJ_CMS_scale_met_unclustered_13TeVUp"  , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);
		  pair<float,float> topJetYieldUncDown = createHistogramAndShiftsCustomVar(var1_DOWN_,topFile_, "TTJ_CMS_scale_met_unclustered_13TeVDown", ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);

		  pair<float,float> topTauYieldUncUp   = createHistogramAndShiftsCustomVar(var1_UP_  ,topFile_,"TTT_CMS_scale_met_unclustered_13TeVUp"   , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 		  
		  pair<float,float> topTauYieldUncDown = createHistogramAndShiftsCustomVar(var1_DOWN_,topFile_,"TTT_CMS_scale_met_unclustered_13TeVDown" , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 

		  pair<float,float> vvtYieldUncUp      = createHistogramAndShiftsCustomVar(var1_UP_  ,vvFile_,  "VVT_CMS_scale_met_unclustered_13TeVUp"  , ("("+inputSelections+"&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		  pair<float,float> vvtYieldUncDown    = createHistogramAndShiftsCustomVar(var1_DOWN_,vvFile_,  "VVT_CMS_scale_met_unclustered_13TeVDown", ("("+inputSelections+"&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  

		  pair<float,float> vvYieldUncUp       = createHistogramAndShiftsCustomVar(var1_UP_  ,vvFile_,  "VVJ_CMS_scale_met_unclustered_13TeVUp"  , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		  pair<float,float> vvYieldUncDown     = createHistogramAndShiftsCustomVar(var1_DOWN_,vvFile_,  "VVJ_CMS_scale_met_unclustered_13TeVDown", ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
											                           
		  pair<float,float> WYieldUncUp        = createHistogramAndShiftsCustomVar(var1_UP_  ,wFile_,   "W_CMS_scale_met_unclustered_13TeVUp"    , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);
		  pair<float,float> WYieldUncDown      = createHistogramAndShiftsCustomVar(var1_DOWN_,wFile_,   "W_CMS_scale_met_unclustered_13TeVDown"  , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);

		  pair<float,float> ZTTYieldUncUp      = createHistogramAndShiftsCustomVar(var1_UP_  ,zttFile_, "ZTT_scale_met_unclustered_13TeVUp"      , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		  pair<float,float> ZTTYieldUncDown    = createHistogramAndShiftsCustomVar(var1_DOWN_,zttFile_, "ZTT_scale_met_unclustered_13TeVDown"    , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		  
		  pair<float,float> zlftYieldUncUp     = createHistogramAndShiftsCustomVar(var1_UP_  ,zllFile_, "ZL_scale_met_unclustered_13TeVUp"       , ("("+inputSelections+"&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);
		  pair<float,float> zlftYieldUncDown   = createHistogramAndShiftsCustomVar(var1_DOWN_,zllFile_, "ZL_scale_met_unclustered_13TeVDown"     , ("("+inputSelections+"&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);


		  var1_UP_   = "m_sv_ClusteredMet_UP";
		  var1_DOWN_ = "m_sv_ClusteredMet_DOWN";
		  //createHistogramAndShifts(
		  pair<float,float> zjftYieldClusUp     = createHistogramAndShiftsCustomVar(var1_UP_  ,zllFile_, "ZJ_CMS_scale_met_clustered_13TeVUp"    , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    
		  pair<float,float> zjftYieldClusDown   = createHistogramAndShiftsCustomVar(var1_DOWN_,zllFile_, "ZJ_CMS_scale_met_clustered_13TeVDown"  , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+Zweight_), luminosity_*leg1Corr*zttScale_,prefix);    
											                           
		  pair<float,float> topJetYieldClusUp   = createHistogramAndShiftsCustomVar(var1_UP_  ,topFile_, "TTJ_CMS_scale_met_clustered_13TeVUp"   , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);
		  pair<float,float> topJetYieldClusDown = createHistogramAndShiftsCustomVar(var1_DOWN_,topFile_, "TTJ_CMS_scale_met_clustered_13TeVDown" , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_+"*"+TTweight_), luminosity_*tauID_*topExtrap,prefix);

		  pair<float,float> topTauYieldClusUp   = createHistogramAndShiftsCustomVar(var1_UP_  ,topFile_, "TTT_CMS_scale_met_clustered_13TeVUp"   , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 		  
		  pair<float,float> topTauYieldClusDown = createHistogramAndShiftsCustomVar(var1_DOWN_,topFile_, "TTT_CMS_scale_met_clustered_13TeVDown" , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+TTweight_),luminosity_*tauIDCorr*topExtrap,prefix); 

		  pair<float,float> vvtYieldClusUp      = createHistogramAndShiftsCustomVar(var1_UP_  ,vvFile_,  "VVT_CMS_scale_met_clustered_13TeVUp"   , ("("+inputSelections+"&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		  pair<float,float> vvtYieldClusDown    = createHistogramAndShiftsCustomVar(var1_DOWN_,vvFile_,  "VVT_CMS_scale_met_clustered_13TeVDown" , ("("+inputSelections+"&&("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  

		  pair<float,float> vvYieldClusUp       = createHistogramAndShiftsCustomVar(var1_UP_  ,vvFile_,  "VVJ_CMS_scale_met_clustered_13TeVUp"   , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
		  pair<float,float> vvYieldClusDown     = createHistogramAndShiftsCustomVar(var1_DOWN_,vvFile_,  "VVJ_CMS_scale_met_clustered_13TeVDown" , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*tauIDCorr*vvScale_,prefix);		  
											                           
		  pair<float,float> WYieldClusUp        = createHistogramAndShiftsCustomVar(var1_UP_  ,wFile_,   "W_CMS_scale_met_clustered_13TeVUp"     , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);
		  pair<float,float> WYieldClusDown      = createHistogramAndShiftsCustomVar(var1_DOWN_,wFile_,   "W_CMS_scale_met_clustered_13TeVDown"   , ("("+inputSelections+"&&!("+ZTT_genTauSel_+"))*"+weight_), luminosity_*leg1Corr,prefix);

		  pair<float,float> ZTTYieldClusUp      = createHistogramAndShiftsCustomVar(var1_UP_  ,zttFile_, "ZTT_scale_met_clustered_13TeVUp"       , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		  pair<float,float> ZTTYieldClusDown    = createHistogramAndShiftsCustomVar(var1_DOWN_,zttFile_, "ZTT_scale_met_clustered_13TeVDown"     , ("("+inputSelections+"&&"+ZTT_genTauSel_+")*"+weight_),    luminosity_*tauIDCorr*zttScale_,prefix);    
		  
		  pair<float,float> zlftYieldClusUp     = createHistogramAndShiftsCustomVar(var1_UP_  ,zllFile_, "ZL_scale_met_clustered_13TeVUp"        , ("("+inputSelections+"&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);
		  pair<float,float> zlftYieldClusDown   = createHistogramAndShiftsCustomVar(var1_DOWN_,zllFile_, "ZL_scale_met_clustered_13TeVDown"      , ("("+inputSelections+"&&"+ZLFT_genLSel_+")*"+weight_),     luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix);

		}
		void createMETSystematicsHiggs(string inputSelections, float scale, string prefix){
		  std::string var1_UP_   = "m_sv_UncMet_UP";
		  std::string var1_DOWN_ = "m_sv_UncMet_DOWN";

		  pair<float,float> ggH125UncUp   = createHistogramAndShiftsCustomVar(var1_UP_   ,dir_+"ggH125.root" ,"ggH125_CMS_scale_met_unclustered_13TeVUp"  ,inputSelections,scale,prefix);
		  pair<float,float> ggH125UncDown = createHistogramAndShiftsCustomVar(var1_DOWN_ ,dir_+"ggH125.root" ,"ggH125_CMS_scale_met_unclustered_13TeVDown",inputSelections,scale,prefix);

		  pair<float,float> qqH125UncUp   = createHistogramAndShiftsCustomVar(var1_UP_   ,dir_+"vbfH125.root","qqH125_CMS_scale_met_unclustered_13TeVUp"  ,inputSelections,scale,prefix);
		  pair<float,float> qqH125UncDown = createHistogramAndShiftsCustomVar(var1_DOWN_ ,dir_+"vbfH125.root","qqH125_CMS_scale_met_unclustered_13TeVDown",inputSelections,scale,prefix);

		  pair<float,float> ZH125UncUp    = createHistogramAndShiftsCustomVar(var1_UP_   ,dir_+"ZH125.root"  ,"ZH125_CMS_scale_met_unclustered_13TeVUp"   ,inputSelections,scale,prefix);
		  pair<float,float> ZH125UncDown  = createHistogramAndShiftsCustomVar(var1_DOWN_ ,dir_+"ZH125.root"  ,"ZH125_CMS_scale_met_unclustered_13TeVDown" ,inputSelections,scale,prefix);

		  pair<float,float> WmH125UncUp    = createHistogramAndShiftsCustomVar(var1_UP_   ,dir_+"WmH125.root"  ,"WmH125_CMS_scale_met_unclustered_13TeVUp"   ,inputSelections,scale,prefix);
		  pair<float,float> WmH125UncDown  = createHistogramAndShiftsCustomVar(var1_DOWN_ ,dir_+"WmH125.root"  ,"WmH125_CMS_scale_met_unclustered_13TeVDown" ,inputSelections,scale,prefix);
		  pair<float,float> WpH125UncUp    = createHistogramAndShiftsCustomVar(var1_UP_   ,dir_+"WpH125.root"  ,"WpH125_CMS_scale_met_unclustered_13TeVUp"   ,inputSelections,scale,prefix);
		  pair<float,float> WpH125UncDown  = createHistogramAndShiftsCustomVar(var1_DOWN_ ,dir_+"WpH125.root"  ,"WpH125_CMS_scale_met_unclustered_13TeVDown" ,inputSelections,scale,prefix);

		  pair<float,float> ttH125UncUp   = createHistogramAndShiftsCustomVar(var1_UP_   ,dir_+"ttH125.root" ,"ttH125_CMS_scale_met_unclustered_13TeVUp"  ,inputSelections,scale,prefix);
		  pair<float,float> ttH125UncDown = createHistogramAndShiftsCustomVar(var1_DOWN_ ,dir_+"ttH125.root" ,"ttH125_CMS_scale_met_unclustered_13TeVDown",inputSelections,scale,prefix);

		  var1_UP_   = "m_sv_ClusteredMet_UP";
		  var1_DOWN_ = "m_sv_ClusteredMet_DOWN";

		  pair<float,float> ggH125ClusUp   = createHistogramAndShiftsCustomVar(var1_UP_,  dir_+"ggH125.root" ,"ggH125_CMS_scale_met_clustered_13TeVUp"  ,inputSelections,scale,prefix);
		  pair<float,float> ggH125ClusDown = createHistogramAndShiftsCustomVar(var1_DOWN_,dir_+"ggH125.root" ,"ggH125_CMS_scale_met_clustered_13TeVDown",inputSelections,scale,prefix);

		  pair<float,float> qqH125ClusUp   = createHistogramAndShiftsCustomVar(var1_UP_,  dir_+"vbfH125.root","qqH125_CMS_scale_met_clustered_13TeVUp"  ,inputSelections,scale,prefix);
		  pair<float,float> qqH125ClusDown = createHistogramAndShiftsCustomVar(var1_DOWN_,dir_+"vbfH125.root","qqH125_CMS_scale_met_clustered_13TeVDown",inputSelections,scale,prefix);

		  pair<float,float> ZH125ClusUp    = createHistogramAndShiftsCustomVar(var1_UP_,  dir_+"ZH125.root"  ,"ZH125_CMS_scale_met_clustered_13TeVUp"   ,inputSelections,scale,prefix);
		  pair<float,float> ZH125ClusDown  = createHistogramAndShiftsCustomVar(var1_DOWN_,dir_+"ZH125.root"  ,"ZH125_CMS_scale_met_clustered_13TeVDown" ,inputSelections,scale,prefix);

		  pair<float,float> WmH125ClusUp    = createHistogramAndShiftsCustomVar(var1_UP_,  dir_+"WmH125.root"  ,"WmH125_CMS_scale_met_clustered_13TeVUp"   ,inputSelections,scale,prefix);
		  pair<float,float> WmH125ClusDown  = createHistogramAndShiftsCustomVar(var1_DOWN_,dir_+"WmH125.root"  ,"WmH125_CMS_scale_met_clustered_13TeVDown" ,inputSelections,scale,prefix);
		  pair<float,float> WpH125ClusUp    = createHistogramAndShiftsCustomVar(var1_UP_,  dir_+"WpH125.root"  ,"WpH125_CMS_scale_met_clustered_13TeVUp"   ,inputSelections,scale,prefix);
		  pair<float,float> WpH125ClusDown  = createHistogramAndShiftsCustomVar(var1_DOWN_,dir_+"WpH125.root"  ,"WpH125_CMS_scale_met_clustered_13TeVDown" ,inputSelections,scale,prefix);

		  pair<float,float> ttH125ClusUp   = createHistogramAndShiftsCustomVar(var1_UP_,  dir_+"ttH125.root" ,"ttH125_CMS_scale_met_clustered_13TeVUp"  ,inputSelections,scale,prefix);
		  pair<float,float> ttH125ClusDown = createHistogramAndShiftsCustomVar(var1_DOWN_,dir_+"ttH125.root" ,"ttH125_CMS_scale_met_clustered_13TeVDown",inputSelections,scale,prefix);

		}












        /*
         * For Inclusive take the Ztt normalization directly from MC (zttFile_)
         * For a category the Ztt normalization is as follows,
         * ZttCategoryYield = ZttMCInclusiveYield * (ZttEmbedded_Category) / *Ztt(
         */

        bool runZTT(std::string preSelection,std::string prefix,std::string zShape, float topExtrap, BkgOutput &output,
                std::string categorySelection = "pt_1>-100", std::string relaxedSelection = "pt_1>-100"){

            float leg1Corr=1.0;
            if(muID_!=0) leg1Corr*=muID_;
            if(eleID_!=0) leg1Corr*=eleID_;


            std::pair<float,float> ztt  = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+Zweight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
            std::pair<float,float> zttDyUp  = createHistogramAndShifts(zttFile_,"ZTT_CMS_htt_dyShape_13TeVUp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+Zweight_+"*"+Zweight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
            std::pair<float,float> zttDyDown  = createHistogramAndShifts(zttFile_,"ZTT_CMS_htt_dyShape_13TeVDown",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZTT_genTauSel_+")*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
            std::pair<float,float> ztt1  = createHistogramAndShifts(zttFile_,"ZTT_1prong",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZTT_genTauSel_+"&&"+ZTT1PRONG_+")*"+weight_+"*"+Zweight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
            std::pair<float,float> ztt2  = createHistogramAndShifts(zttFile_,"ZTT_1prong1pi0",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZTT_genTauSel_+"&&"+ZTT1PRONG1PI0_+")*"+weight_+"*"+Zweight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
            std::pair<float,float> ztt3  = createHistogramAndShifts(zttFile_,"ZTT_3prong",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&"+ZTT_genTauSel_+"&&"+ZTT3PRONG_+")*"+weight_+"*"+Zweight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);

            std::cout<<"      ZTT Selection: "<<preSelection<<"&&"<<trigSelection_<<"&&"<<osSignalSelection_<<"&&"<<categorySelection<<std::endl;
            output.ZTT  = ztt.first;
            output.dZTT = ztt.second;

            printf("      Selection ZTT events in signal region = %f + %f \n",ztt.first,ztt.second);
            return true;
        }


        bool runTOP( std::string preSelection, std::string prefix, std::string zShape, float topExtrap, BkgOutput &output, 
                std::string categorySelection, std::string relaxedSelection ) {


            float leg1Corr=1.0;
            if(muID_!=0) leg1Corr*=muID_;
            if(eleID_!=0) leg1Corr*=eleID_;

            std::cout<<"Top weight: "<<TTweight_<<std::endl;
            std::cout<<"Top: "<<preSelection<<"&&"<<trigSelection_<<"&&"<<osSignalSelection_<<"&&"<<categorySelection<<")*"<<weight_<<"*"<<TTweight_ <<std::endl;

            std::pair<float,float> topShape      = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topShape1      = createHistogramAndShifts(topFile_,"TT_1prong",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&tauDecayMode==0)*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topShape2      = createHistogramAndShifts(topFile_,"TT_other",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+"&&tauDecayMode!=0)*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topShapeUp      = createHistogramAndShifts(topFile_,"TT_CMS_htt_ttbarShape_13TeVUp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topShapeDown      = createHistogramAndShifts(topFile_,"TT_CMS_htt_ttbarShape_13TeVDown",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);

            std::pair<float,float> topYield      = createHistogramAndShifts(topFile_,"TTYield",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);


            std::pair<float,float> toptauShape      = createHistogramAndShifts(topFile_,"TTT",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZTT_genTauSel_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topjetShape      = createHistogramAndShifts(topFile_,"TTJ",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZJFT_genLReject_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topleptonShape      = createHistogramAndShifts(topFile_,"TTL",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+ZLFT_genLSel_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            //std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);

            output.TOP  = topShape.first;
            output.dTOP = topShape.second;
            output.TTT  = toptauShape.first;
            output.dTTT = toptauShape.second;
            output.TTJ  = topjetShape.first;
            output.dTTJ = topjetShape.second;
            output.TTL  = topleptonShape.first;
            output.dTTL = topleptonShape.second;

            printf("      TTbar events in signal region = %f + %f \n",topShape.first,topShape.second);
            //Subtract the ztt ttbar overlap of 1.5% from the ttbar yield
            //not used for 2014 MSSM
            //output.TOP = output.TOP-(output.ZTT*0.015);   //only for  
            //renormalizeHistogram(filelabel_+prefix,"TT",output.TOP);
            //printf("      TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

            return true;}



	/*	bool runFF(string preSelection, string prefix, string zShape, float topExtrap, BkgOutput &output, string categorySelection, string fullSelection,string ffSelection, string ffSelectionData) 
		{
			float leg1Corr=tauID_;
			float tauIDCorr = tauID_*tauID_;
			cout<<"FF Selection= "<<"("<<ffSelection_<<"&&"<<trigSelection_<<"&&"<<categorySelection<<")"<<endl;
			std::string ffcutData = ffSelectionData+ "&&"+trigSelectionData_+"&&"+categorySelection+"&&"+signalSelection_;
			std::string ffcut     = ffSelection+     "&&"+trigSelection_    +"&&"+categorySelection+"&&"+signalSelection_;
			
            //fake factor application region for data ... 
			std::cout<<"weight applied "<<weight_<<std::endl;
			//pair<float,float> dataFF = createHistogramAndShifts(ffFile_,   "FF",("("+ffcutData+")*("+FFweight1_+"*"+FFweight2_+")"),scaleUp_,prefix); 
			pair<float,float> dataFF = createHistogramAndShifts(ffFile_,   "jetFakes",("("+ffcutData+")*("+FFweight1_+"*"+FFweight2_+")"),scaleUp_,prefix); 
            //ZTT for the real tau subtraction
			pair<float,float> ZTTFF    = createHistogramAndShifts(zttFile_,"ZTT",("("+fullSelection+"&&"+ZTT_genTauSel_+")*"+weight_+"*"+Zweight_),luminosity_*tauIDCorr*zttScale_,prefix);    
            


			//Subtracting the real taus 
			float finalYield = dataFF.first - ZTTFF.first;
			//float finalYield = dataFF.first;
			//float finalErr   = errorMult(dataFF,make_pair(LooseToTightSF,LooseToTightSFErr));
			float finalErr   = quadrature(dataFF.second,ZTTFF.second);
			//float finalErr   = dataFF.second;
			std::cout<<"FF Final Yield: "<<finalYield<<" +/- "<<finalErr<<std::endl;
			//renormalizeHistogram(filelabel_+prefix,"FF",finalYield);

			output.FF = finalYield;
			output.dFF = finalErr;
			if(shifts_.size()>0){
				FFSyst(filelabel_, prefix, "FF", 1.1, 0.1);
			}

			return true;


		}*/

        bool runQCD(std::string preSelection, std::string prefix, std::string zShape, float topExtrap, BkgOutput &output, std::string categorySelection, std::string relaxedSelection) 
        {
            float leg1Corr=1.0;
            if(muID_!=0) leg1Corr*=muID_;
            if(eleID_!=0) leg1Corr*=eleID_;
            std::pair<float,float> dataQCDShape = createHistogramAndShifts(dataFile_,"QCD","("+relaxedSelection+"&&"+trigSelectionData_+"&&"+ssSignalSelection_+"&&"+categorySelection+")",scaleUp_,prefix); 
            printf("      Data events in SS Signal QCDShape sideband region = %f + %f \n",dataQCDShape.first,dataQCDShape.second);
            std::pair<float,float> ZQCDShape = createHistogramAndShifts(zttFile_,"ZQCD","("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+Zweight_,luminosity_,prefix); 
            printf("      Z events in SS Signal QCDShape sideband region = %f + %f \n",ZQCDShape.first,ZQCDShape.second);
            std::pair<float,float> TopQCDShape = createHistogramAndShifts(topFile_,"TopQCD","("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_,luminosity_,prefix); 
            printf("      TOP events in SS Signal QCDShape sideband region = %f + %f \n",TopQCDShape.first,TopQCDShape.second);
            std::pair<float,float> VVQCDShape       = createHistogramAndShifts(vvFile_,"VVQCD",("("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_,prefix,false);
            printf("      VV events in SS Signal QCDShape sideband region = %f + %f \n",VVQCDShape.first,VVQCDShape.second);
            std::pair<float,float> WQCDLowShape       = createHistogramAndShifts(wFile_,"WQCD",("("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix,false);
            /*
               std::pair<float,float> dataQCDShape = createHistogramAndShifts(dataFile_,"QCD","("+relaxedSelection+"&&"+trigSelectionData_+"&&"+ssSignalSelection_+")",scaleUp_,prefix); 
               printf("      Data events in SS Signal QCDShape sideband region = %f + %f \n",dataQCDShape.first,dataQCDShape.second);
               std::pair<float,float> ZQCDShape = createHistogramAndShifts(zttFile_,"ZQCD","("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+")*"+weight_+"*"+Zweight_,luminosity_,prefix); 
               printf("      Z events in SS Signal QCDShape sideband region = %f + %f \n",ZQCDShape.first,ZQCDShape.second);
               std::pair<float,float> TopQCDShape = createHistogramAndShifts(topFile_,"TopQCD","("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+")*"+weight_+"*"+TTweight_,luminosity_,prefix); 
               printf("      TOP events in SS Signal QCDShape sideband region = %f + %f \n",TopQCDShape.first,TopQCDShape.second);
               std::pair<float,float> VVQCDShape       = createHistogramAndShifts(vvFile_,"VVQCD",("("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+")*"+weight_),luminosity_,prefix,false);
               printf("      VV events in SS Signal QCDShape sideband region = %f + %f \n",VVQCDShape.first,VVQCDShape.second);
               std::pair<float,float> WQCDLowShape       = createHistogramAndShifts(wFile_,"WQCD",("("+relaxedSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*leg1Corr,prefix,false);
               */



            std::cout<<"QCD Selections= "<<"("<<relaxedSelection<<"&&"<<trigSelectionData_<<"&&"<<ssSignalSelection_<<")"<<std::endl;
            std::pair<float,float> dataQCD = createHistogramAndShifts(dataFile_,"QCDYield","("+preSelection+"&&"+trigSelectionData_+"&&"+ssSignalSelection_+"&&"+categorySelection+")",scaleUp_,prefix); 
            printf("      Data events in SS Signal QCD sideband region = %f + %f \n",dataQCD.first,dataQCD.second);
            std::pair<float,float> ZQCD = createHistogramAndShifts(zttFile_,"ZQCDYield","("+preSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+Zweight_,luminosity_,prefix); 
            printf("      Z events in SS Signal QCD sideband region = %f + %f \n",ZQCD.first,ZQCD.second);
            std::pair<float,float> TopQCD = createHistogramAndShifts(topFile_,"TopQCDYield","("+preSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_+"*"+TTweight_,luminosity_,prefix); 
            printf("      TOP events in SS Signal QCD sideband region = %f + %f \n",TopQCD.first,TopQCD.second);
            std::pair<float,float> VVQCD       = createHistogramAndShifts(vvFile_,"VVQCDYield",("("+preSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_,prefix,false);
            printf("      VV events in SS Signal QCD sideband region = %f + %f \n",VVQCD.first,VVQCD.second);

            std::pair<float,float> ssWLow       = createHistogramAndShifts(wFile_,"WQCDYield",("("+preSelection+"&&"+trigSelection_+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix,false);
            printf("      (MonteCarlo) W events in SS region = %f + %f \n",ssWLow.first,ssWLow.second);

            /*
             * DATADRIVEN W FOUND 
             */

            //Now subtracting off bkgd shapes from data ss shape
            subtractHistogram(filelabel_+prefix,"QCDYield","ZQCDYield");
            subtractHistogram(filelabel_+prefix,"QCDYield","VVQCDYield");
            subtractHistogram(filelabel_+prefix,"QCDYield","TopQCDYield");
            subtractHistogram(filelabel_+prefix,"QCDYield","WQCDYield");

            subtractHistogram(filelabel_+prefix,"QCD","ZQCD");
            subtractHistogram(filelabel_+prefix,"QCD","VVQCD");
            subtractHistogram(filelabel_+prefix,"QCD","TopQCD");
            subtractHistogram(filelabel_+prefix,"QCD","WQCD");


            std::pair<float,float> ssQCD = std::make_pair(TMath::Nint(dataQCD.first
                        -ssWLow.first
                        -TopQCD.first
                        -VVQCD.first
                        -ZQCD.first),
                    sqrt(dataQCD.second*dataQCD.second
                        +ssWLow.second*ssWLow.second
                        +TopQCD.second*TopQCD.second
                        +VVQCD.second*VVQCD.second
                        +ZQCD.second*ZQCD.second));


            if(ssQCD.first<0) {
                ssQCD.first=0.0000001;
                ssQCD.second=1.8;
            }

            printf("SS QCD in  core  =%f -%f -%f -%f -%f= %f +- %f \n",
                    dataQCD.first,
                    ssWLow.first,
                    TopQCD.first,
                    ZQCD.first,
                    VVQCD.first,
                    ssQCD.first,
                    ssQCD.second);


            printf("5. Extrapolate SS QCD -> OS QCD \n");
            std::pair<float,float> osQCD = std::make_pair(ssQCD.first*qcdFactor_,
                    sqrt(ssQCD.second*ssQCD.second*qcdFactor_*qcdFactor_
                        +qcdFactorErr_*qcdFactorErr_*ssQCD.first*ssQCD.first));

            //Now Renormalize
            renormalizeHistogram(filelabel_+prefix,"QCD",osQCD.first);

            printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,qcdFactor_,osQCD.first,osQCD.second);

            output.QCD  = osQCD.first;    
            output.dQCD = osQCD.second;

            if(shifts_.size()>0){
                qcdSyst(filelabel_, prefix, "QCD", 1.1, 0.1);
            }

            return true;


        }

        /*
           bool runW(std::string preSelection,std::string prefix,std::string zShape, float topExtrap, BkgOutput &output, std::string categorySelection, std::string relaxedSelection, std::string wSel) {
//WShape is relaxed
std::pair<float,float> wShape         = createHistogramAndShifts(wFile_,"W",("("+relaxedSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_,prefix,false);
//std::cout<<"Relaxed Selection: "<<relaxedSelection<<std::endl;
std::pair<float,float> wYield         = createHistogramAndShifts(wFile_,"WYield",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_,prefix,false);
std::cout<<"Straight W MC Yield: "<<wYield.first<<" stat error:" <<wYield.second<<std::endl;
std::cout<<"Straight W MC Yield: "<<preSelection+"&&"<<trigSelection_<<"&&"<<categorySelection<<"&&"<<osSignalSelection_<<std::endl; 
renormalizeHistogram(filelabel_+prefix,"W",wYield.first);
output.W  = wYield.first;
output.dW  = wYield.second;
return true;
}
*/

bool runFF(std::string preSelection, std::string prefix, std::string zShape, float topExtrap, BkgOutput &output, std::string categorySelection, std::string relaxedSelection){

            std::string processSelection = "gen_match_2==5";
            //Making the anti-isolated histograms from MC
            TCut preselection = "pt_1>21&&pt_2>30&&npv>0&&id_m_medium_1>0&&tightMuons<=1&&tightElectrons==0&&diLeptons==0&&againstMuonTight3_2>0&&againstElectronVLooseMVA6_2>0";
            TCut ApplicationRegion = "byVLooseIsolationMVArun2v1DBoldDMwLT_2>0.5&&byTightIsolationMVArun2v1DBoldDMwLT_2<0.5";
            TCut SignalRegion = "byTightIsolationMVArun2v1DBoldDMwLT_2>0.5";

            TCut trueSelection = "gen_match_2==5";
            TCut trueLSelection = "gen_match_2<5";
            TCut fakeSelection = "gen_match_2==6";
    
            std::pair<float,float> vvtYield      = createHistogramAndShifts(vvFile_,"VVT_AI",("("+preselection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+trueSelection+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VVT before error inflation: "<<vvtYield.first<<std::endl;

            std::pair<float,float> vvjYield      = createHistogramAndShifts(vvFile_,"VVJ_AI",("("+preselection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+fakeSelection+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VVJ before error inflation: "<<vvjYield.first<<std::endl;

            std::pair<float,float> vvlYield      = createHistogramAndShifts(vvFile_,"VVL_AI",("("+preselection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+trueLSelection+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
            std::cout<<"      VVL before error inflation: "<<vvlYield.first<<std::endl;


            std::pair<float,float> toptauShape      = createHistogramAndShifts(topFile_,"TTT_AI",("("+preselection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+trueSelection+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topjetShape      = createHistogramAndShifts(topFile_,"TTJ_AI",("("+preselection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+fakeSelection+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            std::pair<float,float> topleptonShape      = createHistogramAndShifts(topFile_,"TTL_AI",("("+preselection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+trueLSelection+"&&"+categorySelection+")*"+weight_+"*"+TTweight_), luminosity_*leg1Corr*tauID_*topExtrap, prefix);
            //std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);




            // Data
            TFile * datafile = new TFile(dataFile_.c_str());
            TTree *t = (TTree*) datafile->Get((channel_+"EventTree/eventTree").c_str());
            std::cout<<"Data Entries   "<<t->GetEntries()<<std::endl;

            std::cout<<"Running FF ..."<<std::endl;
            generateFFHistograms(t,"data",preSelection, prefix, zShape, topExtrap, output, categorySelection, relaxedSelection);
            t->Delete();
            datafile->Close();

            //Now that we have all the distributions and shapes we need to subtract the MC from the Data to get the jetFakes distributions 
            //access to all the histograms we just made 
            std::string folder = filelabel_+prefix;

            fout_->cd(folder.c_str());

            TH1F * fakefactorhisto  = new TH1F("jetFakes","jetFakes",bins_,min_,max_);
            //running the systematics 
            std::vector<std::string>  ffsystematics =
                                                      {
                                                         "qcd_syst_up",                  
                                                         "qcd_dm0_njet0_stat_up",        
                                                         "qcd_dm0_njet1_stat_up",        
                                                         "w_syst_up",                    
                                                         "w_dm0_njet0_stat_up",          
                                                         "w_dm0_njet1_stat_up",          
                                                         "tt_syst_up",                   
                                                         "tt_dm0_njet0_stat_up",         
                                                         "tt_dm0_njet1_stat_up",         
                                                         "qcd_syst_down",                  
                                                         "qcd_dm0_njet0_stat_down",        
                                                         "qcd_dm0_njet1_stat_down",        
                                                         "w_syst_down",                    
                                                         "w_dm0_njet0_stat_down",          
                                                         "w_dm0_njet1_stat_down",          
                                                         "tt_syst_down",                   
                                                         "tt_dm0_njet0_stat_down",         
                                                         "tt_dm0_njet1_stat_down"         };

            int numsys = ffsystematics.size(); 

            std::vector<ROOT.TH1F*> FFHistovector;

            for(auto ffsyst : ffsystematics){
                TH1F * fakefactorsyshisto  = new TH1F(("jetFakes_"+ffsyst).c_str(),("jetFakes_"+ffsyst).c_str(),bins_,min_,max_);
                FFHistovector.push_back(fakefactorsyshisto);
                TH1F * W    = (TH1D*) fout_->Get((folder+"/W"  +ffsyst).c_str() ); 
                TH1F * ZJ   = (TH1D*) fout_->Get((folder+"/ZJ" +ffsyst).c_str() );
                TH1F * VVJ  = (TH1D*) fout_->Get((folder+"/VVJ"+ffsyst).c_str() );
                TH1F * VVT  = (TH1D*) fout_->Get((folder+"/VVT"+ffsyst).c_str() );
                TH1F * TTT  = (TH1D*) fout_->Get((folder+"/TTT"+ffsyst).c_str() );
                TH1F * TTJ  = (TH1D*) fout_->Get((folder+"/TTJ"+ffsyst).c_str() );
                TH1F * ZTT  = (TH1D*) fout_->Get((folder+"/TTJ"+ffsyst).c_str() );
                TH1F * data = (TH1D*) fout_->Get((folder+"/data_obs").c_str());
                fakefactorsyshisto->Add(data); 
                fakefactorsyshisto->Add(W,-1); 
                fakefactorsyshisto->Add(ZJ,-1); 
                fakefactorsyshisto->Add(VVJ,-1); 
                fakefactorsyshisto->Add(VVT,-1); 
                fakefactorsyshisto->Add(TTT,-1); 
                fakefactorsyshisto->Add(TTJ,-1); 
                fakefactorsyshisto->Add(ZTT,-1);
                fakefactorsyshisto  -> Write((folder+fakefactorsyshisto->GetName()).c_str(),TObject::kOverwrite);
                //cleaning up 
                W    -> Delete(); 
                ZJ   -> Delete();
                VVJ  -> Delete();
                VVT  -> Delete();
                TTT  -> Delete();
                TTJ  -> Delete();
                ZTT  -> Delete();
                data -> Delete();
                fakefactorsyshisto->Delete();
            }
            //TH1F * fakefactorhisto_qcd_syst_up  = new TH1F("jetFakes_qcd_syst_up","jetFakes_qcd_syst_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_qcd_dm0_njet0_stat_up  = new TH1F("jetFakes_qcd_dm0_njet0_stat_up","jetFakes_qcd_dm0_njet0_stat_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_qcd_dm0_njet1_stat_up  = new TH1F("jetFakes_qcd_dm0_njet1_stat_up","jetFakes_qcd_dm0_njet1_stat_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_w_syst_up  = new TH1F("jetFakes_w_syst_up","jetFakes_w_syst_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_w_dm0_njet0_stat_up  = new TH1F("jetFakes_w_dm0_njet0_stat_up","jetFakes_w_dm0_njet0_stat_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_w_dm0_njet1_stat_up  = new TH1F("jetFakes_w_dm0_njet1_stat_up","jetFakes_w_dm0_njet1_stat_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_tt_syst_up  = new TH1F("jetFakes_tt_syst_up","jetFakes_tt_syst_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_tt_dm0_njet0_stat_up  = new TH1F("jetFakes_tt_dm0_njet0_stat_up","jetFakes_tt_dm0_njet0_stat_up",bins_,min_,max_);
            //TH1F * fakefactorhisto_tt_dm0_njet1_stat_up  = new TH1F("jetFakes_tt_dm0_njet1_stat_up","jetFakes_tt_dm0_njet1_stat_up",bins_,min_,max_);

            //TH1F * fakefactorhisto_qcd_syst_down  = new TH1F("jetFakes_qcd_syst_down","jetFakes_qcd_syst_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_qcd_dm0_njet0_stat_down  = new TH1F("jetFakes_qcd_dm0_njet0_stat_down","jetFakes_qcd_dm0_njet0_stat_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_qcd_dm0_njet1_stat_down  = new TH1F("jetFakes_qcd_dm0_njet1_stat_down","jetFakes_qcd_dm0_njet1_stat_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_w_syst_down  = new TH1F("jetFakes_w_syst_down","jetFakes_w_syst_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_w_dm0_njet0_stat_down  = new TH1F("jetFakes_w_dm0_njet0_stat_down","jetFakes_w_dm0_njet0_stat_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_w_dm0_njet1_stat_down  = new TH1F("jetFakes_w_dm0_njet1_stat_down","jetFakes_w_dm0_njet1_stat_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_tt_syst_down  = new TH1F("jetFakes_tt_syst_down","jetFakes_tt_syst_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_tt_dm0_njet0_stat_down  = new TH1F("jetFakes_tt_dm0_njet0_stat_down","jetFakes_tt_dm0_njet0_stat_down",bins_,min_,max_);
            //TH1F * fakefactorhisto_tt_dm0_njet1_stat_down  = new TH1F("jetFakes_tt_dm0_njet1_stat_down","jetFakes_tt_dm0_njet1_stat_down",bins_,min_,max_);
             
            //TH1F * W    = (TH1D*) fout_->Get((folder+"/W"  ).c_str() ); 
            //TH1F * ZJ   = (TH1D*) fout_->Get((folder+"/ZJ" ).c_str() );
            //TH1F * VVJ  = (TH1D*) fout_->Get((folder+"/VVJ").c_str() );
            //TH1F * VVT  = (TH1D*) fout_->Get((folder+"/VVT").c_str() );
            //TH1F * TTT  = (TH1D*) fout_->Get((folder+"/TTT").c_str() );
            //TH1F * TTJ  = (TH1D*) fout_->Get((folder+"/TTJ").c_str() );
            //TH1F * ZTT  = (TH1D*) fout_->Get((folder+"/TTJ").c_str() );
            //TH1F * data = (TH1D*) fout_->Get((folder+"/data_obs").c_str());
            //fakefactorhisto  = data - W - ZJ - VVJ - VVT - TTT - TTJ - ZTT;

            return true;

}
bool runW(std::string preSelection,std::string prefix,std::string zShape, float topExtrap, BkgOutput &output, std::string categorySelection, std::string relaxedSelection, std::string wSel) {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;



    std::pair<float,float> wYield         = createHistogramAndShifts(wFile_,"WTmp",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix,false);
    std::pair<float,float> wShape         = createHistogramAndShifts(wFile_,"W",("("+relaxedSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix,false);

    //First get data in Sideband
    std::pair<float,float> dataYSdb     = createHistogramAndShifts(dataFile_,"data_obs_sdb","("+preSelection+"&&"+trigSelectionData_+"&&"+categorySelection+"&&"+osWSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataYieldSdb = convertToPoisson(dataYSdb);

    //then get ttbar in sideband
    std::pair<float,float> topYieldSdb      = createHistogramAndShifts(topFile_,"TT_SDB",("("+preSelection+"&&"+trigSelection_+"&&"+categorySelection+"&&"+osWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);
    std::pair<float,float> topInflYieldSdb  = inflateError(topYieldSdb,topErr_);
    printf("TTbar events in sideband region = %f + %f \n",topYieldSdb.first,topInflYieldSdb.second);

    //Next get Diboson in sideband
    std::pair<float,float> vvYieldSdb      = createHistogramAndShifts(vvFile_,"VV_SDB",("("+preSelection+"&&"+trigSelection_+"&&"+categorySelection+"&&"+osWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
    std::pair<float,float> vvInflYieldSdb  = inflateError(vvYieldSdb,vvErr_);
    printf("Diboson events in sideband region = %f + %f \n",vvYieldSdb.first,vvInflYieldSdb.second);

    //finally get Z in sideband
    std::pair<float,float> zSDB        = createHistogramAndShifts(zttFile_,"Z_SDB",("("+preSelection+"&&"+trigSelection_+"&&"+categorySelection+"&&"+osWSelection_+")*"+weight_+"*"+Zweight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
    printf("Z events in sideband region = %f + %f \n",zSDB.first,zSDB.second);

    //Run OS+LS + MT method
    printf("1. Subtract TTbar and diboson from sideband");
    std::pair<float,float> osWHigh = std::make_pair(TMath::Nint(dataYieldSdb.first
                -topInflYieldSdb.first
                -vvInflYieldSdb.first
                -zSDB.first),
            sqrt(dataYieldSdb.second*dataYieldSdb.second
                +topInflYieldSdb.second*topInflYieldSdb.second
                +vvInflYieldSdb.second*vvInflYieldSdb.second
                +zSDB.second*zSDB.second));

    printf("OS W in sideband  =%f -%f -%f -%f  = %f +- %f \n",dataYieldSdb.first,topInflYieldSdb.first,vvInflYieldSdb.first,zSDB.first,osWHigh.first,osWHigh.second);


    std::pair<float,float> wFactor = extractWFactor(wFile_,relaxedSelection+"&&"+trigSelection_+"&&"+categorySelection,prefix,osWSelection_,osSignalSelection_);
    //std::pair<float,float> wFactor = extractWFactor(wFile_,preSelection,prefix,osWSelection_,osSignalSelection_);
    printf("W extrapolation factor as measured in corrected MC = %f +- %f\n",wFactor.first,wFactor.second);

    //std::pair<float,float> wFactorUp = extractWFactor(wFile_,preSelection+"&&"+trigSelection_+"&&charge==0&&"+categorySelection+"",prefix,"WWeightUp");
    //std::pair<float,float> wFactorDown = extractWFactor(wFile_,preSelection+"&&"+trigSelection_+"&&charge==0&&"+categorySelection+"",prefix,"WWeightDown");

    printf("2. Extrapolate W in the low MT region\n");
    std::pair<float,float> osWLow = std::make_pair(osWHigh.first*wFactor.first,
            sqrt(osWHigh.first*osWHigh.first*wFactor.second*wFactor.second+osWHigh.second*osWHigh.second*wFactor.first*wFactor.first));

    printf("OS W  in core  =%f *%f  = %f +- %f \n",osWHigh.first,wFactor.first,osWLow.first,osWLow.second);
    renormalizeHistogram(filelabel_+prefix,"W",osWLow.first);

    printf("OS W MC in signal reg  = %f +- %f \n", wYield.first, wYield.second);
    //std::pair<float,float> wMCYield       = createHistogramAndShifts(wFile_,"WTMP",("("+preSelection+"&&"+trigSelection_+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix);
    //
    output.W  = osWLow.first;
    output.dW = osWLow.second;
    return true;
}

//-------------Helper Functions------------------


void addHistogramZTT(std::string folder, std::string histo1, std::string histo2)
{
    std::cout<<"In AddHistogramZTT"<<std::endl;
    addHistogram(folder,histo1,histo2);
    for(unsigned int i=0;i<shifts_.size();++i) {
        TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1+"_"+shiftsPostFix_[i]+"Up").c_str());
        if(h1!=0) 
        {
            addHistogram(folder,(histo1+"_"+shiftsPostFix_[i]+"Up").c_str(),histo2);
        }
        else
        {
            printf("Shift not found = %s\n",(folder+"/"+histo1+"_"+shiftsPostFix_[i]+"Up").c_str());
        }
        TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo1+"_"+shiftsPostFix_[i]+"Down").c_str());
        if(h2!=0)
        {
            addHistogram(folder,(histo1+"_"+shiftsPostFix_[i]+"Down").c_str(),histo2);
        }       
        else
        {
            printf("Shift not found = %s\n",(folder+"/"+histo1+"_"+shiftsPostFix_[i]+"Down").c_str());
        }
    }//end for


}//end addHistogram ZTT

std::pair<float,float> createHistogramAndShifts(std::string file,std::string name, std::string cut,float scaleFactor = 1, std::string postfix = "",bool normUC  = true, bool keys=false,bool ShapeUncertainty=true) {
    TFile *f  = new TFile(file.c_str());
    if(f==0) printf("Not file Found\n");
    //get the nominal tree first
    std::string append = "";
    if((name=="data_obs"||name=="data_obs_ss"||name=="data_obs_sdb"||name=="data_obs_ss_sdb"||name=="QCD"||name=="QCDYield")||((name=="ZJ_1prong"||name=="ZL_1prong"||name=="ZTT_1prong")&&variable_=="m_2")){
        append="";
    }

    TTree *t= (TTree*)f->Get((channel_+"EventTree"+append+"/eventTree").c_str());
    if(t==0) printf("Not Tree Found in file %s\n",file.c_str());
    std::pair<float,float> yield;

    if(!keys)
        yield =makeHistogram(t,filelabel_+postfix,name,cut,scaleFactor);
    else
        yield =makeTHKeys(t,filelabel_+postfix,name,cut,scaleFactor);

    //now the shifts
    std::pair<float,float> tmpYield;
    for(unsigned int i=0;i<shifts_.size();++i) {

        TTree *ts= (TTree*)f->Get((channel_+"EventTree"+shifts_[i]+"Up/eventTree").c_str());
        if(ts!=0) {
            if(!keys)
                tmpYield = makeHistogram(ts,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",cut,scaleFactor);
            else
                tmpYield = makeTHKeys(ts,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",cut,scaleFactor);

            if(!normUC)
                scaleHistogram(filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",yield.first/tmpYield.first);

        }
        TTree *td= (TTree*)f->Get((channel_+"EventTree"+shifts_[i]+"Down/eventTree").c_str());
        if(td!=0) {
            if(!keys)
                tmpYield = makeHistogram(td,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",cut,scaleFactor);
            else
                tmpYield = makeTHKeys(td,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",cut,scaleFactor);

            if(!normUC)
                scaleHistogram(filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",yield.first/tmpYield.first);

        }
    }
    f->Close();
    return yield;
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,
              const std::string& replace) {
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
}

std::pair<float,float> createHistogramAndShiftsFinal(std::string file,std::string name, std::string cut,float scaleFactor = 1, std::string postfix = "",bool normUC  = true, bool keys=false,bool ShapeUncertainty=true) {
    TFile *f  = new TFile(file.c_str());
    if(f==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *t= (TTree*)f->Get((channel_+"EventTreeFinal/eventTree").c_str());
    if(t==0) printf("Not Tree Found in file %s\n",file.c_str());

    std::pair<float,float> yield;

    if(!keys)
        yield =makeHistogram(t,filelabel_+postfix,name,cut,scaleFactor);
    else
        yield =makeTHKeys(t,filelabel_+postfix,name,cut,scaleFactor);

    //now the shifts
    std::pair<float,float> tmpYield;
    for(unsigned int i=0;i<shifts_.size();++i) {

        TTree *ts= (TTree*)f->Get((channel_+"EventTreeFinal"+shifts_[i]+"Up/eventTree").c_str());
        if(ts!=0) {
            if(!keys)
                tmpYield = makeHistogram(ts,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",cut,scaleFactor);
            else
                tmpYield = makeTHKeys(ts,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",cut,scaleFactor);

            if(!normUC)
                scaleHistogram(filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",yield.first/tmpYield.first);

        }
        TTree *td= (TTree*)f->Get((channel_+"EventTreeFinal"+shifts_[i]+"Down/eventTree").c_str());
        if(td!=0) {
            if(!keys)
                tmpYield = makeHistogram(td,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",cut,scaleFactor);
            else
                tmpYield = makeTHKeys(td,filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",cut,scaleFactor);

            if(!normUC)
                scaleHistogram(filelabel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",yield.first/tmpYield.first);

        }
    }
    f->Close();
    return yield;
}


void setBinning(const std::vector<double>& binning) {
    binning_ = binning;
}

std::pair<float,float> inflateError(std::pair<float,float> input,float error, float error2 =0.0, float error3 = 0.0 ) {
    float value = input.first;
    float err = sqrt(input.second*input.second+(input.first*error)*(input.first*error)+(input.first*error2)*(input.first*error2)+(input.first*error3)*(input.first*error3));

    if(err>value) {
        err=0.99*value;
        printf("Found error above value -> Setting error to value\n");
    }

    return std::make_pair(value,err);
}

void renormalizeHistogram(std::string folder, std::string histo, float yield)
{

    TH1F * h =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    double scaleFactor = yield/h->Integral();


    h->Scale(scaleFactor);
    fout_->cd(folder.c_str());
    h->Write(h->GetName(),TObject::kOverwrite);

    for(unsigned int i=0;i<shifts_.size();++i) {
        TH1F * hh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
        if(hh!=0) {
            hh->Scale(scaleFactor);
            fout_->cd(folder.c_str());
            hh->Write(hh->GetName(),TObject::kOverwrite);
        }
        else
        {
            printf("Shift not found = %s\n",(folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
        }


        TH1F * hhh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Down").c_str());
        if(hhh!=0) {
            hhh->Scale(scaleFactor);
            fout_->cd(folder.c_str());
            hhh->Write(hhh->GetName(),TObject::kOverwrite);
        }
        else
        {
            printf("Shift not found\n");
        }
    }
}

float quadrature(float value, float error, float e0 = 0.0, float e1 = 0.0 ,float e2 = 0.0, float e3 = 0.0 ,float e4 = 0.0, float e5 = 0.0 ){
    float returnValue = sqrt(error*error+(e0*e0+e1*e1+e2*e2+e3*e3+e4*e4+e5*e5)*value*value);
    return returnValue;
}

std::pair<float,float> makeHistogram(TTree* tree,std::string folder,std::string name,std::string cut,float scaleFactor = 1.) {

    if(fout_->Get(folder.c_str())==0)
        fout_->mkdir(folder.c_str());
    TH1F *h=0;

    TString variableOld_=variable_;
    if((name=="data_obs"||name=="data_obs_ss"||name=="data_obs_sdb"||name=="data_obs_ss_sdb"||name=="QCD")&&variable_=="pt2ES"){
        variable_="pt_2";
    }


    if(binning_.size()==0)
        h= new TH1F(name.c_str(),name.c_str(),bins_,min_,max_);
    else 
        h = new TH1F(name.c_str(),name.c_str(),binning_.size()-1,&binning_[0]);
    h->Sumw2();

    tree->Draw((variable_+">>"+name).c_str(),cut.c_str());

    variable_=variableOld_;//

    h->Scale(scaleFactor);

    if(verbose_>0)
        std::cout<< " " <<name<<": "<<h->Integral()<<std::endl;

    //     printf("Created Histogram %s with entries=%f\n",name.c_str(),h->Integral());
    fout_->cd(folder.c_str());

    Double_t error=0.0;
    //LD
    float yield = h->IntegralAndError(1,h->GetNbinsX(),error,"");
    //float yield = h->IntegralAndError(0,h->GetNbinsX()+1,error,"");
    if(yield == 0){
        h->SetBinContent(1,0.00001);
    }
    h->Write(h->GetName(),TObject::kOverwrite);

    return std::make_pair(yield,error);
}

		pair<float,float> createHistogramAndShiftsCustomVar(string variableIn, string file,string name, string cut,float scaleFactor = 1, string postfix = "",bool normUC  = true, bool keys=false,bool ShapeUncertainty=true) {
			TFile *f  = new TFile(file.c_str());
			if(f==0) printf("Not file Found\n");
			//get the nominal tree first
			TTree *t= (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());
			if(t==0) printf("Not Tree Found in file %s\n",file.c_str());
			pair<float,float> yield;

			if(!keys)
			  yield =makeHistogramCustomVar(variableIn, t,filelabel_+postfix,name,cut,scaleFactor);
			else
			  yield =makeTHKeys(t,filelabel_+postfix,name,cut,scaleFactor);

			f->Close();
			return yield;
		}



		pair<float,float> makeHistogramCustomVar(string variableIn, TTree* tree,string folder,string name,string cut, float scaleFactor = 1.) {

			if(fout_->Get(folder.c_str())==0)
				fout_->mkdir(folder.c_str());
			TH1F *h=0;


			if(binning_.size()==0)
				h= new TH1F(name.c_str(),name.c_str(),bins_,min_,max_);
			else 
				h = new TH1F(name.c_str(),name.c_str(),binning_.size()-1,&binning_[0]);
			h->Sumw2();

			tree->Draw((variableIn+">>"+name).c_str(),cut.c_str());

			h->Scale(scaleFactor);

			if(verbose_>0)
			  cout<< " " <<name<<": "<<h->Integral()<<endl;

			fout_->cd(folder.c_str());

			Double_t error=0.0;
			//LD
			float yield = h->IntegralAndError(1,h->GetNbinsX(),error,"");

			if(yield == 0){
			  h->SetBinContent(1,0.00001);
			}
			h->Write(h->GetName(),TObject::kOverwrite);

			return make_pair(yield,error);
		}


void close() {
    fout_->Close();
}


std::pair<float,float> makeTHKeys(TTree* tree,std::string folder,std::string name,std::string cut,float scaleFactor = 1.) {

    if(fout_->Get(folder.c_str())==0)
        fout_->mkdir(folder.c_str());

    TH1Keys *h=0;

    if(binning_.size()==0)
        h= new TH1Keys("tmp","tmp",bins_,min_,max_,"a",0.5);
    else 
        h = new TH1Keys("tmp","tmp",binning_.size()-1,&binning_[0],"a",0.5);
    tree->Draw((variable_+">>tmp").c_str(),cut.c_str());

    if(h->Integral()==0.000) {
        printf("Keys for %s failed, retrying\n",name.c_str());
        delete h;
        if(binning_.size()==0)
            h= new TH1Keys("tmp","tmp",bins_,min_,max_,"a",0.5);
        else 
            h = new TH1Keys("tmp","tmp",binning_.size()-1,&binning_[0],"a",0.5);
        tree->Draw((variable_+">>tmp").c_str(),cut.c_str());

        if(h->Integral()==0.0) {
            printf("KEYS FAILED AGAIN \n");

        }
    }

    //now get the yield
    TH1F *hh=0;
    if(binning_.size()==0)
        hh= new TH1F("tmp2",name.c_str(),bins_,min_,max_);
    else 
        hh = new TH1F("tmp2",name.c_str(),binning_.size()-1,&binning_[0]);
    tree->Draw((variable_+">>tmp2").c_str(),cut.c_str());
    hh->Scale(scaleFactor);
    Double_t error=0.0;
    float yield = hh->IntegralAndError(1,hh->GetNbinsX(),error,"");

    fout_->cd(folder.c_str());
    TH1F * histo =(TH1F*) h->GetHisto();
    histo->Scale(yield/histo->Integral());
    histo->SetName(name.c_str());
    histo->Write();


    delete h;
    delete hh;

    return std::make_pair(yield,error);
}

std::pair<float,float> createHistogramShifted(std::string file,std::string name, std::string cut,std::string shift,float scaleFactor = 1, std::string postfix = "") {
    TFile *f  = new TFile(file.c_str());
    if(f==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *t= (TTree*)f->Get((channel_+"EventTreeFinal/eventTree").c_str());
    if(t==0) printf("Not Tree Found in file %s\n",file.c_str());

    std::pair<float,float> yield;

    yield =makeHistogramShifted(t,filelabel_+postfix,name,cut,shift,scaleFactor);

    f->Close();
    return yield;
}

std::pair<float,float> makeHistogramShifted(TTree* tree,std::string folder,std::string name,std::string cut, std::string shift,float scaleFactor = 1.) {

    if(fout_->Get(folder.c_str())==0)
        fout_->mkdir(folder.c_str());
    TH1F *h=0;

    if(binning_.size()==0)
        h= new TH1F(name.c_str(),name.c_str(),bins_,min_,max_);
    else 
        h = new TH1F(name.c_str(),name.c_str(),binning_.size()-1,&binning_[0]);
    h->Sumw2();


    tree->Draw((variable_+"*"+shift+">>"+name).c_str(),cut.c_str());

    h->Scale(scaleFactor);
    //     printf("Created Histogram %s with entries=%f\n",name.c_str(),h->Integral());
    fout_->cd(folder.c_str());

    Double_t error=0.0;
    float yield = h->IntegralAndError(1,h->GetNbinsX(),error,"");
    if(yield == 0){
        h->SetBinContent(1,0.00001);
    }
    h->Write(h->GetName(),TObject::kOverwrite);

    return std::make_pair(yield,error);
}

void scaleHistogram(std::string folder, std::string histo, float scaleFactor)
{
    TH1F * h =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    h->Scale(scaleFactor);
    fout_->cd(folder.c_str());
    h->Write(h->GetName(),TObject::kOverwrite);
    fout_->cd();

    for(unsigned int i=0;i<shifts_.size();++i) {
        TH1F * hh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
        if(hh!=0) {
            hh->Scale(scaleFactor);
            fout_->cd(folder.c_str());
            hh->Write(hh->GetName(),TObject::kOverwrite);
            fout_->cd();
        }

        TH1F * hhh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Down").c_str());
        if(hhh!=0) {
            hhh->Scale(scaleFactor);
            fout_->cd(folder.c_str());
            hhh->Write(hhh->GetName(),TObject::kOverwrite);
            fout_->cd();
        }

    }
}


std::pair<float,float> extractRFactor(std::string file,std::string preselection,std::string postfix) {
    TFile *f  = new TFile (file.c_str());
    TTree *t = (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());

    std::pair<float,float> ss;
    std::pair<float,float> os;
    ss = makeHistogram(t,filelabel_+postfix,"W_SS",("("+preselection+"&&charge!=0)*"+weight_).c_str());
    os = makeHistogram(t,filelabel_+postfix,"W_OS",("("+preselection+"&&charge==0)*"+weight_).c_str());

    std::cout<<"W Rfactor Selection: ("<<preselection+"&&(charge requirement) )*"<<weight_<<std::endl;
    std::cout<<"W + Jets SS: "<< ss.first<<" OS: "<< os.first<<std::endl;

    float factor = os.first/ss.first;
    float factorerrStat = sqrt(os.second*os.second + ss.second*ss.second);
    //float factorerrSyst = factor*wFactorErr_;
    //float factorErr = sqrt(factorerrStat*factorerrStat+factorerrSyst*factorerrSyst);
    float factorErr = factorerrStat; 

    if(ss.first==0.){ 
        factor=0.;
        factorErr=0.;
    }
    return std::make_pair(factor,factorErr);   

}





std::pair<float,float> extractWFactor(std::string file,std::string preselection,std::string postfix, std::string Wweight = "1") {
    TFile *f  = new TFile (file.c_str());
    TTree *t = (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());

    std::pair<float,float> high;
    std::pair<float,float> low;
    high = makeHistogram(t,filelabel_+postfix,"W_High",("("+preselection+"&&"+wSelection_+")*"+weight_+"*"+Wweight).c_str());
    low = makeHistogram(t,filelabel_+postfix,"W_Low",("("+preselection+"&&"+signalSelection_+")*"+weight_+"*"+Wweight).c_str());

    std::cout<<"W + Jets High: "<< high.first<<" Low: "<< low.first<<std::endl;

    float factor = low.first/high.first;
    float factorerrStat = sqrt(low.second*low.second + high.second*high.second);
    float factorerrSyst = factor*wFactorErr_;
    float factorErr = sqrt(factorerrStat*factorerrStat+factorerrSyst*factorerrSyst);

    if(high.first==0.){ 
        factor=0.;
        factorErr=0.;
    }
    return std::make_pair(factor,factorErr);   

}

std::pair<float,float> extractWFactorFinal(std::string file,std::string preselection,std::string postfix, std::string Wweight = "1") {
    TFile *f  = new TFile (file.c_str());
    TTree *t = (TTree*)f->Get((channel_+"EventTreeFinal/eventTree").c_str());

    std::pair<float,float> high;
    std::pair<float,float> low;

    high = makeHistogram(t,filelabel_+postfix,"W_High",("("+preselection+"&&"+wSelection_+")*"+weight_+"*"+Wweight).c_str());
    low = makeHistogram(t,filelabel_+postfix,"W_Low",("("+preselection+"&&"+signalSelection_+")*"+weight_+"*"+Wweight).c_str());

    std::cout<<"W + Jets High: "<< high.first<<" Low: "<< low.first<<std::endl;

    float factor = low.first/high.first;
    float factorerrStat = sqrt(low.second*low.second + high.second*high.second);
    float factorerrSyst = factor*wFactorErr_;
    float factorErr = sqrt(factorerrStat*factorerrStat+factorerrSyst*factorerrSyst);
    if(high.first==0.){
        factor=0.;
        factorErr=0.;
    }
    return std::make_pair(factor,factorErr);   

}

std::pair<float,float> extractWFactor(std::string file, std::string preselection, std::string postfix, std::string wSel, std::string sigSel) {
    TFile *f  = new TFile (file.c_str());
    TTree *t = (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());
    //TTree *t = (TTree*)f->Get((channel_+"EventTreeFinal/eventTree").c_str());

    std::pair<float,float> high;
    std::pair<float,float> low;


    high = makeHistogram(t,filelabel_+postfix,"W_High",("("+preselection+"&&"+wSel+")*"+weight_).c_str(),luminosity_);
    low = makeHistogram(t,filelabel_+postfix,"W_Low",("("+preselection+"&&"+sigSel+")*"+weight_).c_str(),luminosity_);

    std::cout<<"      Cuts in extract WFactor "<<"      OS W Mt>80: "<<high.first<<"      OS W Mt Low: "<<low.first<<std::endl;
    std::cout<<"      Extract WFactor Second"<<"      OS W Mt>80: "<<high.second<<"      OS W Mt Low: "<<low.second<<std::endl;
    float factor = low.first/high.first;
    float factorerrStat = sqrt(low.second*low.second + high.second*high.second);
    float factorerrSyst = factor*wFactorErr_;
    float factorErr = sqrt(factorerrStat*factorerrStat+factorerrSyst*factorerrSyst);


    std::cout<<"      WFactor Stat Error "<<"      factor: "<<factor<<"      StatError: "<<factorerrStat<<std::endl;
    std::cout<<"      WFactor Syst Error "<<"      factor*wFactorErr_: "<<factor<<"*"<<wFactorErr_<<" = "<<factorerrSyst<<std::endl; 
    std::cout<<"      WFactor Error "<<"      factorError = sqrt(Syst Error^2+Stat Error^2)= "<<factorErr<<std::endl; 
    if(high.first==0.){
        factor=0.;
        factorErr=0.;
    }
    return std::make_pair(factor,factorErr);   

}

void mergeHistogram(std::string folder, std::string histo1, std::string histo2, std::string newName)
{
    TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
    TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
    TH1F *hNew =(TH1F*) h1->Clone(TString(newName));
    hNew->Add(h2,1.);

    for(int i=1;i<h1->GetNbinsX();++i){
        if(h1->GetBinContent(i)<0){
            h1->SetBinContent(i,0.00001);
            h1->SetBinError(i,1.0);
        }
    }

    fout_->cd(folder.c_str());
    hNew->Write(TString(newName),TObject::kOverwrite);
}

std::pair<float,float> convertToPoisson(std::pair<float,float> measurement) {
    float yield = measurement.first;
    float CLHi = TMath::ChisquareQuantile(1-0.32/2,2*yield+2)/2.;
    float CLLo = TMath::ChisquareQuantile(0.32/2,2*yield)/2.;
    printf("Yield =%f Lo=%f Hi=%f\n",measurement.first,CLLo,CLHi);
    return std::make_pair(measurement.first,(CLHi-CLLo)/2.);

}

void subtractHistogram(std::string folder, std::string histo1, std::string histo2)
{
    TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
    TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
    h1->Add(h2,-1.);

    for(int i=1;i<h1->GetNbinsX();++i){
        if(h1->GetBinContent(i)<0){
            h1->SetBinContent(i,0.00001);
            h1->SetBinError(i,1.0);
        }
    }

    fout_->cd(folder.c_str());
    h1->Write(h1->GetName(),TObject::kOverwrite);
}

void addHistogram(std::string folder, std::string histo1, std::string histo2)
{
    TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
    TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
    h1->Add(h2,1.);

    fout_->cd(folder.c_str());
    h1->Write(h1->GetName(),TObject::kOverwrite);
}

void renameHist(std::string folder, std::string name ,std::string histo1)///folder, new name, old name
{
    TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
    TH1F * h2 = (TH1F*) h1->Clone(TString(name));

    h2->Write(h2->GetName(),TObject::kOverwrite);
}


void FixNegativeBins(std::string folder, std::string histo, bool is_qcd, bool verbose=false) {

    TH1F * hist =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    unsigned bins = hist->GetNbinsX();
    for (unsigned i = 1; i <= bins; ++i) {
        if (hist->GetBinContent(i) < 0.){
            hist->SetBinContent(i,0);
            if(verbose)
                std::cout<<"Bin "<< i << " is negative, setting to 0"<<std::endl;
        }
    }
    hist->Write(hist->GetName(),TObject::kOverwrite);
}

void FixNegativeBinsMC(std::string folder, std::string histo, bool is_qcd, bool verbose=false){

    FixNegativeBins(folder, histo, is_qcd, verbose);

    for(unsigned int i=0;i<shifts_.size();++i) {
        TH1F * hh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
        if(hh!=0) {
            FixNegativeBins(folder, (histo+"_"+shiftsPostFix_[i]+"Up").c_str(), is_qcd, verbose);
        }

        TH1F * hhh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Down").c_str());
        if(hhh!=0) {
            FixNegativeBins(folder, (histo+"_"+shiftsPostFix_[i]+"Down").c_str(), is_qcd, verbose);
        }

    }
}


void FixEmptyBins(std::string folder, std::string histo, bool is_qcd, bool verbose=false) {

    TH1F * hist =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    unsigned bins = hist->GetNbinsX();
    unsigned first_populated = 0;
    unsigned last_populated = 0;
    for (unsigned i = 1; i <= bins; ++i) {
        if (hist->GetBinContent(i) > 0. && first_populated == 0) first_populated = i;
        if (hist->GetBinContent(bins-(i-1)) > 0. && last_populated == 0) last_populated = bins-(i-1);
    }
    if (last_populated <= first_populated) {
        if (verbose) std::cout << "Cannot correct this distribution!" << std::endl;
        return;
    }
    if (verbose) std::cout << "First populated bin: " << first_populated << std::endl;
    if (verbose) std::cout << "Last populated bin: " << last_populated << std::endl;
    double av_weight = ( hist->Integral() / double(hist->GetEntries()));
    if (!is_qcd) {
        if (verbose) std::cout << "Integral: " << hist->Integral() << std::endl;
        if (verbose) std::cout << "Entries: " << hist->GetEntries() << std::endl;
        if (verbose) std::cout << "Av. Weight: " << av_weight << std::endl;
    }
    for (unsigned i = first_populated+1; i < last_populated; ++i) {
        if (hist->GetBinContent(i) == 0.) {
            if (verbose) std::cout << "Bin " << i << " is empty!" << std::endl;
            if (is_qcd) {
                hist->SetBinError(i, 1.0);
            } else {
                if (verbose) std::cout << "Set weight to 1.0 * av_weight = " << (1.0 * av_weight) << std::endl;
                hist->SetBinError(i, av_weight);    
            }
        }
    }
    hist->Write(hist->GetName(),TObject::kOverwrite);
}


bool qcdSyst(std::string channel, std::string prefix, std::string histo1, float corr, float unc)
{

    std::string chan = "mt";
    if(channel_ == "eleTau")
        chan = "et";

    TH1F * h1 =(TH1F*) fout_->Get((channel+prefix+"/"+histo1).c_str());
    TH1F * h2 = (TH1F*)h1->Clone(TString(histo1+std::string("_CMS_htt_QCDShape_"+chan+prefix+"_"+energy_+"Up")));
    TH1F * h3 = (TH1F*)h1->Clone(TString(histo1+std::string("_CMS_htt_QCDShape_"+chan+prefix+"_"+energy_+"Down")));
    std::cout << "Channel label is " << chan << std::endl;
    float x,y;
    float cUp = corr+unc;
    float cDown = corr-unc;
    //printf("Creating QCD Shape Systematic \n");
    float scale = h1->Integral();
    for(int i=1;i<h1->GetNbinsX();++i){
        x = h1->GetXaxis()->GetBinCenter(i);
        if(x<50){
            y = h1->GetBinContent(i);
            h1->SetBinContent(i,y*corr);
            h2->SetBinContent(i,y*cUp);
            h3->SetBinContent(i,y*cDown);
        }

    }
    h1->Scale(scale/h1->Integral());
    h2->Scale(scale/h2->Integral());
    h3->Scale(scale/h3->Integral());
    h1->Write(h1->GetName(),TObject::kOverwrite);
    h2->Write(h2->GetName(),TObject::kOverwrite);
    h3->Write(h3->GetName(),TObject::kOverwrite);        

    return true;
}

void generateFFHistograms(TTree * t, std::string process, std::string preSelection, std::string prefix, std::string zShape, float topExtrap, BkgOutput &output, std::string categorySelection, std::string relaxedSelection){

    //creating fakefactor object
    TString ff_file_name = "/afs/hep.wisc.edu/home/samuellh/WorkingArea/CPstuff/Iso_2017/src/HTTutilities/Jet2TauFakes/data/SM2017/tight/vloose/mt/fakeFactors.root";
    TFile* ff_file = TFile::Open(ff_file_name);
    FakeFactor* ff = (FakeFactor*)ff_file->Get("ff_comb");
    const std::vector<std::string>& inputNames = ff->inputs();
    //std::vector<string> inputNames( ff->inputs() ) ;
    if (ff_file==0) std::cout<<"Error in FF file"<<std::endl;



    //different cut strings that are important for the FakeFactor Method

    TCut preselection = "pt_1>21&&pt_2>30&&npv>0&&id_m_medium_1>0&&tightMuons<=1&&tightElectrons==0&&diLeptons==0&&againstMuonTight3_2>0&&againstElectronVLooseMVA6_2>0";
    TCut preselectionIso = "pt_1>21&&pt_2>30&&npv>0&&id_m_medium_1>0&&iso_1<0.15&&byTightIsolationMVArun2v1DBoldDMwLT_2>0.5&&tightMuons<=1&&tightElectrons==0&&diLeptons==0&&againstMuonTight3_2>0&&againstElectronVLooseMVA6_2>0";
    TCut ApplicationRegion = "byVLooseIsolationMVArun2v1DBoldDMwLT_2>0.5&&byTightIsolationMVArun2v1DBoldDMwLT_2<0.5";
    TCut SignalRegion = "byTightIsolationMVArun2v1DBoldDMwLT_2>0.5";

    TCut trueSelection = "gen_match_2<=5";
    TCut fakeSelection = "gen_match_2==6";
    
    TTree * trimmedTree = t->CopyTree(preselection);

    //adding the variables necessary to calculate weight
    Float_t pt_1, pt_2, tau_pt, mt, decayMode_2, m_vis, iso_1,isoTight_2;
    Float_t variable;
    Int_t njets;
    TBranch *b_pt_1, *b_pt_2, *b_tau_pt, *b_mt, *b_decayMode_2, *b_njets, *b_m_vis, *b_iso_1, *b_isoTight_2;
    TBranch *b_variable;
    std::vector<double> variables( inputNames.size() );

    //loop over events in data file (global variable) 
    //TFile *f = new TFile(dataFile_.c_str());
    //if(f==0) printf("Not file Found\n");
    //get the nominal tree first
    //if(t==0) printf("Not Tree Found in file %s\n",file.c_str());
    //setting branch addresses
    trimmedTree->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
    trimmedTree->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
    trimmedTree->SetBranchAddress("njets", &njets, &b_njets);
    trimmedTree->SetBranchAddress("m_vis", &m_vis, &b_m_vis);
    trimmedTree->SetBranchAddress("mt_1", &mt, &b_mt);
    trimmedTree->SetBranchAddress("tauDecayMode", &decayMode_2, &b_decayMode_2);
    trimmedTree->SetBranchAddress("iso_1", &iso_1, &b_iso_1);
    trimmedTree->SetBranchAddress("byTightIsolationMVArun2v1DBoldDMwLT_2", &isoTight_2, &b_isoTight_2);

    //the variable that we are actually plotting    
    trimmedTree->SetBranchAddress(variable_.c_str(), &variable, &b_variable);

    //new fake factor weight
    double ff_nom = 0.0;
    double frac_qcd = 0.0;
    double frac_w = 0.0;
    double frac_tt = 0.0;

    //fake factor systematics 
    double ff_qcd_syst_up = 0.0;
    double ff_qcd_dm0_njet0_stat_up = 0.0;
    double ff_qcd_dm0_njet1_stat_up = 0.0;
    double ff_w_syst_up = 0.0;
    double ff_w_dm0_njet0_stat_up = 0.0;
    double ff_w_dm0_njet1_stat_up = 0.0;
    double ff_tt_syst_up = 0.0;
    double ff_tt_dm0_njet0_stat_up = 0.0;
    double ff_tt_dm0_njet1_stat_up = 0.0;
    double ff_qcd_syst_down = 0.0;
    double ff_qcd_dm0_njet0_stat_down = 0.0;
    double ff_qcd_dm0_njet1_stat_down = 0.0;
    double ff_w_syst_down = 0.0;
    double ff_w_dm0_njet0_stat_down = 0.0;
    double ff_w_dm0_njet1_stat_down = 0.0;
    double ff_tt_syst_down = 0.0;
    double ff_tt_dm0_njet0_stat_down = 0.0;
    double ff_tt_dm0_njet1_stat_down = 0.0;

    //All the new branches in DATA
    
    TBranch *nBff_qcd_syst_up            trimmedtree->Branch("ff_qcd_syst_up"              ,      &ff_qcd_syst_up               ,"ff_qcd_syst_up/F"             );
    TBranch *nBff_qcd_dm0_njet0_stat_up  trimmedtree->Branch("ff_qcd_dm0_njet0_stat_up"    ,      &ff_qcd_dm0_njet0_stat_up     ,"ff_qcd_dm0_njet0_stat_up/F"   );
    TBranch *nBff_qcd_dm0_njet1_stat_up  trimmedtree->Branch("ff_qcd_dm0_njet1_stat_up"    ,      &ff_qcd_dm0_njet1_stat_up     ,"ff_qcd_dm0_njet1_stat_up/F"   );
    TBranch *nBff_w_syst_up              trimmedtree->Branch("ff_w_syst_up"                ,          &ff_w_syst_up             ,"ff_w_syst_up/F"               );
    TBranch *nBff_w_dm0_njet0_stat_up    trimmedtree->Branch("ff_w_dm0_njet0_stat_up"      ,      &ff_w_dm0_njet0_stat_up       ,"ff_w_dm0_njet0_stat_up/F"     );
    TBranch *nBff_w_dm0_njet1_stat_up    trimmedtree->Branch("ff_w_dm0_njet1_stat_up"      ,      &ff_w_dm0_njet1_stat_up       ,"ff_w_dm0_njet1_stat_up/F"     );
    TBranch *nBff_tt_syst_up             trimmedtree->Branch("ff_tt_syst_up"               ,      &ff_tt_syst_up                ,"ff_tt_syst_up/F"              );
    TBranch *nBff_tt_dm0_njet0_stat_up   trimmedtree->Branch("ff_tt_dm0_njet0_stat_up"     ,      &ff_tt_dm0_njet0_stat_up      ,"ff_tt_dm0_njet0_stat_up/F"    );
    TBranch *nBff_tt_dm0_njet1_stat_up   trimmedtree->Branch("ff_tt_dm0_njet1_stat_up"     ,      &ff_tt_dm0_njet1_stat_up      ,"ff_tt_dm0_njet1_stat_up/F"    );
    TBranch *nBff_qcd_syst_down          trimmedtree->Branch("ff_qcd_syst_down"            ,      &ff_qcd_syst_down             ,"ff_qcd_syst_down/F"           );
    TBranch *nBff_qcd_dm0_njet0_stat_down trimmedtree->Branch("ff_qcd_dm0_njet0_stat_down"  ,         &ff_qcd_dm0_njet0_stat_down,"ff_qcd_dm0_njet0_stat_down/F" );
    TBranch *nBff_qcd_dm0_njet1_stat_down trimmedtree->Branch("ff_qcd_dm0_njet1_stat_down"  ,         &ff_qcd_dm0_njet1_stat_down,"ff_qcd_dm0_njet1_stat_down/F" );
    TBranch *nBff_w_syst_down            trimmedtree->Branch("ff_w_syst_down"              ,      &ff_w_syst_down               ,"ff_w_syst_down/F"             );
    TBranch *nBff_w_dm0_njet0_stat_down  trimmedtree->Branch("ff_w_dm0_njet0_stat_down"    ,      &ff_w_dm0_njet0_stat_down     ,"ff_w_dm0_njet0_stat_down/F"   );
    TBranch *nBff_w_dm0_njet1_stat_down  trimmedtree->Branch("ff_w_dm0_njet1_stat_down"    ,      &ff_w_dm0_njet1_stat_down     ,"ff_w_dm0_njet1_stat_down/F"   );
    TBranch *nBff_tt_syst_down           trimmedtree->Branch("ff_tt_syst_down"             ,      &ff_tt_syst_down              ,"ff_tt_syst_down/F"            );
    TBranch *nBff_tt_dm0_njet0_stat_down trimmedtree->Branch("ff_tt_dm0_njet0_stat_down"   ,      &ff_tt_dm0_njet0_stat_down    ,"ff_tt_dm0_njet0_stat_down/F"  );
    TBranch *nBff_tt_dm0_njet1_stat_down trimmedtree->Branch("ff_tt_dm0_njet1_stat_down"   ,      &ff_tt_dm0_njet1_stat_down    ,"ff_tt_dm0_njet1_stat_down/F"  );


    //double fakefactor;
    std::vector<float> fractions(3);

    //dir->cd();
    std::string folder = filelabel_+prefix;
    std::cout<<"The folder corresponding to the output file directory is:   "<<folder<<std::endl;

    fout_->cd(folder.c_str());

    TH1F * fakefactorhisto  = new TH1F("jetFakes","jetFakes",bins_,min_,max_);

    TH1F * fakefactorhisto_qcd_syst_up  = new TH1F("jetFakes_qcd_syst_up","jetFakes_qcd_syst_up",bins_,min_,max_);
    TH1F * fakefactorhisto_qcd_dm0_njet0_stat_up  = new TH1F("jetFakes_qcd_dm0_njet0_stat_up","jetFakes_qcd_dm0_njet0_stat_up",bins_,min_,max_);
    TH1F * fakefactorhisto_qcd_dm0_njet1_stat_up  = new TH1F("jetFakes_qcd_dm0_njet1_stat_up","jetFakes_qcd_dm0_njet1_stat_up",bins_,min_,max_);
    TH1F * fakefactorhisto_w_syst_up  = new TH1F("jetFakes_w_syst_up","jetFakes_w_syst_up",bins_,min_,max_);
    TH1F * fakefactorhisto_w_dm0_njet0_stat_up  = new TH1F("jetFakes_w_dm0_njet0_stat_up","jetFakes_w_dm0_njet0_stat_up",bins_,min_,max_);
    TH1F * fakefactorhisto_w_dm0_njet1_stat_up  = new TH1F("jetFakes_w_dm0_njet1_stat_up","jetFakes_w_dm0_njet1_stat_up",bins_,min_,max_);
    TH1F * fakefactorhisto_tt_syst_up  = new TH1F("jetFakes_tt_syst_up","jetFakes_tt_syst_up",bins_,min_,max_);
    TH1F * fakefactorhisto_tt_dm0_njet0_stat_up  = new TH1F("jetFakes_tt_dm0_njet0_stat_up","jetFakes_tt_dm0_njet0_stat_up",bins_,min_,max_);
    TH1F * fakefactorhisto_tt_dm0_njet1_stat_up  = new TH1F("jetFakes_tt_dm0_njet1_stat_up","jetFakes_tt_dm0_njet1_stat_up",bins_,min_,max_);

    TH1F * fakefactorhisto_qcd_syst_down  = new TH1F("jetFakes_qcd_syst_down","jetFakes_qcd_syst_down",bins_,min_,max_);
    TH1F * fakefactorhisto_qcd_dm0_njet0_stat_down  = new TH1F("jetFakes_qcd_dm0_njet0_stat_down","jetFakes_qcd_dm0_njet0_stat_down",bins_,min_,max_);
    TH1F * fakefactorhisto_qcd_dm0_njet1_stat_down  = new TH1F("jetFakes_qcd_dm0_njet1_stat_down","jetFakes_qcd_dm0_njet1_stat_down",bins_,min_,max_);
    TH1F * fakefactorhisto_w_syst_down  = new TH1F("jetFakes_w_syst_down","jetFakes_w_syst_down",bins_,min_,max_);
    TH1F * fakefactorhisto_w_dm0_njet0_stat_down  = new TH1F("jetFakes_w_dm0_njet0_stat_down","jetFakes_w_dm0_njet0_stat_down",bins_,min_,max_);
    TH1F * fakefactorhisto_w_dm0_njet1_stat_down  = new TH1F("jetFakes_w_dm0_njet1_stat_down","jetFakes_w_dm0_njet1_stat_down",bins_,min_,max_);
    TH1F * fakefactorhisto_tt_syst_down  = new TH1F("jetFakes_tt_syst_down","jetFakes_tt_syst_down",bins_,min_,max_);
    TH1F * fakefactorhisto_tt_dm0_njet0_stat_down  = new TH1F("jetFakes_tt_dm0_njet0_stat_down","jetFakes_tt_dm0_njet0_stat_down",bins_,min_,max_);
    TH1F * fakefactorhisto_tt_dm0_njet1_stat_down  = new TH1F("jetFakes_tt_dm0_njet1_stat_down","jetFakes_tt_dm0_njet1_stat_down",bins_,min_,max_);





    //looping over data events 
    for(int i=0;i<trimmedTree->GetEntries();i++ ){
        trimmedTree->GetEntry(i);
        if(i%1000==0) std::cout<<"working on entry   "<<i<<std::endl;

        //analyzing the cut string
        

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
        ff_nom = 0.0;//normalizing to 1 so that I can multiply 1 and 2 later in the histogramming step
        //std::cout<<"starting Isolation ... "<<std::endl;
        std::cout<<"value of isolation "<<isoTight_2<<std::endl;

        if( isoTight_2<0.5){

            //std::cout<<"Tau 1 is not isolated ... "<<std::endl;
            variables[0] = (double) pt_2;
            variables[1] = (double) decayMode_2; //pt of non-fake tau candidate
            variables[2] = (double) njets;
            variables[3] = (double) m_vis;
            variables[4] = (double) mt;


            //retrieving the fake factor fractions as a function of m_vis and njets
            std::cout<<"Getting fractions"<<std::endl;
            fractions  = getFFractions(folder, variable);

            std::cout<<"fractions qcd  "<<fractions[3]<<std::endl;
            //variables[5] = (double) fractions[3];//frac_qcd;
            frac_qcd = (double) fractions[3];//frac_qcd;
            variables[5] = frac_qcd;//frac_qcd;
            //variables[6] = (double) fractions[0];//frac_w;
            frac_w = (double) fractions[0];//frac_w;
            variables[6] = frac_w;//frac_w;
            //variables[7] = (double) fractions[1];//frac_tt;
            frac_tt = (double) fractions[1];//frac_tt;
            variables[7] = frac_tt;
            ff_nom = ff->value(variables);
            //ff_qcd_syst_up = ff->value(variables,"ff_qcd_syst")
            ff_qcd_syst_up =ff->value(variables,                "ff_qcd_syst_up"                        );
            ff_qcd_dm0_njet0_stat_up =ff->value(variables,      "ff_qcd_dm0_njet0_stat_up"              );
            ff_qcd_dm0_njet1_stat_up =ff->value(variables,      "ff_qcd_dm0_njet1_stat_up"              );
            ff_w_syst_up =ff->value(variables,                  "ff_w_syst_up"                          );
            ff_w_dm0_njet0_stat_up =ff->value(variables,        "ff_w_dm0_njet0_stat_up"                );
            ff_w_dm0_njet1_stat_up =ff->value(variables,        "ff_w_dm0_njet1_stat_up"                );
            ff_tt_syst_up =ff->value(variables,                 "ff_tt_syst_up"                         );
            ff_tt_dm0_njet0_stat_up =ff->value(variables,       "ff_tt_dm0_njet0_stat_up"               );
            ff_tt_dm0_njet1_stat_up =ff->value(variables,       "ff_tt_dm0_njet1_stat_up"               );
            ff_qcd_syst_down =ff->value(variables,              "ff_qcd_syst_down"                      );
            ff_qcd_dm0_njet0_stat_down =ff->value(variables,    "ff_qcd_dm0_njet0_stat_down"            );
            ff_qcd_dm0_njet1_stat_down =ff->value(variables,    "ff_qcd_dm0_njet1_stat_down"            );
            ff_w_syst_down =ff->value(variables,                "ff_w_syst_down"                        );
            ff_w_dm0_njet0_stat_down =ff->value(variables,      "ff_w_dm0_njet0_stat_down"              );
            ff_w_dm0_njet1_stat_down =ff->value(variables,      "ff_w_dm0_njet1_stat_down"              );
            ff_tt_syst_down =ff->value(variables,               "ff_tt_syst_down"                       );
            ff_tt_dm0_njet0_stat_down =ff->value(variables,     "ff_tt_dm0_njet0_stat_down"             );
            ff_tt_dm0_njet1_stat_down =ff->value(variables,     "ff_tt_dm0_njet1_stat_down"             );

        }

        //we need to make the histograms AND THE SHIFTS here if we don't want to store the weights that are calculated per event  ... otherwise harness the weights later??? 
        fakefactorhisto->Fill(variable,ff_nom);


        //all of the systematic shifts 
        fakefactorhisto_qcd_syst_up               ->Fill(variable,weight_*ff_qcd_syst_up);
        fakefactorhisto_qcd_dm0_njet0_stat_up     ->Fill(variable,weight_*ff_qcd_dm0_njet0_stat_up);
        fakefactorhisto_qcd_dm0_njet1_stat_up     ->Fill(variable,weight_*ff_qcd_dm0_njet1_stat_up);
        fakefactorhisto_w_syst_up                 ->Fill(variable,weight_*ff_w_syst_up);
        fakefactorhisto_w_dm0_njet0_stat_up       ->Fill(variable,weight_*ff_w_dm0_njet0_stat_up);
        fakefactorhisto_w_dm0_njet1_stat_up       ->Fill(variable,weight_*ff_w_dm0_njet1_stat_up);
        fakefactorhisto_tt_syst_up                ->Fill(variable,weight_*ff_tt_syst_up);
        fakefactorhisto_tt_dm0_njet0_stat_up      ->Fill(variable,weight_*ff_tt_dm0_njet0_stat_up);
        fakefactorhisto_tt_dm0_njet1_stat_up      ->Fill(variable,weight_*ff_tt_dm0_njet1_stat_up);

        fakefactorhisto_qcd_syst_down             ->Fill(variable,weight_*ff_qcd_syst_down);
        fakefactorhisto_qcd_dm0_njet0_stat_down   ->Fill(variable,weight_*ff_qcd_dm0_njet0_stat_down);
        fakefactorhisto_qcd_dm0_njet1_stat_down   ->Fill(variable,weight_*ff_qcd_dm0_njet1_stat_down);
        fakefactorhisto_w_syst_down               ->Fill(variable,weight_*ff_w_syst_down);
        fakefactorhisto_w_dm0_njet0_stat_down     ->Fill(variable,weight_*ff_w_dm0_njet0_stat_down);
        fakefactorhisto_w_dm0_njet1_stat_down     ->Fill(variable,weight_*ff_w_dm0_njet1_stat_down);
        fakefactorhisto_tt_syst_down              ->Fill(variable,weight_*ff_tt_syst_down);
        fakefactorhisto_tt_dm0_njet0_stat_down    ->Fill(variable,weight_*ff_tt_dm0_njet0_stat_down);
        fakefactorhisto_tt_dm0_njet1_stat_down    ->Fill(variable,weight_*ff_tt_dm0_njet1_stat_down);

    }//end data event loop
    std::cout<<"closing up"<<std::endl;

    fakefactorhisto->Write();


    //all of the systematic shifts 
    fakefactorhisto_qcd_syst_up               ->Write( fakefactorhisto_qcd_syst_up            ->GetName(),TObject::kOverwrite);
    fakefactorhisto_qcd_dm0_njet0_stat_up     ->Write( fakefactorhisto_qcd_dm0_njet0_stat_up  ->GetName(),TObject::kOverwrite);
    fakefactorhisto_qcd_dm0_njet1_stat_up     ->Write( fakefactorhisto_qcd_dm0_njet1_stat_up  ->GetName(),TObject::kOverwrite);
    fakefactorhisto_w_syst_up                 ->Write( fakefactorhisto_w_syst_up              ->GetName(),TObject::kOverwrite);
    fakefactorhisto_w_dm0_njet0_stat_up       ->Write( fakefactorhisto_w_dm0_njet0_stat_up    ->GetName(),TObject::kOverwrite);
    fakefactorhisto_w_dm0_njet1_stat_up       ->Write( fakefactorhisto_w_dm0_njet1_stat_up    ->GetName(),TObject::kOverwrite);
    fakefactorhisto_tt_syst_up                ->Write( fakefactorhisto_tt_syst_up             ->GetName(),TObject::kOverwrite);
    fakefactorhisto_tt_dm0_njet0_stat_up      ->Write( fakefactorhisto_tt_dm0_njet0_stat_up   ->GetName(),TObject::kOverwrite);
    fakefactorhisto_tt_dm0_njet1_stat_up      ->Write( fakefactorhisto_tt_dm0_njet1_stat_up   ->GetName(),TObject::kOverwrite);

    fakefactorhisto_qcd_syst_down             ->Write( fakefactorhisto_qcd_syst_down          ->GetName(),TObject::kOverwrite);
    fakefactorhisto_qcd_dm0_njet0_stat_down   ->Write( fakefactorhisto_qcd_dm0_njet0_stat_down->GetName(),TObject::kOverwrite);
    fakefactorhisto_qcd_dm0_njet1_stat_down   ->Write( fakefactorhisto_qcd_dm0_njet1_stat_down->GetName(),TObject::kOverwrite);
    fakefactorhisto_w_syst_down               ->Write( fakefactorhisto_w_syst_down            ->GetName(),TObject::kOverwrite);
    fakefactorhisto_w_dm0_njet0_stat_down     ->Write( fakefactorhisto_w_dm0_njet0_stat_down  ->GetName(),TObject::kOverwrite);
    fakefactorhisto_w_dm0_njet1_stat_down     ->Write( fakefactorhisto_w_dm0_njet1_stat_down  ->GetName(),TObject::kOverwrite);
    fakefactorhisto_tt_syst_down              ->Write( fakefactorhisto_tt_syst_down           ->GetName(),TObject::kOverwrite);
    fakefactorhisto_tt_dm0_njet0_stat_down    ->Write( fakefactorhisto_tt_dm0_njet0_stat_down ->GetName(),TObject::kOverwrite);
    fakefactorhisto_tt_dm0_njet1_stat_down    ->Write( fakefactorhisto_tt_dm0_njet1_stat_down ->GetName(),TObject::kOverwrite);

    trimmedTree->Delete();
    delete ff;
    ff_file->Close();
    return;

}


//given the variable that is plotted this will return the fractions corresponding to the appropriate processes and regions 
std::vector<float> getFFractions(std::string folder, float variable) {
    
    //travel to histogram file no directory structure ... histos should be there
    //fout_->cd(folder.c_str());
    std::cout<<"The folder and directory where the files are:    "<<folder<<std::endl;

    std::vector<float> fractions;

    //Calculating the Fractions  
    int thebin;
    thebin = findBin(folder.c_str(), "W_AI",variable);
    //std::cout<<"Found the bin!"<<std::endl;
    std::cout<<"The bin!  "<<thebin<<std::endl;
    
     
    float W    = ((TH1D*) fout_->Get((folder+"/W_AI"  ).c_str() ))->GetBinContent(thebin); 
    float ZJ   = ((TH1D*) fout_->Get((folder+"/ZJ_AI" ).c_str() ))->GetBinContent(thebin);
    float VVJ  = ((TH1D*) fout_->Get((folder+"/VVJ_AI").c_str() ))->GetBinContent(thebin);
    float VVT  = ((TH1D*) fout_->Get((folder+"/VVT_AI").c_str() ))->GetBinContent(thebin);
    float TTT  = ((TH1D*) fout_->Get((folder+"/TTT_AI").c_str() ))->GetBinContent(thebin);
    float TTJ  = ((TH1D*) fout_->Get((folder+"/TTJ_AI").c_str() ))->GetBinContent(thebin);
    float ZTT  = ((TH1D*) fout_->Get((folder+"/TTJ_AI").c_str() ))->GetBinContent(thebin);
    float data = ((TH1D*) fout_->Get((folder+"/data_obs_AI").c_str()))->GetBinContent(thebin);

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
    
    //make sure that these add to 1... before subtracting for qcd
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

std::vector<float> getFFractions2D(std::string folder, float m_vis_val, float njets_val) {
    
    //travel to histogram file no directory structure ... histos should be there
    fout_->cd(folder.c_str());
    std::vector<float> fractions;

    //Calculating the Fractions  
    std::pair<int,int> thebins;

    thebins=findBin2D(folder.c_str(),"W",m_vis_val,njets_val);
    //std::cout<<"Found the bin!"<<std::endl;
    std::cout<<"The bins!  "<<thebins.first<<"   2:   "<<thebins.second<<std::endl;
    
     
    float W    = ((TH2D*) fout_->Get("W"   ))->GetBinContent(thebins.first,thebins.second); 
    float ZJ   = ((TH2D*) fout_->Get("ZJ"  ))->GetBinContent(thebins.first,thebins.second);
    float VVJ  = ((TH2D*) fout_->Get("VVJ" ))->GetBinContent(thebins.first,thebins.second);
    float VVT  = ((TH2D*) fout_->Get("VVT" ))->GetBinContent(thebins.first,thebins.second);
    float TTT  = ((TH2D*) fout_->Get("TTT" ))->GetBinContent(thebins.first,thebins.second);
    float TTJ  = ((TH2D*) fout_->Get("TTJ" ))->GetBinContent(thebins.first,thebins.second);
    float ZTT  = ((TH2D*) fout_->Get("TTJ" ))->GetBinContent(thebins.first,thebins.second);
    float data = ((TH2D*) fout_->Get("data"))->GetBinContent(thebins.first,thebins.second);
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

int findBin(std::string folder, std::string histname, float variable){
    
    //fout_->cd(folder.c_str());     
    TH1D * h = (TH1D*) fout_->Get((folder+"/"+histname).c_str());
    std::cout<<"entries in find bin histo "<<h->GetEntries()<<std::endl;
    TAxis *X = h->GetXaxis();   
    int binx = X->FindBin(variable);

    return binx;
}   

std::pair<int,int> findBin2D(std::string folder, std::string histname,float m_vis,float njets){
    
    fout_->cd(folder.c_str());     
    TH2D * h = (TH2D*) fout_->Get(histname.c_str());
    //std::cout<<"entries in find bin histo "<<h->GetEntries()<<std::endl;
    TAxis *X = h->GetXaxis();   
    TAxis *Y = h->GetYaxis();   
    int binx = X->FindBin(m_vis);
    int biny = Y->FindBin(njets);
    std::pair<int,int> binpair = std::make_pair(binx,biny);

    return binpair;
}   


private:
std::string channel_;
std::string filelabel_;
std::vector<std::string> shifts_;
std::vector<std::string> shiftsPostFix_;
std::string energy_;
int samesign_;

//files
TFile *fout_;
int verbose_;
std::string zttFile_;
std::string zllFile_;
std::string wFile_;
std::string vvFile_;
std::string topFile_;
std::string qcdFile_;
std::string dataFile_;
///////////////////////

//selections of regions
std::string preSelection_;
std::string osSignalSelection_;
std::string ssSignalSelection_;
std::string signalSelection_;
std::string osWSelection_;
std::string ssWSelection_;
std::string wSelection_;
std::string qcdSelection_;
std::string relaxedSelection_;
std::string trigSelection_;
std::string trigSelectionData_;
std::string blinding_;
std::string charge_;
std::string ZTT1PRONG_;
std::string ZTT1PRONG1PI0_;
std::string ZTT3PRONG_;
std::string ZLL_genLLSel_;
std::string ZTT_genTauSel_;
std::string ZJFT_genLReject_;
std::string ZLFT_genLSel_;
std::string muTau_genTauSel_;
std::string dataSelection_;

//Luminosity and efficiency corrections
float luminosity_;
float luminosityErr_;
float  muID_   ;      
float muIDErr_;      
float eleID_ ;       
float eleIDErr_;     
float tauID_  ;
float tauIDHigh_;      
float tauIDErr_;     
float vvScale_;
float zttScale_;     
float zttScaleErr_;  

float scaleUp_;
float doJEC_;

//histogram options
std::string variable_;
int bins_;
float min_;
float max_;
std::vector<double> binning_;
std::string weight_;
std::string Zweight_;
std::string TTweight_;
std::string embWeight_;
string nominalSelection_;

//std::string zlftFactor_;
double zlftFactor_;

//external parameters
float topErr_;
float qcdErr_;//tmp
float vvErr_;
float vvlErr_;
float vvjErr_;
float vvtErr_;
float zlftErr_;
float zjftErr_;
float wFactorErr_;
float qcdFactor_;
float qcdFactorErr_;


float bFactorZ_;
float bFactorZErr_;
float bFactorW_;
float bFactorWErr_;

float vbfFactorZ_;
float vbfFactorZErr_;
float vbfFactorW_;
float vbfFactorWErr_;


float boostFactorZ_;
float boostFactorZErr_;
float boostFactorW_;
float boostFactorWErr_;

float vhFactorZ_;
float vhFactorZErr_;
float vhFactorW_;
float vhFactorWErr_;


float bID_;
float bIDErr_;
float bMisID_;
float bMisIDErr_;

std::vector<std::string> mssmMasses_;
std::vector<std::string> smMasses_;
std::vector<std::string> smMassesDC_;

std::vector<float> mssmBBFraction_;
std::vector<float> smSigma_;
std::vector<float> vbfSigma_;
std::vector<float> vhSigma_;

std::string dir_;


};
