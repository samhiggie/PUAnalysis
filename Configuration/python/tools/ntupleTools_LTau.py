import FWCore.ParameterSet.Config as cms

from PUAnalysis.Configuration.tools.analysisTools_LTau import TriggerPaths,TriggerRes,TriggerProcess,TriggerFilter



def makeCollSize(srcName,tagName):
  PSet = cms.PSet(
        pluginType = cms.string("CollectionSizeFiller"),
        src        = cms.InputTag(srcName),
        tag        = cms.string(tagName)
  )
  return PSet

def makeCollSizeVeto(srcName,size, tagName):
  PSet = cms.PSet(
        pluginType = cms.string("CollectionSizeVetoFiller"),
        src        = cms.InputTag(srcName),
        size       = cms.untracked.double(size),
        tag        = cms.string(tagName)
  )
  return PSet

def makeCollSizeOS(srcName,size, tagName):
  PSet = cms.PSet(
        pluginType = cms.string("OSCollectionSizeFiller"),
        src        = cms.InputTag(srcName),
        size       = cms.untracked.double(size),
        tag        = cms.string(tagName)
  )
  return PSet

def makeLTauGeneric(plugin,sourceDiTaus,tagName,methodName):
   PSet = cms.PSet(
         pluginType  = cms.string(plugin),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
   )
   return PSet

def makeMuTauPair(sourceDiTaus,tagName,methodName,leadingOnly=True):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
         leadingOnly = cms.untracked.bool(leadingOnly)
   )
   return PSet

def makeMuTauCSVPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairCSVJetVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet
 
def makeMuTauVBFPair(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairVBFVariableFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeMuTauPtPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairPtJetPairVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet

def makeMuTauMET(sourceDiTaus, sourceMET, prefix):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairMETFiller"),
         src         = cms.InputTag(sourceDiTaus),
         met         = cms.InputTag(sourceMET),
         tag         = cms.string(prefix)
   )
   return PSet
def makeMuTauMETUncert(sourceDiTaus, sourceMET, prefix, shift):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairMETUncertaintyFiller"),
         src         = cms.InputTag(sourceDiTaus),
         met         = cms.InputTag(sourceMET),
         tag         = cms.string(prefix),
         uncert      = cms.string(shift) #EnUp or EnDown Available
   )
   return PSet

def makeMuTauEventWeight(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairWeightFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string("Mu"),
         isMuon      = cms.bool(True)
   )
   return PSet

def makeMuTauPOGSF(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairPOGSFsFiller"),
         src         = cms.InputTag(sourceDiTaus),
         isMu      = cms.bool(True)
   )
   return PSet

def makeMuTauEventWeightTmp(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairWeightFillerTmp"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string("MyMu"),
         isMuon      = cms.bool(True)
   )
   return PSet
def makeMuTauGenMatch(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairGenMCMatching"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet
def makeMuTauNBTag(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairNBTagFiller"),
         src         = cms.InputTag(sourceDiTaus),
         doEffMap      = cms.bool(True)
   )
   return PSet

def makeMuTauEffCSV(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairEffCSVFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeMuTauCSVShape(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairCSVReweightFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeMuTauJetCountPair(sourceDiTaus,tagName,methodName,leadingOnly=True):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairJetCountFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
         leadingOnly = cms.untracked.bool(leadingOnly)
   )
   return PSet

def makeEleTauPair(sourceDiTaus,tagName,methodName,leadingOnly=True):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
         leadingOnly = cms.untracked.bool(leadingOnly)
   )
   return PSet

def makeEleTauCSVPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairCSVJetVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet

def makeEleTauVBFPair(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairVBFVariableFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeEleTauPtPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairPtJetPairVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet

def makeEleTauJetCountPair(sourceDiTaus,tagName,methodName,leadingOnly=True):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairJetCountFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
         leadingOnly = cms.untracked.bool(leadingOnly)
   )
   return PSet

def makeEleTauMET(sourceDiTaus, sourceMET, prefix):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairMETFiller"),
         src         = cms.InputTag(sourceDiTaus),
         met         = cms.InputTag(sourceMET),
         tag         = cms.string(prefix)
   )
   return PSet

def makeEleTauMETUncert(sourceDiTaus, sourceMET, prefix, shift):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairMETUncertaintyFiller"),
         src         = cms.InputTag(sourceDiTaus),
         met         = cms.InputTag(sourceMET),
         tag         = cms.string(prefix),
         uncert      = cms.string(shift)  #EnUp or EnDown Available
   )
   return PSet

def makeEleTauPOGSF(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairPOGSFsFiller"),
         src         = cms.InputTag(sourceDiTaus),
         isMu      = cms.bool(False)
   )
   return PSet


def makeEleTauEventWeight(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairWeightFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string("Ele"),
         isMuon      = cms.bool(False)
   )
   return PSet

def makeEleTauEventWeightTmp(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairWeightFillerTmp"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string("MyEle"),
         isMuon      = cms.bool(False)
   )
   return PSet
def makeEleTauGenMatch(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairGenMCMatching"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet
def makeEleTauNBTag(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairNBTagFiller"),
         src         = cms.InputTag(sourceDiTaus),
         doEffMap      = cms.bool(True)
   )
   return PSet

def makeEleTauEffCSV(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairEffCSVFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeEleTauCSVShape(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairCSVReweightFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet





def addMuTauShortEventTree(process,name,src = 'muTausSorted', srcLL = 'diMuonsOSSorted', srcU='TightMuons', srcE='TightElectrons'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis_LTau.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              genEvent = cms.InputTag('generator'),
                              coreCollections = cms.InputTag(src),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerProcess),
                                  prescales = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              metfilter = cms.PSet(
                                  pluginType = cms.string("TriggerFilterFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerFilter),
                                  BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
                                  BadPFMuonFilter           = cms.InputTag("BadPFMuonFilter"),
                                  paths      = cms.vstring(
                                      "Flag_noBadMuons",
                                      "Flag_badMuons",
                                      "Flag_duplicateMuons",
                                      "Flag_HBHENoiseFilter",
                                      "Flag_HBHENoiseIsoFilter",
                                      "Flag_globalTightHalo2016Filter",
                                      "Flag_goodVertices",
                                      "Flag_eeBadScFilter",
                                      "Flag_EcalDeadCellTriggerPrimitiveFilter"
                                      )
                                  ),
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("slimmedAddPileupInfo"),
                                  tag        = cms.string("pu")
                              ),
                              cov = cms.PSet(
                                  pluginType = cms.string("METSignificanceFiller"),
                                  src        = cms.InputTag("METSignificance"),
                                  tag        = cms.string("metcov")
                              ),
                              PVsSync = cms.PSet(
                                  pluginType = cms.string("VertexSizeFiller"),
                                  src        = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                  tag        = cms.string("npv")
                              ),
                               muTauLHEProduct2 = cms.PSet(
                                  pluginType = cms.string("LHEProductFiller"),
                                  src        = cms.InputTag("externalLHEProducer"),
                                  tag        = cms.string("LHEProduct"),
                              ),
 
                              muTauPOG = makeMuTauPOGSF(src),
                              muTauEventWeight = makeMuTauEventWeight(src),
                              muTauEventWeightTmp = makeMuTauEventWeightTmp(src),
                              muTauGenMCMatch = makeMuTauGenMatch(src),
                              muTauEffCSV = makeMuTauEffCSV(src),
                              muTauCSVShape = makeMuTauCSVShape(src),
                              muTauJES = makeMuTauVBFPair(src),

                              muonsSizeET = makeCollSize(srcU,"tightMuons"),
                              muonsSizeETVeto = makeCollSizeVeto(srcU,0,"extramuon_veto"),
                              electronsSizeET = makeCollSize(srcE,"tightElectrons"),
                              electronsSizeETVeto = makeCollSizeVeto(srcE, 1,"extraelec_veto"),

                              muTauSize = makeCollSize(src,"nCands"),
                              muTauOS = makeCollSizeOS(src,0,"os"),
                              muMuSize = makeCollSize(srcLL,"diLeptons"),

                              muTauHadMass = makeMuTauPair(src,"m_2",'leg2.mass()'),
                              muMuSizeVeto = makeCollSizeVeto(srcLL,0,"dilepton_veto"),#CHECKME
                              muTauVBFDEta = makeMuTauPair(src,"vbfDEta","vbfDEta"),
                              muTauVBFDPhi = makeMuTauPair(src,"vbfDPhi","vbfDPhi"),
                              muTauVBFMass = makeMuTauPair(src,"vbfMass","vbfMass"),#vbfMass
                              muTauVBFMass2 = makeMuTauPair(src,"mjj","vbfMass"),#vbfMass
                              muTauVBFJets20 = makeMuTauPair(src,"njetigap20","vbfNJetsGap20"),
                              muTauVBFJets30 = makeMuTauPair(src,"njetingap","vbfNJetsGap30"),
                              muTauJetsPt30njets = makeMuTauJetCountPair(src,"njets",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")'),
                              muTauJetsPt20njets = makeMuTauJetCountPair(src,"njets20",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")'),

                              #Muon IDs and Isolation
                              muTauRelPFIsoDB04_1 = makeMuTauPair(src,"iso_1",'leg1.userFloat("dBRelIso")'),

                              muTauMET1 = makeMuTauMET(src,"slimmedMETs","pf"),
                              muTauMET2 = makeMuTauMET(src,"slimmedMETsPuppi","puppi"),
                              muTauMET3 = makeMuTauMET(src,"MVAMET:MVAMET","mva"),

                              muTauMETJUncertUp = makeMuTauMETUncert(src,"slimmedMETs","pf","JetUp"),
                              muTauMETJUncertDown = makeMuTauMETUncert(src,"slimmedMETs","pf","JetDown"),
 
                              muTauMETUncertUp = makeMuTauMETUncert(src,"slimmedMETs","pf","EnUp"),
                              muTauMETUncertDown = makeMuTauMETUncert(src,"slimmedMETs","pf","EnDown"),
 
                              muTauMET = makeMuTauPair(src,"met","met.pt()"),
                              muTauMETPhi = makeMuTauPair(src,"metphi","met.phi()"),
                              muTauMvaCovMat00 = makeMuTauPair(src,"cov00","covMatrix00"),#FIXME
                              muTauMvaCovMat10 = makeMuTauPair(src,"cov10","covMatrix10"),#FIXME
                              muTauMvaCovMat01 = makeMuTauPair(src,"cov01","covMatrix01"),#FIXME
                              muTauMvaCovMat11 = makeMuTauPair(src,"cov11","covMatrix11"),#FIXME
             
                              muTauMT = makeMuTauPair(src,"mt12","mt12MET"),
                              muTauMT1 = makeMuTauPair(src,"mt_1","mt1MET"),
                              muTauMT2 = makeMuTauPair(src,"mt_2","mt2MET"),

                              muTauPt1 =  makeMuTauPair(src,"pt_1","leg1.pt"), 
                              muTauPt2 =  makeMuTauPair(src,"pt_2","leg2.pt"), 
                              muTauEta1 = makeMuTauPair(src,"eta_1","leg1.eta"),
                              muTauEta2 = makeMuTauPair(src,"eta_2","leg2.eta"),
                              muTauPhi1 = makeMuTauPair(src,"phi_1","leg1.phi"),
                              muTauPhi2 = makeMuTauPair(src,"phi_2","leg2.phi"),

                              muTauCharge = makeMuTauPair(src,"charge","charge"),
                              muTauPt = makeMuTauPair(src,"pth","pt"),
                              muTauDecayMode = makeMuTauPair(src,"tauDecayMode",'leg2.decayMode()'),

                              muTauTopGenPt = makeMuTauPair(src,"topGenPt","topGenPt"),#FIXME
                              #muTauAntiTopGenPt = makeMuTauPair(src,"antiTopGenPt","antiTopGenPt"),#FIXME

                              #muTauMuTriggerMatch6 = makeMuTauPair(src,"hltOverlapFilterSingleIsoMu21LooseIsoPFTau20",'leg2.userFloat("hltOverlapFilterSingleIsoMu21LooseIsoPFTau20")'),
                              muTauMuTriggerMatch0 = makeMuTauPair(src,"hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07",
                                                                   'leg1.userFloat("hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch1 = makeMuTauPair(src,"hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched",
                                                                   'leg1.userFloat("hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched")'),
                              muTauMuTriggerMatch2 = makeMuTauPair(src,"hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded_1",
                                                                   'leg1.userFloat("hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded")'),
                              muTauMuTriggerMatch3 = makeMuTauPair(src,"hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07",
                                                                   'leg1.userFloat("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch4 = makeMuTauPair(src,"hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07",
                                                                   'leg1.userFloat("hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch5 = makeMuTauPair(src,"hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07",
                                                                   'leg2.userFloat("hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch6 = makeMuTauPair(src,"hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded_2",
                                                                   'leg2.userFloat("hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded")'),
                              muTauMuTriggerMatch7 = makeMuTauPair(src,"hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched",
                                                                   'leg2.userFloat("hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched")'),
                              muTauMuTriggerMatch8 = makeMuTauPair(src,"hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded",
                                                                   'leg2.userFloat("hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded")'),

                              muTauGenPt1 = makeMuTauPair(src,"genPt1",'p4Leg1gen().pt()'),
                              muTauGenPt2 = makeMuTauPair(src,"genPt2",'p4Leg2gen().pt()'),
                              muTauPdg1 = makeMuTauPair(src,"pdg1",'genPdg1()'),
                              muTauPdg2 = makeMuTauPair(src,"pdg2",'genPdg2()'),
                              muTauVisGenPt1 = makeMuTauPair(src,"genVisPt1",'p4VisLeg1gen().pt()'),
                              muTauVisGenPt2 = makeMuTauPair(src,"genVisPt2",'p4VisLeg2gen().pt()'),
                              muTauGenVisMass = makeMuTauPair(src,"genVisMass",'p4VisGen().M()'),
                              muTauGenMassMatched = makeMuTauPair(src,"genFullMassMatched",'p4gen().M()'),
                              muTauGenMass = makeMuTauPair(src,"fullGenMass",'genBosonMass()'),
                              muTauGenBosonPt = makeMuTauPair(src,"genpT",'p4GenBoson().pt()'),
                              muTauGenBosonMass = makeMuTauPair(src,"genMass",'p4GenBoson().M()'),
                              muTauGenBosonPx = makeMuTauPair(src,"genpX",'p4GenBoson().px()'),
                              muTauGenBosonPy = makeMuTauPair(src,"genpY",'p4GenBoson().py()'),
                              muTauGenBosonVisPx = makeMuTauPair(src,"vispX",'p4GenBosonVis().px()'),
                              muTauGenBosonVisPy = makeMuTauPair(src,"vispY",'p4GenBosonVis().py()'),

                              muTauByOldDMMVAIsoTight = makeMuTauPair(src,"byTightIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoMedium = makeMuTauPair(src,"byMediumIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byMediumIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoLoose= makeMuTauPair(src,"byLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byLooseIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoVLoose = makeMuTauPair(src,"byVLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")'),

                              muTauAgainstMuonTight3 = makeMuTauPair(src,"againstMuonTight3_2",'leg2.tauID("againstMuonTight3")'),
                              muTauAgainstEleVLooseMVA6 = makeMuTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              muTauagainstElectronMVA6Raw = makeMuTauPair(src,"againstElectronMVA6Raw_2",'leg2.tauID("againstElectronMVA6Raw")'),
                              muTauagainstElectronMVA6category = makeMuTauPair(src,"againstElectronMVA6category_2",'leg2.tauID("againstElectronMVA6category")'),
                              muTauagainstElectronMediumMVA6 = makeMuTauPair(src,"againstElectronMediumMVA6_2",'leg2.tauID("againstElectronMediumMVA6")'),
                              muTauagainstElectronTightMVA6 = makeMuTauPair(src,"againstElectronTightMVA6_2",'leg2.tauID("againstElectronTightMVA6")'),
                              muTauagainstElectronVLooseMVA6 = makeMuTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              muTauagainstElectronVTightMVA6 = makeMuTauPair(src,"againstElectronVTightMVA6_2",'leg2.tauID("againstElectronVTightMVA6")'),
 
                              muTauGenIsPrompt1 = makeMuTauPair(src,"isPrompt1",'isPrompt1()'),
                              muTauGenIsPromptFS1 = makeMuTauPair(src,"isPromptFS1",'isPromptFS1()'),
                              muTauGenIsDirectTauDecay1 = makeMuTauPair(src,"isTauDecay1",'isDirectPromptTauDecayProduct1()'),
                              muTauGenIsDirectTauDecayFS1 = makeMuTauPair(src,"isTauDecayFS1",'isDirectPromptTauDecayProductFS1()'),

                              muTauGenIsPrompt2 = makeMuTauPair(src,"isPrompt2",'isPrompt2()'),
                              muTauGenIsPromptFS2 = makeMuTauPair(src,"isPromptFS2",'isPromptFS2()'),
                              muTauGenIsDirectTauDecay2 = makeMuTauPair(src,"isTauDecay2",'isDirectPromptTauDecayProduct2()'),
                              muTauGenIsDirectTauDecayFS2 = makeMuTauPair(src,"isTauDecayFS2",'isDirectPromptTauDecayProductFS2()'),


                              muTauMass = makeMuTauPair(src,"m_vis","mass") 


   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)



def addMuTauEventTree(process,name,src = 'muTausSorted',fileout='analysis_mutau.root',srcLL = 'diMuonsOSSorted', srcU='TightMuons', srcE='TightElectrons'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string(fileout) )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              genEvent = cms.InputTag('generator'),
                              coreCollections = cms.InputTag(src),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerProcess),
                                  prescales = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              metfilter = cms.PSet(
                                  pluginType = cms.string("TriggerFilterFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerFilter),
                                  BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
                                  BadPFMuonFilter           = cms.InputTag("BadPFMuonFilter"),
                                  paths      = cms.vstring(
                                      "Flag_noBadMuons",
                                      "Flag_badMuons",
                                      "Flag_duplicateMuons",
                                      "Flag_HBHENoiseFilter",
                                      "Flag_HBHENoiseIsoFilter",
                                      "Flag_globalTightHalo2016Filter",
                                      "Flag_goodVertices",
                                      "Flag_eeBadScFilter",
                                      "Flag_EcalDeadCellTriggerPrimitiveFilter"
                                      )
                              ),
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("slimmedAddPileupInfo"),
                                  tag        = cms.string("pu")
                              ),
                              cov = cms.PSet(
                                  pluginType = cms.string("METSignificanceFiller"),
                                  src        = cms.InputTag("METSignificance"),
                                  tag        = cms.string("metcov")
                              ),
                              PVsSync = cms.PSet(
                                  pluginType = cms.string("VertexSizeFiller"),
                                  src        = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                  tag        = cms.string("npv")
                              ),
                              PVs = cms.PSet(
                                  pluginType = cms.string("VertexSizeFiller"),
                                  src        = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                  tag        = cms.string("vertices")
                              ),
 
                              muTauPOG = makeMuTauPOGSF(src),
                              muTauEventWeight = makeMuTauEventWeight(src),
                              muTauEventWeightTmp = makeMuTauEventWeightTmp(src),
                              muTauGenMCMatch = makeMuTauGenMatch(src),
                              muTauEffCSV = makeMuTauEffCSV(src),
                              muTauJES = makeMuTauVBFPair(src),
                              muTauCSVShape = makeMuTauCSVShape(src),

                              muTauSize = makeCollSize(src,"nCands"),
                              muTauOS = makeCollSizeOS(src,0,"os"),
                              genTaus = makeCollSize("genTauCands","genTaus"), 
                              muMuSize = makeCollSize(srcLL,"diLeptons"),#CHECKME
                              muMuSizeVeto = makeCollSizeVeto(srcLL,0,"dilepton_veto"),#CHECKME

                              muonsSizeMT = makeCollSize(srcU,"tightMuons"),
                              muonsSizeMTVeto = makeCollSizeVeto(srcU,1,"extramuon_veto"),
                              electronsSizeMT = makeCollSize(srcE,"tightElectrons"),
                              electronsSizeMTVeto = makeCollSizeVeto(srcE,0,"extraelec_veto"),

                              muTauDR = makeMuTauPair(src,"dR","dR12"), 
                              #tauSingleL1 =  makeMuTauPair(src,"tauSingleL1_2","leg2.userFloat('LooseIsoPFTau20_SingleL1')"), 
                              #tauL1 =  makeMuTauPair(src,"tauL1_2","leg2.userFloat('LooseIsoPFTau20')"), 
                              #tauMediumL1 =  makeMuTauPair(src,"tauMediumL1_2","leg2.userFloat('MediumIsoPFTau35_Trk_eta2p1')"),

                              tauNIsoTracks =  makeMuTauPair(src,"tauNIsoTracks","leg2.userFloat('nIsoTracks')"), 
                              muTaunIsoGamma = makeMuTauPair(src,"nIsoGamma",'leg2.userFloat("nIsoGamma")'),
                              muTaunIsoNeutral = makeMuTauPair(src,"nIsoNeutral",'leg2.userFloat("nIsoNeutral")'),


                              tauNMatchedSeg =  makeMuTauPair(src,"tauMuonNMatchedSeg","leg2.userFloat('muonNMatchedSeg')"),
                              tauTauHadMatched = makeMuTauPair(src,"tauMuonMatched","leg2.userFloat('muonTauHadMatched')"),
                              tauLeadChargedHadrTrackPt = makeMuTauPair(src,"tauLeadChargedHadrTrackPt","leg2.userFloat('leadChargedHadrTrackPt')"),

                              muTauCharge = makeMuTauPair(src,"charge","charge"),
                              q_1 = makeMuTauPair(src,"q_1","leg1.charge"),
                              q_2 = makeMuTauPair(src,"q_2","leg2.charge"),

                              muTauPt = makeMuTauPair(src,"pth","pt"),
                              muTauHT = makeMuTauPair(src,"ht","ht"),
                              muTauMass = makeMuTauPair(src,"m_vis","mass"),
                              #muTauSVPt = makeMuTauPair(src,"pt_sv","svPt"),ATLATERSTAGE
                              #muTauSVMass = makeMuTauPair(src,"m_sv","svMass"),ATLATERSTAGE
                              muTaulVeto = makeMuTauPair(src,"lVeto","lVeto"),

                              muTauFullPt = makeMuTauPair(src,"fullPt","fullPt"),
                              muTauEta = makeMuTauPair(src,"fullEta","fullEta"),
                              muTauPhi = makeMuTauPair(src,"fullPhi","fullPhi"),
                              muTauE = makeMuTauPair(src,"fullEnergy","fullEnergy"),

                              muTauPt1 =  makeMuTauPair(src,"pt_1","leg1.pt"), 
                              muTauPx1 =  makeMuTauPair(src,"px_1","leg1.px"), 
                              muTauPy1 =  makeMuTauPair(src,"py_1","leg1.py"), 
                              muTauPz1 =  makeMuTauPair(src,"pz_1","leg1.pz"), 
                              muTauPt2 =  makeMuTauPair(src,"pt_2","leg2.pt"), 
                              muTauPx2 =  makeMuTauPair(src,"px_2","leg2.px"), 
                              muTauPy2 =  makeMuTauPair(src,"py_2","leg2.py"), 
                              muTauPz2 =  makeMuTauPair(src,"pz_2","leg2.pz"), 
                              muTauEta1 = makeMuTauPair(src,"eta_1","leg1.eta"),
                              muTauEta2 = makeMuTauPair(src,"eta_2","leg2.eta"),
                              muTauPhi1 = makeMuTauPair(src,"phi_1","leg1.phi"),
                              muTauPhi2 = makeMuTauPair(src,"phi_2","leg2.phi"),

                              muTauMET1 = makeMuTauMET(src,"slimmedMETs","pf"),
                              muTauMET2 = makeMuTauMET(src,"slimmedMETsPuppi","puppi"),
                              muTauMET3 = makeMuTauMET(src,"MVAMET:MVAMET","mva"),
  
                              muTauMETJUncertUp = makeMuTauMETUncert(src,"slimmedMETs","pf","JetUp"),
                              muTauMETJUncertDown = makeMuTauMETUncert(src,"slimmedMETs","pf","JetDown"),

                              muTauMETUncertUp = makeMuTauMETUncert(src,"slimmedMETs","pf","EnUp"),
                              muTauMETUncertDown = makeMuTauMETUncert(src,"slimmedMETs","pf","EnDown"),
                              #muTauGenMET = makeMuTauPair(src,"genMET","met.genMET().pt"),
                              muTauMET = makeMuTauPair(src,"met","met.pt()"),
                              muTauMETPhi = makeMuTauPair(src,"metphi","met.phi()"),
                              muTauMETx = makeMuTauPair(src,"met_ex","met.px()"),
                              muTauMETy = makeMuTauPair(src,"met_ey","met.py()"),
                              muTauMvaCovMat00 = makeMuTauPair(src,"cov00","covMatrix00"),#FIXME
                              muTauMvaCovMat10 = makeMuTauPair(src,"cov10","covMatrix10"),#FIXME
                              muTauMvaCovMat01 = makeMuTauPair(src,"cov01","covMatrix01"),#FIXME
                              muTauMvaCovMat11 = makeMuTauPair(src,"cov11","covMatrix11"),#FIXME

                              muTauMT = makeMuTauPair(src,"mt12","mt12MET"),
                              muTauMT1 = makeMuTauPair(src,"mt_1","mt1MET"),
                              muTauMT2 = makeMuTauPair(src,"mt_2","mt2MET"),

                              muTauTopGenPt = makeMuTauPair(src,"topGenPt","topGenPt"),#FIXME
                              muTauAntiTopGenPt = makeMuTauPair(src,"antiTopGenPt","antiTopGenPt"),#FIXME

                              #BTAGS AND JETS
                              muTauVBFDEta = makeMuTauPair(src,"vbfDEta","vbfDEta"),
                              muTauVBFDPhi = makeMuTauPair(src,"vbfDPhi","vbfDPhi"),
                              muTauVBFMass = makeMuTauPair(src,"vbfMass","vbfMass"),#vbfMass
                              muTauVBFMass2 = makeMuTauPair(src,"mjj","vbfMass"),#vbfMass
                              muTauVBFJets20 = makeMuTauPair(src,"njetigap20","vbfNJetsGap20"),
                              muTauVBFJets30 = makeMuTauPair(src,"njetingap","vbfNJetsGap30"),

                              #Muon IDs and Isolation
                              muTauRelPFIsoDB03 = makeMuTauPair(src,"iso03_1",'leg1.userFloat("dBRelIso03")'),
                              muTauRelPFIsoDB04 = makeMuTauPair(src,"iso_1",'leg1.userFloat("dBRelIso")'),
                              muTauRelPFIsoDB04_1 = makeMuTauPair(src,"iso04_1",'leg1.userFloat("dBRelIso")'),

                              muTauLooseID = makeMuTauPair(src,"id_m_loose_1",'leg1.isLooseMuon()'),
                              muTauUserMediumID = makeMuTauPair(src,"id_m_medium_1",'leg1.userInt("mediumID")'),
                              muTauUserTightID = makeMuTauPair(src,"id_m_tight_1",'leg1.userInt("tightID")'),
                              muTauDecayMode = makeMuTauPair(src,"tauDecayMode",'leg2.decayMode()'),
                              muTauDecayFound = makeMuTauPair(src,"decayModeFinding_2",'leg2.tauID("decayModeFinding")'),
                              muTauDecayFoundOld = makeMuTauPair(src,"decayModeFindingOldDMs_2",'leg2.tauID("decayModeFinding")'),
                              muTauMuTriggerMatch0 = makeMuTauPair(src,"hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07",
                                                                   'leg1.userFloat("hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch1 = makeMuTauPair(src,"hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched",
                                                                   'leg1.userFloat("hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched")'),
                              muTauMuTriggerMatch2 = makeMuTauPair(src,"hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded_1",
                                                                   'leg1.userFloat("hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded")'),
                              muTauMuTriggerMatch3 = makeMuTauPair(src,"hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07",
                                                                   'leg1.userFloat("hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch4 = makeMuTauPair(src,"hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07",
                                                                   'leg1.userFloat("hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch5 = makeMuTauPair(src,"hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07",
                                                                   'leg2.userFloat("hltL3crIsoL1sMu18erTau24erIorMu20erTau24erL1f0L2f10QL3f20QL3trkIsoFiltered0p07")'),
                              muTauMuTriggerMatch6 = makeMuTauPair(src,"hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded_2",
                                                                   'leg2.userFloat("hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded")'),
                              muTauMuTriggerMatch7 = makeMuTauPair(src,"hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched",
                                                                   'leg2.userFloat("hltSelectedPFTau27LooseChargedIsolationAgainstMuonL1HLTMatched")'),
                              muTauMuTriggerMatch8 = makeMuTauPair(src,"hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded",
                                                                   'leg2.userFloat("hltOverlapFilterIsoMu20LooseChargedIsoPFTau27L1Seeded")'),
                              muTauPzeta = makeMuTauPair(src,"pZeta",'pZeta-1.5*pZetaVis'),
                              muTauPZ = makeMuTauPair(src,"pZ",'pZeta'),
                              muTauPZV = makeMuTauPair(src,"pzetavis",'pZetaVis'),
                              muTauTauZIP = makeMuTauPair(src,"tauZIP",'leg2.userFloat("zIP")'),
                              muTauHadMass = makeMuTauPair(src,"m_2",'leg2.mass()'),

                              muTauMuDZ = makeMuTauPair(src,"dZ_1","leg1.userFloat('dZ')"),
                              muTauTauDZ = makeMuTauPair(src,"dZ_2","leg2.userFloat('taudZ')"),
                              muTauMuDXY = makeMuTauPair(src,"d0_1","leg1.userFloat('dXY')"),
                              muTauTauDXY = makeMuTauPair(src,"d0_2","leg2.userFloat('taudXY')"),

                              muTauHaddxy = makeMuTauPair(src,"dxy_2",'leg2.dxy()'),
                              muTauHaddxy_Sig = makeMuTauPair(src,"dxy_Sig_2",'leg2.dxy_Sig()'),

                              #tauIDs

                              muTaubyTightIsolationMVArun2v1DBdR03oldDMwLT = makeMuTauPair(src,"byTightIsolationMVArun2v1DBdR03oldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT")'),
                              muTaubyTightIsolationMVArun2v1PWoldDMwLT = makeMuTauPair(src,"byTightIsolationMVArun2v1PWoldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1PWoldDMwLT")'),
                              muTauByOldDMMVAIso = makeMuTauPair(src,"byIsolationMVArun2v1DBoldDMwLTraw_2",'leg2.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),
                              muTauByOldDMMVAIsoVTight = makeMuTauPair(src,"byVTightIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVTightIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoTight = makeMuTauPair(src,"byTightIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoMedium = makeMuTauPair(src,"byMediumIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byMediumIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoLoose = makeMuTauPair(src,"byLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byLooseIsolationMVArun2v1DBoldDMwLT")'),
                              muTauByOldDMMVAIsoVLoose = makeMuTauPair(src,"byVLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              #muTauByOldDMMVAIsoVVLoose = makeMuTauPair(src,"byVVLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVVLooseIsolationMVArun2v1DBoldDMwLT")'),

                              muTauByOldDMMVAIsoRR1 = makeMuTauPair(src,"tau_idRaw2017v2",     'leg2.tauID("idRaw2017v2")'),
                              #muTauByOldDMMVAIsoRR2 = makeMuTauPair(src,"ibyVVLooseIsolationMVArun2017v2DBoldDMwLT2017", 'leg2.tauID("idVVLoose2017v2")'),
                              muTauByOldDMMVAIsoRR2 = makeMuTauPair(src, "tau_idVVLoose2017v2", 'leg2.tauID("idVVLoose2017v2")'),
                              muTauByOldDMMVAIsoRR3 = makeMuTauPair(src,"tau_idVLoose2017v2",  'leg2.tauID("idVLoose2017v2")'),
                              muTauByOldDMMVAIsoRR4 = makeMuTauPair(src,"tau_idLoose2017v2",   'leg2.tauID("idLoose2017v2")'),
                              muTauByOldDMMVAIsoRR5 = makeMuTauPair(src,"tau_idMed2017v2",     'leg2.tauID("idMed2017v2")'),
                              muTauByOldDMMVAIsoRR6 = makeMuTauPair(src,"tau_idTight2017v2",   'leg2.tauID("idTight2017v2")'),
                              muTauByOldDMMVAIsoRR7 = makeMuTauPair(src,"tau_idVTight2017v2",  'leg2.tauID("idVTight2017v2")'),
                              muTauByOldDMMVAIsoRR8 = makeMuTauPair(src,"tau_idVVTight2017v2", 'leg2.tauID("idVVTight2017v2")'),


                              muTauAgainstMuonTight3 = makeMuTauPair(src,"againstMuonTight3_2",'leg2.tauID("againstMuonTight3")'),
                              muTauAgainstEleVLooseMVA6 = makeMuTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              muTauagainstElectronMVA6Raw = makeMuTauPair(src,"againstElectronMVA6Raw_2",'leg2.tauID("againstElectronMVA6Raw")'),
                              muTauagainstElectronMVA6category = makeMuTauPair(src,"againstElectronMVA6category_2",'leg2.tauID("againstElectronMVA6category")'),
                              muTauagainstElectronMediumMVA6 = makeMuTauPair(src,"againstElectronMediumMVA6_2",'leg2.tauID("againstElectronMediumMVA6")'),
                              muTauagainstElectronTightMVA6 = makeMuTauPair(src,"againstElectronTightMVA6_2",'leg2.tauID("againstElectronTightMVA6")'),
                              muTauagainstElectronVLooseMVA6 = makeMuTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              muTauagainstElectronVTightMVA6 = makeMuTauPair(src,"againstElectronVTightMVA6_2",'leg2.tauID("againstElectronVTightMVA6")'),
                              muTaubyIsolationMVArun2v1DBdR03oldDMwLTraw = makeMuTauPair(src,"byIsolationMVArun2v1DBdR03oldDMwLTraw_2",'leg2.tauID("byIsolationMVArun2v1DBdR03oldDMwLTraw")'),

                              muTauGenPt1 = makeMuTauPair(src,"genPt1",'p4Leg1gen().pt()'),
                              muTauGenPt2 = makeMuTauPair(src,"genPt2",'p4Leg2gen().pt()'),
                              muTauPdg1 = makeMuTauPair(src,"pdg1",'genPdg1()'),
                              muTauPdg2 = makeMuTauPair(src,"pdg2",'genPdg2()'),
                              muTauVisGenPt1 = makeMuTauPair(src,"genVisPt1",'p4VisLeg1gen().pt()'),
                              muTauVisGenPt2 = makeMuTauPair(src,"genVisPt2",'p4VisLeg2gen().pt()'),
                              muTauGenVisMass = makeMuTauPair(src,"genVisMass",'p4VisGen().M()'),
                              muTauGenMassMatched = makeMuTauPair(src,"genFullMassMatched",'p4gen().M()'),
                              muTauGenMass = makeMuTauPair(src,"fullGenMass",'genBosonMass()'),
                              muTauGenBosonPt = makeMuTauPair(src,"genpT",'p4GenBoson().pt()'),
                              muTauGenBosonMass = makeMuTauPair(src,"genMass",'p4GenBoson().M()'),
                              muTauGenBosonPx = makeMuTauPair(src,"genpX",'p4GenBoson().px()'),
                              muTauGenBosonPy = makeMuTauPair(src,"genpY",'p4GenBoson().py()'),
                              muTauGenBosonVisPx = makeMuTauPair(src,"vispX",'p4GenBosonVis().px()'),
                              muTauGenBosonVisPy = makeMuTauPair(src,"vispY",'p4GenBosonVis().py()'),

                              muTauGenIsPrompt1 = makeMuTauPair(src,"isPrompt1",'isPrompt1()'),
                              muTauGenIsPromptFS1 = makeMuTauPair(src,"isPromptFS1",'isPromptFS1()'),
                              muTauGenIsDirectTauDecay1 = makeMuTauPair(src,"isTauDecay1",'isDirectPromptTauDecayProduct1()'),
                              muTauGenIsDirectTauDecayFS1 = makeMuTauPair(src,"isTauDecayFS1",'isDirectPromptTauDecayProductFS1()'),

                              muTauGenIsPrompt2 = makeMuTauPair(src,"isPrompt2",'isPrompt2()'),
                              muTauGenIsPromptFS2 = makeMuTauPair(src,"isPromptFS2",'isPromptFS2()'),
                              muTauGenIsDirectTauDecay2 = makeMuTauPair(src,"isTauDecay2",'isDirectPromptTauDecayProduct2()'),
                              muTauGenIsDirectTauDecayFS2 = makeMuTauPair(src,"isTauDecayFS2",'isDirectPromptTauDecayProductFS2()'),


                              #Jets
                              #muTauJetsPt20nbtag = makeMuTauJetCountPair(src,"nbtag",'userFloat("isbtagged")&&pt()>20&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              #muTauJetsPt20nbtagLoose = makeMuTauJetCountPair(src,"nbtagLooseNoSF",'pt()>20&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.5426'),
                              #muTauJetsPt20nbtagNoSF = makeMuTauJetCountPair(src,"nbtagNoSF",'pt()>20&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              #muTauJetsPt30nbtagNoSf = makeMuTauJetCountPair(src,"nbtag30",'userFloat("isbtagged")&&pt()>30&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              #muTauJetsPt30nbtag = makeMuTauJetCountPair(src,"nbtag30",'pt()>30&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),

                              muTauJetsPt30njets = makeMuTauJetCountPair(src,"njets",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")'),
                              muTauJetsPt30njetsnopu = makeMuTauJetCountPair(src,"njetspuID",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")&&!userFloat("puIDLoose")'),
                              muTauJetsPt20njets = makeMuTauJetCountPair(src,"njetspt20",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")'),
                              muTauJetsPt20njetsnopu = makeMuTauJetCountPair(src,"njetspt20puID",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")&&!userFloat("puIDLoose")'),


                              muTauJet1PtPtSort = makeMuTauPtPair(src,"jpt_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','pt()',0),
                              muTauJet2PtPtSort = makeMuTauPtPair(src,"jpt_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','pt()',1),
                              muTauJet1PFIDPtSort = makeMuTauPtPair(src,"jpfid_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("idTight")',0),
                              muTauJet2PFIDPtSort = makeMuTauPtPair(src,"jpfid_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("idTight")',1),
                              muTauJet1PUIDPtSort = makeMuTauPtPair(src,"jpuid_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("puID")',0),
                              muTauJet2PUIDPtSort = makeMuTauPtPair(src,"jpuid_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("puID")',1),
                              muTauJet1MVAPtSort = makeMuTauPtPair(src,"jmva_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")',"userFloat('pileupJetId:fullDiscriminant')",0),
                              muTauJet2MVAPtSort = makeMuTauPtPair(src,"jmva_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")',"userFloat('pileupJetId:fullDiscriminant')",1),
                              muTauJet1EtaPtSort = makeMuTauPtPair(src,"jeta_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','eta()',0),
                              muTauJet2EtaPtSort = makeMuTauPtPair(src,"jeta_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','eta()',1),
                              muTauJet1PhiPtSort = makeMuTauPtPair(src,"jphi_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','phi()',0),
                              muTauJet2PhiPtSort = makeMuTauPtPair(src,"jphi_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','phi()',1),
                              muTauJet1CSVPtSort = makeMuTauPtPair(src,"jcsv_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',0),
                              muTauJet2CSVPtSort = makeMuTauPtPair(src,"jcsv_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',1),
                              muTauJet1MedIdPtSort = makeMuTauPtPair(src,"jtlvID_1",'','userFloat("idTightLepVeto")',0),
                              muTauJet2MedIdPtSort = makeMuTauPtPair(src,"jtlvID_2",'','userFloat("idTightLepVeto")',1),
                              muTauJet1TightIdPtSort = makeMuTauPtPair(src,"jtightID_1",'','userFloat("idTight")',0),
                              muTauJet2TightIdPtSort = makeMuTauPtPair(src,"jtightID_2",'','userFloat("idTight")',1),

                              muTauBJet1PtPtSort = makeMuTauPtPair(src,"bpt_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','pt()',0),
                              muTauBJet2PtPtSort = makeMuTauPtPair(src,"bpt_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','pt()',1),
                              muTauBJet1MVAPtSort = makeMuTauPtPair(src,"bmva_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941',"userFloat('pileupJetId:fullDiscriminant')",0),
                              muTauBJet2MVAPtSort = makeMuTauPtPair(src,"bmva_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941',"userFloat('pileupJetId:fullDiscriminant')",1),
                              muTauBJet1PFIDPtSort = makeMuTauPtPair(src,"bpfid_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("idTight")',0),
                              muTauBJet2PFIDPtSort = makeMuTauPtPair(src,"bpfid_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("idTight")',1),
                              muTauBJet1PUIDPtSort = makeMuTauPtPair(src,"bpuid_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("puID")',0),
                              muTauBJet2PUIDPtSort = makeMuTauPtPair(src,"bpuid_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("puID")',1),
                              muTauBJet1EtaPtSort = makeMuTauPtPair(src,"beta_1",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','eta()',0),
                              muTauBJet2EtaPtSort = makeMuTauPtPair(src,"beta_2",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','eta()',1),
                              muTauBJet1PhiPtSort = makeMuTauPtPair(src,"bphi_1",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','phi()',0),
                              muTauBJet2PhiPtSort = makeMuTauPtPair(src,"bphi_2",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','phi()',1),
                              muTauBJet1CSVPtSort = makeMuTauPtPair(src,"bcsv_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',0),
                              muTauBJet2CSVPtSort = makeMuTauPtPair(src,"bcsv_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',1),

                              muTauJetsPt20TagMatch = makeMuTauJetCountPair(src,"nTaggableJetsPt20Matched",'pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                              muTauJetsPt20TagNoMatch = makeMuTauJetCountPair(src,"nTaggableJetsPt20NotMatched",'pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                              muTauFirstJetShape = makeLTauGeneric("PATMuTauPairHighestPtJetVarFiller",src,"highestJetShape",'userFloat("ptRMS")'),
                              muTauFirstJetCSV = makeLTauGeneric("PATMuTauPairHighestPtJetVarFiller",src,"highestJetBTagCSV",'bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")'),

                              mumuDR = makeLTauGeneric("PATMuPairFiller",srcLL,"diLeptonDR","dR12"),#FIXME

                              higgsPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("higgsPt"),
                                  method     = cms.string('pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ), #only filled in higgs sample

                              muTauLHEProduct2 = cms.PSet(
                                  pluginType = cms.string("LHEProductFiller"),
                                  src        = cms.InputTag("externalLHEProducer"),
                                  tag        = cms.string("LHEProduct"),
                              ),
                              muTauEmbedPtWeight = cms.PSet(
                                  pluginType = cms.string("GenFilterInfoWeightFiller"),
                                  src        = cms.InputTag("generator"),
                                  #src        = cms.InputTag("generator","EmbWeight"),
                                  tag        = cms.string("aMCNLO_weight"),
                              ),#FIXME
                              muTauEmbedPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("embeddedPt"),#CHECKME
                                  method     = cms.string("pt"),
                                  leadingOnly=cms.untracked.bool(False)
                              ),#FIXME 
                              muTauEmbedEta = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("embeddedEta"),
                                  method     = cms.string("eta"),
                                  leadingOnly=cms.untracked.bool(False)
                              )#FIXME #CHECKME

   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)


def addEleTauShortEventTree(process,name,src='eleTausSorted',srcLL='diElectronsOSSorted', srcU='TightMuons', srcE='TightElectrons'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis_LTau.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              genEvent = cms.InputTag('generator'),
                              coreCollections = cms.InputTag(src),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerProcess),
                                  prescales = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              cov = cms.PSet(
                                  pluginType = cms.string("METSignificanceFiller"),
                                  src        = cms.InputTag("METSignificance"),
                                  tag        = cms.string("metcov")
                              ),
                              eleTauLHEProduct2 = cms.PSet(
                                  pluginType = cms.string("LHEProductFiller"),
                                  src        = cms.InputTag("externalLHEProducer"),
                                  tag        = cms.string("LHEProduct"),
                              ),#WHAT IS THIS
                              metfilter = cms.PSet(
                                  pluginType = cms.string("TriggerFilterFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerFilter),
                                  BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
                                  BadPFMuonFilter           = cms.InputTag("BadPFMuonFilter"),
                                  paths      = cms.vstring(
                                      "Flag_noBadMuons",
                                      "Flag_badMuons",
                                      "Flag_duplicateMuons",
                                      "Flag_HBHENoiseFilter",
                                      "Flag_HBHENoiseIsoFilter",
                                      "Flag_globalTightHalo2016Filter",
                                      "Flag_goodVertices",
                                      "Flag_eeBadScFilter",
                                      "Flag_EcalDeadCellTriggerPrimitiveFilter"
                                      )
                                  ),
 
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("slimmedAddPileupInfo"),
                                  tag        = cms.string("pu")
                              ),

                              eTauPOG = makeEleTauPOGSF(src),
                              eleEleSizeVeto = makeCollSizeVeto(srcLL,0,"dilepton_veto"),
                              eleTauSize = makeCollSize(src,"nCands"),
                              eTauEventWeight = makeEleTauEventWeight(src),
                              eTauEventWeightTmp = makeEleTauEventWeightTmp(src),
                              #eleTauNBTags = makeEleTauNBTag(src),
                              eleTauEffCSV = makeEleTauEffCSV(src),
                              eleTauCSVShape = makeEleTauCSVShape(src),
                              eleTauJES = makeEleTauVBFPair(src),
                              eTauGenMCMatch = makeEleTauGenMatch(src), 
                              eleTauVBFDEta = makeEleTauPair(src,"vbfDEta","vbfDEta"),
                              eleTauVBFDPhi = makeEleTauPair(src,"vbfDPhi","vbfDPhi"),
                              eleTauVBFMass = makeEleTauPair(src,"vbfMass","vbfMass"),#vbfMass
                              eleTauVBFMass2 = makeEleTauPair(src,"mjj","vbfMass"),#vbfMass
                              eleTauVBFJets20 = makeEleTauPair(src,"njetigap20","vbfNJetsGap20"),
                              eleTauVBFJets30 = makeEleTauPair(src,"njetingap","vbfNJetsGap30"),

                              eleTauJetsPt30njets = makeEleTauJetCountPair(src,"njets",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")'),
                              eleTauJetsPt20njets = makeEleTauJetCountPair(src,"njets20",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")'),
                              #Muon IDs and Isolation
                              eleTauRelPFIsoDB03 = makeEleTauPair(src,"iso03_1",'leg1.userFloat("dBRelIso03")'),
                              eleTauRelPFIsoDB03_1 = makeEleTauPair(src,"iso_1",'leg1.userFloat("dBRelIso03")'),
                              eleTauRelPFIsoDB04 = makeEleTauPair(src,"iso04_1",'leg1.userFloat("dBRelIso")'),
                              eleTauRel2PFIsoDB03 = makeEleTauPair(src,"iso_2",'leg2.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),

                              eleTauMET1 = makeEleTauMET(src,"slimmedMETs","pf"),
                              eleTauMET2 = makeEleTauMET(src,"slimmedMETsPuppi","puppi"),
                              eleTauMET3 = makeEleTauMET(src,"MVAMET:MVAMET","mva"),


                              eleTauHadMass = makeEleTauPair(src,"m_2",'leg2.mass()'),
                              eleTauMETUncertUp = makeEleTauMETUncert(src,"slimmedMETs","pf","EnUp"),
                              eleTauMETUncertDown = makeEleTauMETUncert(src,"slimmedMETs","pf","EnDown"),

                              eleTauMETJUncertUp = makeEleTauMETUncert(src,"slimmedMETs","pf","JetUp"),
                              eleTauMETJUncertDown = makeEleTauMETUncert(src,"slimmedMETs","pf","JetDown"),
 
                              eleTauMET = makeEleTauPair(src,"met","met.phi()"), #FIXME
                              eleTauMETPhi = makeEleTauPair(src,"metphi","met.phi()"), #FIXME
                              eleTauMT1 = makeEleTauPair(src,"mt_1","mt1MET"),
                              eleTauMT2 = makeEleTauPair(src,"mt_2","mt2MET"),
                              eleTauMT12 = makeEleTauPair(src,"mt_12","mt12MET"),

                              eleTauMvaCovMat00 = makeEleTauPair(src,"cov00","covMatrix00"),#FIXME
                              eleTauMvaCovMat10 = makeEleTauPair(src,"cov10","covMatrix10"),#FIXME
                              eleTauMvaCovMat01 = makeEleTauPair(src,"cov01","covMatrix01"),#FIXME
                              eleTauMvaCovMat11 = makeEleTauPair(src,"cov11","covMatrix11"),#FIXME

                              eleTauPt1 =  makeEleTauPair(src,"pt_1","leg1.pt"), 
                              eleTauPt2 =  makeEleTauPair(src,"pt_2","leg2.pt"), 
                              eleTauEta1 = makeEleTauPair(src,"eta_1","leg1.eta"),
                              eleTauEta2 = makeEleTauPair(src,"eta_2","leg2.eta"),
                              eleTauPhi1 = makeEleTauPair(src,"phi_1","leg1.phi"),
                              eleTauPhi2 = makeEleTauPair(src,"phi_2","leg2.phi"),

                              eleTauCharge = makeEleTauPair(src,"charge","charge"),
                              eleTauPt = makeEleTauPair(src,"pth","pt"),
                              eleTauDecayMode = makeEleTauPair(src,"tauDecayMode",'leg2.decayMode()'),

                              eleTauTopGenPt = makeEleTauPair(src,"topGenPt","topGenPt"),#FIXME
                              eleTauAntiTopGenPt = makeEleTauPair(src,"antiTopGenPt","antiTopGenPt"),#FIXME

                              eleTauEleTriggerMatch1 = makeEleTauPair(src,"hltEle32WPTightGsfTrackIsoFilter",
                                                                      'leg1.userFloat("hltEle32WPTightGsfTrackIsoFilter")'),
                              eleTauEleTriggerMatch2 = makeEleTauPair(src,"hltEle24erWPTightGsfTrackIsoFilterForTau",
                                                                      'leg1.userFloat("hltEle24erWPTightGsfTrackIsoFilterForTau")'),
                              eleTauEleTriggerMatch3 = makeEleTauPair(src,"hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30",
                                                                     'leg1.userFloat("hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30")'),
                              eleTauEleTriggerMatch4 = makeEleTauPair(src,"hltEle35noerWPTightGsfTrackIsoFilter",
                                                                     'leg1.userFloat("hltEle35noerWPTightGsfTrackIsoFilter")'),
                              eleTauEleTriggerMatch5 = makeEleTauPair(src,"hltSelectedPFTau30LooseChargedIsolationL1HLTMatched",
                                                                     'leg2.userFloat("hltSelectedPFTau30LooseChargedIsolationL1HLTMatched")'),
                              eleTauEleTriggerMatch6 = makeEleTauPair(src,"hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30_2",
                                                                     'leg2.userFloat("hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30")'),
                              eleTauEleTriggerMatch7 = makeEleTauPair(src,"hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30_1",
                                                                     'leg1.userFloat("hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30")'),

                              eleTauGenPt1 = makeEleTauPair(src,"genPt1",'p4Leg1gen().pt()'),
                              eleTauGenPt2 = makeEleTauPair(src,"genPt2",'p4Leg2gen().pt()'),
                              eleTauPdg1 = makeEleTauPair(src,"pdg1",'genPdg1()'),
                              eleTauPdg2 = makeEleTauPair(src,"pdg2",'genPdg2()'),
                              eleTauVisGenPt1 = makeEleTauPair(src,"genVisPt1",'p4VisLeg1gen().pt()'),
                              eleTauVisGenPt2 = makeEleTauPair(src,"genVisPt2",'p4VisLeg2gen().pt()'),
                              eleTauGenVisMass = makeEleTauPair(src,"genVisMass",'p4VisGen().M()'),
                              eleTauGenMassMatched = makeEleTauPair(src,"genFullMassMatched",'p4gen().M()'),
                              eleTauGenMass = makeEleTauPair(src,"fullGenMass",'genBosonMass()'),
                              eleTauGenBosonPt = makeEleTauPair(src,"genpT",'p4GenBoson().pt()'),
                              eleTauGenBosonMass = makeEleTauPair(src,"genMass",'p4GenBoson().M()'),
                              eleTauGenBosonPx = makeEleTauPair(src,"genpX",'p4GenBoson().px()'),
                              eleTauGenBosonPy = makeEleTauPair(src,"genpY",'p4GenBoson().py()'),
                              eleTauGenBosonVisPx = makeEleTauPair(src,"vispX",'p4GenBosonVis().px()'),
                              eleTauGenBosonVisPy = makeEleTauPair(src,"vispY",'p4GenBosonVis().py()'),

                              eleTauMass = makeEleTauPair(src,"m_vis","mass"), 

                              eleTauByOldDMMVAIsoTight = makeEleTauPair(src,"byTightIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByOldDMMVAIsoMedium = makeEleTauPair(src,"byMediumIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byMediumIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByOldDMMVAIsoVTight = makeEleTauPair(src,"byVTightIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVTightIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByOldDMMVAIsoVLoose = makeEleTauPair(src,"byVLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              #eleTauByOldDMMVAIsoVVLoose = makeEleTauPair(src,"byVVLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByOldDMMVAIsoLoose = makeEleTauPair(src,"byLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byLooseIsolationMVArun2v1DBoldDMwLT")'),

                              eleTauAgainstMuonLoose3 = makeEleTauPair(src,"againstMuonLoose3_2",'leg2.tauID("againstMuonLoose3")'),
                              eleTauAgainstMuonTight3 = makeEleTauPair(src,"againstMuonTight3_2",'leg2.tauID("againstMuonTight3")'),

                              eleTauagainstElectronMVA6Raw = makeEleTauPair(src,"againstElectronMVA6Raw_2",'leg2.tauID("againstElectronMVA6Raw")'),
                              eleTauagainstElectronMVA6category = makeEleTauPair(src,"againstElectronMVA6category_2",'leg2.tauID("againstElectronMVA6category")'),
                              eleTauAgainstEleVLooseMVA6 = makeEleTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              eleTauAgainstElectronLooseMVA6 = makeEleTauPair(src,"againstElectronLooseMVA6_2",'leg2.tauID("againstElectronLooseMVA6")'),
                              eleTauagainstElectronMediumMVA6 = makeEleTauPair(src,"againstElectronMediumMVA6_2",'leg2.tauID("againstElectronMediumMVA6")'),
                              eleTauagainstElectronTightMVA6 = makeEleTauPair(src,"againstElectronTightMVA6_2",'leg2.tauID("againstElectronTightMVA6")'),
                              eleTauagainstElectronVTightMVA6 = makeEleTauPair(src,"againstElectronVTightMVA6_2",'leg2.tauID("againstElectronVTightMVA6")')


   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)





#Tree for e+tau + MET final state
def addEleTauEventTree(process,name,src='eleTausSorted',fileout='analysis_eletau.root',srcLL='diElectronsOSSorted', srcU='TightMuons', srcE='TightElectrons'):
   process.TFileService = cms.Service("TFileService", fileName = cms.string(fileout) )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              genEvent = cms.InputTag('generator'),
                              coreCollections = cms.InputTag(src),
                              trigger = cms.PSet(
                                  pluginType = cms.string("TriggerFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerProcess),
                                  prescales = cms.InputTag("patTrigger"),
                                  paths      = cms.vstring(TriggerPaths)
                              ),
                              metfilter = cms.PSet(
                                  pluginType = cms.string("TriggerFilterFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerFilter),
                                  BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
                                  BadPFMuonFilter           = cms.InputTag("BadPFMuonFilter"),
                                  paths      = cms.vstring(
                                      "Flag_noBadMuons",
                                      "Flag_badMuons",
                                      "Flag_duplicateMuons",
                                      "Flag_HBHENoiseFilter",
                                      "Flag_HBHENoiseIsoFilter",
                                      "Flag_globalTightHalo2016Filter",
                                      "Flag_goodVertices",
                                      "Flag_eeBadScFilter",
                                      "Flag_EcalDeadCellTriggerPrimitiveFilter"
                                      )
                                  ),
 
                              pu = cms.PSet(
                                  pluginType = cms.string("PUFiller"),
                                  src        = cms.InputTag("slimmedAddPileupInfo"),
                                  tag        = cms.string("pu")
                              ),
                              cov = cms.PSet(
                                  pluginType = cms.string("METSignificanceFiller"),
                                  src        = cms.InputTag("METSignificance"),
                                  tag        = cms.string("metcov")
                              ),
                              PVsSync = cms.PSet(
                                  pluginType = cms.string("VertexSizeFiller"),
                                  src        = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                  #src        = cms.InputTag("primaryVertexFilter"),
                                  tag        = cms.string("npv")
                              ),
                              PVs = cms.PSet(
                                  pluginType = cms.string("VertexSizeFiller"),
                                  src        = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                  #src        = cms.InputTag("primaryVertexFilter"),
                                  tag        = cms.string("vertices")
                              ),


                              eTauPOG = makeEleTauPOGSF(src),
                              eTauEventWeight = makeEleTauEventWeight(src),
                              eTauEventWeightTmp = makeEleTauEventWeightTmp(src),
                              #eleTauNBTags = makeEleTauNBTag(src),
                              eleTauEffCSV = makeEleTauEffCSV(src),
                              eleTauCSVShape = makeEleTauCSVShape(src),
                              eleTauJES = makeEleTauVBFPair(src),
                              eTauGenMCMatch = makeEleTauGenMatch(src),

                              muonsSizeET = makeCollSize(srcU,"tightMuons"),
                              muonsSizeETVeto = makeCollSizeVeto(srcU,0,"extramuon_veto"),
                              electronsSizeET = makeCollSize(srcE,"tightElectrons"),
                              electronsSizeETVeto = makeCollSizeVeto(srcE, 1,"extraelec_veto"),

                              eleTauSize = makeCollSize(src,"nCands"),
                              eleTauOS = makeCollSizeOS(src,0,"os"),
                              eleEleSize = makeCollSize(srcLL,"diLeptons"),
                              eleEleSizeVeto = makeCollSizeVeto(srcLL,0,"dilepton_veto"),
                              genTaus = makeCollSize("genTauCands","genTaus"), #FIXME

                              eleTauDR = makeEleTauPair(src,"dR","dR12"), 
                              
                              tauSingleL1 =  makeEleTauPair(src,"tauSingleL1_2","leg2.userFloat('LooseIsoPFTau20_SingleL1')"), 
                              tauL1 =  makeEleTauPair(src,"tauL1_2","leg2.userFloat('LooseIsoPFTau20')"), 
                              tauMediumL1 =  makeEleTauPair(src,"tauMediumL1_2","leg2.userFloat('MediumIsoPFTau35_Trk_eta2p1')"),


                              tauNIsoTracks =  makeEleTauPair(src,"tauNIsoTracks","leg2.userFloat('nIsoTracks')"), 
                              eleTaunIsoGamma = makeEleTauPair(src,"nIsoGamma",'leg2.userFloat("nIsoGamma")'),
                              eleTaunIsoNeutral = makeEleTauPair(src,"nIsoNeutral",'leg2.userFloat("nIsoNeutral")'),


                              tauNMatchedSeg =  makeEleTauPair(src,"tauMuonNMatchedSeg","leg2.userFloat('muonNMatchedSeg')"), 
                              tauTauHadMatched = makeEleTauPair(src,"tauMuonMatched","leg2.userFloat('muonTauHadMatched')"),
                              tauLeadChargedHadrTrackPt = makeEleTauPair(src,"tauLeadChargedHadrTrackPt","leg2.userFloat('leadChargedHadrTrackPt')"),

                              eleTauCharge = makeEleTauPair(src,"charge","charge"),
                              eleTauCharge1 = makeEleTauPair(src,"q_1","leg1.charge"),
                              eleTauCharge2 = makeEleTauPair(src,"q_2","leg2.charge"),

                              eleTauPt = makeEleTauPair(src,"pth","pt"),
                              eleTauHT = makeEleTauPair(src,"ht","ht"),
                              eleTauMass = makeEleTauPair(src,"m_vis","mass"),
                              #eleTauSVPt = makeEleTauPair(src,"pt_sv","svPt"),
                              #eleTauSVMass = makeEleTauPair(src,"m_sv","svMass"),
                              eleTaulVeto = makeEleTauPair(src,"lVeto","lVeto"),

                              eleTauFullPt = makeEleTauPair(src,"fullPt","fullPt"),
                              eleTauEta = makeEleTauPair(src,"fullEta","fullEta"),
                              eleTauPhi = makeEleTauPair(src,"fullPhi","fullPhi"),
                              eleTauE = makeEleTauPair(src,"fullEnergy","fullEnergy"),

                              eleTauPt1 =  makeEleTauPair(src,"pt_1","leg1.pt"), 
                              eleTauPt2 =  makeEleTauPair(src,"pt_2","leg2.pt"), 
                              eleTauEta1 = makeEleTauPair(src,"eta_1","leg1.eta"),
                              eleTauSCEta1 = makeEleTauPair(src,"SCeta_1","leg1.superCluster().eta()"),
                              eleTauEta2 = makeEleTauPair(src,"eta_2","leg2.eta"),
                              eleTauPhi1 = makeEleTauPair(src,"phi_1","leg1.phi"),
                              eleTauPhi2 = makeEleTauPair(src,"phi_2","leg2.phi"),

                              eleTauMET1 = makeEleTauMET(src,"slimmedMETs","pf"),
                              eleTauMET2 = makeEleTauMET(src,"slimmedMETsPuppi","puppi"),
                              eleTauMET3 = makeEleTauMET(src,"MVAMET:MVAMET","mva"),

                              eleTauMETJUncertUp = makeEleTauMETUncert(src,"slimmedMETs","pf","JetUp"),
                              eleTauMETJUncertDown = makeEleTauMETUncert(src,"slimmedMETs","pf","JetDown"),
 
                              eleTauMETUncertUp = makeEleTauMETUncert(src,"slimmedMETs","pf","EnUp"),
                              eleTauMETUncertDown = makeEleTauMETUncert(src,"slimmedMETs","pf","EnDown"), 

                              eleTauMET = makeEleTauPair(src,"met","met.pt()"),
                              eleTauMETPhi = makeEleTauPair(src,"metphi","met.phi()"),
                              eleTauMETx = makeEleTauPair(src,"met_ex","met.px()"),
                              eleTauMETy = makeEleTauPair(src,"met_ey","met.py()"),
                              eleTauCovMat00 = makeEleTauPair(src,"cov00","covMatrix00"),
                              eleTauCovMat10 = makeEleTauPair(src,"cov10","covMatrix10"),
                              eleTauCovMat01 = makeEleTauPair(src,"cov01","covMatrix01"),
                              eleTauCovMat11 = makeEleTauPair(src,"cov11","covMatrix11"),

                              eleTauMT = makeEleTauPair(src,"mt12","mt12MET"),
                              eleTauMT1 = makeEleTauPair(src,"mt_1","mt1MET"),
                              eleTauMT2 = makeEleTauPair(src,"mt_2","mt2MET"),

                              eleTauTopGenPt = makeEleTauPair(src,"topGenPt","topGenPt"),
                              eleTauAntiTopGenPt = makeEleTauPair(src,"antiTopGenPt","antiTopGenPt"),

                              #BTAGS AND JETS
                              eleTauVBFDEta = makeEleTauPair(src,"vbfDEta","vbfDEta"),
                              eleTauVBFDPhi = makeEleTauPair(src,"vbfDPhi","vbfDPhi"),
                              eleTauVBFMass = makeEleTauPair(src,"mjj","vbfMass"), #vbfMass
                              eleTauVBFMass2 = makeEleTauPair(src,"vbfMass","vbfMass"), #vbfMass
                              eleTauVBFJets20 = makeEleTauPair(src,"njetingap20","vbfNJetsGap20"),
                              eleTauVBFJets30 = makeEleTauPair(src,"njetingap","vbfNJetsGap30"),

                              eleTauDZVZ = makeEleTauPair(src,"dz_vz",'abs(leg1.vz-leg2.vz)'),
                              eleTauDPhi = makeEleTauPair(src,"dPhi12",'dPhi12'),
                              eleTauDPhi1MET = makeEleTauPair(src,"dPhi1MET",'dPhi1MET'),
                              eleTauDPhi2MET = makeEleTauPair(src,"dPhi2MET",'dPhi2MET'),
                              eleTauPzeta = makeEleTauPair(src,"pZeta",'pZeta-1.5*pZetaVis'),#EO 
                              eleTauPZ = makeEleTauPair(src,"pzeta",'pZeta'),#EO
                              eleTauPZV = makeEleTauPair(src,"pzetavis",'pZetaVis'),#EO

                              #Trigger
                              eleTauEleTriggerMatch1 = makeEleTauPair(src,"hltEle32WPTightGsfTrackIsoFilter",
                                                                      'leg1.userFloat("hltEle32WPTightGsfTrackIsoFilter")'),
                              eleTauEleTriggerMatch2 = makeEleTauPair(src,"hltEle24erWPTightGsfTrackIsoFilterForTau",
                                                                      'leg1.userFloat("hltEle24erWPTightGsfTrackIsoFilterForTau")'),
                              eleTauEleTriggerMatch3 = makeEleTauPair(src,"hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30",
                                                                     'leg1.userFloat("hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30")'),
                              eleTauEleTriggerMatch4 = makeEleTauPair(src,"hltEle35noerWPTightGsfTrackIsoFilter",
                                                                     'leg1.userFloat("hltEle35noerWPTightGsfTrackIsoFilter")'),
                              eleTauEleTriggerMatch5 = makeEleTauPair(src,"hltSelectedPFTau30LooseChargedIsolationL1HLTMatched",
                                                                     'leg2.userFloat("hltSelectedPFTau30LooseChargedIsolationL1HLTMatched")'),
                              eleTauEleTriggerMatch6 = makeEleTauPair(src,"hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30_2",
                                                                     'leg2.userFloat("hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30")'),
                              eleTauEleTriggerMatch7 = makeEleTauPair(src,"hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30_1",
                                                                     'leg1.userFloat("hltOverlapFilterIsoEle24WPTightGsfLooseIsoPFTau30")'),

                              eleTauByOldDMMVAIsoRR1 = makeEleTauPair(src,"tau_idRaw2017v2",     'leg2.tauID("idRaw2017v2")'),
                              eleTauByOldDMMVAIsoRR2 = makeEleTauPair(src,"byVVLooseIsolationMVArun2017v2DBoldDMwLT2017", 'leg2.tauID("idVVLoose2017v2")'),
                              eleTauByOldDMMVAIsoRR3 = makeEleTauPair(src,"tau_idVLoose2017v2",  'leg2.tauID("idVLoose2017v2")'),
                              eleTauByOldDMMVAIsoRR4 = makeEleTauPair(src,"tau_idLoose2017v2",   'leg2.tauID("idLoose2017v2")'),
                              eleTauByOldDMMVAIsoRR5 = makeEleTauPair(src,"tau_idMed2017v2",     'leg2.tauID("idMed2017v2")'),
                              eleTauByOldDMMVAIsoRR6 = makeEleTauPair(src,"tau_idTight2017v2",   'leg2.tauID("idTight2017v2")'),
                              eleTauByOldDMMVAIsoRR7 = makeEleTauPair(src,"tau_idVTight2017v2",  'leg2.tauID("idVTight2017v2")'),
                              eleTauByOldDMMVAIsoRR8 = makeEleTauPair(src,"tau_idVVTight2017v2", 'leg2.tauID("idVVTight2017v2")'),

                              #Ele IDs and Isolation
                              eleTauRelPFIsoDB03 = makeEleTauPair(src,"iso_1",'leg1.userFloat("dBRelIso03")'),
                              eleTauRel2PFIsoDB03 = makeEleTauPair(src,"iso_2",'leg2.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),
                              eleTauRelPFIsoDB04 = makeEleTauPair(src,"iso04_1",'leg1.userFloat("dBRelIso")'),

                              eleTauDecayMode = makeEleTauPair(src,"tauDecayMode",'leg2.decayMode()'),
                              eleTauDecayFound = makeEleTauPair(src,"decayModeFinding_2",'leg2.tauID("decayModeFinding")'),
                              eleTauProngs = makeEleTauPair(src,"tauProngs",'leg2.signalChargedHadrCands.size()'),#see Decay Modes
                              eleTauHadMass = makeEleTauPair(src,"m_2",'leg2.mass()'),
                              eleTauHaddxy = makeEleTauPair(src,"dxy_2",'leg2.dxy()'),
                              eleTauHaddxy_Sig = makeEleTauPair(src,"dxy_Sig_2",'leg2.dxy_Sig()'),

                              #tauIDs
                              eleTauByOldDMMVAIsoTight = makeEleTauPair(src,"byTightIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1DBoldDMwLT")'),
                              eleTaubyTightIsolationMVArun2v1DBdR03oldDMwLT = makeEleTauPair(src,"byTightIsolationMVArun2v1DBdR03oldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1DBdR03oldDMwLT")'),
                              eleTaubyTightIsolationMVArun2v1PWoldDMwLT = makeEleTauPair(src,"byTightIsolationMVArun2v1PWoldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1PWoldDMwLT")'),
                              eleTaubyTightIsolationMVArun2v1PWdR03oldDMwLT = makeEleTauPair(src,"byTightIsolationMVArun2v1PWdR03oldDMwLT_2",'leg2.tauID("byTightIsolationMVArun2v1PWdR03oldDMwLT")'),

                              eleTauByOldDMMVAIsoMedium = makeEleTauPair(src,"byMediumIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byMediumIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByOldDMMVAIsoLoose = makeEleTauPair(src,"byLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byLooseIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByOldDMMVAIsoVLoose = makeEleTauPair(src,"byVLooseIsolationMVArun2v1DBoldDMwLT_2",'leg2.tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              eleTauByCharged = makeEleTauPair(src,"chargedIsoPtSum_2",'leg2.tauID("chargedIsoPtSum")'),
                              eleTauByNeutral = makeEleTauPair(src,"neutralIsoPtSum_2",'leg2.tauID("neutralIsoPtSum")'),
                              eleTauByPU = makeEleTauPair(src,"puCorrPtSum_2",'leg2.tauID("puCorrPtSum")'), 
                              eleTauAgainstMuonLoose3 = makeEleTauPair(src,"againstMuonLoose3_2",'leg2.tauID("againstMuonLoose3")'),
                              eleTauAgainstMuonTight3 = makeEleTauPair(src,"againstMuonTight3_2",'leg2.tauID("againstMuonTight3")'),

                              eleTauagainstElectronMVA6Raw = makeEleTauPair(src,"againstElectronMVA6Raw_2",'leg2.tauID("againstElectronMVA6Raw")'),
                              eleTauagainstElectronMVA6category = makeEleTauPair(src,"againstElectronMVA6category_2",'leg2.tauID("againstElectronMVA6category")'),
                              eleTauAgainstEleVLooseMVA6 = makeEleTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              eleTauAgainstElectronLooseMVA6 = makeEleTauPair(src,"againstElectronLooseMVA6_2",'leg2.tauID("againstElectronLooseMVA6")'),
                              eleTauagainstElectronMediumMVA6 = makeEleTauPair(src,"againstElectronMediumMVA6_2",'leg2.tauID("againstElectronMediumMVA6")'),
                              eleTauagainstElectronTightMVA6 = makeEleTauPair(src,"againstElectronTightMVA6_2",'leg2.tauID("againstElectronTightMVA6")'),
                              eleTauagainstElectronVTightMVA6 = makeEleTauPair(src,"againstElectronVTightMVA6_2",'leg2.tauID("againstElectronVTightMVA6")'),

                              eleTauByOldDMMVAIso = makeEleTauPair(src,"byIsolationMVArun2v1DBoldDMwLTraw_2",'leg2.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),
                              eleTaubyIsolationMVArun2v1DBdR03oldDMwLTraw = makeEleTauPair(src,"byIsolationMVArun2v1DBdR03oldDMwLTraw_2",'leg2.tauID("byIsolationMVArun2v1DBdR03oldDMwLTraw")'),
                              eleTaubyIsolationMVArun2v1PWdR03oldDMwLTraw = makeEleTauPair(src,"byIsolationMVArun2v1PWdR03oldDMwLTraw_2",'leg2.tauID("byIsolationMVArun2v1PWdR03oldDMwLTraw")'),
                              eleTaubyIsolationMVArun2v1PWoldDMwLTraw = makeEleTauPair(src,"byIsolationMVArun2v1PWoldDMwLTraw_2",'leg2.tauID("byIsolationMVArun2v1PWoldDMwLTraw")'),
                              eleTaubyPhotonPtSumOutsideSignalCone = makeEleTauPair(src,"byPhotonPtSumOutsideSignalCone_2",'leg2.tauID("byPhotonPtSumOutsideSignalCone")'),
                              eleTauchargedIsoPtSumdR03 = makeEleTauPair(src,"chargedIsoPtSumdR03_2",'leg2.tauID("chargedIsoPtSumdR03")'),
                              eleTauneutralIsoPtSumWeight = makeEleTauPair(src,"neutralIsoPtSumWeight_2",'leg2.tauID("neutralIsoPtSumWeight")'),
                              eleTauneutralIsoPtSumWeightdR03 = makeEleTauPair(src,"neutralIsoPtSumWeightdR03_2",'leg2.tauID("neutralIsoPtSumWeightdR03")'),
                              eleTauneutralIsoPtSumdR03 = makeEleTauPair(src,"neutralIsoPtSumdR03_2",'leg2.tauID("neutralIsoPtSumdR03")'),
                              eleTauphotonPtSumOutsideSignalCone = makeEleTauPair(src,"photonPtSumOutsideSignalCone_2",'leg2.tauID("photonPtSumOutsideSignalCone")'),
                              eleTauphotonPtSumOutsideSignalConedR03 = makeEleTauPair(src,"photonPtSumOutsideSignalConedR03_2",'leg2.tauID("photonPtSumOutsideSignalConedR03")'),
                              eleTaufootprintCorrection = makeEleTauPair(src,"footprintCorrection_2",'leg2.tauID("footprintCorrection")'),
                              eleTaufootprintCorrectiondR03 = makeEleTauPair(src,"footprintCorrectiondR03_2",'leg2.tauID("footprintCorrectiondR03")'),

                              eleTauMVANonTrig80 = makeEleTauPair(src,"id_e_mva_nt_80_1",'leg1.userFloat("eleMVAIDnonIso80")'),#CHECKME #rename
                              eleTauMVANonTrig90 = makeEleTauPair(src,"id_e_mva_nt_90_1",'leg1.userFloat("eleMVAIDnonIso90")'),#CHECKME #rename
                              #eleTauCBIDVeto = makeEleTauPair(src,"id_e_cut_veto_1",'leg1.userFloat("CBIDVeto")'),#CHECKME #rename
                              #eleTauCBIDLoose = makeEleTauPair(src,"id_e_cut_loose_1",'leg1.userFloat("CBIDLoose")'),#CHECKME #rename
                              #eleTauCBIDMedium = makeEleTauPair(src,"id_e_cut_medium_1",'leg1.userFloat("CBIDMedium")'),#CHECKME #rename
                              #eleTauCBIDTight = makeEleTauPair(src,"id_e_cut_tight_1",'leg1.userFloat("CBIDTight")'),#CHECKME #rename

                              eleTauEleDZ = makeEleTauPair(src,"dZ_1","leg1.userFloat('dZ')"),
                              eleTauTauDZ = makeEleTauPair(src,"dZ_2","leg2.userFloat('taudZ')"),
                              eleTauEleDXY = makeEleTauPair(src,"d0_1","leg1.userFloat('dXY')"),
                              eleTauTauDXY = makeEleTauPair(src,"d0_2","leg2.userFloat('taudXY')"),
                              eleTauConversion = makeEleTauPair(src,"eleConversion","leg1.userInt('eleConversion')"),
                              eleTauPassConversion = makeEleTauPair(src,"ePassConversion",'leg1.passConversionVeto()'),

                              eleTauGenPt1 = makeEleTauPair(src,"genPt1",'p4Leg1gen().pt()'),
                              eleTauGenPt2 = makeEleTauPair(src,"genPt2",'p4Leg2gen().pt()'),
                              eleTauPdg1 = makeEleTauPair(src,"pdg1",'genPdg1()'),
                              eleTauPdg2 = makeEleTauPair(src,"pdg2",'genPdg2()'),
                              eleTauVisGenPt1 = makeEleTauPair(src,"genVisPt1",'p4VisLeg1gen().pt()'),
                              eleTauVisGenPt2 = makeEleTauPair(src,"genVisPt2",'p4VisLeg2gen().pt()'),
                              eleTauGenVisMass = makeEleTauPair(src,"genVisMass",'p4VisGen().M()'),
                              eleTauGenMassMatched = makeEleTauPair(src,"genFullMassMatched",'p4gen().M()'),
                              eleTauGenBosonMass = makeEleTauPair(src,"genMass",'p4GenBoson().M()'),
                              eleTauGenBosonPt = makeEleTauPair(src,"genpT",'p4GenBoson().pt()'),
                              eleTauGenBosonPx = makeEleTauPair(src,"genpX",'p4GenBoson().px()'),
                              eleTauGenBosonPy = makeEleTauPair(src,"genpY",'p4GenBoson().py()'),
                              eleTauGenBosonVisPx = makeEleTauPair(src,"vispX",'p4GenBosonVis().px()'),
                              eleTauGenBosonVisPy = makeEleTauPair(src,"vispY",'p4GenBosonVis().py()'),
                              eleTauGenMass = makeEleTauPair(src,"fullGenMass",'genBosonMass()'),

                              eleTauGenIsPrompt1 = makeEleTauPair(src,"isPrompt1",'isPrompt1()'),
                              eleTauGenIsPromptFS1 = makeEleTauPair(src,"isPromptFS1",'isPromptFS1()'),
                              eleTauGenIsDirectTauDecay1 = makeEleTauPair(src,"isTauDecay1",'isDirectPromptTauDecayProduct1()'),
                              eleTauGenIsDirectTauDecayFS1 = makeEleTauPair(src,"isTauDecayFS1",'isDirectPromptTauDecayProductFS1()'),
                              eleTauGenIsPrompt2 = makeEleTauPair(src,"isPrompt2",'isPrompt2()'),
                              eleTauGenIsPromptFS2 = makeEleTauPair(src,"isPromptFS2",'isPromptFS2()'),
                              eleTauGenIsDirectTauDecay2 = makeEleTauPair(src,"isTauDecay2",'isDirectPromptTauDecayProduct2()'),
                              eleTauGenIsDirectTauDecayFS2 = makeEleTauPair(src,"isTauDecayFS2",'isDirectPromptTauDecayProductFS2()'),

                              #Jets
                              eleTauJetsPt20nbtag = makeEleTauJetCountPair(src,"nbtag",'userFloat("isbtagged")&&pt()>20&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              eleTauJetsPt20nbtagNoSF = makeEleTauJetCountPair(src,"nbtagNoSF",'pt()>20&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              eleTauJetsPt20nbtagLoose = makeEleTauJetCountPair(src,"nbtagLooseNoSF",'pt()>20&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.5426'),
                              eleTauJetsPt30nbtagNoSF = makeEleTauJetCountPair(src,"nbtag30NoSF",'pt()>30&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              eleTauJetsPt30nbtag = makeEleTauJetCountPair(src,"nbtag30",'userFloat("isbtagged")&&pt()>30&&abs(eta)<2.4&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941'),
                              eleTauJetsPt30njets = makeEleTauJetCountPair(src,"njets",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")'),
                              eleTauJetsPt30njetsLoosepu = makeEleTauJetCountPair(src,"njetspuID",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")&&!userFloat("puIDLoose")'),
                              eleTauJetsPt20njets = makeEleTauJetCountPair(src,"njetspt20",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")'),
                              eleTauJetsPt20njetsLoosepu = makeEleTauJetCountPair(src,"njetspt20puID",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")&&!userFloat("puIDLoose")'),

                              eleTauJet1PtPtSort = makeEleTauPtPair(src,"jpt_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','pt()',0),
                              eleTauJet2PtPtSort = makeEleTauPtPair(src,"jpt_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','pt()',1),
                              eleTauJet1MVAPtSort = makeEleTauPtPair(src,"jmva_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")',"userFloat('pileupJetId:fullDiscriminant')",0),
                              eleTauJet2MVAPtSort = makeEleTauPtPair(src,"jmva_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")',"userFloat('pileupJetId:fullDiscriminant')",1),
                              eleTauJet1PFIDPtSort = makeEleTauPtPair(src,"jpfid_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("idTight")',0),
                              eleTauJet2PFIDPtSort = makeEleTauPtPair(src,"jpfid_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("idTight")',1),
                              eleTauJet1PUIDPtSort = makeEleTauPtPair(src,"jpuid_1",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("puID")',0),
                              eleTauJet2PUIDPtSort = makeEleTauPtPair(src,"jpuid_2",'abs(eta())<4.7&&pt()>20&&userFloat("idTight")','userFloat("puID")',1),
                              eleTauJet1EtaPtSort = makeEleTauPtPair(src,"jeta_1",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','eta()',0),
                              eleTauJet2EtaPtSort = makeEleTauPtPair(src,"jeta_2",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','eta()',1),
                              eleTauJet1PhiPtSort = makeEleTauPtPair(src,"jphi_1",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','phi()',0),
                              eleTauJet2PhiPtSort = makeEleTauPtPair(src,"jphi_2",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','phi()',1),
                              eleTauJet1CSVPtSort = makeEleTauPtPair(src,"jcsv_1",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',0),
                              eleTauJet2CSVPtSort = makeEleTauPtPair(src,"jcsv_2",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',1),
                              eleTauJet1MedIdPtSort = makeEleTauPtPair(src,"jtlvID_1",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','userFloat("idTightLepVeto")',0),
                              eleTauJet2MedIdPtSort = makeEleTauPtPair(src,"jtlvID_2",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','userFloat("idTightLepVeto")',1),
                              eleTauJet1TightIdPtSort = makeEleTauPtPair(src,"jtightID_1",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','userFloat("idTight")',0),
                              eleTauJet2TightIdPtSort = makeEleTauPtPair(src,"jtightID_2",'abs(eta())<4.7&&pt>20&&userFloat("idTight")','userFloat("idTight")',1),

                              eleTauBJet1PtPtSort = makeEleTauPtPair(src,"bpt_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','pt()',0),
                              eleTauBJet2PtPtSort = makeEleTauPtPair(src,"bpt_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','pt()',1),
                              eleTauBJet1MVAPtSort = makeEleTauPtPair(src,"bmva_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941',"userFloat('pileupJetId:fullDiscriminant')",0),
                              eleTauBJet2MVAPtSort = makeEleTauPtPair(src,"bmva_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941',"userFloat('pileupJetId:fullDiscriminant')",1),
                              eleTauBJet1PFIDPtSort = makeEleTauPtPair(src,"bpfid_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("idTight")',0),
                              eleTauBJet2PFIDPtSort = makeEleTauPtPair(src,"bpfid_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("idTight")',1),
                              eleTauBJet1PUIDPtSort = makeEleTauPtPair(src,"bpuid_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("puID")',0),
                              eleTauBJet2PUIDPtSort = makeEleTauPtPair(src,"bpuid_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','userFloat("puID")',1),
                              eleTauBJet1EtaPtSort = makeEleTauPtPair(src,"beta_1",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','eta()',0),
                              eleTauBJet2EtaPtSort = makeEleTauPtPair(src,"beta_2",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','eta()',1),
                              eleTauBJet1PhiPtSort = makeEleTauPtPair(src,"bphi_1",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','phi()',0),
                              eleTauBJet2PhiPtSort = makeEleTauPtPair(src,"bphi_2",'abs(eta())<2.4&&pt>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','phi()',1),
                              eleTauBJet1CSVPtSort = makeEleTauPtPair(src,"bcsv_1",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',0),
                              eleTauBJet2CSVPtSort = makeEleTauPtPair(src,"bcsv_2",'abs(eta())<2.4&&pt()>20&&userFloat("idTight")&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4941','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',1),


                              eleTauJetsPt20TagMatch = makeEleTauJetCountPair(src,"nTaggableJetsPt20Matched",'pt()>20&&abs(eta)<2.4&&abs(partonFlavour)==5'),
                              eleTauJetsPt20TagNoMatch = makeEleTauJetCountPair(src,"nTaggableJetsPt20NotMatched",'pt()>30&&abs(eta)<2.4&&abs(partonFlavour)!=5'),
                              eleTauFirstJetShape = makeLTauGeneric("PATEleTauPairHighestPtJetVarFiller",src,"highestJetShape",'userFloat("ptRMS")'),
                              eleTauFirstJetCSV = makeLTauGeneric("PATEleTauPairHighestPtJetVarFiller",src,"highestJetBTagCSV",'bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")'),

                              eeDR = makeLTauGeneric("PATElePairFiller",srcLL,"diLeptonDR","dR12"),#FIXME

                              eleTauLHEProduct2 = cms.PSet(
                                  pluginType = cms.string("LHEProductFiller"),
                                  src        = cms.InputTag("externalLHEProducer"),
                                  tag        = cms.string("LHEProduct"),
                              ),#WHAT IS THIS
                              eleTauEmbedPtWeight = cms.PSet(
                                  pluginType = cms.string("GenFilterInfoWeightFiller"),
                                  src        = cms.InputTag("generator"),
                                  tag        = cms.string("aMCNLO_weight"),
                              ),
                              higgsPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("higgsPt"),
                                  method     = cms.string('pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              eleTauEmbedPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("embeddedPt"),#CHECKME
                                  method     = cms.string("pt"),
                                  leadingOnly=cms.untracked.bool(False)
                              ),
                              eleTauEmbedEta = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("embeddedEta"),#CHECKME
                                  method     = cms.string("eta"),
                                  leadingOnly=cms.untracked.bool(False)
                              )
   )

   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)


