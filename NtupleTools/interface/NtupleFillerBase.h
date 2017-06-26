#ifndef PUAnalysis_NtupleTools_NtupleFillerBase_h 
#define PUAnalysis_NtupleTools_NtupleFillerBase_h

#include <iostream>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TBranch.h"
#include "TTree.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

class NtupleFillerBase {

 public:
  NtupleFillerBase() {}
  NtupleFillerBase(const edm::ParameterSet&,TTree*,edm::ConsumesCollector&) {}

  ~NtupleFillerBase(){}

  virtual void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)=0;
};

#include "FWCore/PluginManager/interface/PluginFactory.h"

typedef edmplugin::PluginFactory<NtupleFillerBase*(const edm::ParameterSet&,TTree*,edm::ConsumesCollector)> NtupleFillerFactory;

#endif
