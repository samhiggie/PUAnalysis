#ifndef __PUAnalysis_DataFormats_Analysis_CompositeRefCandidateT1T2MEt_h__
#define __PUAnalysis_DataFormats_Analysis_CompositeRefCandidateT1T2MEt_h__

#include "TMatrixD.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Common/interface/Ptr.h"


#include "PUAnalysis/DataFormats/interface/tauAnalysisAuxFunctions.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"


template<typename T1, typename T2>
class CompositePtrCandidateT1T2MEt : public reco::LeafCandidate
{
  typedef edm::Ptr<T1> T1Ptr;
  typedef edm::Ptr<T2> T2Ptr;
  typedef edm::Ptr<pat::Jet> JetPtr;
  typedef edm::Ptr<pat::MET> METPtr;
  typedef std::vector<JetPtr> JetPtrVector;

 public:

  /// default constructor
  CompositePtrCandidateT1T2MEt() {}

  /// constructor with MEt
  CompositePtrCandidateT1T2MEt(const T1Ptr leg1, const T2Ptr leg2, const reco::CandidatePtr met)
    : leg1_(leg1), leg2_(leg2), met_(met), covMatrix_(2,2) {}

  /// constructor without MEt
  CompositePtrCandidateT1T2MEt(const T1Ptr leg1, const T2Ptr leg2)
    : leg1_(leg1), leg2_(leg2) {}

  /// destructor
  ~CompositePtrCandidateT1T2MEt() {}

  /// access to daughter particles
  const T1Ptr leg1() const { return leg1_; }
  const T2Ptr leg2() const { return leg2_; }


  const int genPdg1() const {return pdg1_; }
  const int genPdg2() const {return pdg2_; }
  const float genBosonMass() const {return genBosonMass_;}

  /// access to gen. momenta
  reco::Candidate::LorentzVector p4gen() const { return p4Leg1gen() + p4Leg2gen(); }
  reco::Candidate::LorentzVector p4VisGen() const { return p4VisLeg1gen() + p4VisLeg2gen(); }

  reco::Candidate::LorentzVector p4GenBoson() const { return p4Boson_; }
  reco::Candidate::LorentzVector p4GenBosonVis() const { return p4BosonVis_; }

  /// access to gen. mother particles
  /// (undecayed tau leptons)
  const reco::Candidate::LorentzVector& p4Leg1gen() const { return p4Leg1gen_; }
  const reco::Candidate::LorentzVector& p4Leg2gen() const { return p4Leg2gen_; }

  /// access to visible gen. daughter particles
  /// (electrons, muons, kaons, charged and neutral pions produced in tau decay)
  const reco::Candidate::LorentzVector& p4VisLeg1gen() const { return p4VisLeg1gen_; }
  const reco::Candidate::LorentzVector& p4VisLeg2gen() const { return p4VisLeg2gen_; }


  /// set decay statusFlag
  const int isPrompt1() const { return isPrompt1_; } 
  const int isPromptFS1() const { return isPromptFS1_; } 
  const int isDirectPromptTauDecayProduct1() const { return isTauDecayFlag1_; }  
  const int isDirectPromptTauDecayProductFS1() const { return isTauDecayFlagFS1_; } 

  const int isPrompt2() const { return isPrompt2_; } 
  const int isPromptFS2() const { return isPromptFS2_; } 
  const int isDirectPromptTauDecayProduct2() const { return isTauDecayFlag2_; }  
  const int isDirectPromptTauDecayProductFS2() const { return isTauDecayFlagFS2_; } 



  /// energy ratio of visible gen. daughter/mother particles
  double x1gen() const { return ( p4Leg1gen_.energy() > 0. ) ? p4VisLeg1gen_.energy()/p4Leg1gen_.energy() : -1.; }
  double x2gen() const { return ( p4Leg2gen_.energy() > 0. ) ? p4VisLeg2gen_.energy()/p4Leg2gen_.energy() : -1.; }

  float isData() const {return data_;}
  //Top Gen Pt
  float isTop() const {return top_;}
  float topGenPt() const {return topGenPt_;}
  float antiTopGenPt() const {return antiTopGenPt_;}

  /// return the number of source particle-like Candidates
  /// (the candidates used to construct this Candidate)
  /// MET does not count.
  size_t numberOfSourceCandidatePtrs() const { return 2; }

  /// return a Ptr to one of the source Candidates
  /// (the candidates used to construct this Candidate)
  reco::CandidatePtr sourceCandidatePtr( size_type i ) const {
    if(i==0) return leg1();
    else if(i==1) return leg2();
    else assert(0);
  }

  /// access to missing transverse momentum
  const METPtr met() const { return met_; }
  //const reco::Candidate::LorentzVector& metOld() const { return metOld_; }

  // get sum of charge of visible decay products
  // (not need to declare it in CompositePtrCandidateT1T2MEt;
  //  already declared in Candidate base-class)

  /// get four-momentum of visible decay products
  const reco::Candidate::LorentzVector& p4Vis() const { return p4Vis_; }

  /// get four-momentum and scaling factors for momenta of visible decay products
  /// computed by collinear approximation
  const reco::Candidate::LorentzVector& p4CollinearApprox() const { return p4CollinearApprox_; }
  double x1CollinearApprox() const { return x1CollinearApprox_; }
  double x2CollinearApprox() const { return x2CollinearApprox_; }
  bool collinearApproxIsValid() const { return collinearApproxIsValid_; }
  double svMass() const { return svMass_; }
  double svPt()   const { return svPt_; }
  double fullPt()  const { return fullPt_; }
  double fullEta()  const { return fullEta_; }
  double fullPhi()  const { return fullPhi_; }
  double fullEnergy()  const { return fullEnergy_; }

  double mJJCSVSort() const { return mJJCSVSort_; }
  double mJJReg() const { return mJJReg_; }
  double mJJHMassSort() const { return mJJHMassSort_; }

  double lVeto() const { return lVeto_; }

  /// get "pseudo" four-momentum computed by CDF method
  /// (for a description of the method, see e.g. CDF note 8972)
  const reco::Candidate::LorentzVector& p4CDFmethod() const { return p4CDFmethod_; }

  /// get transverse mass of visible decay products + missing transverse momentum
  double mt12MET() const { return mt12MET_; }

  /// get transverse mass of first/second
  /// visible decay product + missing transverse momentum
  double mt1MET() const { return mt1MET_; }
  double mt2MET() const { return mt2MET_; }

  /// get acoplanarity angle (angle in transverse plane) between visible decay products
  double dPhi12() const { return dPhi12_; }

  /// get separation in eta-phi between visible decay products
  double dR12() const { return dR12_; }

  /// get minimal/maximal pseudo-rapidity of visible decay products
  double visEtaMin() const { return visEtaMin_; }
  double visEtaMax() const { return visEtaMax_; }

  /// get acoplanarity angle (angle in transverse plane) between first/second
  /// visible decay product and missing transverse momentum
  double dPhi1MET() const { return dPhi1MET_; }
  double dPhi2MET() const { return dPhi2MET_; }

  /// get values of CDF-"zeta" variables
  /// (indicating the consistency of the missing transverse momentum observed in an event
  ///  with the hypothesis of originating from tau neutrinos)
  double pZeta() const { return pZeta_; }
  double pZetaVis() const { return pZetaVis_; }

  // MET projected along the direction of the nearest lepton if within pi/2 otherwise just full MET
  double projMET() const { return projMET_; }
  
  double metPhi() const { return metPhi_; }
  double covMatrix00() const { return covMatrix00_; }
  double covMatrix01() const { return covMatrix01_; }
  double covMatrix10() const { return covMatrix10_; } 
  double covMatrix11() const { return covMatrix11_; }
  //double covMatrixSig00() const { return covMatrixSig00_; }
  //double covMatrixSig01() const { return covMatrixSig01_; }
  //double covMatrixSig10() const { return covMatrixSig10_; } 
  //double covMatrixSig11() const { return covMatrixSig11_; }




  //Vertex variables

  //Z difference of the first and second leg after propagation of tracks to the beamspot
  double dz() const {return dZ12_;}
  //Z Position of the first leg and second leg
  double z1() const {return z1_;}
  double z2() const {return z2_;}
  //Distance of closest approach of the two tracks
  double dca() const {return dca_;}
  //Transverse Distance from beamspot of the crossing point of the two track trajectories
  double crossingPointDistance() const {return crossingPointDistance_;}


  //////RECOIL
  reco::Candidate::LorentzVector recoil() const {return recoil_;}
  reco::Candidate::LorentzVector calibratedMET() const {return calibratedMET_;}
  reco::Candidate::LorentzVector metOld() const {return metOld_;}

  pat::Jet J1MatchedB() const {return J1MatchedB_;}
  pat::Jet J2MatchedB() const {return J2MatchedB_;}

  ////get rid of these
  double J1MatchedBpt() const {
    //std::cout<<"Matched b pt"<<J1MatchedB_.pt()<<std::endl; 
    return J1MatchedB_.pt();}
  double J2MatchedBpt() const {return J2MatchedB_.pt();}

  double recoilDPhi() const {return recoilDPhi_;}
  double EventBTag() const {return EventBTag_;}
  double NBTags() const {return NBTags_;}
  double NBTagsUp() const {return NBTagsUp_;}
  double NBTagsDown() const {return NBTagsDown_;}
  TMatrixD covMatrix() const {return covMatrix_;}


  //Jet variables
  int nJets() const {return jets_.size();}
  std::vector<JetPtr>  jets() const {return jets_;}
  double  ht() const {return ht_;}

  //bEfficiency variables
  double SFCSVL1() const {
    //std::cout << SFCSVL1_ << " SFCSVL1" << std::endl;
    return SFCSVL1_;}
  double SFCSVL2() const {return SFCSVL2_;}
  double SFCSVM1() const {return SFCSVM1_;}
  double SFCSVM2() const {return SFCSVM2_;}
  double SFCSVT1() const {return SFCSVT1_;}
  double SFCSVT2() const {return SFCSVT2_;}

  double SFCSVL1err() const {return SFCSVL1err_;}
  double SFCSVL2err() const {return SFCSVL2err_;}
  double SFCSVM1err() const {return SFCSVM1err_;}
  double SFCSVM2err() const {return SFCSVM2err_;}
  double SFCSVT1err() const {return SFCSVT1err_;}
  double SFCSVT2err() const {return SFCSVT2err_;}

  //JJ Variables
  float mJJ() const {return mJJ_;}
  float ptJJ() const {return ptJJ_;}
  float etaJJ() const {return etaJJ_;}
  float phiJJ() const {return phiJJ_;}
  float energyJJ() const {return EJJ_;}

  //VBF Variables
  float vbfMass() const {return vbfMass_;}
  float vbfDEta() const {return vbfDEta_;}
  float vbfDPhi() const {return vbfDPhi_;}
  float vbfPt1() const {return vbfPt1_;}
  float vbfPt2() const {return vbfPt2_;}
  float vbfDiJetPt() const {return vbfDiJetPt_;}
  float vbfDiTauPt() const {return vbfDiTauPt_;}
  float vbfEta1() const {return vbfEta1_;}
  float vbfEta2() const {return vbfEta2_;}
  float vbfDPhiHJ() const {return vbfDPhiHJ_;}
  float vbfC1() const {return vbfC1_;}
  float vbfC2() const {return vbfC2_;}

  int   vbfNJetsGap20() const {return vbfNJetsGap20_;}
  int   vbfNJetsGap30() const {return vbfNJetsGap30_;}

  reco::Candidate::PolarLorentzVector SVFourVector() const {
    reco::Candidate::PolarLorentzVector SVFourVec(svMass(),fullEta(),fullPhi(),fullEnergy());
    return SVFourVec; }
  ///csv sorting and 125gev selection
  float hhMass() const { 
    return (SVFourVector()+JJ_).M();
  }; 
  float hhMassReg() const { 
    return (SVFourVector()+JJReg_).M();
  }; 
  float hhPt() const { return (SVFourVector()+JJ_).pt();}; 
  float hhEta() const { return (SVFourVector()+JJ_).eta();}; 
  float hhPhi() const { return (SVFourVector()+JJ_).phi();}; 
  float hhE() const { return (SVFourVector() + JJ_).E();}; 


  /// clone  object
  CompositePtrCandidateT1T2MEt<T1,T2>* clone() const { return new CompositePtrCandidateT1T2MEt<T1,T2>(*this); }

  friend std::ostream& operator<<(std::ostream& out, const CompositePtrCandidateT1T2MEt<T1,T2>& dic) {
    out << "Di-Candidate m = " << dic.mass();
    return out;
  }


  void setLVeto(double LVeto) { lVeto_ = LVeto; }
  void setSVMass(double svMass) { svMass_ = svMass; }
  void setSVPt(double svPt) { svPt_ = svPt; }

  void setJJReg(math::PtEtaPhiELorentzVector JJReg){
    JJReg_=JJReg;
  }

  void setJJVariables(reco::Candidate::LorentzVector JJ){
    JJ_ = JJ;
    mJJ_ = JJ.M();
    if(mJJ_ < 0 ) mJJ_ = -9999;
    ptJJ_ = JJ.pt();
    etaJJ_ = JJ.eta();
    phiJJ_ = JJ.phi();
    EJJ_ = JJ.E();
  };

  void setMatchedBJets(pat::Jet& J1MatchedB, 
		       pat::Jet& J2MatchedB) { J1MatchedB_ = J1MatchedB; J2MatchedB_ = J2MatchedB; }

  void setCSVSortedJets(JetPtrVector cleanedJetsCSVSort) { 
    CSVSize = cleanedJetsCSVSort.size();
    if(CSVSize>0)
    J1CSVSort_ = cleanedJetsCSVSort.at(0); 
    if(CSVSize>1)
      J2CSVSort_ = cleanedJetsCSVSort.at(1); }

 private:
  void setmJJCSVSort(double mJJCSVSort) { mJJCSVSort_ = mJJCSVSort; }
  void setmJJReg(double mJJReg) { mJJReg_ = mJJReg; }
  void setmJJHMassSort(double mJJHMassSort) { mJJHMassSort_ = mJJHMassSort; }
  void setFullPt(double fullPt) { fullPt_ = fullPt; }
  void setFullEta(double fullEta) { fullEta_ = fullEta; }
  void setFullPhi(double fullPhi) { fullPhi_ = fullPhi; }
  void setFullEnergy(double fullEnergy) { fullEnergy_ = fullEnergy; }

  /// allow only CompositePtrCandidateT1T2MEtAlgorithm to change values of data-members
  template<typename T1_type, typename T2_type> friend class CompositePtrCandidateT1T2MEtAlgorithm;
  template<typename T1_type, typename T2_type> friend class CompositePtrCandidateT1T2MEtVertexAlgorithm;

  ///btag SF's
  void setSFCSVL1(double SFCSVL1) { SFCSVL1_ = SFCSVL1; 
    //std::cout << SFCSVL1_ << "SFCSVL1" << std::endl;
  }
  void setSFCSVL2(double SFCSVL2) { SFCSVL2_ = SFCSVL2; }
  void setSFCSVM1(double SFCSVM1) { SFCSVM1_ = SFCSVM1; }
  void setSFCSVM2(double SFCSVM2) { SFCSVM2_ = SFCSVM2; }
  void setSFCSVT1(double SFCSVT1) { SFCSVT1_ = SFCSVT1; }
  void setSFCSVT2(double SFCSVT2) { SFCSVT2_ = SFCSVT2; }

  void setSFCSVL1err(double SFCSVL1err) { SFCSVL1err_ = SFCSVL1err; }
  void setSFCSVL2err(double SFCSVL2err) { SFCSVL2err_ = SFCSVL2err; }
  void setSFCSVM1err(double SFCSVM1err) { SFCSVM1err_ = SFCSVM1err; }
  void setSFCSVM2err(double SFCSVM2err) { SFCSVM2err_ = SFCSVM2err; }
  void setSFCSVT1err(double SFCSVT1err) { SFCSVT1err_ = SFCSVT1err; }
  void setSFCSVT2err(double SFCSVT2err) { SFCSVT2err_ = SFCSVT2err; }

  void setIsData(bool data){data_ = data;}
  ///set top pt
  void setIsTop(bool top){top_ = top;}
  void setTopGenPt(float topGenPt){topGenPt_ = topGenPt;}
  void setAntiTopGenPt(float antiTopGenPt){antiTopGenPt_ = antiTopGenPt;}

  /// set gen. four-momenta
  void setP4Leg1gen(const reco::Candidate::LorentzVector& p4) { p4Leg1gen_ = p4; }
  void setP4Leg2gen(const reco::Candidate::LorentzVector& p4) { p4Leg2gen_ = p4; }
  void setP4VisLeg1gen(const reco::Candidate::LorentzVector& p4) { p4VisLeg1gen_ = p4; }
  void setP4VisLeg2gen(const reco::Candidate::LorentzVector& p4) { p4VisLeg2gen_ = p4; }

  void setPdg1(int pdg) {pdg1_ = pdg;}
  void setPdg2(int pdg) {pdg2_ = pdg;}
  void setGenBosonMass(float genBosonMass) { genBosonMass_ = genBosonMass; }
  void setGenBosonP4(const reco::Candidate::LorentzVector& p4) { p4Boson_ = p4; }
  void setGenBosonP4Vis(const reco::Candidate::LorentzVector& p4) { p4BosonVis_ = p4; }

  /// set decay statusFlag
  void setIsPrompt1(int isPrompt1) { isPrompt1_=isPrompt1; } //genLeg1->statusFlags().isPrompt());
  void setIsPromptFS1(int isPromptFS1) { isPromptFS1_=isPromptFS1; } //genLeg1->isPromptFinalState());
  void setIsDirectPromptTauDecayProduct1(int isTauDecayFlag1) { isTauDecayFlag1_=isTauDecayFlag1; }  //genLeg1->statusFlags().isDirectPromptTauDecayProduct());
  void setIsDirectPromptTauDecayProductFS1(int isTauDecayFlagFS1) { isTauDecayFlagFS1_=isTauDecayFlagFS1; } //genLeg1->isDirectPromptTauDecayProductFinalState());

  /// set decay statusFlag
  void setIsPrompt2(int isPrompt2) { isPrompt2_=isPrompt2; } //genLeg1->statusFlags().isPrompt());
  void setIsPromptFS2(int isPromptFS2) { isPromptFS2_=isPromptFS2; } //genLeg1->isPromptFinalState());
  void setIsDirectPromptTauDecayProduct2(int isTauDecayFlag2) { isTauDecayFlag2_=isTauDecayFlag2; }  //genLeg1->statusFlags().isDirectPromptTauDecayProduct());
  void setIsDirectPromptTauDecayProductFS2(int isTauDecayFlagFS2) { isTauDecayFlagFS2_=isTauDecayFlagFS2; } //genLeg1->isDirectPromptTauDecayProductFinalState());




  /// set four-momentum of visible decay products
  void setP4Vis(const reco::Candidate::LorentzVector& p4) { p4Vis_ = p4; }
  /// set four-momentum and scaling factors for momenta of visible decay products
  /// computed by collinear approximation
  void setCollinearApproxQuantities(const reco::Candidate::LorentzVector& p4, double x1, double x2, bool isValid)
  {
    p4CollinearApprox_ = p4;
    x1CollinearApprox_ = x1;
    x2CollinearApprox_ = x2;
    collinearApproxIsValid_ = isValid;
  }
  /// set "pseudo" four-momentum computed by CDF method
  /// (for a description of the method, see e.g. CDF note 8972)
  void setP4CDFmethod(const reco::Candidate::LorentzVector& p4) { p4CDFmethod_ = p4; }
  /// set transverse mass of visible decay products + missing transverse momentum
  void setMt12MET(double mt) { mt12MET_ = mt; }
  /// set transverse mass of first/second
  /// visible decay product + missing transverse momentum
  void setMt1MET(double mt) { mt1MET_ = mt; }
  void setMt2MET(double mt) { mt2MET_ = mt; }
  /// set acoplanarity angle (angle in transverse plane) between visible decay products
  void setDPhi12(double dPhi) { dPhi12_ = dPhi; }
  /// set separation in eta-phi between visible decay products
  void setDR12(double dR) { dR12_ = dR; }
  /// set minimal/maximal pseudo-rapidity of visible decay products
  void setVisEtaMin(double eta) { visEtaMin_ = eta; }
  void setVisEtaMax(double eta) { visEtaMax_ = eta; }
  /// set acoplanarity angle (angle in transverse plane) between first/second
  /// visible decay product and missing transverse momentum
  void setDPhi1MET(double dPhi) { dPhi1MET_ = dPhi; }
  void setDPhi2MET(double dPhi) { dPhi2MET_ = dPhi; }
  /// set values of CDF-"zeta" variables
  void setPzeta(double pZeta) { pZeta_ = pZeta; }
  void setPzetaVis(double pZetaVis) { pZetaVis_ = pZetaVis; }
  /// set value of Projected MET
  void setProjMET(double projMET) { projMET_ = projMET; }
  void setCalibratedMET(const reco::Candidate::LorentzVector& met) { calibratedMET_ = met; }
  void setMETold(const reco::Candidate::LorentzVector& metOld) { metOld_ = metOld; }
  void setCovMatrix(TMatrixD covMatrix) { covMatrix_ = covMatrix; }
  void setMetPhi(double metPhi) { metPhi_ = metPhi; }
  void setCovMat00(TMatrixD covMatrix) { covMatrix00_ = covMatrix[0][0]; }
  void setCovMat01(TMatrixD covMatrix) { covMatrix01_ = covMatrix[0][1]; }
  void setCovMat10(TMatrixD covMatrix) { covMatrix10_ = covMatrix[1][0]; }    
  void setCovMat11(TMatrixD covMatrix) { covMatrix11_ = covMatrix[1][1]; }
  //void setCovMatSig00(double covMatrix) { covMatrixSig00_ = covMatrix; }
  //void setCovMatSig01(double covMatrix) { covMatrixSig01_ = covMatrix; }
  //void setCovMatSig10(double covMatrix) { covMatrixSig10_ = covMatrix; }    
  //void setCovMatSig11(double covMatrix) { covMatrixSig11_ = covMatrix; }



  /// set vertex variables
  void setVertexVariables(double dca,double crossingPointDistance, double dZ12, double Z1, double Z2) {
    dca_ = dca;
    crossingPointDistance_ = crossingPointDistance;
    dZ12_ = dZ12;
    z1_ = Z1;
    z2_ = Z2;
  }


  //set VBF Variables
  void setVBFVariables(float mass, float deta, float dphi, int jets20,int jets30,float pt1, float pt2, float dijetpt, float ditaupt, float eta1, float eta2, float dphihj, float c1, float c2) {
    vbfMass_ = mass;
    vbfDEta_ = deta;
    vbfDPhi_ = dphi;
    if(jets20<0)
      jets20 = 0;
    vbfNJetsGap20_ = jets20;
    if(jets30<0)
      jets30 = 0;
    vbfNJetsGap30_ = jets30;
    vbfPt1_=pt1;
    vbfPt2_=pt2;
    vbfDiJetPt_ = dijetpt;
    vbfDiTauPt_ = ditaupt;
    vbfEta1_=eta1;
    vbfEta2_=eta2;
    vbfDPhiHJ_ = dphihj;
    vbfC1_ = c1;
    vbfC2_ = c2;
    
  }



  /// set values of recoil
  void setRecoil(reco::Candidate::LorentzVector recoil) { recoil_ = recoil; }
  void setRecoilDPhi(double recoilDPhi) { recoilDPhi_ = recoilDPhi; }
  void setEventBTag(bool EventBTag) { EventBTag_ = EventBTag; }
  void setNBTags(int NBTags) { NBTags_ = NBTags; }
  void setNBTagsUp(int NBTagsUp) { NBTagsUp_ = NBTagsUp; }
  void setNBTagsDown(int NBTagsDown) { NBTagsDown_ = NBTagsDown; }


  //jet variables
  void setJetVariables(std::vector<JetPtr> jets,double ht) {
    jets_ = jets;
    ht_ = ht;
  }
  /// references/pointers to decay products
  T1Ptr leg1_;
  T2Ptr leg2_;
  METPtr met_;

  pat::Jet J1MatchedB_;
  pat::Jet J2MatchedB_;
  float CSVSize;
  JetPtr J1CSVSort_; JetPtr J2CSVSort_;

  reco::Candidate::LorentzVector metOld_;
  reco::Candidate::LorentzVector calibratedMET_;

  bool data_;

  bool top_;
  float topGenPt_;
  float antiTopGenPt_;

  /// gen. four-momenta
  reco::Candidate::LorentzVector p4Leg1gen_;
  reco::Candidate::LorentzVector p4Leg2gen_;
  reco::Candidate::LorentzVector p4VisLeg1gen_;
  reco::Candidate::LorentzVector p4VisLeg2gen_;
  reco::Candidate::LorentzVector p4Boson_;
  reco::Candidate::LorentzVector p4BosonVis_;


  //gen Pdg Id
  int pdg1_;
  int pdg2_;
  float genBosonMass_;

  //genStatus Flag
  int isPrompt1_;
  int isPromptFS1_;
  int isTauDecayFlag1_;
  int isTauDecayFlagFS1_;

  //genStatus Flag
  int isPrompt2_;
  int isPromptFS2_;
  int isTauDecayFlag2_;
  int isTauDecayFlagFS2_;



  //CSV SF variables
  double SFCSVL1_;
  double SFCSVL2_;
  double SFCSVM1_;
  double SFCSVM2_;
  double SFCSVT1_;
  double SFCSVT2_;

  double SFCSVL1err_;
  double SFCSVL2err_;
  double SFCSVM1err_;
  double SFCSVM2err_;
  double SFCSVT1err_;
  double SFCSVT2err_;



  /// four-momentum of visible decay products
  reco::Candidate::LorentzVector p4Vis_;
  /// four-momentum and scaling factors for momenta of visible decay products computed by collinear approximation
  reco::Candidate::LorentzVector p4CollinearApprox_;
  bool collinearApproxIsValid_;
  double x1CollinearApprox_;
  double x2CollinearApprox_;
  /// "pseudo" four-momentum computed by CDF method
  reco::Candidate::LorentzVector p4CDFmethod_;
  /// transverse mass of visible decay products + missing transverse momentum
  double mt12MET_;
  /// transverse mass of first/second visible decay product + missing transverse momentum
  double mt1MET_;
  double mt2MET_;
  /// acoplanarity angle (angle in transverse plane) between visible decay products
  double dPhi12_;
  /// separation in eta-phi between visible decay products
  double dR12_;
  /// minimal/maximal pseudo-rapidity of visible decay products
  double visEtaMin_;
  double visEtaMax_;
  /// acoplanarity angle (angle in transverse plane) between first/second
  /// visible decay product and missing transverse momentum
  double dPhi1MET_;
  double dPhi2MET_;
  /// CDF-"zeta" variables
  double pZeta_;
  double pZetaVis_;
  /// Projected MET Variable
  double projMET_;
  /// More MET Variables
  double metPhi_;
  double covMatrix00_;
  double covMatrix01_;
  double covMatrix10_;
  double covMatrix11_;
  //double covMatrixSig00_;
  //double covMatrixSig01_;
  //double covMatrixSig10_;
  //double covMatrixSig11_;




  /// Vertex variables
  double dca_;
  double crossingPointDistance_;
  double dZ12_;
  double z1_;
  double z2_;
  
  TMatrixD covMatrix_;

  //reco::Candidate::PolarLorentzVector SVFourVector;
  reco::Candidate::LorentzVector JJ_;
  math::PtEtaPhiELorentzVector JJReg_;

  //JJ variables
  double mJJ_,ptJJ_,etaJJ_,phiJJ_,EJJ_;

  //recoil
  reco::Candidate::LorentzVector recoil_;
  double recoilDPhi_;
  bool EventBTag_;
  int NBTags_;
  int NBTagsUp_;
  int NBTagsDown_;

  //jets
  std::vector<JetPtr> jets_;
  double ht_;
    
  //VBF
  double vbfMass_;
  double vbfDEta_;
  double vbfDPhi_;
  double vbfPt1_;
  double vbfPt2_;
  double vbfEta1_;
  double vbfEta2_;
  double vbfDiJetPt_;
  double vbfDiTauPt_;
  double vbfDPhiHJ_;
  double vbfC1_;
  double vbfC2_;
  int vbfNJetsGap20_;
  int vbfNJetsGap30_;

  double lVeto_;

  double svMass_;
  double svPt_;

  double mJJCSVSort_;
  double mJJReg_;
  double mJJHMassSort_;
  double fullPt_;
  double fullEta_;
  double fullPhi_;
  double fullEnergy_;

};

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

typedef CompositePtrCandidateT1T2MEt<reco::Candidate, reco::Candidate> DiCandidatePair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Tau> PATElecTauPair;
//typedef CompositePtrCandidateT1T2MEt<pat::Electron, reco::RecoEcalCandidate> PATElecSCPair;
typedef CompositePtrCandidateT1T2MEt<pat::Muon, pat::Tau> PATMuTauPair;
//typedef CompositePtrCandidateT1T2MEt<pat::Muon, pat::Jet> PATMuJetPair;
//typedef CompositePtrCandidateT1T2MEt<pat::Muon, reco::RecoChargedCandidate> PATMuTrackPair;
typedef CompositePtrCandidateT1T2MEt<pat::Tau, pat::Tau> PATDiTauPair;
//typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Muon> PATElecMuPair;
typedef CompositePtrCandidateT1T2MEt<pat::Electron, pat::Electron> PATElecPair;
//typedef CompositePtrCandidateT1T2MEt<pat::Electron, reco::RecoChargedCandidate> PATEleTrackPair;
typedef CompositePtrCandidateT1T2MEt<pat::Muon, pat::Muon> PATMuPair;
//typedef CompositePtrCandidateT1T2MEt<pat::Jet, pat::Jet> PATJetPair;

//typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATJetPair> PATMuMuJJQuad;
//typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATMuTauPair> PATMuMuMuTauQuad;
typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATDiTauPair> PATMuMuTauTauQuad;
//typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATElecTauPair> PATMuMuEleTauQuad;
//typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATElecMuPair> PATMuMuEleMuQuad;
//typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATMuPair> PATMuMuMuMuQuad;
//typedef CompositePtrCandidateT1T2MEt<PATMuPair,PATElecPair> PATMuMuEleEleQuad;
//typedef CompositePtrCandidateT1T2MEt<PATElecPair,PATElecTauPair> PATEleEleEleTauQuad;
//typedef CompositePtrCandidateT1T2MEt<PATElecPair,PATDiTauPair> PATEleEleTauTauQuad;
//typedef CompositePtrCandidateT1T2MEt<PATElecPair,PATElecPair> PATEleEleEleEleQuad;
//typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATMuTauPair> PATEleEleMuTauQuad;
//typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATElecMuPair> PATEleEleEleMuQuad;
//typedef CompositePtrCandidateT1T2MEt<PATElecPair, PATMuPair> PATEleEleMuMuQuad;

#endif
