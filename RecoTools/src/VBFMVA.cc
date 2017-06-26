// Original Author:  Joshua Swanson
//         Created:  Wed 16 May 2012
#include <TFile.h>
#include "PUAnalysis/RecoTools/interface/VBFMVA.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"


void VBFMVA::Initialize( std::string Weights ) {

  	fIsInitialized = kTRUE;

	fTMVAReader = new TMVA::Reader( "!Color:!Silent:Error" );  
	vbfvars.resize(8);
	fTMVAReader->AddVariable("mjj", &vbfvars[0]);
	fTMVAReader->AddVariable("dEta", &vbfvars[1]);
	fTMVAReader->AddVariable("C1", &vbfvars[6]);
	fTMVAReader->AddVariable("C2", &vbfvars[7]);

	fTMVAReader->BookMVA("BDTG", Weights);

}

//--------------------------------------------------------------------------------------------------
Double_t VBFMVA::calcVBFMVA(Double_t mjj,
			Double_t dEta,
			Double_t C1,
			Double_t C2) {
  
	if (!fIsInitialized) { 
		std::cout << "Error: VBFMVA not properly initialized.\n"; 
		return -9999;
	}
  
  	//set all input variables
	vbfvars[0] = mjj;
	vbfvars[1] = dEta;
	vbfvars[2] = C1;
	vbfvars[3] = C2;

                                                
	// Evaluate MVA
	float mva = fTMVAReader->EvaluateMVA( vbfvars, "BDTG");

  	return mva;
  	
}




