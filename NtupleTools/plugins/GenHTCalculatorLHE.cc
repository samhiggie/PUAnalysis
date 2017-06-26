#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "TH1D.h"
#include "TH2D.h"

class GenHTCalculatorLHE : public edm::EDFilter {

	public:
		GenHTCalculatorLHE (const edm::ParameterSet &);
		virtual bool filter(edm::Event&, const edm::EventSetup&);
		virtual void beginJob();
		virtual void endJob();
	private:
		edm::EDGetTokenT<LHEEventProduct> LHEParticleTag_;
		int statusGen_;

		std::map<std::string,TH1D*> h1_;
		std::map<std::string,TH2D*> h2_;
		std::map<std::string,TH1D*> h3_;

		double sumpt;

		double nall;
		double nsel;
};
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Common/interface/Handle.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <map>
#include <memory>

using namespace edm;
using namespace std;
using namespace reco;


GenHTCalculatorLHE::GenHTCalculatorLHE( const ParameterSet & cfg ) :
	LHEParticleTag_(consumes<LHEEventProduct>(cfg.getUntrackedParameter<edm::InputTag> ("LHETag", edm::InputTag("externalLHEProducer")))),
	statusGen_(cfg.getUntrackedParameter<int>("PartonMultiplicity", 5))
{
}

void GenHTCalculatorLHE::beginJob() {
	nall=0;
	nsel=0;	

	edm::Service<TFileService> fs;
	h1_["LHE_PARTONMULTIPLICITY"]                    =fs->make<TH1D>("LHE_PARTONMULTIPLICITY","hepeup().NUP",20,0.,20.);
	h2_["LHE_LEADINGPARTON_PT"]   =fs->make<TH2D>("LHE_LEADINGPARTON_PT","",20,0,20,100,0,100);
	h3_["LHE_PUPSUM"]                    =fs->make<TH1D>("LHE_PUPSUM","",100,0.,1000.);

}

void GenHTCalculatorLHE::endJob() {
	cout<<"********************************************************************"<<endl;
	cout<<"GEN LEVEL HT Calculation"<<endl<<endl;
	cout<<"********************************************************************"<<endl;




}

bool GenHTCalculatorLHE::filter (Event & ev, const EventSetup &) {
	nall++;

	bool found=true;
        sumpt=0;
        double px=0;
        double py=0;

	edm::Handle<LHEEventProduct> lheeventinfo;
	if(!ev.getByToken(LHEParticleTag_, lheeventinfo)){
		LogDebug("") << ">>> LHE info not found!!";
		return false;
	}
	int nup = lheeventinfo->hepeup().NUP;
	h1_["LHE_PARTONMULTIPLICITY"]->Fill(nup);

	double ptPART=sqrt( lheeventinfo->hepeup().PUP.at(0)[0]*lheeventinfo->hepeup().PUP.at(0)[0] + lheeventinfo->hepeup().PUP.at(0)[1]*lheeventinfo->hepeup().PUP.at(0)[1] );
        //Loop to calculate MAdgraph HT
	for (int i = 0; i < nup ; ++i) {
		if (lheeventinfo->hepeup().ISTUP[i] <0||((abs(lheeventinfo->hepeup().IDUP[i])>5&&lheeventinfo->hepeup().IDUP[i]!=21) )) {
		        //cout<<"Only want final state parton, skipping for HT"<<endl;
			continue;
		}
                //cout<<"Parton number: "<<i<<" Out of "<<nup<<endl; 
                //cout<<"PUP size: "<<lheeventinfo->hepeup().PUP.size()<<endl; 
                //cout<<"ISTUP value: "<<lheeventinfo->hepeup().ISTUP[i]<<endl; 
                //cout<<"IDUP value: "<<lheeventinfo->hepeup().IDUP[i]<<endl; 
	        px=lheeventinfo->hepeup().PUP.at(i)[0];
                //cout<<"PX component: "<<lheeventinfo->hepeup().PUP.at(i)[0]<<endl;
	        py=lheeventinfo->hepeup().PUP.at(i)[1];
                //cout<<"PY component: "<<lheeventinfo->hepeup().PUP.at(i)[1]<<endl;
                double pt=sqrt(px*px+py*py);
                //cout<<"PT component: "<<pt<<endl;
                sumpt+=pt;
	}
	//cout<<"Sum of PUP: "<<sumpt<<endl;

	h2_["LHE_LEADINGPARTON_PT"]  ->Fill(lheeventinfo->hepeup().NUP, ptPART);
	h3_["LHE_PUPSUM"]->Fill(sumpt);


	return found;
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(GenHTCalculatorLHE);
