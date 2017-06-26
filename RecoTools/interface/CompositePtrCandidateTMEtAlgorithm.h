#ifndef PUAnalysis_RecoTools_CompositePtrCandidateTMEtAlgorithm_h
#define PUAnalysis_RecoTools_CompositePtrCandidateTMEtAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/normalizedPhi.h"

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

#include "PUAnalysis/RecoTools/interface/candidateAuxFunctions.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 

#include <TMath.h>

template<typename T>
class CompositePtrCandidateTMEtAlgorithm 
{
  typedef edm::Ptr<T> TPtr;
  typedef edm::Ptr<pat::MET> METPtr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef std::vector<JetPtr> JetPtrVector;

 public:

  CompositePtrCandidateTMEtAlgorithm()
  {
    verbosity_ = 0;
  }
  ~CompositePtrCandidateTMEtAlgorithm() {}


  CompositePtrCandidateTMEt<T> buildCompositePtrCandidate(const TPtr visDecayProducts, 
							  METPtr met,
							  JetPtrVector pfJets,
							  edm::View<T> visProductCollection,
							  const reco::GenParticleCollection* genParticles)
  {
    CompositePtrCandidateTMEt<T> compositePtrCandidate(visDecayProducts, met);
  
    if ( visDecayProducts.isNull() ) {
      edm::LogError ("CompositePtrCandidateTMEtAlgorithm") << " Pointer to visible Decay products invalid !!";
      return compositePtrCandidate;
    }

    if ( met.isNull() ) {
      edm::LogError ("CompositePtrCandidateTMEtAlgorithm") << " Pointer to missing transverse momentum invalid !!";
      return compositePtrCandidate;
    }

    reco::Candidate::LorentzVector recoil(-met->px()-visDecayProducts->px(),-met->py()-visDecayProducts->py(),0.0,sqrt(pow(met->px()+visDecayProducts->px(),2)+pow(met->py()+visDecayProducts->py(),2)));

    compositePtrCandidate.setRecoil(recoil);
    compositePtrCandidate.setRecoilDPhi(deltaPhi(recoil.phi(),visDecayProducts->phi()));
    compositePtrCandidate.setCharge(visDecayProducts->charge());
    compositePtrCandidate.setMt(compMt(visDecayProducts->p4(), met->px(), met->py()));
    compositePtrCandidate.setDPhi(TMath::Abs(normalizedPhi(visDecayProducts->phi() - met->phi())));
    compositePtrCandidate.setPx(visDecayProducts->px() + met->px());
    compositePtrCandidate.setPy(visDecayProducts->py() + met->py());
    compositePtrCandidate.setPt(sqrt( (visDecayProducts->py() + met->py())*(visDecayProducts->py() + met->py()) + (visDecayProducts->px() + met->px())*(visDecayProducts->px() + met->px())));
    computeMETPz(compositePtrCandidate, met->px(), met->py());
    //printf("correctedMET: %f\n",met->pt());
    //calibrate the MET
    reco::Candidate::LorentzVector correctedMET = met->p4();
    compositePtrCandidate.setCalibratedMET(correctedMET);
    //printf("correctedMET: %f\n",correctedMET.pt());
    compositePtrCandidate.setCorMt(compMt(visDecayProducts->p4(), correctedMET.px(), correctedMET.py()));
    compositePtrCandidate.setCorPt(sqrt( (visDecayProducts->py() + correctedMET.py())*(visDecayProducts->py() + correctedMET.py()) + (visDecayProducts->px() + correctedMET.px())*(visDecayProducts->px() + correctedMET.px())));
    compositePtrCandidate.setCorPx(visDecayProducts->px() + correctedMET.px());
    compositePtrCandidate.setCorPy(visDecayProducts->py() + correctedMET.py());
    //Jets
    JetPtrVector cleanedJets;
    for(unsigned int i=0;i<pfJets.size();++i)
	    if((reco::deltaR(pfJets.at(i)->p4(),visDecayProducts->p4())>0.5)&&fabs(pfJets.at(i)->eta())<2.4&&pfJets.at(i)->userFloat("idLoose")>0)
		    cleanedJets.push_back(pfJets.at(i));

    //sort them by Pt
    sortRefVectorByPt(cleanedJets);
    unsigned int nJets = cleanedJets.size();


    if(nJets>1) 
	    compositePtrCandidate.setJJVariables((cleanedJets.at(0)->p4()+cleanedJets.at(1)->p4()).M(),(cleanedJets.at(0)->p4()+cleanedJets.at(1)->p4()).pt());
    else
	    compositePtrCandidate.setJJVariables(0.0,0.0);


    //find the nearest jet to leg1
    double ht = visDecayProducts->pt();
    for(unsigned int k=0;k<nJets;++k)
	    ht+=cleanedJets.at(k)->pt();


    compositePtrCandidate.setJetValues(cleanedJets,ht); //sets cleaned jets as  default jets()


    //--- compute gen. level quantities
    if ( genParticles ) {
	    compGenQuantities(compositePtrCandidate, genParticles);
	    compTrueMet(compositePtrCandidate, genParticles);
	    compositePtrCandidate.setGenMt(compMt(compositePtrCandidate.p4Leptongen(), compositePtrCandidate.trueMEx(),compositePtrCandidate.trueMEy()));
    }


    return compositePtrCandidate;
  }

 private: 

  void computeMETPz(CompositePtrCandidateTMEt<T>& compositePtrCandidate, double MetPx, double MetPy){
	  // WARNING: This assumes that the lepton+MET is a W boson
	  // For coherence, this should be moved out of this general class (I am lazy right now) 
	  double M_W  = 80.4;

	  double pxmu = compositePtrCandidate.lepton()->px();
	  double pymu = compositePtrCandidate.lepton()->py();
	  double pzmu = compositePtrCandidate.lepton()->pz();
	  double emu = compositePtrCandidate.lepton()->energy();
	  double pznu = 0.;
	  double otherSol_ = 0.;
	  bool isComplex_=false;

	  double a = M_W*M_W + 2.0*pxmu*MetPx + 2.0*pymu*MetPy;
	  double A = 4.0*(emu*emu - pzmu*pzmu);
	  double B = -4.0*a*pzmu;
	  double C = 4.0*emu*emu*(MetPx*MetPx+MetPy*MetPy) - a*a;

	  double tmproot = B*B - 4.0*A*C;

	  if (tmproot<0) {
		  isComplex_= true;
		  pznu = - B/(2*A); // take real part of complex roots
		  otherSol_ = pznu;
	  }
	  else {
		  isComplex_ = false;
		  double tmpsol1 = (-B + TMath::Sqrt(tmproot))/(2.0*A);
		  double tmpsol2 = (-B - TMath::Sqrt(tmproot))/(2.0*A);

		  if (TMath::Abs(tmpsol2-pzmu) < TMath::Abs(tmpsol1-pzmu)) { pznu = tmpsol2; otherSol_ = tmpsol1;}
		  else { pznu = tmpsol1; otherSol_ = tmpsol2; }
		  // if pznu is > 300 pick the most central root
		  if ( pznu > 300. ) {
			  if (TMath::Abs(tmpsol1)<TMath::Abs(tmpsol2) ) { pznu = tmpsol1; otherSol_ = tmpsol2; }
			  else { pznu = tmpsol2; otherSol_ = tmpsol1; }
		  }
	  }
	  compositePtrCandidate.setMetPz(pznu);
	  compositePtrCandidate.setMetPzB(otherSol_);
	  compositePtrCandidate.setIsComplex(isComplex_);
	  double PX_TOTAL=pxmu+MetPx;
	  double PY_TOTAL=pymu+MetPy;
	  double PZ_TOTAL=pzmu+pznu;
	  double EN_TOTAL=sqrt(PX_TOTAL*PX_TOTAL+PY_TOTAL*PY_TOTAL+PZ_TOTAL*PZ_TOTAL);
	  compositePtrCandidate.setWP4(math::XYZTLorentzVector(PX_TOTAL,PY_TOTAL,PZ_TOTAL,EN_TOTAL));
  } 

  void compGenQuantities(CompositePtrCandidateTMEt<T>& compositePtrCandidate, const reco::GenParticleCollection* genParticles)
  {
	  const reco::GenParticle* genLepton = findGenParticle(compositePtrCandidate.lepton()->p4(), *genParticles, 0.5, -1);
	  if ( genLepton ) {
		  compositePtrCandidate.setP4Leptongen(genLepton->p4());
		  compositePtrCandidate.setP4VisLeptongen(getVisMomentum(genLepton, genParticles));
		  compositePtrCandidate.setPdg(genLepton->pdgId());
	  }
  }     

  void compTrueMet(CompositePtrCandidateTMEt<T>& compositePtrCandidate, const reco::GenParticleCollection* genParticles){
	  double trueMEY  = 0.0;
	  double trueMEX  = 0.0;;
	  double trueMEZ  = 0.0;;

	  for( unsigned i = 0; i < genParticles->size(); i++ ) {
		  const reco::GenParticle& genpart = (*genParticles)[i];
		  if( genpart.status() == 1 && fabs(genpart.eta()) < 5.0 ) { 
			  if( std::abs(genpart.pdgId()) == 12 ||
					  std::abs(genpart.pdgId()) == 14 ||
					  std::abs(genpart.pdgId()) == 16  
					  //  ||std::abs(genpart.pdgId()) < 7   || 
					  //  std::abs(genpart.pdgId()) == 21 
			    ) {
				  trueMEX += genpart.px();
				  trueMEY += genpart.py();
				  trueMEZ += genpart.pz();

			  } 
		  }
	  }
	  double true_met = sqrt( trueMEX*trueMEX + trueMEY*trueMEY );
	  double true_phi = atan2(trueMEY,trueMEX);	

	  compositePtrCandidate.setTrueMet(true_met);
	  compositePtrCandidate.setTrueMetPhi(true_phi);
	  compositePtrCandidate.setTrueMEy(trueMEY);
	  compositePtrCandidate.setTrueMEx(trueMEX);
	  compositePtrCandidate.setTrueMEz(trueMEZ);
  }





  double compMt(const reco::Candidate::LorentzVector& visParticle, 
		  double metPx, double metPy)
  {
	  double px = visParticle.px() + metPx;
	  double py = visParticle.py() + metPy;
	  double et = visParticle.Et() + TMath::Sqrt(metPx*metPx + metPy*metPy);
	  double mt2 = et*et - (px*px + py*py);
	  if ( mt2 < 0 ) {
		  //      edm::LogWarning ("compMt") << " mt2 = " << mt2 << " must not be negative !!";
		  return 0.;
	  }
	  return TMath::Sqrt(mt2);
  }

  class refVectorPtSorter {
	  public:
		  refVectorPtSorter(const JetPtrVector vec)
		  {
			  vec_ = vec;
		  }

		  refVectorPtSorter()
		  {
		  }


		  ~refVectorPtSorter()
		  {}

		  bool operator()(size_t a , size_t b) {
			  return (vec_.at(a)->pt() > vec_.at(b)->pt());
		  }
	  private:
		  JetPtrVector vec_;
  };



  void sortRefVectorByPt(JetPtrVector& vec)
  {
	  std::vector<size_t> indices;
	  indices.reserve(vec.size());
	  for(unsigned int i=0;i<vec.size();++i)
		  indices.push_back(i);

	  refVectorPtSorter sorter(vec);
	  std::sort(indices.begin(),indices.end(),sorter);

	  JetPtrVector sorted;
	  sorted.reserve(vec.size());

	  for(unsigned int i=0;i<indices.size();++i)
		  sorted.push_back(vec.at(indices.at(i)));

	  vec = sorted;
  }



  int verbosity_;
};

#endif 

