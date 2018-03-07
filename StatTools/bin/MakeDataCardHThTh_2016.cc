
#include "PUAnalysis/StatTools/interface/DataCardCreatorHThTh_2016.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 


int main (int argc, char* argv[]) 
{

	optutl::CommandLineParser parser ("Background subtraction ");

	//Input Files
	parser.addOption("channel",optutl::CommandLineParser::kString,"Channel  ","mutau");
	parser.addOption("shifts",optutl::CommandLineParser::kStringVector,"Systematic Shifts(Supported Tau,Jet,Unc and whatever else in the tree) ");
	parser.addOption("zttFile",optutl::CommandLineParser::kString,"File with the ZTT","ZTT.root");
	parser.addOption("zEmbeddedSample",optutl::CommandLineParser::kString,"File with the ZTT+2jets","");
	parser.addOption("zllFile",optutl::CommandLineParser::kString,"File with the ZLL","ZLL.root");
	parser.addOption("wFile",optutl::CommandLineParser::kString,"File with the W","W.root");
	parser.addOption("vvFile",optutl::CommandLineParser::kString,"File with the VV","VV.root");
	parser.addOption("topFile",optutl::CommandLineParser::kString,"File with the TOP","TOP.root");
	parser.addOption("qcdFile",optutl::CommandLineParser::kString,"File with the QCD","QCD.root");
	parser.addOption("dataFile",optutl::CommandLineParser::kString,"DATA! File","DATA.root");

	parser.addOption("doSys",optutl::CommandLineParser::kDouble,"Do Systematics",0.0); //addme default NO
	parser.addOption("useTEC",optutl::CommandLineParser::kDouble,"Use TEC folder",0.0); //addme default NO

	//Input Selections
	parser.addOption("preselection",     optutl::CommandLineParser::kString,"preselection",    "");
	parser.addOption("nominalselection",optutl::CommandLineParser::kString,"nominalselection","");
	parser.addOption("preselectiondata",     optutl::CommandLineParser::kString,"preselectionData",    "");
	parser.addOption("preselectionUp",   optutl::CommandLineParser::kString,"preselectionUp",  "");//addme
	parser.addOption("preselectionDown", optutl::CommandLineParser::kString,"preselectionDown","");//addme

	parser.addOption("signalselection",optutl::CommandLineParser::kString," Signal ","mt_1<30");
	parser.addOption("wselection",optutl::CommandLineParser::kString,"W sideband defintion ","mt_1>70");
	parser.addOption("qcdSelection",optutl::CommandLineParser::kString,"QCD Shape definition");
	parser.addOption("qcdSelectionMax",optutl::CommandLineParser::kString,"QCD Shape definition Max");
	parser.addOption("qcdselectiondata",optutl::CommandLineParser::kString,"QCD Shape definition Data");
	parser.addOption("relaxedSelection",optutl::CommandLineParser::kString,"Relaxed Selection");
	parser.addOption("bselection",optutl::CommandLineParser::kString,"Btagging requirement for MSSM","nbtag>=1");
	parser.addOption("trigSelection",optutl::CommandLineParser::kString,"Trigger Selection","crossTrigger>0||(lTrigger>0&&pt_1>25)");
	parser.addOption("trigSelectionData",optutl::CommandLineParser::kString,"Trigger Selection","crossTrigger>0||(lTrigger>0&&pt_1>25)");
	parser.addOption("blinding",optutl::CommandLineParser::kString,"Blinding","pt_1>0");
	parser.addOption("charge",optutl::CommandLineParser::kString,"charge","charge==0");
	parser.addOption("bTagSF",optutl::CommandLineParser::kString,"bTagSF","1");
	parser.addOption("folder",optutl::CommandLineParser::kString,"folder","_inclusive");

	//Other Options
	parser.addOption("luminosity",optutl::CommandLineParser::kDouble,"Luminosity",10.);
	parser.addOption("luminosityErr",optutl::CommandLineParser::kDouble,"LuminosityErr",0.04);

	parser.addOption("variable",optutl::CommandLineParser::kString,"Shape variable ","mass");
	parser.addOption("variableUp",optutl::CommandLineParser::kString,"Shape variable Up","mass");//addme
	parser.addOption("variableDown",optutl::CommandLineParser::kString,"Shape variable Down","mass");//addme

	parser.addOption("Zweight",optutl::CommandLineParser::kString,"Zweight","1");
	parser.addOption("ttweight",optutl::CommandLineParser::kString,"ttweight","1");
	parser.addOption("weight",optutl::CommandLineParser::kString,"Weight for MC (Multiply Weight Factors here for efficiencies)","__WEIGHT__");

	parser.addOption("embWeight",optutl::CommandLineParser::kString,"Weight for Embedded","__CORR__");
	parser.addOption("min",optutl::CommandLineParser::kDouble,"Minimum value",0.);
	parser.addOption("max",optutl::CommandLineParser::kDouble,"Maximum Value ",500.);
	parser.addOption("bins",optutl::CommandLineParser::kInteger,"Number of Bins",50);
	parser.addOption("verbose",optutl::CommandLineParser::kInteger,"verbose",0);
	parser.addOption("binningHighStat",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");
	parser.addOption("binningLowStat",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");


	//Input Scale Factors
	parser.addOption("topSF",optutl::CommandLineParser::kDouble,"TTBar Scale Factor",1.0);
	parser.addOption("topErr",optutl::CommandLineParser::kDouble,"TTBar Relative Error",0.075);
	parser.addOption("qcdErr",optutl::CommandLineParser::kDouble,"QCD ERROR",0.15);
	parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.3);   
	parser.addOption("zLFTErr",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",0.25);
	parser.addOption("zLFTFactor",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",1.0);
	parser.addOption("zJFTErr",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.2);
	parser.addOption("zttScale",optutl::CommandLineParser::kDouble,"Z tau tau scale",1.00);
	parser.addOption("zttScaleErr",optutl::CommandLineParser::kDouble,"Z tau tau scale error",0.033);
	parser.addOption("vvScale",optutl::CommandLineParser::kDouble,"VV scale",1.00);
	parser.addOption("muID",optutl::CommandLineParser::kDouble,"Mu ID",1.0);
	parser.addOption("muIDErr",optutl::CommandLineParser::kDouble,"MuIDErr",0.02);
	parser.addOption("bID",optutl::CommandLineParser::kDouble,"B ID",0.94);
	parser.addOption("bIDErr",optutl::CommandLineParser::kDouble,"BIDErr",0.10);
	parser.addOption("bmisID",optutl::CommandLineParser::kDouble,"B MISID",1.21);
	parser.addOption("bmisIDErr",optutl::CommandLineParser::kDouble,"BMISIDErr",0.17);
	parser.addOption("tauID",optutl::CommandLineParser::kDouble,"Tau ID",1.0);
	parser.addOption("tauIDHigh",optutl::CommandLineParser::kDouble,"Tau ID Pt>40",1.0);
	parser.addOption("tauIDErr",optutl::CommandLineParser::kDouble,"Tau IDErr",0.06);
	parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.06);
	parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
	parser.addOption("wFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.06);
	parser.addOption("bFactorZ",optutl::CommandLineParser::kDouble,"B factor Z",1.0);
	parser.addOption("bFactorW",optutl::CommandLineParser::kDouble,"B Factor W",1.0);
	parser.addOption("bFactorZErr",optutl::CommandLineParser::kDouble,"Probability of Z +1 b Error",0.011);
	parser.addOption("bFactorWErr",optutl::CommandLineParser::kDouble,"Probability of W+ 1 b Error",0.05);
	parser.addOption("samesign",optutl::CommandLineParser::kDouble,"Plot Same Sign",0.0);
	parser.addOption("energy",optutl::CommandLineParser::kString,"Center of Mass Energy","13TeV");

	parser.addOption("dir",optutl::CommandLineParser::kString,"dir","../inputs/mutau");
	parser.addOption("bitmask",optutl::CommandLineParser::kIntegerVector,"Choose what to run");
	parser.addOption("scaleUp",optutl::CommandLineParser::kDouble,"scale up for extrapolation to higher lumi",1.0);

	//category options

	parser.parseArguments (argc, argv);
	std::vector<int> bitmask = parser.integerVector("bitMask");
	DataCardCreatorHThTh_2016 creator(parser);

	printf("HighStat has %d entries ,LowStat has %d entries\n",(int)parser.doubleVector("binningHighStat").size(),(int)parser.doubleVector("binningLowStat").size());

	//Inclusive
	creator.setBinning(parser.doubleVector("binningLowStat"));

	printf(" -------------------------------------\n"); 
	printf(" --------New Variable--------\n"); 
	printf(" Running OS LS MT \n"); 
		printf("INCLUSIVE: MT Cut:  preselection -------------------------------------\n"); 
		std::string inclSel = parser.stringValue("preselection"); //signalselection  has mt_cut
		std::string foldername = parser.stringValue("folder");
                std::cout<<"using preselection: "<<inclSel<<std::endl;
		BkgOutput output = creator.runOSLSMT(inclSel,foldername,parser.stringValue("zEmbeddedSample"),parser.doubleValue("topSF"));
		creator.makeHiggsShape(inclSel,inclSel,foldername);
	
       
	if(bitmask[1]==1){
	printf(" -------Running Signal Category Bit Mask 1, FullExtrapBTAG----------\n"); 

		printf("INCLUSIVE: MT Cut : preselection+extraselection -------------------------------------\n"); 
		std::string inclSel = parser.stringValue("preselection"); 
		std::string catSel = parser.stringValue("extraselection"); //any cat cut
		std::string catDataSel = parser.stringValue("extraselection"); //any cat cut
		std::string bTagSF = parser.stringValue("bTagSF");					 	    
		std::string foldername = parser.stringValue("folder");
		creator.makeHiggsShape(inclSel,catSel,"_extraselection");
		BkgOutput outputIncl = creator.runFullExtrapBtag(inclSel,parser.stringValue("wselection"),inclSel,catSel,foldername,parser.stringValue("zEmbeddedSample"),parser.doubleValue("topSF"),
				1,//parser.doubleValue("zExtrap"),
				1,//parser.doubleValue("zExtrapErr"),
				bTagSF//parser.doubleValue("BTagSF")
				);
	}

	creator.close();
}
