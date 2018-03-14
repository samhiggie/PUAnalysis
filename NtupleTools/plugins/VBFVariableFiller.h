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
        uncertNames={"AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "SubTotalAbsolute", "SubTotalMC", "SubTotalPileUp", "SubTotalPt", "SubTotalRelative", "SubTotalScale", "TimePtEta", "Total", "Closure"};
        shiftedPt= { 
            "jesAbsoluteFlavMap+",
            "jesAbsoluteFlavMap-",
            "jesAbsoluteMPFBias+",
            "jesAbsoluteMPFBias-",
            "jesAbsoluteScale+",
            "jesAbsoluteScale-",
            "jesAbsoluteStat+",
            "jesAbsoluteStat-",
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
            "jesTotal+",
            "jesTotal-",
            "jesClosure+",
            "jesClosure-",
        };

        for(unsigned int i=0; i<uncertNames.size(); i++){
            njetVecUp.push_back(-999);
            njetVecDown.push_back(-999);
            vbfVecUp.push_back(-999);
            vbfVecDown.push_back(-999);
        }

        TBranch *nBranchNjetUp0 =  t->Branch(("njet_"+uncertNames[0]+"Up").c_str(),&njetVecUp[0],("njet_"+uncertNames[0]+"Up/I").c_str());
        TBranch *nBranchNjetDown0 =  t->Branch(("njet_"+uncertNames[0]+"Down").c_str(),&njetVecDown[0],("njet_"+uncertNames[0]+"Down/I").c_str());
        TBranch *nBranchVBFUp0 =  t->Branch(("vbfMass_"+uncertNames[0]+"Up").c_str(),&vbfVecUp[0],("vbfMass_"+uncertNames[0]+"Up/F").c_str());
        TBranch *nBranchVBFDown0 =  t->Branch(("vbfMass_"+uncertNames[0]+"Down").c_str(),&vbfVecDown[0],("vbfMass_"+uncertNames[0]+"Down/F").c_str());
        TBranch *nBranchNjetUp1 =  t->Branch(("njet_"+uncertNames[1]+"Up").c_str(),&njetVecUp[1],("njet_"+uncertNames[1]+"Up/I").c_str());
        TBranch *nBranchNjetDown1 =  t->Branch(("njet_"+uncertNames[1]+"Down").c_str(),&njetVecDown[1],("njet_"+uncertNames[1]+"Down/I").c_str());
        TBranch *nBranchVBFUp1 =  t->Branch(("vbfMass_"+uncertNames[1]+"Up").c_str(),&vbfVecUp[1],("vbfMass_"+uncertNames[1]+"Up/F").c_str());
        TBranch *nBranchVBFDown1 =  t->Branch(("vbfMass_"+uncertNames[1]+"Down").c_str(),&vbfVecDown[1],("vbfMass_"+uncertNames[1]+"Down/F").c_str());
        TBranch *nBranchNjetUp2 =  t->Branch(("njet_"+uncertNames[2]+"Up").c_str(),&njetVecUp[2],("njet_"+uncertNames[2]+"Up/I").c_str());
        TBranch *nBranchNjetDown2 =  t->Branch(("njet_"+uncertNames[2]+"Down").c_str(),&njetVecDown[2],("njet_"+uncertNames[2]+"Down/I").c_str());
        TBranch *nBranchVBFUp2 =  t->Branch(("vbfMass_"+uncertNames[2]+"Up").c_str(),&vbfVecUp[2],("vbfMass_"+uncertNames[2]+"Up/F").c_str());
        TBranch *nBranchVBFDown2 =  t->Branch(("vbfMass_"+uncertNames[2]+"Down").c_str(),&vbfVecDown[2],("vbfMass_"+uncertNames[2]+"Down/F").c_str());
        TBranch *nBranchNjetUp3 =  t->Branch(("njet_"+uncertNames[3]+"Up").c_str(),&njetVecUp[3],("njet_"+uncertNames[3]+"Up/I").c_str());
        TBranch *nBranchNjetDown3 =  t->Branch(("njet_"+uncertNames[3]+"Down").c_str(),&njetVecDown[3],("njet_"+uncertNames[3]+"Down/I").c_str());
        TBranch *nBranchVBFUp3 =  t->Branch(("vbfMass_"+uncertNames[3]+"Up").c_str(),&vbfVecUp[3],("vbfMass_"+uncertNames[3]+"Up/F").c_str());
        TBranch *nBranchVBFDown3 =  t->Branch(("vbfMass_"+uncertNames[3]+"Down").c_str(),&vbfVecDown[3],("vbfMass_"+uncertNames[3]+"Down/F").c_str());
        TBranch *nBranchNjetUp4 =  t->Branch(("njet_"+uncertNames[4]+"Up").c_str(),&njetVecUp[4],("njet_"+uncertNames[4]+"Up/I").c_str());
        TBranch *nBranchNjetDown4 =  t->Branch(("njet_"+uncertNames[4]+"Down").c_str(),&njetVecDown[4],("njet_"+uncertNames[4]+"Down/I").c_str());
        TBranch *nBranchVBFUp4 =  t->Branch(("vbfMass_"+uncertNames[4]+"Up").c_str(),&vbfVecUp[4],("vbfMass_"+uncertNames[4]+"Up/F").c_str());
        TBranch *nBranchVBFDown4 =  t->Branch(("vbfMass_"+uncertNames[4]+"Down").c_str(),&vbfVecDown[4],("vbfMass_"+uncertNames[4]+"Down/F").c_str());
        TBranch *nBranchNjetUp5 =  t->Branch(("njet_"+uncertNames[5]+"Up").c_str(),&njetVecUp[5],("njet_"+uncertNames[5]+"Up/I").c_str());
        TBranch *nBranchNjetDown5 =  t->Branch(("njet_"+uncertNames[5]+"Down").c_str(),&njetVecDown[5],("njet_"+uncertNames[5]+"Down/I").c_str());
        TBranch *nBranchVBFUp5 =  t->Branch(("vbfMass_"+uncertNames[5]+"Up").c_str(),&vbfVecUp[5],("vbfMass_"+uncertNames[5]+"Up/F").c_str());
        TBranch *nBranchVBFDown5 =  t->Branch(("vbfMass_"+uncertNames[5]+"Down").c_str(),&vbfVecDown[5],("vbfMass_"+uncertNames[5]+"Down/F").c_str());
        TBranch *nBranchNjetUp6 =  t->Branch(("njet_"+uncertNames[6]+"Up").c_str(),&njetVecUp[6],("njet_"+uncertNames[6]+"Up/I").c_str());
        TBranch *nBranchNjetDown6 =  t->Branch(("njet_"+uncertNames[6]+"Down").c_str(),&njetVecDown[6],("njet_"+uncertNames[6]+"Down/I").c_str());
        TBranch *nBranchVBFUp6 =  t->Branch(("vbfMass_"+uncertNames[6]+"Up").c_str(),&vbfVecUp[6],("vbfMass_"+uncertNames[6]+"Up/F").c_str());
        TBranch *nBranchVBFDown6 =  t->Branch(("vbfMass_"+uncertNames[6]+"Down").c_str(),&vbfVecDown[6],("vbfMass_"+uncertNames[6]+"Down/F").c_str());
        TBranch *nBranchNjetUp7 =  t->Branch(("njet_"+uncertNames[7]+"Up").c_str(),&njetVecUp[7],("njet_"+uncertNames[7]+"Up/I").c_str());
        TBranch *nBranchNjetDown7 =  t->Branch(("njet_"+uncertNames[7]+"Down").c_str(),&njetVecDown[7],("njet_"+uncertNames[7]+"Down/I").c_str());
        TBranch *nBranchVBFUp7 =  t->Branch(("vbfMass_"+uncertNames[7]+"Up").c_str(),&vbfVecUp[7],("vbfMass_"+uncertNames[7]+"Up/F").c_str());
        TBranch *nBranchVBFDown7 =  t->Branch(("vbfMass_"+uncertNames[7]+"Down").c_str(),&vbfVecDown[7],("vbfMass_"+uncertNames[7]+"Down/F").c_str());
        TBranch *nBranchNjetUp8 =  t->Branch(("njet_"+uncertNames[8]+"Up").c_str(),&njetVecUp[8],("njet_"+uncertNames[8]+"Up/I").c_str());
        TBranch *nBranchNjetDown8 =  t->Branch(("njet_"+uncertNames[8]+"Down").c_str(),&njetVecDown[8],("njet_"+uncertNames[8]+"Down/I").c_str());
        TBranch *nBranchVBFUp8 =  t->Branch(("vbfMass_"+uncertNames[8]+"Up").c_str(),&vbfVecUp[8],("vbfMass_"+uncertNames[8]+"Up/F").c_str());
        TBranch *nBranchVBFDown8 =  t->Branch(("vbfMass_"+uncertNames[8]+"Down").c_str(),&vbfVecDown[8],("vbfMass_"+uncertNames[8]+"Down/F").c_str());
        TBranch *nBranchNjetUp9 =  t->Branch(("njet_"+uncertNames[9]+"Up").c_str(),&njetVecUp[9],("njet_"+uncertNames[9]+"Up/I").c_str());
        TBranch *nBranchNjetDown9 =  t->Branch(("njet_"+uncertNames[9]+"Down").c_str(),&njetVecDown[9],("njet_"+uncertNames[9]+"Down/I").c_str());
        TBranch *nBranchVBFUp9 =  t->Branch(("vbfMass_"+uncertNames[9]+"Up").c_str(),&vbfVecUp[9],("vbfMass_"+uncertNames[9]+"Up/F").c_str());
        TBranch *nBranchVBFDown9 =  t->Branch(("vbfMass_"+uncertNames[9]+"Down").c_str(),&vbfVecDown[9],("vbfMass_"+uncertNames[9]+"Down/F").c_str());
        TBranch *nBranchNjetUp10 =  t->Branch(("njet_"+uncertNames[10]+"Up").c_str(),&njetVecUp[10],("njet_"+uncertNames[10]+"Up/I").c_str());
        TBranch *nBranchNjetDown10 =  t->Branch(("njet_"+uncertNames[10]+"Down").c_str(),&njetVecDown[10],("njet_"+uncertNames[10]+"Down/I").c_str());
        TBranch *nBranchVBFUp10 =  t->Branch(("vbfMass_"+uncertNames[10]+"Up").c_str(),&vbfVecUp[10],("vbfMass_"+uncertNames[10]+"Up/F").c_str());
        TBranch *nBranchVBFDown10 =  t->Branch(("vbfMass_"+uncertNames[10]+"Down").c_str(),&vbfVecDown[10],("vbfMass_"+uncertNames[10]+"Down/F").c_str());
        TBranch *nBranchNjetUp11 =  t->Branch(("njet_"+uncertNames[11]+"Up").c_str(),&njetVecUp[11],("njet_"+uncertNames[11]+"Up/I").c_str());
        TBranch *nBranchNjetDown11 =  t->Branch(("njet_"+uncertNames[11]+"Down").c_str(),&njetVecDown[11],("njet_"+uncertNames[11]+"Down/I").c_str());
        TBranch *nBranchVBFUp11 =  t->Branch(("vbfMass_"+uncertNames[11]+"Up").c_str(),&vbfVecUp[11],("vbfMass_"+uncertNames[11]+"Up/F").c_str());
        TBranch *nBranchVBFDown11 =  t->Branch(("vbfMass_"+uncertNames[11]+"Down").c_str(),&vbfVecDown[11],("vbfMass_"+uncertNames[11]+"Down/F").c_str());
        TBranch *nBranchNjetUp12 =  t->Branch(("njet_"+uncertNames[12]+"Up").c_str(),&njetVecUp[12],("njet_"+uncertNames[12]+"Up/I").c_str());
        TBranch *nBranchNjetDown12 =  t->Branch(("njet_"+uncertNames[12]+"Down").c_str(),&njetVecDown[12],("njet_"+uncertNames[12]+"Down/I").c_str());
        TBranch *nBranchVBFUp12 =  t->Branch(("vbfMass_"+uncertNames[12]+"Up").c_str(),&vbfVecUp[12],("vbfMass_"+uncertNames[12]+"Up/F").c_str());
        TBranch *nBranchVBFDown12 =  t->Branch(("vbfMass_"+uncertNames[12]+"Down").c_str(),&vbfVecDown[12],("vbfMass_"+uncertNames[12]+"Down/F").c_str());
        TBranch *nBranchNjetUp13 =  t->Branch(("njet_"+uncertNames[13]+"Up").c_str(),&njetVecUp[13],("njet_"+uncertNames[13]+"Up/I").c_str());
        TBranch *nBranchNjetDown13 =  t->Branch(("njet_"+uncertNames[13]+"Down").c_str(),&njetVecDown[13],("njet_"+uncertNames[13]+"Down/I").c_str());
        TBranch *nBranchVBFUp13 =  t->Branch(("vbfMass_"+uncertNames[13]+"Up").c_str(),&vbfVecUp[13],("vbfMass_"+uncertNames[13]+"Up/F").c_str());
        TBranch *nBranchVBFDown13 =  t->Branch(("vbfMass_"+uncertNames[13]+"Down").c_str(),&vbfVecDown[13],("vbfMass_"+uncertNames[13]+"Down/F").c_str());
        TBranch *nBranchNjetUp14 =  t->Branch(("njet_"+uncertNames[14]+"Up").c_str(),&njetVecUp[14],("njet_"+uncertNames[14]+"Up/I").c_str());
        TBranch *nBranchNjetDown14 =  t->Branch(("njet_"+uncertNames[14]+"Down").c_str(),&njetVecDown[14],("njet_"+uncertNames[14]+"Down/I").c_str());
        TBranch *nBranchVBFUp14 =  t->Branch(("vbfMass_"+uncertNames[14]+"Up").c_str(),&vbfVecUp[14],("vbfMass_"+uncertNames[14]+"Up/F").c_str());
        TBranch *nBranchVBFDown14 =  t->Branch(("vbfMass_"+uncertNames[14]+"Down").c_str(),&vbfVecDown[14],("vbfMass_"+uncertNames[14]+"Down/F").c_str());
        TBranch *nBranchNjetUp15 =  t->Branch(("njet_"+uncertNames[15]+"Up").c_str(),&njetVecUp[15],("njet_"+uncertNames[15]+"Up/I").c_str());
        TBranch *nBranchNjetDown15 =  t->Branch(("njet_"+uncertNames[15]+"Down").c_str(),&njetVecDown[15],("njet_"+uncertNames[15]+"Down/I").c_str());
        TBranch *nBranchVBFUp15 =  t->Branch(("vbfMass_"+uncertNames[15]+"Up").c_str(),&vbfVecUp[15],("vbfMass_"+uncertNames[15]+"Up/F").c_str());
        TBranch *nBranchVBFDown15 =  t->Branch(("vbfMass_"+uncertNames[15]+"Down").c_str(),&vbfVecDown[15],("vbfMass_"+uncertNames[15]+"Down/F").c_str());
        TBranch *nBranchNjetUp16 =  t->Branch(("njet_"+uncertNames[16]+"Up").c_str(),&njetVecUp[16],("njet_"+uncertNames[16]+"Up/I").c_str());
        TBranch *nBranchNjetDown16 =  t->Branch(("njet_"+uncertNames[16]+"Down").c_str(),&njetVecDown[16],("njet_"+uncertNames[16]+"Down/I").c_str());
        TBranch *nBranchVBFUp16 =  t->Branch(("vbfMass_"+uncertNames[16]+"Up").c_str(),&vbfVecUp[16],("vbfMass_"+uncertNames[16]+"Up/F").c_str());
        TBranch *nBranchVBFDown16 =  t->Branch(("vbfMass_"+uncertNames[16]+"Down").c_str(),&vbfVecDown[16],("vbfMass_"+uncertNames[16]+"Down/F").c_str());
        TBranch *nBranchNjetUp17 =  t->Branch(("njet_"+uncertNames[17]+"Up").c_str(),&njetVecUp[17],("njet_"+uncertNames[17]+"Up/I").c_str());
        TBranch *nBranchNjetDown17 =  t->Branch(("njet_"+uncertNames[17]+"Down").c_str(),&njetVecDown[17],("njet_"+uncertNames[17]+"Down/I").c_str());
        TBranch *nBranchVBFUp17 =  t->Branch(("vbfMass_"+uncertNames[17]+"Up").c_str(),&vbfVecUp[17],("vbfMass_"+uncertNames[17]+"Up/F").c_str());
        TBranch *nBranchVBFDown17 =  t->Branch(("vbfMass_"+uncertNames[17]+"Down").c_str(),&vbfVecDown[17],("vbfMass_"+uncertNames[17]+"Down/F").c_str());
        TBranch *nBranchNjetUp18 =  t->Branch(("njet_"+uncertNames[18]+"Up").c_str(),&njetVecUp[18],("njet_"+uncertNames[18]+"Up/I").c_str());
        TBranch *nBranchNjetDown18 =  t->Branch(("njet_"+uncertNames[18]+"Down").c_str(),&njetVecDown[18],("njet_"+uncertNames[18]+"Down/I").c_str());
        TBranch *nBranchVBFUp18 =  t->Branch(("vbfMass_"+uncertNames[18]+"Up").c_str(),&vbfVecUp[18],("vbfMass_"+uncertNames[18]+"Up/F").c_str());
        TBranch *nBranchVBFDown18 =  t->Branch(("vbfMass_"+uncertNames[18]+"Down").c_str(),&vbfVecDown[18],("vbfMass_"+uncertNames[18]+"Down/F").c_str());
        TBranch *nBranchNjetUp19 =  t->Branch(("njet_"+uncertNames[19]+"Up").c_str(),&njetVecUp[19],("njet_"+uncertNames[19]+"Up/I").c_str());
        TBranch *nBranchNjetDown19 =  t->Branch(("njet_"+uncertNames[19]+"Down").c_str(),&njetVecDown[19],("njet_"+uncertNames[19]+"Down/I").c_str());
        TBranch *nBranchVBFUp19 =  t->Branch(("vbfMass_"+uncertNames[19]+"Up").c_str(),&vbfVecUp[19],("vbfMass_"+uncertNames[19]+"Up/F").c_str());
        TBranch *nBranchVBFDown19 =  t->Branch(("vbfMass_"+uncertNames[19]+"Down").c_str(),&vbfVecDown[19],("vbfMass_"+uncertNames[19]+"Down/F").c_str());
        TBranch *nBranchNjetUp20 =  t->Branch(("njet_"+uncertNames[20]+"Up").c_str(),&njetVecUp[20],("njet_"+uncertNames[20]+"Up/I").c_str());
        TBranch *nBranchNjetDown20 =  t->Branch(("njet_"+uncertNames[20]+"Down").c_str(),&njetVecDown[20],("njet_"+uncertNames[20]+"Down/I").c_str());
        TBranch *nBranchVBFUp20 =  t->Branch(("vbfMass_"+uncertNames[20]+"Up").c_str(),&vbfVecUp[20],("vbfMass_"+uncertNames[20]+"Up/F").c_str());
        TBranch *nBranchVBFDown20 =  t->Branch(("vbfMass_"+uncertNames[20]+"Down").c_str(),&vbfVecDown[20],("vbfMass_"+uncertNames[20]+"Down/F").c_str());
        TBranch *nBranchNjetUp21 =  t->Branch(("njet_"+uncertNames[21]+"Up").c_str(),&njetVecUp[21],("njet_"+uncertNames[21]+"Up/I").c_str());
        TBranch *nBranchNjetDown21 =  t->Branch(("njet_"+uncertNames[21]+"Down").c_str(),&njetVecDown[21],("njet_"+uncertNames[21]+"Down/I").c_str());
        TBranch *nBranchVBFUp21 =  t->Branch(("vbfMass_"+uncertNames[21]+"Up").c_str(),&vbfVecUp[21],("vbfMass_"+uncertNames[21]+"Up/F").c_str());
        TBranch *nBranchVBFDown21 =  t->Branch(("vbfMass_"+uncertNames[21]+"Down").c_str(),&vbfVecDown[21],("vbfMass_"+uncertNames[21]+"Down/F").c_str());
        TBranch *nBranchNjetUp22 =  t->Branch(("njet_"+uncertNames[22]+"Up").c_str(),&njetVecUp[22],("njet_"+uncertNames[22]+"Up/I").c_str());
        TBranch *nBranchNjetDown22 =  t->Branch(("njet_"+uncertNames[22]+"Down").c_str(),&njetVecDown[22],("njet_"+uncertNames[22]+"Down/I").c_str());
        TBranch *nBranchVBFUp22 =  t->Branch(("vbfMass_"+uncertNames[22]+"Up").c_str(),&vbfVecUp[22],("vbfMass_"+uncertNames[22]+"Up/F").c_str());
        TBranch *nBranchVBFDown22 =  t->Branch(("vbfMass_"+uncertNames[22]+"Down").c_str(),&vbfVecDown[22],("vbfMass_"+uncertNames[22]+"Down/F").c_str());
        TBranch *nBranchNjetUp23 =  t->Branch(("njet_"+uncertNames[23]+"Up").c_str(),&njetVecUp[23],("njet_"+uncertNames[23]+"Up/I").c_str());
        TBranch *nBranchNjetDown23 =  t->Branch(("njet_"+uncertNames[23]+"Down").c_str(),&njetVecDown[23],("njet_"+uncertNames[23]+"Down/I").c_str());
        TBranch *nBranchVBFUp23 =  t->Branch(("vbfMass_"+uncertNames[23]+"Up").c_str(),&vbfVecUp[23],("vbfMass_"+uncertNames[23]+"Up/F").c_str());
        TBranch *nBranchVBFDown23 =  t->Branch(("vbfMass_"+uncertNames[23]+"Down").c_str(),&vbfVecDown[23],("vbfMass_"+uncertNames[23]+"Down/F").c_str());
        TBranch *nBranchNjetUp24 =  t->Branch(("njet_"+uncertNames[24]+"Up").c_str(),&njetVecUp[24],("njet_"+uncertNames[24]+"Up/I").c_str());
        TBranch *nBranchNjetDown24 =  t->Branch(("njet_"+uncertNames[24]+"Down").c_str(),&njetVecDown[24],("njet_"+uncertNames[24]+"Down/I").c_str());
        TBranch *nBranchVBFUp24 =  t->Branch(("vbfMass_"+uncertNames[24]+"Up").c_str(),&vbfVecUp[24],("vbfMass_"+uncertNames[24]+"Up/F").c_str());
        TBranch *nBranchVBFDown24 =  t->Branch(("vbfMass_"+uncertNames[24]+"Down").c_str(),&vbfVecDown[24],("vbfMass_"+uncertNames[24]+"Down/F").c_str());
        TBranch *nBranchNjetUp25 =  t->Branch(("njet_"+uncertNames[25]+"Up").c_str(),&njetVecUp[25],("njet_"+uncertNames[25]+"Up/I").c_str());
        TBranch *nBranchNjetDown25 =  t->Branch(("njet_"+uncertNames[25]+"Down").c_str(),&njetVecDown[25],("njet_"+uncertNames[25]+"Down/I").c_str());
        TBranch *nBranchVBFUp25 =  t->Branch(("vbfMass_"+uncertNames[25]+"Up").c_str(),&vbfVecUp[25],("vbfMass_"+uncertNames[25]+"Up/F").c_str());
        TBranch *nBranchVBFDown25 =  t->Branch(("vbfMass_"+uncertNames[25]+"Down").c_str(),&vbfVecDown[25],("vbfMass_"+uncertNames[25]+"Down/F").c_str());
        TBranch *nBranchNjetUp26 =  t->Branch(("njet_"+uncertNames[26]+"Up").c_str(),&njetVecUp[26],("njet_"+uncertNames[26]+"Up/I").c_str());
        TBranch *nBranchNjetDown26 =  t->Branch(("njet_"+uncertNames[26]+"Down").c_str(),&njetVecDown[26],("njet_"+uncertNames[26]+"Down/I").c_str());
        TBranch *nBranchVBFUp26 =  t->Branch(("vbfMass_"+uncertNames[26]+"Up").c_str(),&vbfVecUp[26],("vbfMass_"+uncertNames[26]+"Up/F").c_str());
        TBranch *nBranchVBFDown26 =  t->Branch(("vbfMass_"+uncertNames[26]+"Down").c_str(),&vbfVecDown[26],("vbfMass_"+uncertNames[26]+"Down/F").c_str());
        TBranch *nBranchNjetUp27 =  t->Branch(("njet_"+uncertNames[27]+"Up").c_str(),&njetVecUp[27],("njet_"+uncertNames[27]+"Up/I").c_str());
        TBranch *nBranchNjetDown27 =  t->Branch(("njet_"+uncertNames[27]+"Down").c_str(),&njetVecDown[27],("njet_"+uncertNames[27]+"Down/I").c_str());
        TBranch *nBranchVBFUp27 =  t->Branch(("vbfMass_"+uncertNames[27]+"Up").c_str(),&vbfVecUp[27],("vbfMass_"+uncertNames[27]+"Up/F").c_str());
        TBranch *nBranchVBFDown27 =  t->Branch(("vbfMass_"+uncertNames[27]+"Down").c_str(),&vbfVecDown[27],("vbfMass_"+uncertNames[27]+"Down/F").c_str());
        TBranch *nBranchNjetUp28 =  t->Branch(("njet_"+uncertNames[28]+"Up").c_str(),&njetVecUp[28],("njet_"+uncertNames[28]+"Up/I").c_str());
        TBranch *nBranchNjetDown28 =  t->Branch(("njet_"+uncertNames[28]+"Down").c_str(),&njetVecDown[28],("njet_"+uncertNames[28]+"Down/I").c_str());
        TBranch *nBranchVBFUp28 =  t->Branch(("vbfMass_"+uncertNames[28]+"Up").c_str(),&vbfVecUp[28],("vbfMass_"+uncertNames[28]+"Up/F").c_str());
        TBranch *nBranchVBFDown28 =  t->Branch(("vbfMass_"+uncertNames[28]+"Down").c_str(),&vbfVecDown[28],("vbfMass_"+uncertNames[28]+"Down/F").c_str());
        TBranch *nBranchNjetUp29 =  t->Branch(("njet_"+uncertNames[29]+"Up").c_str(),&njetVecUp[29],("njet_"+uncertNames[29]+"Up/I").c_str());
        TBranch *nBranchNjetDown29 =  t->Branch(("njet_"+uncertNames[29]+"Down").c_str(),&njetVecDown[29],("njet_"+uncertNames[29]+"Down/I").c_str());
        TBranch *nBranchVBFUp29 =  t->Branch(("vbfMass_"+uncertNames[29]+"Up").c_str(),&vbfVecUp[29],("vbfMass_"+uncertNames[29]+"Up/F").c_str());
        TBranch *nBranchVBFDown29 =  t->Branch(("vbfMass_"+uncertNames[29]+"Down").c_str(),&vbfVecDown[29],("vbfMass_"+uncertNames[29]+"Down/F").c_str());
        TBranch *nBranchNjetUp30 =  t->Branch(("njet_"+uncertNames[30]+"Up").c_str(),&njetVecUp[30],("njet_"+uncertNames[30]+"Up/I").c_str());
        TBranch *nBranchNjetDown30 =  t->Branch(("njet_"+uncertNames[30]+"Down").c_str(),&njetVecDown[30],("njet_"+uncertNames[30]+"Down/I").c_str());
        TBranch *nBranchVBFUp30 =  t->Branch(("vbfMass_"+uncertNames[30]+"Up").c_str(),&vbfVecUp[30],("vbfMass_"+uncertNames[30]+"Up/F").c_str());
        TBranch *nBranchVBFDown30 =  t->Branch(("vbfMass_"+uncertNames[30]+"Down").c_str(),&vbfVecDown[30],("vbfMass_"+uncertNames[30]+"Down/F").c_str());
        TBranch *nBranchNjetUp31 =  t->Branch(("njet_"+uncertNames[31]+"Up").c_str(),&njetVecUp[31],("njet_"+uncertNames[31]+"Up/I").c_str());
        TBranch *nBranchNjetDown31 =  t->Branch(("njet_"+uncertNames[31]+"Down").c_str(),&njetVecDown[31],("njet_"+uncertNames[31]+"Down/I").c_str());
        TBranch *nBranchVBFUp31 =  t->Branch(("vbfMass_"+uncertNames[31]+"Up").c_str(),&vbfVecUp[31],("vbfMass_"+uncertNames[31]+"Up/F").c_str());
        TBranch *nBranchVBFDown31 =  t->Branch(("vbfMass_"+uncertNames[31]+"Down").c_str(),&vbfVecDown[31],("vbfMass_"+uncertNames[31]+"Down/F").c_str());
        TBranch *nBranchNjetUp32 =  t->Branch(("njet_"+uncertNames[32]+"Up").c_str(),&njetVecUp[32],("njet_"+uncertNames[32]+"Up/I").c_str());
        TBranch *nBranchNjetDown32 =  t->Branch(("njet_"+uncertNames[32]+"Down").c_str(),&njetVecDown[32],("njet_"+uncertNames[32]+"Down/I").c_str());
        TBranch *nBranchVBFUp32 =  t->Branch(("vbfMass_"+uncertNames[32]+"Up").c_str(),&vbfVecUp[32],("vbfMass_"+uncertNames[32]+"Up/F").c_str());
        TBranch *nBranchVBFDown32 =  t->Branch(("vbfMass_"+uncertNames[32]+"Down").c_str(),&vbfVecDown[32],("vbfMass_"+uncertNames[32]+"Down/F").c_str());
        TBranch *nBranchNjetUp33 =  t->Branch(("njet_"+uncertNames[33]+"Up").c_str(),&njetVecUp[33],("njet_"+uncertNames[33]+"Up/I").c_str());
        TBranch *nBranchNjetDown33 =  t->Branch(("njet_"+uncertNames[33]+"Down").c_str(),&njetVecDown[33],("njet_"+uncertNames[33]+"Down/I").c_str());
        TBranch *nBranchVBFUp33 =  t->Branch(("vbfMass_"+uncertNames[33]+"Up").c_str(),&vbfVecUp[33],("vbfMass_"+uncertNames[33]+"Up/F").c_str());
        TBranch *nBranchVBFDown33 =  t->Branch(("vbfMass_"+uncertNames[33]+"Down").c_str(),&vbfVecDown[33],("vbfMass_"+uncertNames[33]+"Down/F").c_str());
        TBranch *nBranchNjetUp34 =  t->Branch(("njet_"+uncertNames[34]+"Up").c_str(),&njetVecUp[34],("njet_"+uncertNames[34]+"Up/I").c_str());
        TBranch *nBranchNjetDown34 =  t->Branch(("njet_"+uncertNames[34]+"Down").c_str(),&njetVecDown[34],("njet_"+uncertNames[34]+"Down/I").c_str());
        TBranch *nBranchVBFUp34 =  t->Branch(("vbfMass_"+uncertNames[34]+"Up").c_str(),&vbfVecUp[34],("vbfMass_"+uncertNames[34]+"Up/F").c_str());
        TBranch *nBranchVBFDown34 =  t->Branch(("vbfMass_"+uncertNames[34]+"Down").c_str(),&vbfVecDown[34],("vbfMass_"+uncertNames[34]+"Down/F").c_str());
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
typedef VBFVariableFiller<PATMuTauPair> PATMuTauPairVBFVariableFiller;
typedef VBFVariableFiller<PATElecTauPair> PATEleTauPairVBFVariableFiller;
typedef VBFVariableFiller<PATDiTauPair> PATDiTauPairVBFVariableFiller;

