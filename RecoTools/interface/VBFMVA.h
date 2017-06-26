// Original Author:  Joshua Swanson
//         Created:  Wed 16 May 2012
#ifndef RecoTools_calcVBFMVA_H
#define RecoTools_calcVBFMVA_H

// system include files
#include <memory>
#include <vector>

// user include files
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "Rtypes.h"

//
// class decleration



class VBFMVA  {
   	public:
		
		void   Initialize(  std::string Weights  );
		Bool_t IsInitialized() const { return fIsInitialized; }
		
		
		double calcVBFMVA(double mjj,
			double dEta,
			double C1,
			double C2	);
			
	
	protected:
	
		Bool_t       fIsInitialized;
		TMVA::Reader	*fTMVAReader;		
		std::vector<Float_t> vbfvars;

};


#endif
