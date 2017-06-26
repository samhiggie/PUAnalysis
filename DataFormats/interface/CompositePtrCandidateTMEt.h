#ifndef __PUAnalysis_DataFormats_CompositeRefCandidateTMEt_h__
#define __PUAnalysis_DataFormats_CompositeRefCandidateTMEt_h__

/** \class CompositeRefCandidateTMEt
 *
 * Combination of visible tau decay products with missing transverse momentum 
 * (representing the undetected momentum carried away 
 *  the neutrino produced in a W --> tau nu decay and the neutrinos produced in the tau decay)
 * 
 * \authors Christian Veelken
 *
 * \version $Revision: 1.4 $
 *
 * $Id: CompositePtrCandidateTMEt.h,v 1.4 2012/07/01 17:02:13 ojalvo Exp $
 *
 */

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/LeafCandidate.h" 
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

template<typename T>

class CompositePtrCandidateTMEt : public reco::LeafCandidate 
{
  typedef edm::Ptr<T> TPtr;
  typedef edm::Ptr<pat::MET> METPtr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef std::vector<edm::Ptr<pat::Jet> > JetPtrVector;

 public:

  /// default constructor
  CompositePtrCandidateTMEt() {}

  /// constructor with MEt
  CompositePtrCandidateTMEt(const TPtr visDecayProducts, const METPtr met)
    : visDecayProducts_(visDecayProducts), met_(met) {recoilDPhi_=0;}

  /// destructor
  ~CompositePtrCandidateTMEt() {}

  /// access to daughter particles
  const TPtr lepton() const { return visDecayProducts_; }

  const int genPdg() const {return pdg_; }

  /// access to gen. mother particles
  /// (undecayed tau leptons)
  const reco::Candidate::LorentzVector& p4Leptongen() const { return p4Leptongen_; }
  
  /// access to visible gen. daughter particles
  /// (electrons, muons, kaons, charged and neutral pions produced in tau decay)
  const reco::Candidate::LorentzVector& p4VisLeptongen() const { return p4VisLeptongen_; }

  /// access to missing transverse momentum
  const METPtr met() const { return met_; }

  /// get transverse mass of visible decay products + missing transverse momentum
  double Mt() const { return mt_; }
  double mJJ() const {return mjj_;}
  double ptJJ() const {return ptjj_;}
  void setJJVariables(double mjj,double ptjj) {
    mjj_ = mjj;
    ptjj_ = ptjj;
  }

  double genMt() const { return genMt_; }
  double corMt() const { return corMt_; }

  /// build transverse momentum 
  double Pt() const { return pt_; }
  double Px() const { return px_; }
  double Py() const { return py_; }

  double corPt() const { return corPt_; }
  double corPx() const { return corPx_; }
  double corPy() const { return corPy_; }

  double trueMet() const {return trueMet_;}
  double trueMetPhi() const {return trueMetPhi_;}
  double trueMEx() const {return trueMEx_;}
  double trueMEy() const {return trueMEy_;}
  double trueMEz() const {return trueMEz_;}


  reco::Candidate::LorentzVector calibratedMET() const {return calibratedMET_;}


  /// get acoplanarity angle (angle in transverse plane) between visible decay products 
  /// and missing transverse momentum 
  double dPhi() const { return dPhi_; } 
  const reco::Candidate::LorentzVector recoil() const {return recoil_;}
  double recoilDPhi() const {return recoilDPhi_;}

  // rebuild neutrino pz, assuming this is a W:
  // This has yet to be tested (and the definition of the neutrino pz revised)
  double metPz() const {return metPz_;}
  double metPzB() const {return metPzB_;}
  bool isPzSolutionComplex() const { return isPzSolutionComplex_;}
  math::XYZTLorentzVector WP4()  const {return WP4_;}

  ///Jet variables
  const JetPtrVector jets() const {return jets_;}
  int nJets() const {return jets_.size();}
  double ht() const {return ht_;}
  const JetPtr jet(int i) const {return jets_.at(i);}

  /// clone  object
  CompositePtrCandidateTMEt<T>* clone() const { return new CompositePtrCandidateTMEt<T>(*this); }

 private:
  
  void setJetValues(const JetPtrVector& jets,double ht) {
    jets_ = jets;
    ht_   = ht;
  }

  /// allow only CompositePtrCandidateTMEtAlgorithm to change values of data-members
  template<typename T_type> friend class CompositePtrCandidateTMEtAlgorithm; 

  void setP4Leptongen(const reco::Candidate::LorentzVector& p4) { p4Leptongen_ = p4; }
  void setP4VisLeptongen(const reco::Candidate::LorentzVector& p4) { p4VisLeptongen_ = p4; }


  /// set transverse mass of visible decay products + missing transverse momentum
  void setMt(double mt) { mt_ = mt; }
  void setPx(double px) { px_ = px; }
  void setPy(double py) { py_ = py; }
  void setPt(double pt) { pt_ = pt; }

  void setCalibratedMET(const reco::Candidate::LorentzVector& met) { calibratedMET_ = met; }
  void setCorMt(double corMt) { corMt_ = corMt; }
  void setCorPx(double corPx) { corPx_ = corPx; }
  void setCorPy(double corPy) { corPy_ = corPy; }
  void setCorPt(double corPt) { corPt_ = corPt; }

  void setTrueMet(double trueMet){trueMet_=trueMet;}
  void setTrueMetPhi(double trueMetPhi){trueMetPhi_=trueMetPhi;}
  void setTrueMEy(double trueMEy){trueMEy_=trueMEy;}
  void setTrueMEx(double trueMEx){trueMEx_=trueMEx;}
  void setTrueMEz(double trueMEz){trueMEz_=trueMEz;}

  void setGenMt(double genMt) {genMt_ = genMt; }


  void setPdg(int pdg) {pdg_ = pdg;}


  /// set acoplanarity angle (angle in transverse plane) between visible decay products 
  /// and missing transverse momentum
  void setDPhi(double dPhi) { dPhi_ = dPhi; }
  
  void setRecoil(const reco::Candidate::LorentzVector& recoil) {recoil_ = recoil; }
  void setRecoilDPhi(double dPhi) {recoilDPhi_ = dPhi;}


  
  // rebuild neutrino pz (with a different name just in case), assuming this is a W:
  void setMetPz(double metPz) {metPz=metPz_;}
  void setMetPzB(double metPzB) {metPzB=metPzB_;}
  void setIsComplex(double isPzSolutionComplex){isPzSolutionComplex=isPzSolutionComplex_;}
  void setWP4 ( math::XYZTLorentzVector WP4) {WP4=WP4_;} 

  /// references/pointers to decay products and missing transverse momentum
  reco::Candidate::LorentzVector recoil_;
  double recoilDPhi_;

  TPtr visDecayProducts_;
  METPtr met_;
  /// transverse mass of visible decay products + missing transverse momentum
  double mt_;
  double corMt_;
  /// W momentum:
  double px_;
  double py_;
  double pt_;
  double corPx_;
  double corPy_;
  double corPt_;
  reco::Candidate::LorentzVector calibratedMET_;

  /// acoplanarity angle (angle in transverse plane) between visible decay products
  /// and missing transverse momentum
  double dPhi_;

  // pz of the neutrino (once the candidate is assumed to be a W boson)
  double metPz_;
  double metPzB_;
  double isPzSolutionComplex_;
  math::XYZTLorentzVector WP4_;

  JetPtrVector jets_;
  double ht_;


  //JJ variables
  double mjj_,ptjj_;

  /// gen. four-momenta
  reco::Candidate::LorentzVector p4Leptongen_;
  reco::Candidate::LorentzVector p4VisLeptongen_;

  int pdg_;

  //true Met
  double trueMet_;
  double trueMetPhi_;
  double trueMEy_;
  double trueMEx_;
  double trueMEz_;
  double genMt_;
};

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

//typedef CompositePtrCandidateTMEt<pat::Tau> PATTauNuPair;
//typedef CompositePtrCandidateTMEt<pat::Muon> PATMuonNuPair;
//typedef CompositePtrCandidateTMEt<pat::Electron> PATElectronNuPair;
//typedef CompositePtrCandidateTMEt<reco::Candidate> PATCandNuPair;

#endif
