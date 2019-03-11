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
class VBFVariableFiller_FSA : public NtupleFillerBase {
    public:
        VBFVariableFiller_FSA(){
        }


        VBFVariableFiller_FSA(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
            NtupleFillerBase(iConfig,t,iC),
            src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src")))
    {
        uncertNames={"Closure","Eta0to3","Eta0to5","Eta3to5","ClosureNew"};
        shiftedPt= { 
            "jesClosure+",
            "jesClosure-",
            "jesEta0to3+",
            "jesEta0to3-",
            "jesEta0to5+",
            "jesEta0to5-",
            "jesEta3to5+",
            "jesEta3to5-",
            "jesClosureNew+",
            "jesClosureNew-",
        };

        for(unsigned int i=0; i<uncertNames.size(); i++){
            njetVecUp.push_back(-999);
            njetVecDown.push_back(-999);
            vbfVecUp.push_back(-999);
            vbfVecDown.push_back(-999);
        }

        TBranch *nBranchNjetUp0 =  t->Branch(("njet_merge_"+uncertNames[0]+"Up").c_str(),&njetVecUp[0],("njet_merge_"+uncertNames[0]+"Up/I").c_str());
        TBranch *nBranchNjetDown0 =  t->Branch(("njet_merge_"+uncertNames[0]+"Down").c_str(),&njetVecDown[0],("njet_merge_"+uncertNames[0]+"Down/I").c_str());
        TBranch *nBranchVBFUp0 =  t->Branch(("vbfMass_merge_"+uncertNames[0]+"Up").c_str(),&vbfVecUp[0],("vbfMass_merge_"+uncertNames[0]+"Up/F").c_str());
        TBranch *nBranchVBFDown0 =  t->Branch(("vbfMass_merge_"+uncertNames[0]+"Down").c_str(),&vbfVecDown[0],("vbfMass_merge_"+uncertNames[0]+"Down/F").c_str());
        TBranch *nBranchNjetUp1 =  t->Branch(("njet_merge_"+uncertNames[1]+"Up").c_str(),&njetVecUp[1],("njet_merge_"+uncertNames[1]+"Up/I").c_str());
        TBranch *nBranchNjetDown1 =  t->Branch(("njet_merge_"+uncertNames[1]+"Down").c_str(),&njetVecDown[1],("njet_merge_"+uncertNames[1]+"Down/I").c_str());
        TBranch *nBranchVBFUp1 =  t->Branch(("vbfMass_merge_"+uncertNames[1]+"Up").c_str(),&vbfVecUp[1],("vbfMass_merge_"+uncertNames[1]+"Up/F").c_str());
        TBranch *nBranchVBFDown1 =  t->Branch(("vbfMass_merge_"+uncertNames[1]+"Down").c_str(),&vbfVecDown[1],("vbfMass_merge_"+uncertNames[1]+"Down/F").c_str());
        TBranch *nBranchNjetUp2 =  t->Branch(("njet_merge_"+uncertNames[2]+"Up").c_str(),&njetVecUp[2],("njet_merge_"+uncertNames[2]+"Up/I").c_str());
        TBranch *nBranchNjetDown2 =  t->Branch(("njet_merge_"+uncertNames[2]+"Down").c_str(),&njetVecDown[2],("njet_merge_"+uncertNames[2]+"Down/I").c_str());
        TBranch *nBranchVBFUp2 =  t->Branch(("vbfMass_merge_"+uncertNames[2]+"Up").c_str(),&vbfVecUp[2],("vbfMass_merge_"+uncertNames[2]+"Up/F").c_str());
        TBranch *nBranchVBFDown2 =  t->Branch(("vbfMass_merge_"+uncertNames[2]+"Down").c_str(),&vbfVecDown[2],("vbfMass_merge_"+uncertNames[2]+"Down/F").c_str());
        TBranch *nBranchNjetUp3 =  t->Branch(("njet_merge_"+uncertNames[3]+"Up").c_str(),&njetVecUp[3],("njet_merge_"+uncertNames[3]+"Up/I").c_str());
        TBranch *nBranchNjetDown3 =  t->Branch(("njet_merge_"+uncertNames[3]+"Down").c_str(),&njetVecDown[3],("njet_merge_"+uncertNames[3]+"Down/I").c_str());
        TBranch *nBranchVBFUp3 =  t->Branch(("vbfMass_merge_"+uncertNames[3]+"Up").c_str(),&vbfVecUp[3],("vbfMass_merge_"+uncertNames[3]+"Up/F").c_str());
        TBranch *nBranchVBFDown3 =  t->Branch(("vbfMass_merge_"+uncertNames[3]+"Down").c_str(),&vbfVecDown[3],("vbfMass_merge_"+uncertNames[3]+"Down/F").c_str());
        TBranch *nBranchNjetUp4 =  t->Branch(("njet_merge_"+uncertNames[4]+"Up").c_str(),&njetVecUp[4],("njet_merge_"+uncertNames[4]+"Up/I").c_str());
        TBranch *nBranchNjetDown4 =  t->Branch(("njet_merge_"+uncertNames[4]+"Down").c_str(),&njetVecDown[4],("njet_merge_"+uncertNames[4]+"Down/I").c_str());
        TBranch *nBranchVBFUp4 =  t->Branch(("vbfMass_merge_"+uncertNames[4]+"Up").c_str(),&vbfVecUp[4],("vbfMass_merge_"+uncertNames[4]+"Up/F").c_str());
        TBranch *nBranchVBFDown4 =  t->Branch(("vbfMass_merge_"+uncertNames[4]+"Down").c_str(),&vbfVecDown[4],("vbfMass_merge_"+uncertNames[4]+"Down/F").c_str());
    }


        ~VBFVariableFiller_FSA()
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
                        vbfmass=-999;
                        njets=0;

                        for(unsigned int i=0;i<handle->at(0).jets().size();++i){
                            //id Loose and eta jets already cleaned
                            if( handle->at(0).jets().at(i)->userCand(shiftedPt[c])->pt()>30 )  {
                                njets++;
                            }
                        }//end njet loop


                        if (njets>1){
                            if(  handle->at(0).jets().at(0)->userCand(shiftedPt[c])->pt()>20  &&  handle->at(0).jets().at(1)->userCand(shiftedPt[c])->pt()>20) {
                                firstJet= (*(handle->at(0).jets().at(0)));
                                secondJet= (*(handle->at(0).jets().at(1)));   
                                vbfmass = (firstJet.userCand(shiftedPt[c])->p4()+secondJet.userCand(shiftedPt[c])->p4()).M();
                            }
                        }

                        int type = c % 2; // 0 is njet(vbf)Up, 1 is njet(vbf)Down
                        int fill = c/2; // 0 is njet(vbf)Up, 1 is njet(vbf)Down
                        //std::cout<<"njets: "<<njets<<std::endl;
                        //std::cout<<"vbfmass: "<<vbfmass<<std::endl;
                        if (type==0){
                            njetVecUp[fill]=njets;
                            vbfVecUp[fill]=vbfmass;
                        }
                        else {
                            njetVecDown[fill]=njets;
                            vbfVecDown[fill]=vbfmass;
                        }

                    }//end cut [i]
                }//handle exists

            }//events exist and is MC 

        }

    protected:
        edm::EDGetTokenT<std::vector<T>> src_;
        int njets;
        float vbfmass;
        StringCutObjectSelector<pat::Jet>*cut;
        StringObjectFunction<pat::Jet>*function;

        //std::vector<StringCutObjectSelector<pat::Jet>*> cutnew;
        //std::vector<TBranch*> myBranches;

        std::vector<int> njetVecUp;
        std::vector<int> njetVecDown;
        std::vector<float> vbfVecUp;
        std::vector<float> vbfVecDown;

        std::vector< std::string > uncertNames;
        std::vector< std::string > cuts;
        std::vector< std::string > shiftedPt;
};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef VBFVariableFiller_FSA<PATMuTauPair> PATMuTauPairVBFVariableFiller_FSA;
typedef VBFVariableFiller_FSA<PATElecTauPair> PATEleTauPairVBFVariableFiller_FSA;
typedef VBFVariableFiller_FSA<PATDiTauPair> PATDiTauPairVBFVariableFiller_FSA;

