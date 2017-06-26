#ifndef _TauAnalysis_CandidateTools_FetchCollection_
#define _TauAnalysis_CandidateTools_FetchCollection_

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

namespace pf {

template<class T, class G>
void fetchCollection(T& c,
		     edm::EDGetTokenT<G> const& tag,
		     const edm::Event& iEvent) {
  
  if( tag.isUninitialized() ) return;
  
  bool found = iEvent.getByToken(tag, c);
  
  if(!found ) {
    std::ostringstream  err;
    err<<" cannot fetchCollection (getToken) "
    <<std::endl;
    edm::LogError("PFPAT")<<err.str();
    throw cms::Exception( "MissingProduct", err.str());
  }
  
}
 
}

#endif
