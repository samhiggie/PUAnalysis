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
            src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src")))
    {
        uncertNames={"AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "AbsoluteSample", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeSample","RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "SubTotalAbsolute", "SubTotalMC", "SubTotalPileUp", "SubTotalPt", "SubTotalRelative", "SubTotalScale", "TimePtEta", "TotalNoFlavorNoTime","TotalNoFlavor","TotalNoTime","Total", "Closure"};
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
            "jesClosure+",
            "jesClosure-",
        };

        //new vector of TBranches for all the uncertainty shapes 
        std::cout<<"initializing branches"<<std::endl;
        std::vector<TBranch *> njet_uncertBranches_Up;
        std::vector<TBranch *> njet_uncertBranches_Down;
        std::vector<TBranch *> vbfmass_uncertBranches_Up;
        std::vector<TBranch *> vbfmass_uncertBranches_Down;
        std::vector<TBranch *> jeta_uncertBranches_Up;
        std::vector<TBranch *> jeta_uncertBranches_Down;

        for(unsigned int i=0; i<uncertNames.size(); i++){
            njetVecUp.push_back(-999);
            njetVecDown.push_back(-999);
            vbfVecUp.push_back(-999.);
            vbfVecDown.push_back(-999.);
            jetaVecUp.push_back(-999.);
            jetaVecDown.push_back(-999.);
        }
        for(unsigned int i=0; i<uncertNames.size(); i++){
            t->Branch(("njet_"+uncertNames[i]+"Up").c_str(),&njetVecUp[i],("njet_"+uncertNames[i]+"Up/I").c_str());
            t->Branch(("njet_"+uncertNames[i]+"Down").c_str(),&njetVecDown[i],("njet_"+uncertNames[i]+"Down/I").c_str());
            t->Branch(("vbfMass_"+uncertNames[i]+"Up").c_str(),&vbfVecUp[i],("vbfMass_"+uncertNames[i]+"Up/F").c_str());
            t->Branch(("vbfMass_"+uncertNames[i]+"Down").c_str(),&vbfVecDown[i],("vbfMass_"+uncertNames[i]+"Down/F").c_str());
            t->Branch(("jeta_"+uncertNames[i]+"Up").c_str(),&jetaVecUp[i],("jeta_"+uncertNames[i]+"Up/F").c_str());
            t->Branch(("jeta_"+uncertNames[i]+"Down").c_str(),&jetaVecDown[i],("jeta_"+uncertNames[i]+"Down/F").c_str());
        }
       
    }


        ~VBFVariableFiller()
        { 
            //if(function!=0) delete function;
            //if(cut!=0) delete cut;
        }


        void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
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
                                firstJet= (*(handle->at(0).jets().at(0)));
                                secondJet= (*(handle->at(0).jets().at(1)));   
                                vbfmass = (firstJet.userCand(shiftedPt[c])->p4()+secondJet.userCand(shiftedPt[c])->p4()).M();
                                //std::cout<<"VBF mass "<<vbfmass<<std::endl;
                            }
                        }

                        int type = c % 2; // 0 is njet(vbf)Up, 1 is njet(vbf)Down
                        int fill = c/2; // 0 is njet(vbf)Up, 1 is njet(vbf)Down
                        //std::cout<<"njets: "<<njets<<std::endl;
                        //std::cout<<"vbfmass: "<<vbfmass<<std::endl;
                        if (type==0){
                            njetVecUp[fill]=njets;
                            vbfVecUp[fill]=vbfmass;
                            jetaVecUp[fill]=jeta;
                        }
                        else {
                            njetVecDown[fill]=njets;
                            vbfVecDown[fill]=vbfmass;
                            jetaVecDown[fill]=jeta;
                        }

                    }//end cut [i]
                }//handle exists

            }//events exist and is MC 

        }

    protected:
        edm::EDGetTokenT<std::vector<T>> src_;
        int njets;
        float vbfmass;
        float jeta;
        StringCutObjectSelector<pat::Jet>*cut;
        StringObjectFunction<pat::Jet>*function;

        //std::vector<StringCutObjectSelector<pat::Jet>*> cutnew;
        //std::vector<TBranch*> myBranches;

        std::vector<int> njetVecUp;
        std::vector<int> njetVecDown;
        std::vector<float> vbfVecUp;
        std::vector<float> vbfVecDown;
        std::vector<float> jetaVecUp;
        std::vector<float> jetaVecDown;

        std::vector< std::string > uncertNames;
        std::vector< std::string > cuts;
        std::vector< std::string > shiftedPt;
};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef VBFVariableFiller<PATMuTauPair> PATMuTauPairVBFVariableFiller;
typedef VBFVariableFiller<PATElecTauPair> PATEleTauPairVBFVariableFiller;
typedef VBFVariableFiller<PATDiTauPair> PATDiTauPairVBFVariableFiller;

