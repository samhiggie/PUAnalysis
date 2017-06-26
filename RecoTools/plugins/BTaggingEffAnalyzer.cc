// -*- C++ -*-
//
// Package:    BTaggingEffAnalyzer
// Class:      BTaggingEffAnalyzer
// 
/**\class BTaggingEffAnalyzer BTaggingEffAnalyzer.cc Analysis/EDSHyFT/plugins/BTaggingEffAnalyzer.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH2D.h"
#include "TH1.h"


//
// class declaration
//

class BTaggingEffAnalyzer : public edm::EDAnalyzer {
	public:
		explicit BTaggingEffAnalyzer(const edm::ParameterSet&);
		~BTaggingEffAnalyzer();

		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


	private:
		virtual void beginJob() ;
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob() ;

		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

		// ----------member data ---------------------------
		const edm::EDGetTokenT<pat::JetCollection> jetsTag;
		const edm::EDGetTokenT<pat::TauCollection> tausTag;
		const std::string   discriminatorTag;
		const double  discriminatorValue;
		const int     ptNBins;
		const double  ptMin;
		const double  ptMax;
		const int     etaNBins;
		const double  etaMin;
		const double  etaMax;
		edm::Service<TFileService>  fs;
		TH2D  *h2_BTaggingEff_Denom_b;
		TH2D  *h2_BTaggingEff_Denom_c;
		TH2D  *h2_BTaggingEff_Denom_udsg;
		TH2D  *h2_BTaggingEff_Num_b;
		TH2D  *h2_BTaggingEff_Num_c;
		TH2D  *h2_BTaggingEff_Num_udsg;
		TH2D  *h2_BTaggingEff_b;
		TH2D  *h2_BTaggingEff_c;
		TH2D  *h2_BTaggingEff_udsg;
};

//
// constants, enums and typedefs
//
//typedef std::vector<pat::Jet> pat::JetCollection;

//
// static data member definitions
//

//
// constructors and destructor
//
BTaggingEffAnalyzer::BTaggingEffAnalyzer(const edm::ParameterSet& iConfig) :

	jetsTag(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("JetsTag"))),
	tausTag(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("TausTag"))),
	discriminatorTag(iConfig.getParameter<std::string>("DiscriminatorTag")),
	discriminatorValue(iConfig.getParameter<double>("DiscriminatorValue")),
	ptNBins(iConfig.getParameter<int>("PtNBins")),
	ptMin(iConfig.getParameter<double>("PtMin")),
	ptMax(iConfig.getParameter<double>("PtMax")),
	etaNBins(iConfig.getParameter<int>("EtaNBins")),
	etaMin(iConfig.getParameter<double>("EtaMin")),
	etaMax(iConfig.getParameter<double>("EtaMax"))

{
	//now do what ever initialization is needed
	h2_BTaggingEff_Denom_b    = fs->make<TH2D>("h2_BTaggingEff_Denom_b", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_Denom_c    = fs->make<TH2D>("h2_BTaggingEff_Denom_c", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_Denom_udsg = fs->make<TH2D>("h2_BTaggingEff_Denom_udsg", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_Num_b    = fs->make<TH2D>("h2_BTaggingEff_Num_b", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_Num_c    = fs->make<TH2D>("h2_BTaggingEff_Num_c", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_Num_udsg = fs->make<TH2D>("h2_BTaggingEff_Num_udsg", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_b    = fs->make<TH2D>("h2_BTaggingEff_b", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_c    = fs->make<TH2D>("h2_BTaggingEff_c", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
	h2_BTaggingEff_udsg    = fs->make<TH2D>("h2_BTaggingEff_udsg", ";p_{T} [GeV];#eta", ptNBins, ptMin, ptMax, etaNBins, etaMin, etaMax);
}


BTaggingEffAnalyzer::~BTaggingEffAnalyzer()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
	void
BTaggingEffAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	edm::Handle<pat::TauCollection> taus;
	iEvent.getByToken(tausTag,taus);

	//edm::Handle<pat::EleCollection> eles;
	//iEvent.getByToken(elesTag,eles);


	edm::Handle<pat::JetCollection> jets;
	iEvent.getByToken(jetsTag,jets);
// loop over jets
	for(pat::JetCollection::const_iterator it = jets->begin(); it != jets->end(); ++it)
	{
		int partonFlavor = it->partonFlavour();
		if (it->pt()<30 || (it->eta()>2.4||it->eta()<-2.4)) continue;

		bool selectEvent=false;
		for(pat::TauCollection::const_iterator tau = taus->begin(); tau != taus->end(); ++tau){
			if (tau->tauID("decayModeFinding")>0.5 &&tau->tauID("byLooseIsolationMVArun2v1DBoldDMwLT") > 0.5&& (tau->eta()<-2.3||tau->eta()>2.3)) selectEvent = true;
		}
		if (selectEvent==false) continue;


		if( abs(partonFlavor)==5 )
		{
			h2_BTaggingEff_Denom_b->Fill(it->pt(), it->eta());
			if( it->bDiscriminator(discriminatorTag.c_str()) >= discriminatorValue ) {h2_BTaggingEff_Num_b->Fill(it->pt(), it->eta()); h2_BTaggingEff_b->Fill(it->pt(), it->eta());}

		}
		else if( abs(partonFlavor)==4 )
		{
			h2_BTaggingEff_Denom_c->Fill(it->pt(), it->eta());
			if( it->bDiscriminator(discriminatorTag.c_str()) >= discriminatorValue ) {h2_BTaggingEff_Num_c->Fill(it->pt(), it->eta());h2_BTaggingEff_c->Fill(it->pt(), it->eta()); }
		}
		else
		{
			h2_BTaggingEff_Denom_udsg->Fill(it->pt(), it->eta());
			if( it->bDiscriminator(discriminatorTag.c_str()) >= discriminatorValue ) {h2_BTaggingEff_Num_udsg->Fill(it->pt(), it->eta());h2_BTaggingEff_udsg->Fill(it->pt(), it->eta()); }
		}
	}
}


// ------------ method called once each job just before starting event loop  ------------
	void 
BTaggingEffAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
	void 
BTaggingEffAnalyzer::endJob() 
{
	h2_BTaggingEff_b->Divide(h2_BTaggingEff_Denom_b);
	h2_BTaggingEff_c->Divide(h2_BTaggingEff_Denom_c);
	h2_BTaggingEff_udsg->Divide(h2_BTaggingEff_Denom_udsg);
}

// ------------ method called when starting to processes a run  ------------
	void 
BTaggingEffAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
	void 
BTaggingEffAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
	void 
BTaggingEffAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
	void 
BTaggingEffAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BTaggingEffAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BTaggingEffAnalyzer);
