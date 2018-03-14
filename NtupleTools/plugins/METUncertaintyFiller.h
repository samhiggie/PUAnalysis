// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "DataFormats/Math/interface/Error.h"
#include <TTree.h>
#include <math.h>
#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include <TMath.h>
//
// class declaration
//

template<typename T>
class METUncertaintyFiller : public NtupleFillerBase {
    public:
        METUncertaintyFiller(){
        }


        METUncertaintyFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
            met_(iC.consumes<edm::View<pat::MET>>(iConfig.getParameter<edm::InputTag>("met"))),
            src_(iC.consumes<std::vector<T> >(iConfig.getParameter<edm::InputTag>("src"))), 
            tag_(iConfig.getParameter<std::string>("tag")),
            uncert_(iConfig.getParameter<std::string>("uncert"))
    {
        value = new float[5];
        t->Branch((tag_+"mt"+uncert_).c_str(),&value[0],(tag_+"mt"+uncert_+"/F").c_str());
        t->Branch((tag_+"mt_2"+uncert_).c_str(),&value[1],(tag_+"mt_2"+uncert_+"/F").c_str());
        t->Branch((tag_+"mt_1"+uncert_).c_str(),&value[2],(tag_+"mt_1"+uncert_+"/F").c_str());
        t->Branch((tag_+"met"+uncert_).c_str(),&value[3],(tag_+"met"+uncert_+"/F").c_str());
        t->Branch((tag_+"metphi"+uncert_).c_str(),&value[4],(tag_+"metphi"+uncert_+"/F").c_str());
    }


        ~METUncertaintyFiller()
        { 

        }


        void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
        {

            //function_pt = new StringObjectFunction<T>("leg1.pt");
            //function_eta = new StringObjectFunction<T>("leg1.eta");
            //
            //

            edm::Handle<std::vector<T>> handle;
            edm::Handle<edm::View<pat::MET>> metHandle;
            if( iEvent.getByToken(src_,handle) &&iEvent.getByToken(met_,metHandle)){
                //std::cout<<"Met Size: "<<metHandle->size()<<std::endl;

                bool foundMET=false; 
                const pat::MET *pfMET = 0;
                if (metHandle->size()==1){
                    pfMET = &(metHandle->front());
                    foundMET=true;
                }
                else{
                    for (size_t i = 0; i < metHandle->size(); ++i) {
                        const pat::MET& met = (*metHandle)[i];
                        //for ( auto name : met.userCandNames() ) std::cout << name << std::endl;   
                        double l1pdg = handle->at(0).leg1()->pdgId();
                        double l1eta = (round(handle->at(0).leg1()->eta()*1000))/1000.0;
                        double l1phi = (round(handle->at(0).leg1()->phi()*1000))/1000.0;
                        double l2pdg = handle->at(0).leg2()->pdgId();
                        double l2eta = (round(handle->at(0).leg2()->eta()*1000))/1000.0;
                        double l2phi = (round(handle->at(0).leg2()->phi()*1000))/1000.0;
                        double m1pdg = met.userCand("lepton0")->pdgId();
                        double m1eta = (round(met.userCand("lepton0")->eta()*1000))/1000.0;
                        double m1phi = (round(met.userCand("lepton0")->phi()*1000))/1000.0;
                        double m2pdg = met.userCand("lepton1")->pdgId();
                        double m2eta = (round(met.userCand("lepton1")->eta()*1000))/1000.0;
                        double m2phi = (round(met.userCand("lepton1")->phi()*1000))/1000.0;

                        if ( l1pdg==m1pdg && l2pdg==m2pdg && l1phi == m1phi && l2phi == m2phi && l1eta==m1eta && l2eta==m2eta)
                        { 
                            //std::cout<<"FOUND MET MATCH"<<std::endl;
                            pfMET = &(metHandle->at(i)); 
                            foundMET=true;
                            break;
                        }
                    }//end met loop
                }//end else

                if(!foundMET) { 
                    std::cout<<"===============MET NOT FOUND============="<<std::endl;
                    
                }



                double et_leg1 = handle->at(0).leg1()->et();
                double et_leg2 = handle->at(0).leg2()->et();
                double px_leg1 = handle->at(0).leg1()->px();
                double px_leg2 = handle->at(0).leg2()->px();
                double py_leg1 = handle->at(0).leg1()->py();
                double py_leg2 = handle->at(0).leg2()->py();
                double metPt = 0;
                double metPhi = -999;
                double metPx = 0;
                double metPy = 0;
                if(foundMET&&uncert_=="EnUp"){
                    metPt = pfMET->shiftedPt(pat::MET::UnclusteredEnUp);
                    metPhi = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp);
                    metPx = pfMET->shiftedPx(pat::MET::UnclusteredEnUp);
                    metPy = pfMET->shiftedPy(pat::MET::UnclusteredEnUp);
                }
                else if(foundMET&&uncert_=="EnDown"){
                    metPt = pfMET->shiftedPt(pat::MET::UnclusteredEnDown);
                    metPhi = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown);
                    metPx = pfMET->shiftedPx(pat::MET::UnclusteredEnDown);
                    metPy = pfMET->shiftedPy(pat::MET::UnclusteredEnDown);
                }
                else if(foundMET&&uncert_=="JetUp"){
                    metPt = pfMET->shiftedPt(pat::MET::JetEnUp);
                    metPhi = pfMET->shiftedPhi(pat::MET::JetEnUp);
                    metPx = pfMET->shiftedPx(pat::MET::JetEnUp);
                    metPy = pfMET->shiftedPy(pat::MET::JetEnUp);
                }
                else if(foundMET&&uncert_=="JetDown"){
                    metPt = pfMET->shiftedPt(pat::MET::JetEnDown);
                    metPhi = pfMET->shiftedPhi(pat::MET::JetEnDown);
                    metPx = pfMET->shiftedPx(pat::MET::JetEnDown);
                    metPy = pfMET->shiftedPy(pat::MET::JetEnDown);
                }
                else {
                    metPt = pfMET->pt();
                    metPhi = pfMET->phi();
                    metPx = pfMET->px();
                    metPy = pfMET->py();
                }

                /*
                   if (doGen_) {
                   double et_leg1 = handle->at(0).p4Leg1gen()->et();
                   double et_leg2 = handle->at(0).p4VisLeg2gen()->et();
                   double px_leg1 = handle->at(0).p4Leg1gen()->px();
                   double px_leg2 = handle->at(0).p4VisLeg2gen()->px();
                   double py_leg1 = handle->at(0).p4Leg1gen()->py();
                   double py_leg2 = handle->at(0).p4VisLeg2gen()->py();
                   double metPt = pfMET->genMET()->pt();
                   double metPx = pfMET->genMET()->px();
                   double metPy = pfMET->genMET()->py();

                   }

*/
                double px = px_leg1 + px_leg2 + metPx;
                double px1 = px_leg1 + metPx;
                double px2 = px_leg2 + metPx;
                double py = py_leg1 + py_leg2 + metPy;
                double py1 = py_leg1 + metPy;
                double py2 = py_leg2 + metPy;
                double et = et_leg2 + et_leg1 + TMath::Sqrt(metPx*metPx + metPy*metPy);
                double et1 = et_leg1 + TMath::Sqrt(metPx*metPx + metPy*metPy);
                double et2 = et_leg2 + TMath::Sqrt(metPx*metPx + metPy*metPy);
                double mt1 = et1*et1 - (px1*px1 + py1*py1);
                double mt2 = et2*et2 - (px2*px2 + py2*py2);
                double mt = et*et - (px*px + py*py);

                value[0] = TMath::Sqrt(mt);
                value[1] = TMath::Sqrt(mt2);
                value[2] = TMath::Sqrt(mt1); 
                value[3] = metPt;
                value[4] = metPhi;
            }
            else{
                //std::cout<<"slimmedMETs not found for ntuple"<<std::endl;
                value [0]= -999;
                value [1]= -999;
                value [2]= -999;
                value [3]= -999;
                value [4]= -999;
            }
        }

    private:
        edm::EDGetTokenT<edm::View<pat::MET>> met_;
        edm::EDGetTokenT<std::vector<T> > src_;
        std::string tag_;
        std::string uncert_;
        float* value;

};


#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"

typedef METUncertaintyFiller<PATMuTauPair> PATMuTauPairMETUncertaintyFiller;
typedef METUncertaintyFiller<PATElecTauPair> PATEleTauPairMETUncertaintyFiller;
typedef METUncertaintyFiller<PATDiTauPair> PATDiTauPairMETUncertaintyFiller;

