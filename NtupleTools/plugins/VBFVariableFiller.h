// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "Math/GenVector/VectorUtil.h" 
#include "TMath.h"

#include <TTree.h>

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

#include "DataFormats/PatCandidates/interface/MET.h"
#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"
#include "TauAnalysis/ClassicSVfit/interface/FastMTT.h"
#include "HTT-utilities/RecoilCorrections/interface/RecoilCorrector.h"

//
// class decleration
//
template<typename T>
class VBFVariableFiller : public NtupleFillerBase {
    public:
        VBFVariableFiller(){
        }


        VBFVariableFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
            NtupleFillerBase(iConfig,t,iC),
	      src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))),
	      cov_(iC.consumes<math::Error<2>::type>(edm::InputTag("METSignificance:METCovariance")))
    {
      uncertNames = {
	"AbsoluteFlavMap",
	"AbsoluteMPFBias",
	"AbsoluteScale",
	"AbsoluteStat",
	"AbsoluteSample",
	"FlavorQCD",
	"Fragmentation",
	"PileUpDataMC",
	"PileUpPtBB",
	"PileUpPtEC1",
	"PileUpPtEC2",
	"PileUpPtHF",
	"PileUpPtRef",
	"RelativeBal",
	"RelativeSample",
	"RelativeFSR",
	"RelativeJEREC1",
	"RelativeJEREC2",
	"RelativeJERHF",
	"RelativePtBB",
	"RelativePtEC1",
	"RelativePtEC2",
	"RelativePtHF",
	"RelativeStatEC",
	"RelativeStatFSR",
	"RelativeStatHF",
	"SinglePionECAL",
	"SinglePionHCAL",
	"SubTotalAbsolute",
	"SubTotalMC",
	"SubTotalPileUp",
	"SubTotalPt",
	"SubTotalRelative",
	"SubTotalScale",
	"TimePtEta",
	"TotalNoFlavorNoTime",
	"TotalNoFlavor",
	"TotalNoTime",
	"Total",
	"Eta3to5",
	"Eta0to5",
	"Eta0to3",
	"EC2",
	"Closure",
      }; // end uncertNames
      // uncertNames={"AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "AbsoluteSample", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeSample","RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "SubTotalAbsolute", "SubTotalMC", "SubTotalPileUp", "SubTotalPt", "SubTotalRelative", "SubTotalScale", "TimePtEta", "TotalNoFlavorNoTime","TotalNoFlavor","TotalNoTime","Total", "Closure"};
      shiftedPt= { 
            "jesAbsoluteFlavMap+",
            "jesAbsoluteFlavMap-",
            "jesAbsoluteMPFBias+",
            "jesAbsoluteMPFBias-",
            "jesAbsoluteScale+",
            "jesAbsoluteScale-",
            "jesAbsoluteStat+",
            "jesAbsoluteStat-",
            "jesAbsoluteSample+",
            "jesAbsoluteSample-",
            "jesFlavorQCD+",
            "jesFlavorQCD-",
            "jesFragmentation+",
            "jesFragmentation-",
            "jesPileUpDataMC+",
            "jesPileUpDataMC-",
            "jesPileUpPtBB+",
            "jesPileUpPtBB-",
            "jesPileUpPtEC1+",
            "jesPileUpPtEC1-",
            "jesPileUpPtEC2+",
            "jesPileUpPtEC2-",
            "jesPileUpPtHF+",
            "jesPileUpPtHF-",
            "jesPileUpPtRef+",
            "jesPileUpPtRef-",
            "jesRelativeBal+",
            "jesRelativeBal-",
            "jesRelativeSample+",
            "jesRelativeSample-",
            "jesRelativeFSR+",
            "jesRelativeFSR-",
            "jesRelativeJEREC1+",
            "jesRelativeJEREC1-",
            "jesRelativeJEREC2+",
            "jesRelativeJEREC2-",
            "jesRelativeJERHF+",
            "jesRelativeJERHF-",
            "jesRelativePtBB+",
            "jesRelativePtBB-",
            "jesRelativePtEC1+",
            "jesRelativePtEC1-",
            "jesRelativePtEC2+",
            "jesRelativePtEC2-",
            "jesRelativePtHF+",
            "jesRelativePtHF-",
            "jesRelativeStatEC+",
            "jesRelativeStatEC-",
            "jesRelativeStatFSR+",
            "jesRelativeStatFSR-",
            "jesRelativeStatHF+",
            "jesRelativeStatHF-",
            "jesSinglePionECAL+",
            "jesSinglePionECAL-",
            "jesSinglePionHCAL+",
            "jesSinglePionHCAL-",
            "jesSubTotalAbsolute+",
            "jesSubTotalAbsolute-",
            "jesSubTotalMC+",
            "jesSubTotalMC-",
            "jesSubTotalPileUp+",
            "jesSubTotalPileUp-",
            "jesSubTotalPt+",
            "jesSubTotalPt-",
            "jesSubTotalRelative+",
            "jesSubTotalRelative-",
            "jesSubTotalScale+",
            "jesSubTotalScale-",
            "jesTimePtEta+",
            "jesTimePtEta-",
            "jesTotalNoFlavorNoTime+",
            "jesTotalNoFlavorNoTime-",
            "jesTotalNoFlavor+",
            "jesTotalNoFlavor-",
            "jesTotalNoTime+",
            "jesTotalNoTime-",
            "jesTotal+",
            "jesTotal-",
	    "jesEta3to5+",
	    "jesEta3to5-",
	    "jesEta0to5+",
	    "jesEta0to5-",
	    "jesEta0to3+",
	    "jesEta0to3-",
	    "jesEC2+",
	    "jesEC2-",
            "jesClosure+",
            "jesClosure-",
        };

        //new vector of TBranches for all the uncertainty shapes 
        //std::cout<<"initializing branches"<<std::endl;
        std::vector<TBranch *> njet_uncertBranches_Up;
        std::vector<TBranch *> njet_uncertBranches_Down;
        std::vector<TBranch *> vbfmass_uncertBranches_Up;
        std::vector<TBranch *> vbfmass_uncertBranches_Down;
        std::vector<TBranch *> met_uncertBranches_Up;
        std::vector<TBranch *> met_uncertBranches_Down;
        std::vector<TBranch *> metphi_uncertBranches_Up;
        std::vector<TBranch *> metphi_uncertBranches_Down;
        std::vector<TBranch *> jeta_uncertBranches_Up;
        std::vector<TBranch *> jeta_uncertBranches_Down;

        for(unsigned int i=0; i<uncertNames.size(); i++){
            njetVecUp.push_back(-999);
            njetVecDown.push_back(-999);
            vbfVecUp.push_back(-999.);
            vbfVecDown.push_back(-999.);
            metVecUp.push_back(-999.);
            metVecDown.push_back(-999.);
	    metphiVecUp.push_back(-999.);
            metphiVecDown.push_back(-999.);
	    msvVecUp.push_back(-999.);
	    msvVecDown.push_back(-999.);
	    ptsvVecUp.push_back(-999.);
	    ptsvVecDown.push_back(-999.);
            jetaVecUp.push_back(-999.);
            jetaVecDown.push_back(-999.);
	    
        }
        for(unsigned int i=0; i<uncertNames.size(); i++){
            t->Branch(("njet_"   +uncertNames[i]+"Up").c_str(),  &njetVecUp[i],    ("njet_"+    uncertNames[i]+"Up/I"  ).c_str());
            t->Branch(("njet_"   +uncertNames[i]+"Down").c_str(),&njetVecDown[i],  ("njet_"+    uncertNames[i]+"Down/I").c_str());
            t->Branch(("vbfMass_"+uncertNames[i]+"Up").c_str(),  &vbfVecUp[i],     ("vbfMass_"+ uncertNames[i]+"Up/F"  ).c_str());
            t->Branch(("vbfMass_"+uncertNames[i]+"Down").c_str(),&vbfVecDown[i],   ("vbfMass_"+ uncertNames[i]+"Down/F").c_str());
            t->Branch(("met_"    +uncertNames[i]+"Up").c_str(),  &metVecUp[i],     ("met_"+     uncertNames[i]+"Up/F"  ).c_str());
            t->Branch(("met_"    +uncertNames[i]+"Down").c_str(),&metVecDown[i],   ("met_"+     uncertNames[i]+"Down/F").c_str());    
            t->Branch(("metphi_" +uncertNames[i]+"Up").c_str(),  &metphiVecUp[i],  ("metphi_"+  uncertNames[i]+"Up/F"  ).c_str());
            t->Branch(("metphi_" +uncertNames[i]+"Down").c_str(),&metphiVecDown[i],("metphi_"+  uncertNames[i]+"Down/F").c_str());
	    t->Branch(("jeta_"   +uncertNames[i]+"Up").c_str(),  &jetaVecUp[i],    ("jeta_"+    uncertNames[i]+"Up/F"  ).c_str());
            t->Branch(("jeta_"   +uncertNames[i]+"Down").c_str(),&jetaVecDown[i],  ("jeta_"+    uncertNames[i]+"Down/F").c_str());

	    t->Branch(("m_sv_"   +uncertNames[i]+"Up").c_str(),   &msvVecUp[i],    ("m_sv_"+    uncertNames[i]+"Up/F"  ).c_str());
	    t->Branch(("m_sv_"   +uncertNames[i]+"Down").c_str(), &msvVecDown[i],  ("m_sv_"+    uncertNames[i]+"Down/F").c_str());
            t->Branch(("pt_sv_"  +uncertNames[i]+"Up").c_str(),   &ptsvVecUp[i],   ("pt_sv_"+   uncertNames[i]+"Up/F"  ).c_str());
            t->Branch(("pt_sv_"   +uncertNames[i]+"Down").c_str(),&ptsvVecDown[i], ("pt_sv_"+   uncertNames[i]+"Down/F").c_str());

	    //t->Branch(("m_sv_"   +uncertNames[i]+"Up").c_str(),  &jetaVecUp[i],    ("m_sv_"+    uncertNames[i]+"Up/F"  ).c_str());
            //t->Branch(("pt_sv_"   +uncertNames[i]+"Down").c_str(),&jetaVecDown[i],  ("pt_sv_"+    uncertNames[i]+"Down/F").c_str());
        }

	t->Branch("m_sv",            &svFitMass,        "m_sv/F");
	t->Branch("pt_sv",           &svFitPt,          "pt_sv/F");
	t->Branch("phi_sv",          &svFitPhi,         "phi_sv/F");
	t->Branch("eta_sv",          &svFitEta,         "eta_sv/F");
	t->Branch("m_sv_muonESUp",   &svFitMass_MESUp,  "m_sv_muonESUp/F");
	t->Branch("m_sv_muonESDown", &svFitMass_MESDown,"m_sv_muonESDown/F");
	t->Branch("m_sv_DOWN",         &svFitMass_DOWN,     "m_sv_DOWN/F");
	t->Branch("pt_sv_DOWN",        &svFitPt_DOWN,       "pt_sv_DOWN/F");
	t->Branch("phi_sv_DOWN",     &svFitPhi_DOWN,    "phi_sv_DOWN/F");
	t->Branch("eta_sv_DOWN",     &svFitEta_DOWN,    "eta_sv_DOWN/F");

	t->Branch("m_sv_UP",         &svFitMass_UP,     "m_sv_UP/F");
	t->Branch("pt_sv_UP",        &svFitPt_UP,       "pt_sv_UP/F");
	t->Branch("phi_sv_UP",       &svFitPhi_UP,      "phi_sv_UP/F");
	t->Branch("eta_sv_UP",       &svFitEta_UP,      "eta_sv_UP/F");
    }


        ~VBFVariableFiller()
        { 
            //if(function!=0) delete function;
            //if(cut!=0) delete cut;
        }


        void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
	  edm::Handle<math::Error<2>::type> covHandle;
	  TMatrixD covMET(2, 2);

	  if (iEvent.getByToken(cov_,covHandle)) {
	    covMET[0][0] = (*covHandle)(0,0);
	    covMET[1][0] = (*covHandle)(1,0);
	    covMET[0][1] = (*covHandle)(1,0); // (1,0) is the only one saved
	    covMET[1][1] = (*covHandle)(1,1);
	  }
	  else
	    std::cout<<"ERROR GETTING THE COVARIANCE MATRIX THIS IS REALLY BAD!!!!!"<<std::endl;

	  edm::Handle<std::vector<T> > handle;
	  //printf("Get Jets\n");
	  //njets=0
	  if(iEvent.getByToken(src_,handle) && !iEvent.isRealData()) { //event exists
	    if(handle->size()>0){//JEts exits 
	      
	      for ( unsigned int c=0;c<shiftedPt.size();c++){
		pat::Jet firstJet;
		pat::Jet secondJet;
		vbfmass=-999.;
		njets=0;
		jeta=-999.;
		
		
		for(unsigned int i=0;i<handle->at(0).jets().size();++i){
		  //id Loose and eta jets already cleaned
		  firstJet= (*(handle->at(0).jets().at(0)));
		  //jeta = (firstJet.userCand(shiftedPt[c])->p4()).Eta();
		  //jeta = firstJet.userCand(shiftedPt[c])->p4().eta();
		  //jeta = (firstJet.userCand(shiftedPt[c])->p4()).M();
		  //std::cout<<"Shifted leading jeta ... "<<jeta<<std::endl;
		  if( handle->at(0).jets().at(i)->userCand(shiftedPt[c])->pt()>30 )  {
		    njets++;
		    jeta = firstJet.userCand(shiftedPt[c])->p4().eta();
		  }
		}//end njet loop
		
		
		if (njets>1){
		  if(  handle->at(0).jets().at(0)->userCand(shiftedPt[c])->pt()>20  &&  handle->at(0).jets().at(1)->userCand(shiftedPt[c])->pt()>20) {
		    firstJet  = (*(handle->at(0).jets().at(0)));
		    secondJet = (*(handle->at(0).jets().at(1)));   
		    vbfmass   = (firstJet.userCand(shiftedPt[c])->p4()+secondJet.userCand(shiftedPt[c])->p4()).M();
		    //std::cout<<"VBF mass "<<vbfmass<<std::endl;
		  }
		}
		
		int type = c % 2; // 0 is njet(vbf)Up, 1 is njet(vbf)Down
		int fill = c/2; // 0 is njet(vbf)Up, 1 is njet(vbf)Down
		//std::cout<<"njets: "<<njets<<std::endl;
		//std::cout<<"shift applied: "<< uncertNames[c/2]<<std::endl;
		//std::cout<<"vbfmass: "<<vbfmass<<std::endl;
		//std::cout<<"met pt : "<<handle->at(0).met()->p4().pt()<<std::endl;
		//std::cout<<"met pt shifted: "<<handle->at(0).met()->userCand(shiftedPt[c])->pt()<<std::endl;
		//std::cout<<"met phi shifted: "<<handle->at(0).met()->userCand(shiftedPt[c])->phi()<<std::endl;

		met    = handle->at(0).met()->userCand(shiftedPt[c])->p4().pt();
		metphi = handle->at(0).met()->userCand(shiftedPt[c])->p4().phi();
		
		//now for SVFit!
		std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
		measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToMuDecay,   handle->at(0).leg1()->pt(),  handle->at(0).leg1()->eta(),  handle->at(0).leg1()->phi(),  0.10566)); 
		measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToHadDecay,  handle->at(0).leg2()->pt(),  handle->at(0).leg2()->eta(),  handle->at(0).leg2()->phi(),  handle->at(0).leg2()->mass(),  handle->at(0).leg2()->decayMode()));
		//measured leptons, measured met x, measured met y, covmet, 0, return values

		float t_svFitMass, t_svFitPt, t_svFitEta, t_svFitPhi;
		runSVFitAndRecoil(measuredTauLeptons, met*TMath::Cos(metphi), met*TMath::Sin(metphi), covMET, handle, 0, t_svFitMass, t_svFitPt, t_svFitEta, t_svFitPhi);
		
		if (type==0){

		  njetVecUp[fill]=njets;

		  vbfVecUp[fill]=vbfmass;

		  jetaVecUp[fill]=jeta;

		  metVecUp[fill]=met;

		  metphiVecUp[fill]=metphi;

		  msvVecUp[fill]=t_svFitMass;

		  ptsvVecUp[fill]=t_svFitPt;

		}
		else {
		  //std::cout<<"Starting type 1"<<std::endl;
		  njetVecDown[fill]=njets;
		  vbfVecDown[fill]=vbfmass;
		  jetaVecDown[fill]=jeta;
		  metVecDown[fill]=met;
		  metphiVecDown[fill]=metphi;
		  msvVecDown[fill]=t_svFitMass;
		  ptsvVecDown[fill]=t_svFitPt;
		  //std::cout<<"Ending type 1"<<std::endl;
		}
	       
		//std::cout<<"finished"<<std::endl;
	      }//end cut [i]
	      
	      //////////////now for the ES shifts
	      
	      met = handle->at(0).met()->pt();
	      metphi = handle->at(0).met()->phi();
	      
	      float phi1 = handle->at(0).leg1()->phi();
	      float eta1 = handle->at(0).leg1()->eta();
	      float pt1 = handle->at(0).leg1()->pt();

	      float phi2 = handle->at(0).leg2()->phi();
	      float eta2 = handle->at(0).leg2()->eta();
	      float pt2 = handle->at(0).leg2()->pt();
	      float m2 = handle->at(0).leg2()->mass();
	      float decayMode2 = handle->at(0).leg2()->decayMode();
	      float ES_UP_scale=1.0; // this value is for jet -> tau fakes
	      if (eta1<-2.1) ES_UP_scale=1.027;
	      else if (eta1>-2.1 && eta1<-1.2) ES_UP_scale=1.009;
	      else if (eta1>-1.2 && eta1<1.2) ES_UP_scale=1.004;
	      else if (eta1>1.2  && eta1<2.1) ES_UP_scale=1.009;
	      else ES_UP_scale=1.017;

	      double pt1_UP;
	      pt1_UP = pt1 * ES_UP_scale;
	      double metcorr_ex_UP, metcorr_ey_UP;
	      double dx1_UP, dy1_UP;
	      dx1_UP = pt1_UP * TMath::Cos( phi1 ) * (( 1. / ES_UP_scale ) - 1.);
	      dy1_UP = pt1_UP * TMath::Sin( phi1 ) * (( 1. / ES_UP_scale ) - 1.);
	      metcorr_ex_UP = met*TMath::Cos(metphi) + dx1_UP;
	      metcorr_ey_UP = met*TMath::Sin(metphi) + dy1_UP;
	      std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
	      measuredTauLeptonsUP.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToMuDecay, pt1_UP, eta1,  phi1, 0.10566));
	      measuredTauLeptonsUP.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToHadDecay,  pt2, eta2, phi2,  m2, decayMode2));

	      runSVFitAndRecoil(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, handle, 0, svFitMass_MESUp, svFitPt_MESUp, svFitEta_MESUp, svFitPhi_MESUp);

	      //met*TMath::Cos(metphi), met*TMath::Sin(metphi)
	      float ES_DOWN_scale=1.0; // jet
	      if (eta1<-2.1) ES_DOWN_scale=1 - 0.027;
	      else if (eta1<-1.2) ES_DOWN_scale=1-0.009;
	      else if (eta1<1.2) ES_DOWN_scale=1-0.004;
	      else if (eta1<2.1) ES_DOWN_scale=1-0.009;
	      else ES_DOWN_scale=1-0.017;
	      double pt1_DOWN;
	      pt1_DOWN = pt1 * ES_DOWN_scale;
	      double metcorr_ex_DOWN, metcorr_ey_DOWN;
	      double dx1_DOWN, dy1_DOWN;
	      dx1_DOWN = pt1_DOWN * TMath::Cos( phi1 ) * (( 1. / ES_DOWN_scale ) - 1.);
	      dy1_DOWN = pt1_DOWN * TMath::Sin( phi1 ) * (( 1. / ES_DOWN_scale ) - 1.);
	      metcorr_ex_DOWN = met*TMath::Cos(metphi) + dx1_DOWN;
	      metcorr_ey_DOWN =  met*TMath::Sin(metphi) + dy1_DOWN;

	      std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;
	      measuredTauLeptonsDOWN.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToMuDecay, pt1_DOWN, eta1,  phi1, 0.10566));
	      measuredTauLeptonsDOWN.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToHadDecay,  pt2, eta2, phi2,  m2, decayMode2));
	      runSVFitAndRecoil(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, handle, 0, svFitMass_MESDown, svFitPt_MESDown, svFitEta_MESDown, svFitPhi_MESDown);

	      float gen_match_2 = handle->at(0).leg2()->userInt("gen_match");
	      if (gen_match_2<=5){
                float ES_UP_scale=1.0; // this value is for jet -> tau fakes
                if (gen_match_2<5) ES_UP_scale=1.03; // for gen matched ele/muon
		/*
                if (year==2016){
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.010; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.009; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.011; // for real taus
                }
                else if (year==2017){
		
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.008; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.008; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.009; // for real taus
                }
                else if (year==2018){
		*/
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.011; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.008; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_UP_scale=1.009; // for real taus
		  //}

                double pt2_UP;
                double mass2_UP=m2;
                if (decayMode2!=0) mass2_UP = m2 * ES_UP_scale;
                pt2_UP = pt2 * ES_UP_scale;
                double metcorr_ex_UP, metcorr_ey_UP;
                double dx2_UP, dy2_UP;
                dx2_UP = pt2_UP * TMath::Cos( phi2 ) * (( 1. / ES_UP_scale ) - 1.);
                dy2_UP = pt2_UP * TMath::Sin( phi2 ) * (( 1. / ES_UP_scale ) - 1.);
                metcorr_ex_UP = met*TMath::Cos(metphi) + dx2_UP;
                metcorr_ey_UP =  met*TMath::Sin(metphi) + dy2_UP;

		std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsUP;
                measuredTauLeptonsUP.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToMuDecay, pt1, eta1,  phi1, 0.10566));
                measuredTauLeptonsUP.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToHadDecay,  pt2_UP, eta2, phi2,  mass2_UP, decayMode2));
		runSVFitAndRecoil(measuredTauLeptonsUP, metcorr_ex_UP, metcorr_ey_UP, covMET, handle, 0, svFitMass_UP, svFitPt_UP, svFitEta_UP, svFitPhi_UP);

                float ES_DOWN_scale=1.0; // jet
                if (gen_match_2<5) ES_DOWN_scale=0.97;  // elec/mu
		/*
                if (year==2016){
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.990; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.991; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.989; // for real taus
                }
                else if (year==2017){
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.992; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.992; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.991; // for real taus
                }
                else if (year==2018){
		*/
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.989; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.992; // for real taus
		  if (gen_match_2==5 && decayMode2==0) ES_DOWN_scale=0.991; // for real taus
		  //}
                double pt2_DOWN;
                double mass2_DOWN = m2;
                pt2_DOWN = pt2 * ES_DOWN_scale;
                if (decayMode2!=0) mass2_DOWN = m2 * ES_DOWN_scale;
                double metcorr_ex_DOWN, metcorr_ey_DOWN;
                double dx2_DOWN, dy2_DOWN;
                dx2_DOWN = pt2_DOWN * TMath::Cos( phi2 ) * (( 1. / ES_DOWN_scale ) - 1.);
                dy2_DOWN = pt2_DOWN * TMath::Sin( phi2 ) * (( 1. / ES_DOWN_scale ) - 1.);
                metcorr_ex_DOWN = met*TMath::Cos(metphi) + dx2_DOWN;
                metcorr_ey_DOWN =  met*TMath::Sin(metphi) + dy2_DOWN;

		std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptonsDOWN;
                measuredTauLeptonsDOWN.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToMuDecay, pt1, eta1,  phi1, 0.10566));
                measuredTauLeptonsDOWN.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToHadDecay,  pt2_DOWN, eta2, phi2,  mass2_DOWN, decayMode2));
		runSVFitAndRecoil(measuredTauLeptonsDOWN, metcorr_ex_DOWN, metcorr_ey_DOWN, covMET, handle, 0, svFitMass_DOWN, svFitPt_DOWN, svFitEta_DOWN, svFitPhi_DOWN);

	      }
	    }//handle exists
	    
	  }//events exist and is MC 

	  if(iEvent.getByToken(src_,handle)) { //event exists fill the nominal values
	    met = handle->at(0).met()->pt();
	    metphi = handle->at(0).met()->phi();
	    
	    //now for SVFit!
	    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
	    //measuredTauLeptons.clear();
	    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToMuDecay,   handle->at(0).leg1()->pt(),  handle->at(0).leg1()->eta(),  handle->at(0).leg1()->phi(), 0.10566)); 
	    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(classic_svFit::MeasuredTauLepton::kTauToHadDecay,  handle->at(0).leg2()->pt(),  handle->at(0).leg2()->eta(),  handle->at(0).leg2()->phi(),  handle->at(0).leg2()->mass(),  handle->at(0).leg2()->decayMode()));
	    //measured leptons, measured met x, measured met y, covmet, 0, return values
	    float t_svFitMass, t_svFitPt, t_svFitEta, t_svFitPhi;
	    runSVFit(measuredTauLeptons, met*TMath::Cos(metphi), met*TMath::Sin(metphi), covMET, 0, t_svFitMass, t_svFitPt, t_svFitEta, t_svFitPhi);
	    svFitMass = t_svFitMass; 
	    svFitPt = t_svFitPt; 
	    svFitPhi = t_svFitPhi; 
	    svFitEta = t_svFitEta;
	    //std::cout <<"nominal svFit Mass: "<<svFitMass<< " Pt: "<<svFitPt<< " Phi: "<<svFitPhi<< " Eta: "<<svFitEta<< " MET: "<<met<< " metphi: "<< metphi<<" NLeptons: "<< measuredTauLeptons.size()<<std::endl;
	  }
	}

	void runSVFit(std::vector<classic_svFit::MeasuredTauLepton> & measuredTauLeptons, double measuredMETx, double measuredMETy, TMatrixD &covMET, float num, float &svFitMass, float& svFitPt, float &svFitEta, float &svFitPhi){
	  FastMTT aFastMTTAlgo;
	  aFastMTTAlgo.run(measuredTauLeptons,measuredMETx,measuredMETy,covMET);
	  LorentzVector ttP4 = aFastMTTAlgo.getBestP4();
	  svFitMass = ttP4.M(); // return value is in units of GeV
	  svFitPt = ttP4.Pt();
	  svFitEta = ttP4.Eta();
	  svFitPhi = ttP4.Phi();
	  //std::cout << "found mass = " << svFitMass << std::endl;

	}

	void runSVFitAndRecoil(std::vector<classic_svFit::MeasuredTauLepton> & measuredTauLeptons, double measuredMETx, double measuredMETy, TMatrixD &covMET, edm::Handle<std::vector<T> > handle, float num, float &svFitMass, float& svFitPt, float &svFitEta, float &svFitPhi){

	  RecoilCorrector recoilPFMetCorrector("HTT-utilities/RecoilCorrections/data/TypeI-PFMet_Run2018.root"); // Type I PF MET 2018
	  //recoil correction
	  float pfmetcorr_ex;
	  float pfmetcorr_ey;
	  recoilPFMetCorrector.CorrectByMeanResolution(
						       measuredMETx, // uncorrected type I pf met px (float)
						       measuredMETy, // uncorrected type I pf met py (float)
						       handle->at(0).p4GenBoson().px(), // generator Z/W/Higgs px (float)
						       handle->at(0).p4GenBoson().px(), // generator Z/W/Higgs py (float)
						       handle->at(0).p4GenBosonVis().px(), // generator visible Z/W/Higgs px (float)
						       handle->at(0).p4GenBosonVis().py(), // generator visible Z/W/Higgs py (float)
						       njets,  // number of jets (hadronic jet multiplicity) (int)
						       pfmetcorr_ex, // corrected type I pf met px (float)
						       pfmetcorr_ey  // corrected type I pf met py (float)
						       );	

	  //std::cout<<"input met "<< sqrt(measuredMETx*measuredMETx+measuredMETy*measuredMETy) <<" recoil corrected met: "<< sqrt(pfmetcorr_ex*pfmetcorr_ex+pfmetcorr_ey*pfmetcorr_ey) <<std::endl;
	  
	  FastMTT aFastMTTAlgo;
	  aFastMTTAlgo.run(measuredTauLeptons,pfmetcorr_ex,pfmetcorr_ey,covMET);
	  LorentzVector ttP4 = aFastMTTAlgo.getBestP4();
	  svFitMass = ttP4.M(); // return value is in units of GeV
	  svFitPt = ttP4.Pt();
	  svFitEta = ttP4.Eta();
	  svFitPhi = ttP4.Phi();
	  //std::cout << "found mass = " << svFitMass << std::endl;

	}

    protected:
        edm::EDGetTokenT<std::vector<T>> src_;
	edm::EDGetTokenT<math::Error<2>::type> cov_;
        int njets;
        float vbfmass;
	float met;
	float metphi;
        float jeta;
        StringCutObjectSelector<pat::Jet>*cut;
        StringObjectFunction<pat::Jet>*function;

        //std::vector<StringCutObjectSelector<pat::Jet>*> cutnew;
        //std::vector<TBranch*> myBranches;

        std::vector<int> njetVecUp;
        std::vector<int> njetVecDown;
        std::vector<float> vbfVecUp;
        std::vector<float> vbfVecDown;
        std::vector<float> metVecUp;
        std::vector<float> metVecDown;
        std::vector<float> metphiVecUp;
        std::vector<float> metphiVecDown;
        std::vector<float> jetaVecUp;
        std::vector<float> jetaVecDown;
        std::vector<float> msvVecUp;
        std::vector<float> msvVecDown;
        std::vector<float> ptsvVecUp;
        std::vector<float> ptsvVecDown;
	float svFitMass;       
	float svFitPt;         
	float svFitPhi;        
	float svFitEta;        
	float svFitMass_MESUp; 
	float svFitMass_MESDown;
	float svFitPt_MESUp;
	float svFitPt_MESDown;
	float svFitEta_MESUp;
	float svFitEta_MESDown;
	float svFitPhi_MESUp;
	float svFitPhi_MESDown;
	float svFitMass_DOWN;  
	float svFitPt_DOWN;    
	float svFitPhi_DOWN;   
	float svFitEta_DOWN;   
	float svFitMass_UP;    
	float svFitPt_UP;      
	float svFitPhi_UP;     
	float svFitEta_UP;     
        std::vector< std::string > uncertNames;
        std::vector< std::string > cuts;
        std::vector< std::string > shiftedPt;
};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef VBFVariableFiller<PATMuTauPair> PATMuTauPairVBFVariableFiller;
typedef VBFVariableFiller<PATElecTauPair> PATEleTauPairVBFVariableFiller;
typedef VBFVariableFiller<PATDiTauPair> PATDiTauPairVBFVariableFiller;

