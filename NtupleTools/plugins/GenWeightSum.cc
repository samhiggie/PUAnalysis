#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "TH1F.h"
#include <TTree.h>

class GenWeightSum : public edm::EDFilter {

	public:
		GenWeightSum (const edm::ParameterSet &);
		virtual bool filter(edm::Event&, const edm::EventSetup&);
		virtual void beginJob();
		virtual void endJob();
	private:
		edm::EDGetTokenT<GenEventInfoProduct> src_;

		TH1F * genWeights;


		unsigned int nall;
		unsigned int sumweight;
		float weight;
};

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Common/interface/Handle.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include <map>
#include <memory>

using namespace edm;
using namespace std;
using namespace reco;


GenWeightSum::GenWeightSum( const ParameterSet & cfg ) :
	src_(consumes<GenEventInfoProduct>(cfg.getUntrackedParameter<edm::InputTag>("genWeightSrc",edm::InputTag("generator"))))
{

		edm::Service<TFileService> fs;
		genWeights = fs->make<TH1F>( "genWeights","genWeights",2,-1,1);


}

void GenWeightSum::beginJob() {
	cout<<"Begin Job"<<endl;
	nall=0;
	sumweight=0;
}

void GenWeightSum::endJob() {
	cout<<"********************************************************************"<<endl;
	cout<<"GEN LEVEL FILTERING"<<endl<<endl;
	cout<<"Total Analyzed =   "<<nall<<endl;
	cout<<"GEN Weights total Analyzed =   "<<sumweight<<endl;
	cout<<"********************************************************************"<<endl;

}

bool GenWeightSum::filter (Event & ev, const EventSetup &) {
	nall++;

	float weight=.5;

	edm::Handle<GenEventInfoProduct> genEvt;
	if(ev.getByToken(src_,genEvt)) {
		sumweight += genEvt->weight();
		if ( (genEvt->weight()) <0) weight=-0.5;	
	}
	genWeights->Fill(weight);
	return true;

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(GenWeightSum);
