// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include <TTree.h>

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMET.h"

#include "PUAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
template<class T>
reco::TransientTrack getTrack(const T& cand, const TransientTrackBuilder& builder);
template<> 
reco::TransientTrack getTrack<pat::Muon>(const pat::Muon& muon, const TransientTrackBuilder& builder) { return builder.build(muon.innerTrack()); }
template<> 
reco::TransientTrack getTrack<pat::Electron>(const pat::Electron& electron, const TransientTrackBuilder& builder) { return builder.build(electron.gsfTrack()); }
//
// class decleration
//
template<typename T>
class VertexFiller : public NtupleFillerBase {
	public:
		VertexFiller(){
		}


		VertexFiller(const edm::ParameterSet& iConfig, TTree* t,edm::ConsumesCollector && iC):
			src_(iConfig.getParameter<edm::InputTag>("src")),
			tag_(iConfig.getParameter<std::string>("tag"))
	{
		vdof = 0;
		vposx = 0;
		vposy = 0;
		vposz = 0;
		//		v_cxx = 0;
		//		v_cyx = 0;
		//		v_cyy = 0;
		//		v_czx = 0;
		//		v_czy = 0;
		//		v_czz = 0;
		vnormChi2 = 0;
		visValid = 0;

		t->Branch((tag_+"dof").c_str(),&vdof,(tag_+"dof/I").c_str());
		t->Branch((tag_+"x").c_str(),&vposx,(tag_+"x/F").c_str());
		t->Branch((tag_+"y").c_str(),&vposy,(tag_+"y/F").c_str());
		t->Branch((tag_+"z").c_str(),&vposz,(tag_+"z/F").c_str());
		//		t->Branch((tag_+"cxx").c_str(),&v_cxx,(tag_+"cxx/F").c_str());
		//		t->Branch((tag_+"cyx").c_str(),&v_cyx,(tag_+"cyx/F").c_str());
		//		t->Branch((tag_+"cyy").c_str(),&v_cyy,(tag_+"cyy/F").c_str());
		//		t->Branch((tag_+"czx").c_str(),&v_czx,(tag_+"czx/F").c_str());
		//		t->Branch((tag_+"czy").c_str(),&v_czy,(tag_+"czy/F").c_str());
		//		t->Branch((tag_+"czz").c_str(),&v_czz,(tag)+"czz/F").c_str());
		t->Branch((tag_+"normChi2").c_str(),&vnormChi2,(tag_+"normChi2/F").c_str());
		t->Branch((tag_+"isValid").c_str(),&visValid,(tag_+"isValid/I").c_str());
	}


		~VertexFiller()
		{ 

		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			edm::Handle<std::vector<T> > handleT;
			//			if(iEvent.getByLabel(src_,handle)) {
			//				if (TransientTrackBuilder_!=0) std::cout << "!!!" << std::endl;
			//				std::cout << handle->at(0).numberOfDaughters() << std::endl;
			//				//std::cout << handleT->at(0).leg1()->pt() << std::endl;
			//				//value = handle->size();
			//				value=handle->at(0).mass();
			//			}
			edm::ESHandle<TransientTrackBuilder> myTransientTrackBuilder;
			iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",myTransientTrackBuilder);
			TransientTrackBuilder_ = myTransientTrackBuilder.product();
			std::vector<reco::TransientTrack> transientTracks;
			if(iEvent.getByLabel(src_,handleT)){
				if (handleT->size()>0){
					transientTracks.push_back(getTrack(*(handleT->at(0).leg1()->leg1()), *TransientTrackBuilder_));
					transientTracks.push_back(getTrack(*(handleT->at(0).leg1()->leg2()), *TransientTrackBuilder_));
					transientTracks.push_back(getTrack(*(handleT->at(0).leg2()->leg1()), *TransientTrackBuilder_));
					transientTracks.push_back(getTrack(*(handleT->at(0).leg2()->leg2()), *TransientTrackBuilder_));
					KalmanVertexFitter fitter(true);
					TransientVertex myVertex = fitter.vertex(transientTracks);
					if (myVertex.isValid()){
							vposx = myVertex.position().x();
							vposy = myVertex.position().y();
							vposz = myVertex.position().z();
							vdof = myVertex.degreesOfFreedom();
							//					v_cxx = myVertex.positionError().cxx();
							//				v_cyx = myVertex.positionError().cyx();
							//					v_cyy = myVertex.positionError().cyy();
							//					v_czx = myVertex.positionError().czx();
							//				v_czy = myVertex.positionError().czy();
							//					v_czz = myVertex.positionError().czz();
							vnormChi2 = myVertex.normalisedChiSquared(); //normalised or normalized?
 							visValid = myVertex.isValid();
					} else {
							vposx = 1729;
							vposy = 1729;
							vposz = 1729;
							vdof = 1729;
							//					v_cxx = myVertex.positionError().cxx();
							//				v_cyx = myVertex.positionError().cyx();
							//					v_cyy = myVertex.positionError().cyy();
							//					v_czx = myVertex.positionError().czx();
							//				v_czy = myVertex.positionError().czy();
							//					v_czz = myVertex.positionError().czz();
							vnormChi2 = 1729; //normalised or normalized?
							visValid = 1729;
					}
				}
			} else printf("StringBasedNtupleFiller: Obj not found \n");
		}


							protected:
		const TransientTrackBuilder* TransientTrackBuilder_; 
		edm::InputTag src_;
		std::string tag_;
		int vdof;
		float vposx;
		float vposy;
		float vposz;
		//		float v_cxx;
		//		float v_cyx;
		//		float v_cyy;
		//		float v_czx;
		//		float v_zy;
		//		float v_zz;
		float vnormChi2;
		int visValid;
};

#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "PUAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
//typedef VertexFiller<PATMuMuMuMuQuad> MuMuMuMuVertexFiller;
//typedef VertexFiller<PATMuMuEleEleQuad> MuMuEleEleVertexFiller;
//typedef VertexFiller<PATEleEleMuMuQuad> EleEleMuMuVertexFiller;
//typedef VertexFiller<PATEleEleEleEleQuad> EleEleEleEleVertexFiller;

