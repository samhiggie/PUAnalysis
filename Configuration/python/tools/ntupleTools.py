import FWCore.ParameterSet.Config as cms

from PUAnalysis.Configuration.tools.analysisTools import TriggerPaths,TriggerRes,TriggerProcess,TriggerFilter


from RecoMET.METFilters.BadChargedCandidateFilter_cfi import *


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


##start diTaus

def makeDiTauVBFPair(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairVBFVariableFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet
def makeDiTauVBFPair_FSA(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairVBFVariableFiller_FSA"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeDiTauPair(sourceDiTaus,tagName,methodName,leadingOnly=True):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
         leadingOnly = cms.untracked.bool(leadingOnly)
   )
   return PSet

def makeDiTauCSVPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairCSVJetVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet

def makeDiTauPtNoPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairPtJetVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet

def makeDiTauPtPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairPtJetPairVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
   )
   return PSet

def makeDiTauEventWeight(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairWeightFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string("Mu"),
         isMuon      = cms.bool(True)
   )
   return PSet

def makeDiTauPairZPTReweight(sourceDiTaus,tag,genMassZ,genPtZ):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairZWeightFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tag),
         massZ       = cms.string(genMassZ),
         ptZ         = cms.string(genPtZ)
   )
   return PSet


def makeEmbeddedEventSF(sourceDiTaus,runSF,tag,genPt1,genEta1,genPt2,genEta2):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairEmbeddedSFFiller"),
         src         = cms.InputTag(sourceDiTaus),
         isEmbedded  = cms.bool(runSF),
         tag         = cms.string(tag),
         pt1          = cms.string(genPt1),
         eta1         = cms.string(genEta1),
         pt2          = cms.string(genPt2),
         eta2         = cms.string(genEta2)

   )
   return PSet

def makeEmbeddedTriggerMatch(sourceDiTaus,runSF,genPt1,genEta1,genPhi1,genPt2,genEta2,genPhi2,triggerfilter):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairEmbeddedTriggerFilterFiller"),
         src         = cms.InputTag(sourceDiTaus),
         isEmbedded  = cms.bool(runSF),
         pt_1          = cms.string(genPt1),
         eta_1         = cms.string(genEta1),
         phi_1          = cms.string(genPhi1),
         pt_2          = cms.string(genPt2),
         eta_2         = cms.string(genEta2),
         phi_2          = cms.string(genPhi2),
         triggerFilter  = cms.string(triggerfilter), 
         triggerBits   = cms.InputTag("TriggerResults","","SIMembedding"),
         objects = cms.InputTag("slimmedPatTrigger")

   )
   return PSet

def makeDiTauGenMatch(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairGenMCMatching"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeDiTauNBTag(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairNBTagFiller"),
         src         = cms.InputTag(sourceDiTaus),
         doEffMap      = cms.bool(True)
   )
   return PSet

def makeDiTauEffCSV(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairEffCSVFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet

def makeDiTauCSVShape(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairCSVReweightFiller"),
         src         = cms.InputTag(sourceDiTaus)
   )
   return PSet


def makeDiTauJetCountPair(sourceDiTaus,tagName,methodName,leadingOnly=True):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairJetCountFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         method      = cms.string(methodName),
         leadingOnly = cms.untracked.bool(leadingOnly)
   )
   return PSet

def makeDiTauMETUncert(sourceDiTaus, sourceMET, prefix, shift):
   PSet = cms.PSet(
         pluginType  = cms.string("PATDiTauPairMETUncertaintyFiller"),
         src         = cms.InputTag(sourceDiTaus),
         met         = cms.InputTag(sourceMET),
         tag         = cms.string(prefix),
         uncert      = cms.string(shift)  #EnUp or EnDown Available
   )
   return PSet
###finish ditaus
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

def makeMuTauPtNoPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairPtJetVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
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

def makeMuTauEventWeight(sourceDiTaus):
   PSet = cms.PSet(
         pluginType  = cms.string("PATMuTauPairWeightFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string("Mu"),
         isMuon      = cms.bool(True)
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

def makeEleTauPtNoPair(sourceDiTaus,tagName,cutName,methodName,rank):
   PSet = cms.PSet(
         pluginType  = cms.string("PATEleTauPairPtJetVarFiller"),
         src         = cms.InputTag(sourceDiTaus),
         tag         = cms.string(tagName),
         cut         = cms.string(cutName),
         method      = cms.string(methodName),
         rank = cms.untracked.double(rank)
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

def makeHiggsClassification(srcName):
   PSet = cms.PSet(
        pluginType = cms.string("HiggsClassificationFiller"),
        src= cms.InputTag(srcName)
   )
   return PSet


def addDiTauEventTree(process,name,src = 'diTausOS', srcLL = 'diMuonsOSSorted', srcU='TightMuons', srcE='TightElectrons',triggerCollection='HLT', isEmbedded=False, isJHU=False):
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis_TauTau.root") )
   eventTree = cms.EDAnalyzer('EventTreeMaker',
                              genEvent = cms.InputTag('generator'),
                              coreCollections = cms.InputTag(src),
                               trigger = cms.PSet(
                                   pluginType = cms.string("TriggerFiller"),
			           src        = cms.InputTag("TriggerResults","",triggerCollection),
			           prescales = cms.InputTag("patTrigger"),
                                   paths      = cms.vstring(TriggerPaths)
                               ),
                               pu = cms.PSet(
                                   pluginType = cms.string("PUFiller"),
                                   src        = cms.InputTag("slimmedAddPileupInfo"),
                                   tag        = cms.string("pu")
                                   #samplename        = cms.string(sampleName)
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
                              diTauGenMCMatch = makeDiTauGenMatch(src),
                              metfilter = cms.PSet(
                                  pluginType = cms.string("TriggerFilterFiller"),
                                  src = cms.InputTag(TriggerRes,"",TriggerFilter),
                                  BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
                                  BadPFMuonFilter           = cms.InputTag("BadPFMuonFilter"),
                                  paths      = cms.vstring(
                                      "Flag_noBadMuons",
                                      "Flag_HBHENoiseFilter",
                                      "Flag_HBHENoiseIsoFilter",
                                      "Flag_globalTightHalo2016Filter",
                                      "Flag_goodVertices",
                                      "Flag_eeBadScFilter",
                                      "Flag_EcalDeadCellTriggerPrimitiveFilter"
                                      )
                              ),
                              diTauMETUncertUp = makeDiTauMETUncert(src,"slimmedMETs","pf","EnUp"),
                              diTauMETUncertDown = makeDiTauMETUncert(src,"slimmedMETs","pf","EnDown"),

                              diTauMETJUncertUp = makeDiTauMETUncert(src,"slimmedMETs","pf","JetUp"),
                              diTauMETJUncertDown = makeDiTauMETUncert(src,"slimmedMETs","pf","JetDown"),

                              diTauPt1 =  makeDiTauPair(src,"pt_1","leg1.pt"),
                              diTauPt2 =  makeDiTauPair(src,"pt_2","leg2.pt"), 
                              diTauEta1 = makeDiTauPair(src,"eta_1","leg1.eta"),
                              diTauEta2 = makeDiTauPair(src,"eta_2","leg2.eta"),
                              diTauPhi1 = makeDiTauPair(src,"phi_1","leg1.phi"),
                              diTauPhi2 = makeDiTauPair(src,"phi_2","leg2.phi"),
                              diTauHadMass1 = makeDiTauPair(src,"m_1",'leg1.mass()'),
                              diTauHadMass2 = makeDiTauPair(src,"m_2",'leg2.mass()'),
                              diTauCharge = makeDiTauPair(src,"charge","charge"),
                              q_1 = makeDiTauPair(src,"q_1","leg1.charge"),
                              q_2 = makeDiTauPair(src,"q_2","leg2.charge"),
                              diTauPt = makeDiTauPair(src,"pth","pt"),#FILLED
                              diTauHT = makeDiTauPair(src,"ht","ht"),#FILLED
                              diTauMass = makeDiTauPair(src,"m_vis","mass"),#FILLED
                              #diTauSVPt = makeDiTauPair(src,"pt_sv","svPt"),#FILLEDATLATERSTAGE
                              #diTauSVMass = makeDiTauPair(src,"m_sv","svMass"),#FILLEDATLATERSTAGE
			      diTaulVeto = makeDiTauPair(src,"lVeto","lVeto"),
		              diTauTopGenPt = makeDiTauPair(src,"topGenPt","topGenPt"),#FIXME
		              diTauAntiTopGenPt = makeDiTauPair(src,"antiTopGenPt","antiTopGenPt"),#FIXM

                              diTauFullPt = makeDiTauPair(src,"fullPt","fullPt"),#FILLED
                              diTauEta = makeDiTauPair(src,"fullEta","fullEta"),#FILLED
                              diTauPhi = makeDiTauPair(src,"fullPhi","fullPhi"),#FILLED
                              diTauE = makeDiTauPair(src,"fullEnergy","fullEnergy"),#FILLED
                              diTauMET = makeDiTauPair(src,"met","met.pt()"),#FILLED
                              diTauMETPhi = makeDiTauPair(src,"metphi","met.phi()"),#FILLED

                              diTauMT = makeDiTauPair(src,"mt12","mt12MET"),#FILLED
                              diTauMT1 = makeDiTauPair(src,"mt_1","mt1MET"),#FILLED
                              diTaupfMT1 = makeDiTauPair(src,"pfmt_1","mt1MET"),#FILLED
                              diTauMT2 = makeDiTauPair(src,"mt_2","mt2MET"),#FILLED
                              diTaupfMT2 = makeDiTauPair(src,"pfmt_2","mt2MET"),#FILLED
                              

			      diTauMassLL = makeLTauGeneric("PATMuPairFiller",srcLL,"LLmass","mass"),
                              diTauPt1LL =  makeLTauGeneric("PATMuPairFiller",srcLL,"LLpt_1","leg1.pt"), #FILLED
                              diTauPt2LL =  makeLTauGeneric("PATMuPairFiller",srcLL,"LLpt_2","leg2.pt"), #FILLED
                              diTauEta1LL = makeLTauGeneric("PATMuPairFiller",srcLL,"LLeta_1","leg1.eta"),#FILLED
                              diTauEta2LL = makeLTauGeneric("PATMuPairFiller",srcLL,"LLeta_2","leg2.eta"),#FILLED
                              diTauPhi1LL = makeLTauGeneric("PATMuPairFiller",srcLL,"LLphi_1","leg1.phi"),#FILLED
                              diTauPhi2LL = makeLTauGeneric("PATMuPairFiller",srcLL,"LLphi_2","leg2.phi"),#FILLED
                              #diTauEffCSV = makeDiTauEffCSV(src),  ##need to put csv eff back in
                              #diTauCSVShape = makeDiTauCSVShape(src), ## need to put csv shape back in
                              diTauJES = makeDiTauVBFPair(src),#FILLED
                              #diTauJES_FSA = makeDiTauVBFPair_FSA(src),#FILLED

                              diTauSize = makeCollSize(src,"nCands"),
                              diTauOS = makeCollSizeOS(src,0,"os"),
                              genTaus = makeCollSize("genTauCands","genTaus"), 
                              muMuSize = makeCollSize(srcLL,"diLeptons"),#CHECKME
                              muMuSizeVeto = makeCollSizeVeto(srcLL,0,"dilepton_veto"),#CHECKME
                              muonsSizeMT = makeCollSize(srcU,"tightMuons"),#FILLED
                              muonsSizeMTVeto = makeCollSizeVeto(srcU,0,"extramuon_veto"),#FILLED
                              electronsSizeMT = makeCollSize(srcE,"tightElectrons"),#FILLED
                              electronsSizeMTVeto = makeCollSizeVeto(srcE,0,"extraelec_veto"),#FILLED
                              #tauNIsoTracks =  makeDiTauPair(src,"tauNIsoTracks","leg2.userFloat('nIsoTracks')"), #FILLED
                              #tauNMatchedSeg =  makeDiTauPair(src,"tauMuonNMatchedSeg","leg2.userFloat('muonNMatchedSeg')"),#FILLED
                              #tauTauHadMatched = makeDiTauPair(src,"tauMuonMatched","leg2.userFloat('muonTauHadMatched')"),#FILLED
                              #tauLeadChargedHadrTrackPt = makeDiTauPair(src,"tauLeadChargedHadrTrackPt","leg2.userFloat('leadChargedHadrTrackPt')"),
                              diTauDecayModeLeg1 = makeDiTauPair(src,"decayMode_1",'leg1.decayMode()'),
                              diTauDecayModeLeg2 = makeDiTauPair(src,"decayMode_2",'leg2.decayMode()'),

                              diTauHLTMatchHLTLeg1     = makeDiTauPair(src,"hltHpsMed35_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau35TrackPt1MediumChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTPLeg1     = makeDiTauPair(src,"hltHpsMedTP35_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau35TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              diTauHLTMatchHLT40Leg1     = makeDiTauPair(src,"hltHpsMed40_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau40TrackPt1MediumChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTP40Leg1     = makeDiTauPair(src,"hltHpsMedTP40_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau40TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg")'),

                              diTauHLTMatchHLTTightLeg1     = makeDiTauPair(src,"hltHpsTight35_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau35TrackPt1TightChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTightTPLeg1     = makeDiTauPair(src,"hltHpsTightTP35_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              diTauHLTMatchHLTTight40Leg1     = makeDiTauPair(src,"hltHpsTight40_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau40TrackPt1TightChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTightTP40Leg1     = makeDiTauPair(src,"hltHpsTightTP40_1",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltHpsDoublePFTau40TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")'),

                              diTauHLTMatchHLTLeg2     = makeDiTauPair(src,"hltHpsMed35_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau35TrackPt1MediumChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTPLeg2     = makeDiTauPair(src,"hltHpsMedTP35_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau35TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              diTauHLTMatchHLT40Leg2     = makeDiTauPair(src,"hltHpsMed40_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau40TrackPt1MediumChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTP40Leg2     = makeDiTauPair(src,"hltHpsMedTP40_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau40TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg")'),

                              diTauHLTMatchHLTTightLeg2     = makeDiTauPair(src,"hltHpsTight35_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau35TrackPt1TightChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTightTPLeg2     = makeDiTauPair(src,"hltHpsTightTP35_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              diTauHLTMatchHLTTight40Leg2     = makeDiTauPair(src,"hltHpsTight40_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau40TrackPt1TightChargedIsolationDz02Reg")'),
                              diTauHLTMatchHLTTightTP40Leg2     = makeDiTauPair(src,"hltHpsTightTP40_2",
                                                                       methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltHpsDoublePFTau40TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              #diTauHLTMatchHLTLeg1     = makeDiTauPair(src,"hltTight35_1",
                              #                                         methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              #diTauHLTMatchHLTCombLeg1 = makeDiTauPair(src,"hltMed40_1",
                              #                                         methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltDoublePFTau40TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              #diTauHLTMatchHLTTight40Leg1 = makeDiTauPair(src,"hltTight40_1",
                              #                                         methodName = "1" if isEmbedded or isJHU else 'leg1.userFloat("hltDoublePFTau40TrackPt1TightChargedIsolationDz02Reg")'),
                              #diTauHLTMatchHLTLeg2     = makeDiTauPair(src,"hltTight35_2",
                              #                                         methodName = "1" if isEmbedded or isJHU else'leg2.userFloat("hltDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              #diTauHLTMatchHLTCombLeg2 = makeDiTauPair(src,"hltMed40_2",
                              #                                         methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltDoublePFTau40TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg")'),
                              #diTauHLTMatchHLTTight40Leg2 = makeDiTauPair(src,"hltTight40_2",
                              #                                         methodName = "1" if isEmbedded or isJHU else 'leg2.userFloat("hltDoublePFTau40TrackPt1TightChargedIsolationDz02Reg")'),

                              diTauAgainstMuonTight3Leg1 = makeDiTauPair(src,"againstMuonTight3_1",'leg1.tauID("againstMuonTight3")'),
                              diTauAgainstMuonTight3Leg2 = makeDiTauPair(src,"againstMuonTight3_2",'leg2.tauID("againstMuonTight3")'),
                              diTauAgainstMuonLoose3Leg1 = makeDiTauPair(src,"againstMuonLoose3_1",'leg1.tauID("againstMuonLoose3")'),
                              diTauAgainstMuonLoose3Leg2 = makeDiTauPair(src,"againstMuonLoose3_2",'leg2.tauID("againstMuonLoose3")'),
                              diTauAgainstEleVLooseMVA6Leg1 = makeDiTauPair(src,"againstElectronVLooseMVA6_1",'leg1.tauID("againstElectronVLooseMVA6")'),
                              diTauAgainstEleVLooseMVA6Leg2 = makeDiTauPair(src,"againstElectronVLooseMVA6_2",'leg2.tauID("againstElectronVLooseMVA6")'),
                              diTauAgainstEleMVA6rawLeg1 = makeDiTauPair(src,"againstElectronMVA6Raw_1",'leg1.tauID("againstElectronMVA6Raw")'),
                              diTauAgainstEleMVA6rawLeg2 = makeDiTauPair(src,"againstElectronMVA6Raw_2",'leg2.tauID("againstElectronMVA6Raw")'),

                              diTauDeepIDjetLeg1 = makeDiTauPair(src,"deepjetID_1",'leg1.tauID("byDeepTau2017v1VSjetraw")'),
                              diTauDeepIDjetLeg2 = makeDiTauPair(src,"deepjetID_2",'leg2.tauID("byDeepTau2017v1VSjetraw")'),
                              diTauDeepIDeLeg1 = makeDiTauPair(src,"deepeID_1",'leg1.tauID("byDeepTau2017v1VSeraw")'),
                              diTauDeepIDeLeg2 = makeDiTauPair(src,"deepeID_2",'leg2.tauID("byDeepTau2017v1VSeraw")'),
                              diTauDeepIDmLeg1 = makeDiTauPair(src,"deepmID_1",'leg1.tauID("byDeepTau2017v1VSmuraw")'),
                              diTauDeepIDmLeg2 = makeDiTauPair(src,"deepmID_2",'leg2.tauID("byDeepTau2017v1VSmuraw")'),
                              diTauDeepVVLoosejetLeg1 = makeDiTauPair(src,"deepVVLjetID_1",'leg1.tauID("byVVLooseDeepTau2017v1VSjet")'),
                              diTauDeepVVLoosejetLeg2 = makeDiTauPair(src,"deepVVLjetID_2",'leg2.tauID("byVVLooseDeepTau2017v1VSjet")'),
                              diTauDeepVVLooseeLeg1 = makeDiTauPair(src,"deepVVLeID_1",'leg1.tauID("byVVLooseDeepTau2017v1VSe")'),
                              diTauDeepVVLooseeLeg2 = makeDiTauPair(src,"deepVVLeID_2",'leg2.tauID("byVVLooseDeepTau2017v1VSe")'),
                              diTauDeepVVLoosemLeg1 = makeDiTauPair(src,"deepVVLmID_1",'leg1.tauID("byVVLooseDeepTau2017v1VSmu")'),
                              diTauDeepVVLoosemLeg2 = makeDiTauPair(src,"deepVVLmID_2",'leg2.tauID("byVVLooseDeepTau2017v1VSmu")'),

                              diTauDeepVLoosejetLeg1 = makeDiTauPair(src,"deepVLjetID_1",'leg1.tauID("byVLooseDeepTau2017v1VSjet")'),
                              diTauDeepVLoosejetLeg2 = makeDiTauPair(src,"deepVLjetID_2",'leg2.tauID("byVLooseDeepTau2017v1VSjet")'),
                              diTauDeepVLooseeLeg1 = makeDiTauPair(src,"deepVLeID_1",'leg1.tauID("byVLooseDeepTau2017v1VSe")'),
                              diTauDeepVLooseeLeg2 = makeDiTauPair(src,"deepVLeID_2",'leg2.tauID("byVLooseDeepTau2017v1VSe")'),
                              diTauDeepVLoosemLeg1 = makeDiTauPair(src,"deepVLmID_1",'leg1.tauID("byVLooseDeepTau2017v1VSmu")'),
                              diTauDeepVLoosemLeg2 = makeDiTauPair(src,"deepVLmID_2",'leg2.tauID("byVLooseDeepTau2017v1VSmu")'),

                              diTauDeepLoosejetLeg1 = makeDiTauPair(src,"deepLjetID_1",'leg1.tauID("byLooseDeepTau2017v1VSjet")'),
                              diTauDeepLoosejetLeg2 = makeDiTauPair(src,"deepLjetID_2",'leg2.tauID("byLooseDeepTau2017v1VSjet")'),
                              diTauDeepLooseeLeg1 = makeDiTauPair(src,"deepLeID_1",'leg1.tauID("byLooseDeepTau2017v1VSe")'),
                              diTauDeepLooseeLeg2 = makeDiTauPair(src,"deepLeID_2",'leg2.tauID("byLooseDeepTau2017v1VSe")'),
                              diTauDeepLoosemLeg1 = makeDiTauPair(src,"deepLmID_1",'leg1.tauID("byLooseDeepTau2017v1VSmu")'),
                              diTauDeepLoosemLeg2 = makeDiTauPair(src,"deepLmID_2",'leg2.tauID("byLooseDeepTau2017v1VSmu")'),

                              diTauDeepMediumjetLeg1 = makeDiTauPair(src,"deepMjetID_1",'leg1.tauID("byMediumDeepTau2017v1VSjet")'),
                              diTauDeepMediumjetLeg2 = makeDiTauPair(src,"deepMjetID_2",'leg2.tauID("byMediumDeepTau2017v1VSjet")'),
                              diTauDeepMediumeLeg1 = makeDiTauPair(src,"deepMeID_1",'leg1.tauID("byMediumDeepTau2017v1VSe")'),
                              diTauDeepMediumeLeg2 = makeDiTauPair(src,"deepMeID_2",'leg2.tauID("byMediumDeepTau2017v1VSe")'),
                              diTauDeepMediummLeg1 = makeDiTauPair(src,"deepMmID_1",'leg1.tauID("byMediumDeepTau2017v1VSmu")'),
                              diTauDeepMediummLeg2 = makeDiTauPair(src,"deepMmID_2",'leg2.tauID("byMediumDeepTau2017v1VSmu")'),
                              diTauDeepTightjetLeg1 = makeDiTauPair(src,"deepTjetID_1",'leg1.tauID("byTightDeepTau2017v1VSjet")'),
                              diTauDeepTightjetLeg2 = makeDiTauPair(src,"deepTjetID_2",'leg2.tauID("byTightDeepTau2017v1VSjet")'),
                              diTauDeepTighteLeg1 = makeDiTauPair(src,"deepTeID_1",'leg1.tauID("byTightDeepTau2017v1VSe")'),
                              diTauDeepTighteLeg2 = makeDiTauPair(src,"deepTeID_2",'leg2.tauID("byTightDeepTau2017v1VSe")'),
                              diTauDeepTightmLeg1 = makeDiTauPair(src,"deepTmID_1",'leg1.tauID("byTightDeepTau2017v1VSmu")'),
                              diTauDeepTightmLeg2 = makeDiTauPair(src,"deepTmID_2",'leg2.tauID("byTightDeepTau2017v1VSmu")'),
                              diTauDeepVTightjetLeg1 = makeDiTauPair(src,"deepVTjetID_1",'leg1.tauID("byVTightDeepTau2017v1VSjet")'),
                              diTauDeepVTightjetLeg2 = makeDiTauPair(src,"deepVTjetID_2",'leg2.tauID("byVTightDeepTau2017v1VSjet")'),
                              diTauDeepVTighteLeg1 = makeDiTauPair(src,"deepVTeID_1",'leg1.tauID("byVTightDeepTau2017v1VSe")'),
                              diTauDeepVTighteLeg2 = makeDiTauPair(src,"deepVTeID_2",'leg2.tauID("byVTightDeepTau2017v1VSe")'),
                              diTauDeepVTightmLeg1 = makeDiTauPair(src,"deepVTmID_1",'leg1.tauID("byVTightDeepTau2017v1VSmu")'),
                              diTauDeepVTightmLeg2 = makeDiTauPair(src,"deepVTmID_2",'leg2.tauID("byVTightDeepTau2017v1VSmu")'),

                              diTauIsoLeg1 = makeDiTauPair(src,"iso_1",'leg1.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),
                              diTauIsoLeg2 = makeDiTauPair(src,"iso_2",'leg2.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),

                              diTauVTightIsoLeg1 = makeDiTauPair(src,"isoVTight_1",'leg1.tauID("byVTightIsolationMVArun2v1DBoldDMwLT")'),
                              diTauVTightIsoLeg2 = makeDiTauPair(src,"isoVTight_2",'leg2.tauID("byVTightIsolationMVArun2v1DBoldDMwLT")'),
                              diTauTightIsoLeg1 = makeDiTauPair(src,"isoTight_1",'leg1.tauID("byTightIsolationMVArun2v1DBoldDMwLT")'),
                              diTauTightIsoLeg2 = makeDiTauPair(src,"isoTight_2",'leg2.tauID("byTightIsolationMVArun2v1DBoldDMwLT")'),
                              diTauMediumIsoLeg1 = makeDiTauPair(src,"isoMed_1",'leg1.tauID("byMediumIsolationMVArun2v1DBoldDMwLT")'),
                              diTauMediumIsoLeg2 = makeDiTauPair(src,"isoMed_2",'leg2.tauID("byMediumIsolationMVArun2v1DBoldDMwLT")'),
                              diTauLooseIsoLeg1 = makeDiTauPair(src,"isoLoose_1",'leg1.tauID("byLooseIsolationMVArun2v1DBoldDMwLT")'),
                              diTauLooseIsoLeg2 = makeDiTauPair(src,"isoLoose_2",'leg2.tauID("byLooseIsolationMVArun2v1DBoldDMwLT")'),
                              diTauVLooseIsoLeg1 = makeDiTauPair(src,"isoVLoose_1",'leg1.tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              diTauVLooseIsoLeg2 = makeDiTauPair(src,"isoVLoose_2",'leg2.tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              diTauVVLooseIsoLeg1 = makeDiTauPair(src,"isoVLoose_1",'leg1.tauID("byVVLooseIsolationMVArun2v1DBoldDMwLT")'),
                              diTauVVLooseIsoLeg2 = makeDiTauPair(src,"isoVLoose_2",'leg2.tauID("byVVLooseIsolationMVArun2v1DBoldDMwLT")'),

			      diTauRawMVAIso1 = makeDiTauPair(src,"isoMVARaw_1",'leg1.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),
			      diTauRawMVAIso2 = makeDiTauPair(src,"isoMVARaw_2",'leg2.tauID("byIsolationMVArun2v1DBoldDMwLTraw")'),
			      diTauRawDBIso1 = makeDiTauPair(src,"isoDBRaw_1",'leg1.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits")'),
			      diTauRawDBIso2 = makeDiTauPair(src,"isoDBRaw_2",'leg2.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits")'),

####Rerun
                              ##diTauByOldDMMVAIsoRR1_1 = makeDiTauPair(src,"Raw2017v2_1",     'leg1.tauID("idRaw2017v2")'),
                              ##diTauByOldDMMVAIsoRR2_1 = makeDiTauPair(src,"VVLoose2017v2_1", 'leg1.tauID("idVVLoose2017v2")'),
                              ##diTauByOldDMMVAIsoRR3_1 = makeDiTauPair(src,"VLoose2017v2_1",  'leg1.tauID("idVLoose2017v2")'),
                              ##diTauByOldDMMVAIsoRR4_1 = makeDiTauPair(src,"Loose2017v2_1",   'leg1.tauID("idLoose2017v2")'),
                              ##diTauByOldDMMVAIsoRR5_1 = makeDiTauPair(src,"Med2017v2_1",     'leg1.tauID("idMed2017v2")'),
                              ##diTauByOldDMMVAIsoRR6_1 = makeDiTauPair(src,"Tight2017v2_1",   'leg1.tauID("idTight2017v2")'),
                              ##diTauByOldDMMVAIsoRR7_1 = makeDiTauPair(src,"VTight2017v2_1",  'leg1.tauID("idVTight2017v2")'),
                              ##diTauByOldDMMVAIsoRR8_1 = makeDiTauPair(src,"VVTight2017v2_1", 'leg1.tauID("idVVTight2017v2")'),
                              ##diTauByOldDMMVAIsoRR1_2 = makeDiTauPair(src,"idRaw2017v2_2",     'leg2.tauID("idRaw2017v2")'),
                              ##diTauByOldDMMVAIsoRR2_2 = makeDiTauPair(src,"idVVLoose2017v2_2", 'leg2.tauID("idVVLoose2017v2")'),
                              ##diTauByOldDMMVAIsoRR3_2 = makeDiTauPair(src,"idVLoose2017v2_2",  'leg2.tauID("idVLoose2017v2")'),
                              ##diTauByOldDMMVAIsoRR4_2 = makeDiTauPair(src,"idLoose2017v2_2",   'leg2.tauID("idLoose2017v2")'),
                              ##diTauByOldDMMVAIsoRR5_2 = makeDiTauPair(src,"idMed2017v2_2",     'leg2.tauID("idMed2017v2")'),
                              ##diTauByOldDMMVAIsoRR6_2 = makeDiTauPair(src,"idTight2017v2_2",   'leg2.tauID("idTight2017v2")'),
                              ##diTauByOldDMMVAIsoRR7_2 = makeDiTauPair(src,"idVTight2017v2_2",  'leg2.tauID("idVTight2017v2")'),
                              ##diTauByOldDMMVAIsoRR8_2 = makeDiTauPair(src,"idVVTight2017v2_2", 'leg2.tauID("idVVTight2017v2")'),

####Rerun
###Embedded option
                              diTauEmbeddedSF  = makeEmbeddedEventSF(src, 
                                                                     True if isEmbedded else False, 
                                                                     "embedded_trig_sf", 'p4Leg1gen().pt()','p4Leg1gen().eta()','p4Leg2gen().pt()','p4Leg2gen().eta()'),
                              diTauEmbeddedTriggerMatch = makeEmbeddedTriggerMatch(src, 
                                                                                   True if isEmbedded else False,
                                                                                   'p4Leg1gen().pt()','p4Leg1gen().eta()', 'p4Leg1gen().phi()', 'p4Leg2gen().pt()','p4Leg2gen().eta()', 'p4Leg2gen().phi()', "hltDoubleL2IsoTau26eta2p2"),

                              diTauGenPt1 = makeDiTauPair(src,"genPt1",'p4Leg1gen().pt()'),
                              diTauGenPt2 = makeDiTauPair(src,"genPt2",'p4Leg2gen().pt()'),
                              diTauGenEta1 = makeDiTauPair(src,"genEta1",'p4Leg1gen().eta()'),
                              diTauGenEta2 = makeDiTauPair(src,"genEta2",'p4Leg2gen().eta()'),
                              diTauPdg1 = makeDiTauPair(src,"pdg1",'genPdg1()'),
                              diTauPdg2 = makeDiTauPair(src,"pdg2",'genPdg2()'),
                              diTauVisGenPt1 = makeDiTauPair(src,"genVisPt1",'p4VisLeg1gen().pt()'),
                              diTauVisGenPt2 = makeDiTauPair(src,"genVisPt2",'p4VisLeg2gen().pt()'),
                              diTauGenVisMass = makeDiTauPair(src,"genVisMass",'p4VisGen().M()'),
                              diTauGenMassMatched = makeDiTauPair(src,"genFullMassMatched",'p4gen().M()'),
                              diTauGenMass = makeDiTauPair(src,"fullGenMass",'genBosonMass()'),
                              diTauGenBosonPt = makeDiTauPair(src,"genpT",'p4GenBoson().pt()'),
                              diTauGenBosonMass = makeDiTauPair(src,"genMass",'p4GenBoson().M()'),
                              diTauGenBosonPx = makeDiTauPair(src,"genpX",'p4GenBoson().px()'),
                              diTauGenBosonPy = makeDiTauPair(src,"genpY",'p4GenBoson().py()'),
                              diTauGenBosonVisPx = makeDiTauPair(src,"vispX",'p4GenBosonVis().px()'),
                              diTauGenBosonVisPy = makeDiTauPair(src,"vispY",'p4GenBosonVis().py()'),

                              diTauGenZPTReweight = makeDiTauPairZPTReweight(src,'_zweight_','p4GenBoson().M()','p4GenBoson().pt()'),
                              #Jets
                              diTauMJJReg = makeDiTauPair(src,"mJJReg","mJJReg"),#FIXME
                              diTauMJJ    = makeDiTauPair(src,"mJJ","mJJ"),#FILLED
                              diTauJJPt   = makeDiTauPair(src,"ptJJ","ptJJ"),
                              diTauJJEta  = makeDiTauPair(src,"etaJJ","etaJJ"),

                              diTauJJEnergy = makeDiTauPair(src,"energyJJ","energyJJ"),
                              diTauVBFDEta = makeDiTauPair(src,"jdeta","vbfDEta"),
                              diTauVBFMass = makeDiTauPair(src,"mjj","vbfMass"),#vbfMass
                              diTauVBFJets20 = makeDiTauPair(src,"njetingap20","vbfNJetsGap20"),
                              diTauVBFJets30 = makeDiTauPair(src,"njetingap","vbfNJetsGap30"),
                              ##FIX ME apply loose ID
                              diTauJetsPt20nbtag = makeDiTauJetCountPair(src,"nbtag",'userFloat("isbtagged")&&pt()>20&&abs(eta)<2.4&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.8484'),
                              diTauJetsPt20nbtagLoose = makeDiTauJetCountPair(src,"nbtagLooseNoSF",'pt()>20&&abs(eta)<2.4&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.46'),
                              diTauJetsPt20nbtagNoSF = makeDiTauJetCountPair(src,"nbtagNoSF",'pt()>20&&abs(eta)<2.4&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.8484'),
                              #diTauJetsPt30nbtagNoSf = makeDiTauJetCountPair(src,"nbtag30",'userFloat("isbtagged")&&pt()>30&&abs(eta)<2.4&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.8484'),
                              diTauJetsPt30nbtag = makeDiTauJetCountPair(src,"nbtag30",'pt()>30&&abs(eta)<2.4&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.8484'),

                              diTauJetsPt30njets = makeDiTauJetCountPair(src,"njets_2016",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")'),
                              diTauJetsPt30njetsVetoLowpt = makeDiTauJetCountPair(src,"njets",'pt()>30&&abs(eta)<4.7&&userFloat("idTight")&&!(pt()<50&&(abs(eta)<3.139&&abs(eta)>2.65))'),
                              diTauJetsPt30njetsnopu = makeDiTauJetCountPair(src,"njetspuID",'pt()>30&&abs(eta)<4.7&&!userFloat("puIDLoose")'),
                              diTauJetsPt20njets = makeDiTauJetCountPair(src,"njetspt20",'pt()>20&&abs(eta)<4.7&&userFloat("idTight")'),
                              diTauJetsPt20njetsnopu = makeDiTauJetCountPair(src,"njetspt20puID",'pt()>20&&abs(eta)<4.7&&!userFloat("puIDLoose")'),


                              diTauJet1PtPtSort = makeDiTauPtPair(src,"jpt_1",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','pt()',0),
                              diTauJet2PtPtSort = makeDiTauPtPair(src,"jpt_2",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','pt()',1),
                              #diTauJet1PFIDPtSort = makeDiTauPtPair(src,"jpfid_1",'abs(eta())<4.7&&pt()>20','userFloat("idLoose")',0),
                              #diTauJet2PFIDPtSort = makeDiTauPtPair(src,"jpfid_2",'abs(eta())<4.7&&pt()>20','userFloat("idLoose")',1),
                              #diTauJet1PUIDPtSort = makeDiTauPtPair(src,"jpuid_1",'abs(eta())<4.7&&pt()>20','userFloat("puID")',0),
                              #diTauJet2PUIDPtSort = makeDiTauPtPair(src,"jpuid_2",'abs(eta())<4.7&&pt()>20','userFloat("puID")',1),
                              #diTauJet1MVAPtSort = makeDiTauPtPair(src,"jmva_1",'abs(eta())<4.7&&pt()>20',"userFloat('pileupJetId:fullDiscriminant')",0),
                              #diTauJet2MVAPtSort = makeDiTauPtPair(src,"jmva_2",'abs(eta())<4.7&&pt()>20',"userFloat('pileupJetId:fullDiscriminant')",1),
                              #diTauJet1EtaPtSort = makeDiTauPtPair(src,"jeta_1",'abs(eta())<4.7&&pt()>20','eta()',0),
                              #diTauJet2EtaPtSort = makeDiTauPtPair(src,"jeta_2",'abs(eta())<4.7&&pt()>20','eta()',1),
                              #diTauJet1PhiPtSort = makeDiTauPtPair(src,"jphi_1",'abs(eta())<4.7&&pt()>20','phi()',0),
                              #diTauJet2PhiPtSort = makeDiTauPtPair(src,"jphi_2",'abs(eta())<4.7&&pt()>20','phi()',1),
                              #diTauJet1CSVPtSort = makeDiTauPtPair(src,"jcsv_1",'abs(eta())<2.4&&pt()>20','bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")',0),
                              #diTauJet2CSVPtSort = makeDiTauPtPair(src,"jcsv_2",'abs(eta())<2.4&&pt()>20','bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")',1),

                              diTauDeepJet1EtaPtSort = makeDiTauPtPair(src,"jeta_1",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','eta()',0),
                              diTauDeepJet2EtaPtSort = makeDiTauPtPair(src,"jeta_2",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','eta()',1),
                              diTauDeepJet1PhiPtSort = makeDiTauPtPair(src,"jphi_1",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','phi()',0),
                              diTauDeepJet2PhiPtSort = makeDiTauPtPair(src,"jphi_2",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','phi()',1),
                              diTauDeepJet1CSVPtSort = makeDiTauPtPair(src,"jcsv_1",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',0),
                              diTauDeepJet2CSVPtSort = makeDiTauPtPair(src,"jcsv_2",'abs(eta())<4.7&&pt()>30&&userFloat("idTight")','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',1),
                              #diTauJet1MedIdPtSort = makeDiTauPtPair(src,"jtlvID_1",'','userFloat("idTightLepVeto")',0),
                              #diTauJet2MedIdPtSort = makeDiTauPtPair(src,"jtlvID_2",'','userFloat("idTightLepVeto")',1),
                              #diTauJet1TightIdPtSort = makeDiTauPtPair(src,"jtightID_1",'','userFloat("idTight")',0),
                              #diTauJet2TightIdPtSort = makeDiTauPtPair(src,"jtightID_2",'','userFloat("idTight")',1),

                              diTauDeepBJet1PtPtSort = makeDiTauPtPair(src,"bpt_1",'abs(eta())<2.5&&pt()>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','pt()',0),
                              diTauDeepBJet2PtPtSort = makeDiTauPtPair(src,"bpt_2",'abs(eta())<2.5&&pt()>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','pt()',1),
                              #diTauBJet1MVAPtSort = makeDiTauPtPair(src,"bmva_1",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484',"userFloat('pileupJetId:fullDiscriminant')",0),
                              #diTauBJet2MVAPtSort = makeDiTauPtPair(src,"bmva_2",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484',"userFloat('pileupJetId:fullDiscriminant')",1),
                              #diTauBJet1PFIDPtSort = makeDiTauPtPair(src,"bpfid_1",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','userFloat("idLoose")',0),
                              #diTauBJet2PFIDPtSort = makeDiTauPtPair(src,"bpfid_2",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','userFloat("idLoose")',1),
                              #diTauBJet1PUIDPtSort = makeDiTauPtPair(src,"bpuid_1",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','userFloat("puID")',0),
                              #diTauBJet2PUIDPtSort = makeDiTauPtPair(src,"bpuid_2",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','userFloat("puID")',1),
                              #diTauBJet1EtaPtSort = makeDiTauPtPair(src,"beta_1",'abs(eta())<2.4&&pt>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','eta()',0),
                              #diTauBJet2EtaPtSort = makeDiTauPtPair(src,"beta_2",'abs(eta())<2.4&&pt>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','eta()',1),
                              #diTauBJet1PhiPtSort = makeDiTauPtPair(src,"bphi_1",'abs(eta())<2.4&&pt>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','phi()',0),
                              #diTauBJet2PhiPtSort = makeDiTauPtPair(src,"bphi_2",'abs(eta())<2.4&&pt>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>0.8484','phi()',1),
                              #diTauBJet1CSVPtSort = makeDiTauPtPair(src,"bcsv_1",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.8484','bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")',0),
                              #diTauBJet2CSVPtSort = makeDiTauPtPair(src,"bcsv_2",'abs(eta())<2.4&&pt()>20&&bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")>.8484','bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")',1),

                              diTauJetsPt20TagMatch = makeDiTauJetCountPair(src,"nTaggableJetsPt20Matched",'pt()>20&&abs(eta)<2.5&&abs(partonFlavour)==5'),
                              diTauJetsPt20TagNoMatch = makeDiTauJetCountPair(src,"nTaggableJetsPt20NotMatched",'pt()>30&&abs(eta)<2.5&&abs(partonFlavour)!=5'),
                              #diTauFirstJetShape = makeLTauGeneric("PATDiTauPairHighestPtJetVarFiller",src,"highestJetShape",'userFloat("ptRMS")'),
                              #diTauFirstJetCSV = makeLTauGeneric("PATDiTauPairHighestPtJetVarFiller",src,"highestJetBTagCSV",'bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags")'),

                              diTauDeepBJet1EtaPtSort = makeDiTauPtPair(src,"beta_1",'abs(eta())<2.5&&pt>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','eta()',0),
                              diTauDeepBJet2EtaPtSort = makeDiTauPtPair(src,"beta_2",'abs(eta())<2.5&&pt>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','eta()',1),
                              diTauDeepBJet1PhiPtSort = makeDiTauPtPair(src,"bphi_1",'abs(eta())<2.5&&pt>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','phi()',0),
                              diTauDeepBJet2PhiPtSort = makeDiTauPtPair(src,"bphi_2",'abs(eta())<2.5&&pt>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','phi()',1),
                              diTauDeepBJet1CSVPtSort = makeDiTauPtPair(src,"bcsv_1",'abs(eta())<2.5&&pt()>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',0),
                              diTauDeepBJet2CSVPtSort = makeDiTauPtPair(src,"bcsv_2",'abs(eta())<2.5&&pt()>20&&bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")>0.4184','bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")',1),

                              diTauDeepJetsPt20TagMatch = makeDiTauJetCountPair(src,"nTaggableJetsPt20Matched",'pt()>20&&abs(eta)<2.5&&abs(partonFlavour)==5'),
                              diTauDeepJetsPt20TagNoMatch = makeDiTauJetCountPair(src,"nTaggableJetsPt20NotMatched",'pt()>30&&abs(eta)<2.5&&abs(partonFlavour)!=5'),
                              diTauDeepFirstJetCSV = makeLTauGeneric("PATDiTauPairHighestPtJetVarFiller",src,"highestJetBTagCSV",'bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll")'),

                              higgsPt = cms.PSet(
                                  pluginType = cms.string("PATGenParticleFiller"),
                                  src        = cms.InputTag("genDaughters"),
                                  tag        = cms.string("higgsPt"),
                                  method     = cms.string('pt()'),
                                  leadingOnly=cms.untracked.bool(True)
                              ),
                              diTauLHEProduct2 = cms.PSet(
                                  pluginType = cms.string("LHEProductFiller"),
                                  src        = cms.InputTag("externalLHEProducer"),
                                  tag        = cms.string("LHEProduct"),
                              )
                              higgsClass = makeHiggsClassification("rivetProducerHTXS")
                              )
   setattr(process, name, eventTree)
   p = cms.Path(getattr(process,name))
   setattr(process, name+'Path', p)
