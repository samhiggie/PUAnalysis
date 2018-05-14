
import FWCore.ParameterSet.Config as cms
from CommonTools.ParticleFlow.Isolation.tools_cfi import *


from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.helpers import *
from PhysicsTools.PatAlgos.tools.tauTools import *
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.metTools import *
from PhysicsTools.PatAlgos.tools.pfTools import *
from PhysicsTools.PatAlgos.tools.trigTools import *
import sys

def defaultReconstructionBCDEF(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1'],HLT = 'TriggerResults',triggerFilter='RECO'):
  process.load("PUAnalysis.Configuration.startUpSequence_cff")
  process.load("Configuration.StandardSequences.Services_cff")
  process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
  process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
  process.load("DQMServices.Core.DQM_cfg")
  process.load("DQMServices.Components.DQMEnvironment_cfi")
  process.load('Configuration.StandardSequences.Services_cff')
  process.load('Configuration.EventContent.EventContent_cff')
  process.load('SimGeneral.MixingModule.mixNoPU_cfi')
  process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
  process.load('Configuration.StandardSequences.MagneticField_38T_cff')
  process.load('Configuration.StandardSequences.EndOfProcess_cff')
 
  #Make the TriggerPaths Global variable to be accesed by the ntuples
  global TriggerPaths
  TriggerPaths= triggerPaths
  global TriggerProcess
  TriggerProcess= triggerProcess
  global TriggerRes
  TriggerRes=HLT 
  global TriggerFilter
  TriggerFilter=triggerFilter

  process.analysisSequence = cms.Sequence()


  MiniAODMETfilter(process)

  MiniAODEleVIDEmbedder(process,"slimmedElectrons")  
  MiniAODMuonIDEmbedder(process,"slimmedMuons",True) #is HIP  

  recorrectJets(process, True) #adds patJetsReapplyJEC  
  reRunMET(process,True)


  metSignificance(process)

  muonTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODMuonID") 
  #electronTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODElectronVID") 
  
  #Build good vertex collection

  #reRunTaus(process)
  #selectTauDecayMode(process, 'rerunSlimmedTaus', 'pt>10')
  #tauTriggerMatchMiniAOD(process,triggerProcess,HLT,"selectTauDM") #ESTaus
  #tauEffi(process,'selectTauDM',True)
  tauOverloading(process,'slimmedTaus','miniAODMuonID','offlineSlimmedPrimaryVertices')
  #tauOverloading(process,'tauTriggerEfficiencies','triggeredPatMuons','offlineSlimmedPrimaryVertices')
  
  triLeptons(process)
  #jetOverloading(process,"slimmedJets",True)
  jetOverloading(process,"patJetsReapplyJEC",True)
  #jetOverloading(process,"patJetsReapplyJEC") #"slimmedJets")
  jetFilter(process,"patOverloadedJets")


  #Default selections for systematics
  applyDefaultSelectionsPT(process)

  process.runAnalysisSequence = cms.Path(process.analysisSequence)



def defaultReconstruction(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1'],HLT = 'TriggerResults',triggerFilter='RECO'):
  process.load("PUAnalysis.Configuration.startUpSequence_cff")
  process.load("Configuration.StandardSequences.Services_cff")
  process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
  process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
  process.load("DQMServices.Core.DQM_cfg")
  process.load("DQMServices.Components.DQMEnvironment_cfi")
  process.load('Configuration.StandardSequences.Services_cff')
  process.load('Configuration.EventContent.EventContent_cff')
  process.load('SimGeneral.MixingModule.mixNoPU_cfi')
  process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
  process.load('Configuration.StandardSequences.MagneticField_38T_cff')
  process.load('Configuration.StandardSequences.EndOfProcess_cff')
 
  #Make the TriggerPaths Global variable to be accesed by the ntuples
  global TriggerPaths
  TriggerPaths= triggerPaths
  global TriggerProcess
  TriggerProcess= triggerProcess
  global TriggerRes
  TriggerRes=HLT 
  global TriggerFilter
  TriggerFilter=triggerFilter

  process.analysisSequence = cms.Sequence()

  #BadMuonFilter(process)
  MiniAODMETfilter(process)

  MiniAODEleVIDEmbedder(process,"slimmedElectrons")  
  MiniAODMuonIDEmbedder(process,"slimmedMuons", False) #is HIP  

  recorrectJets(process, True) #adds patJetsReapplyJEC  
  reRunMET(process,True)

  #mvaMet2(process, True) #isData
  metSignificance(process)

  muonTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODMuonID") 
  #electronTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODElectronVID") 
  
  #Build good vertex collection
  #goodVertexFilter(process)  
  #reRunTaus(process)
  selectTauDecayMode(process, 'slimmedTaus', 'pt>10')
  tauTriggerMatchMiniAOD(process,triggerProcess,HLT,"selectTauDM") #ESTaus
  tauEffi(process,'triggeredPatTaus',True)
  tauOverloading(process,'tauTriggerEfficiencies','triggeredPatMuons','offlineSlimmedPrimaryVertices')
  
  triLeptons(process)
  #jetOverloading(process,"slimmedJets",True)
  jetOverloading(process,"patJetsReapplyJEC",True)
  #jetOverloading(process,"patJetsReapplyJEC") #"slimmedJets")
  jetFilter(process,"patOverloadedJets")


  #Default selections for systematics
  applyDefaultSelectionsPT(process)

  process.runAnalysisSequence = cms.Path(process.analysisSequence)



def defaultReconstructionMC(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v1','HLT_Mu11_PFTau15_v2','HLT_Mu15_v1','HLT_Mu15_v2'],HLT = 'TriggerResults',triggerFilter='PAT'):
  process.load("PUAnalysis.Configuration.startUpSequence_cff")
  process.load("Configuration.StandardSequences.Services_cff")
  process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
  process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
  process.load("DQMServices.Core.DQM_cfg")
  process.load("DQMServices.Components.DQMEnvironment_cfi")
  process.load('Configuration.StandardSequences.Services_cff')
  process.load('Configuration.EventContent.EventContent_cff')
  process.load('SimGeneral.MixingModule.mixNoPU_cfi')
  process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
  process.load('Configuration.StandardSequences.MagneticField_38T_cff')
  process.load('Configuration.StandardSequences.EndOfProcess_cff')
 
  #Make the TriggerPaths Global variable to be accesed by the ntuples
  global TriggerPaths
  TriggerPaths= triggerPaths
  global TriggerProcess
  TriggerProcess= triggerProcess
  global TriggerRes
  TriggerRes=HLT 
  global TriggerFilter
  TriggerFilter=triggerFilter
  
  process.analysisSequence = cms.Sequence()

  #Apply Tau Energy Scale Changes
  #EScaledTaus(process,False)


  MiniAODEleVIDEmbedder(process,"slimmedElectrons")  
  MiniAODMuonIDEmbedder(process,"slimmedMuons")  

  #BadMuonFilter(process)
  MiniAODMETfilter(process)

  recorrectJets(process, False) #adds patJetsReapplyJEC
  reRunMET(process,False)

  metSignificance(process)


  #no trigger here!!!  
  muonTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODMuonID")#NEW
  #electronTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODElectronVID")#NEW
  
  #Build good vertex collection
  #goodVertexFilter(process)  
  genmatchtaus(process)  
  #reRunTaus(process)
  selectTauDecayMode(process, 'slimmedTaus', 'pt>10')
  tauTriggerMatchMiniAOD(process,triggerProcess,HLT,"selectTauDM")
  tauEffi(process,'triggeredPatTaus',False)
  tauOverloading(process,'tauTriggerEfficiencies','triggeredPatMuons','offlineSlimmedPrimaryVertices')
  
  triLeptons(process)
  #jetOverloading(process,"slimmedJets",False)
  jetOverloading(process,"patJetsReapplyJEC",False)

  MiniAODJES(process,"patOverloadedJets")
  jetFilter(process,"jetsEmbedJES")

  GenSumWeights(process)
  GenHTCalculator(process)
  #Default selections for systematics
  applyDefaultSelectionsPT(process)

  process.runAnalysisSequence = cms.Path(process.analysisSequence)

def defaultReconstructionEMB(process,triggerProcess = 'HLT',triggerPaths = ['HLT_Mu9','HLT_Mu11_PFTau15_v1'],HLT = 'TriggerResults',triggerFilter='LHEembeddingCLEAN'):
  process.load("PUAnalysis.Configuration.startUpSequence_cff")
  process.load("Configuration.StandardSequences.Services_cff")
  process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
  process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
  process.load("DQMServices.Core.DQM_cfg")
  process.load("DQMServices.Components.DQMEnvironment_cfi")
  process.load('Configuration.StandardSequences.Services_cff')
  process.load('Configuration.EventContent.EventContent_cff')
  process.load('SimGeneral.MixingModule.mixNoPU_cfi')
  process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
  process.load('Configuration.StandardSequences.MagneticField_38T_cff')
  process.load('Configuration.StandardSequences.EndOfProcess_cff')
 
  #Make the TriggerPaths Global variable to be accesed by the ntuples
  global TriggerPaths
  TriggerPaths= triggerPaths
  global TriggerProcess
  TriggerProcess= triggerProcess
  global TriggerRes
  TriggerRes=HLT 
  global TriggerFilter
  TriggerFilter=triggerFilter

  process.analysisSequence = cms.Sequence()

  #BadMuonFilter(process)
  MiniAODMETfilter(process)

  MiniAODEleVIDEmbedder(process,"slimmedElectrons")  
  MiniAODMuonIDEmbedder(process,"slimmedMuons") #is not HIP, use standard ID   

  recorrectJets(process, True) #adds patJetsReapplyJEC  
  reRunMET(process,True)

  #mvaMet2(process, True) #isData
  metSignificance(process)

  muonTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODMuonID") 
  electronTriggerMatchMiniAOD(process,triggerProcess,HLT,"miniAODElectronVID") 
  #tauTriggerMatchMiniAOD(process,triggerProcess,HLT,"slimmedTaus") #ESTaus
  
  #Build good vertex collection
  #goodVertexFilter(process)  
  tauEffi(process,'slimmedTaus',True)
  tauOverloading(process,'tauTriggerEfficiencies','triggeredPatMuons','offlineSlimmedPrimaryVertices')
  
  triLeptons(process)
  #jetOverloading(process,"slimmedJets",True)
  jetOverloading(process,"patJetsReapplyJEC",True)
  #jetOverloading(process,"patJetsReapplyJEC") #"slimmedJets")
  jetFilter(process,"patOverloadedJets")

  #Default selections for systematics
  applyDefaultSelectionsPT(process)

  process.runAnalysisSequence = cms.Path(process.analysisSequence)




def genmatchtaus(process):
    process.tauGenJets = cms.EDProducer(
        "TauGenJetProducer",
        GenParticles =  cms.InputTag('prunedGenParticles'),
        includeNeutrinos = cms.bool( False ),
        verbose = cms.untracked.bool( False )
        )
    # Create filtered groups of tau decay paths
    process.tauGenJetsSelectorAllHadrons = cms.EDFilter("TauGenJetDecayModeSelector",
         src = cms.InputTag("tauGenJets"),
         select = cms.vstring('oneProng0Pi0', 
                              'oneProng1Pi0', 
                              'oneProng2Pi0', 
                              'oneProngOther',
                              'threeProng0Pi0', 
                              'threeProng1Pi0', 
                              'threeProngOther', 
                              'rare'),
         filter = cms.bool(False)
    )
    process.tauGenJetsSelectorElectrons = cms.EDFilter("TauGenJetDecayModeSelector",
         src = cms.InputTag("tauGenJets"),
         select = cms.vstring('electron'), 
         filter = cms.bool(False)
    )
    
    process.tauGenJetsSelectorMuons = cms.EDFilter("TauGenJetDecayModeSelector",
         src = cms.InputTag("tauGenJets"),
         select = cms.vstring('muon'), 
         filter = cms.bool(False)
    )

    process.buildGenTaus = cms.Sequence( 
        process.tauGenJets 
        * process.tauGenJetsSelectorAllHadrons
        * process.tauGenJetsSelectorElectrons
        * process.tauGenJetsSelectorMuons
    )
    process.analysisSequence*=process.buildGenTaus


def MiniAODJES(process, jSrc="slimmedJets"):
    process.jetsEmbedJES = cms.EDProducer(
            "MiniAODJetFullSystematicsEmbedder",
            src = cms.InputTag(jSrc),
            corrLabel = cms.string('AK4PFchs'),
            fName = cms.string("Summer16_23Sep2016AllV4_DATA_UncertaintySources_AK4PFchs.txt")
            )

    process.analysisSequence*=process.jetsEmbedJES


#FIXME
#def BadMuonFilter(process):
#
#    process.badGlobalMuonTagger = cms.EDFilter("BadGlobalMuonTagger",
#            muons = cms.InputTag("slimmedMuons"),
#            vtx   = cms.InputTag("offlineSlimmedPrimaryVertices"),
#            muonPtCut = cms.double(20),
#            selectClones = cms.bool(False),
#            taggingMode = cms.bool(True),
#            )
#    process.cloneGlobalMuonTagger = process.badGlobalMuonTagger.clone(
#                selectClones = True
#                )
#
#    process.noBadGlobalMuons = cms.Sequence(process.cloneGlobalMuonTagger + process.badGlobalMuonTagger)
#    process.analysisSequence*=process.noBadGlobalMuons


def MiniAODMETfilter(process):
    process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
    process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
    process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
    process.BadPFMuonFilter.taggingMode =  cms.bool(True)

    process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
    process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
    process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
    process.BadPFMuonFilter.taggingMode =  cms.bool(True)

    process.BadMuon = cms.Sequence(process.BadPFMuonFilter*process.BadChargedCandidateFilter)
    process.analysisSequence*=process.BadMuon


def jetOverloading(process,jets, data):

  process.patOverloadedJets = cms.EDProducer('PATJetOverloader',
                                        src = cms.InputTag(jets),
                                        genJets = cms.InputTag("slimmedGenJets"), #One collections of gen jets is saved, slimmedGenJets, made from ak4GenJets
					isData = cms.bool(data)
  )                                        

  process.jetOverloading = cms.Sequence(process.patOverloadedJets)
  process.analysisSequence*=process.jetOverloading


def jetFilter(process,jets):

  process.filteredJets = cms.EDProducer('PATJetFilter',
                                        src = cms.InputTag(jets)
  )                                        

  process.jetFiltering = cms.Sequence(process.filteredJets)
  process.analysisSequence*=process.jetFiltering


def PATJetMVAEmbedder(process,jets):

  process.patMVAEmbeddedJets = cms.EDProducer('PATJetMVAEmbedder',
                                        src = cms.InputTag(jets)
  )                                        

  process.jetMVAEmbedding = cms.Sequence(process.patMVAEmbeddedJets)
  process.analysisSequence*=process.jetMVAEmbedding


def MiniAODMuonIDEmbedder(process,muons, isHIP=False):
  process.miniAODMuonID = cms.EDProducer(
      "MiniAODMuonIDEmbedder",
      src=cms.InputTag(muons),
      vertices=cms.InputTag("offlineSlimmedPrimaryVertices"),
      isHip=cms.bool(isHIP)
      )

  process.embedMuonIDs = cms.Sequence(process.miniAODMuonID)
  process.analysisSequence*=process.embedMuonIDs


def MiniAODEleVIDEmbedder(process, eles):
  #Turn on versioned cut-based ID
  from PhysicsTools.SelectorUtils.tools.vid_id_tools import setupAllVIDIdsInModule, setupVIDElectronSelection, switchOnVIDElectronIdProducer, DataFormat, setupVIDSelection
  #from PhysicsTools.SelectorUtils.tools.vid_id_tools import  setupAllVIDIdsInModule, setupVIDElectronSelection, switchOnVIDElectronIdProducer, DataFormat
  switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
  process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cfi")
  process.egmGsfElectronIDs.physicsObjectaus = cms.InputTag(eles)
  from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry
  #egmGsfElectronIDSequence should already be defined in egmGsfElectronIDs_cfi 
  #process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)
  process.egmGsfElectronIDSequence = cms.Sequence(process.electronMVAValueMapProducer+process.egmGsfElectronIDs)
  id_modules = [
      'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff',
      'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
      'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
      'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff',
      'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff']
  for idmod in id_modules:
      setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection,None,False)
  
  IDLabels = ["eleMVAIDnonTrig80", "eleMVAIDnonTrig90","CBID","CBIDVeto", "CBIDLoose", "CBIDMedium", "CBIDTight","eleHEEPid"] # keys of based id user floats
  IDTags = [
          cms.InputTag('egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp80'),
          cms.InputTag('egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp90'),
          cms.InputTag('egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1'),
          cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto'),
          cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose'),
          cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium'),
          cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight'),
          cms.InputTag('egmGsfElectronIDs:heepElectronID-HEEPV60')
  ]
  # Embed cut-based VIDs
  process.miniAODElectronVID = cms.EDProducer(
      "MiniAODElectronVIDEmbedder",
      src=cms.InputTag(eles),
      idLabels = cms.vstring(*IDLabels),
      ids = cms.VInputTag(*IDTags),
      eleIsoLabel = cms.string("dBRelIso")
  )
   
  process.embedEleIDs = cms.Sequence(process.egmGsfElectronIDSequence+process.miniAODElectronVID)
  process.analysisSequence*=process.embedEleIDs

   
def EScaledTaus(process,smearing):  #second arg is bool

  process.ESTausID = cms.EDProducer("ESTauProducer",
                                    src = cms.InputTag("slimmedTaus"),
                                    module_label = cms.string("FROGS"),
                                    genParticles = cms.InputTag("genParticles"),
                                    smearConstituents = cms.bool(smearing),
                                    smearMCParticle = cms.bool(False),
                                    energyScale  = cms.double(1.0),
                                    energyScaleDB= cms.int32(0),
                                    deltaEta     = cms.double(0.0),
                                    deltaPhi     = cms.double(0.0),
                                    deltaPtB     = cms.double(0.0),
                                    deltaPtE     = cms.double(0.0)
                                    )
  
  process.EScaledTaus = cms.Sequence(process.ESTausID)
  process.analysisSequence*=process.EScaledTaus


def mvaMet2(process, isData):

   from RecoMET.METPUSubtraction.MVAMETConfiguration_cff import runMVAMET


   runMVAMET( process, jetCollectionPF = "patJetsReapplyJEC"  )
   process.MVAMET.srcLeptons  = cms.VInputTag("slimmedMuons", "slimmedElectrons", "slimmedTaus")
   process.MVAMET.requireOS = cms.bool(False)
   process.MVAMET.debug = cms.bool(False)
   process.tauMET.srcPFCands =  cms.InputTag("packedPFCandidates")

   process.analysisSequence = cms.Sequence(process.analysisSequence*process.MVAMET)



def metSignificance(process):
   process.load("RecoMET.METProducers.METSignificance_cfi")
   process.load("RecoMET.METProducers.METSignificanceParams_cfi")

   from RecoMET.METProducers.METSignificanceParams_cfi import METSignificanceParams
 
   process.METSignificance = cms.EDProducer(
       "METSignificanceProducer",
       srcLeptons = cms.VInputTag(
          'slimmedElectrons',
          'slimmedMuons',
          'slimmedPhotons'
       ),
       srcPfJets            = cms.InputTag('slimmedJets'),
       srcMet               = cms.InputTag('slimmedMETs'),
       srcPFCandidates      = cms.InputTag('packedPFCandidates'),
       srcJetSF             = cms.string('AK4PFchs'),
       srcJetResPt          = cms.string('AK4PFchs_pt'),
       srcJetResPhi         = cms.string('AK4PFchs_phi'),
       srcRho               = cms.InputTag('fixedGridRhoAll'),
 
       parameters = METSignificanceParams
   )
   process.analysisSequence *= process.METSignificance


def reRunMET(process, runOnData):
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

    runMetCorAndUncFromMiniAOD(process,
            isData=runOnData
            )
    process.analysisSequence *= process.fullPatMetSequence



def reapplyPUJetID(process, srcJets = cms.InputTag("slimmedJets")):
    from RecoJets.JetProducers.PileupJetID_cfi import pileupJetId
    process.pileupJetIdUpdated = pileupJetId.clone(
        jets = srcJets,
        inputIsCorrected = True,
        applyJec = True,
        vertexes = cms.InputTag("offlineSlimmedPrimaryVertices") ) 
    process.analysisSequence *= process.pileupJetIdUpdated
   
def recorrectJetsSQL(process, isData = False):
    JECTag = 'Summer16_23Sep2016V3_MC'
    if(isData):
      JECTag = 'Summer16_23Sep2016AllV3_DATA'
    #cmssw_base = os.environ['CMSSW_BASE']
    ## getting the JEC from the DB
    #process.load("CondCore.CondDB.CondDB_cfi")
    process.load("CondCore.DBCommon.CondDBCommon_cfi")
    process.jec = cms.ESSource("PoolDBESSource",
                               DBParameters = cms.PSet( messageLevel = cms.untracked.int32(0)),
                               timetype = cms.string('runnumber'),
                               toGet = cms.VPSet(cms.PSet(record = cms.string('JetCorrectionsRecord'),
                                                          tag    = cms.string('JetCorrectorParametersCollection_'+JECTag+'_AK4PFchs'),
                                                          label  = cms.untracked.string('AK4PFchs')
                                                          )
                                                 ),
                               connect = cms.string('sqlite_fip:PUAnalysis/Configuration/data/'+JECTag+'.db')
                               #connect = cms.string('sqlite:////'+cmssw_base+'/src/PUAnalysis/Configuration/data/'+JECTag+'.db')
                               # uncomment above tag lines and this comment to use MC JEC
                               )

     ## add an es_prefer statement to resolve a possible conflict from simultaneous connection to a global tag
    process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')
    ## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
    from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
    process.patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
      src = cms.InputTag("slimmedJets"),
      levels = ['L1FastJet', 'L2Relative', 'L3Absolute'],
      payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!
    from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
    process.patJetsReapplyJEC = updatedPatJets.clone(
      jetSource = cms.InputTag("slimmedJets"),
      jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
      )
    if(isData):
        process.patJetCorrFactorsReapplyJEC.levels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']
    process.analysisSequence *= process.patJetCorrFactorsReapplyJEC


def recorrectJets(process, isData = False):
    ## https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
    from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
    process.patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
    src = cms.InputTag("slimmedJets"),
      levels = ['L1FastJet', 'L2Relative', 'L3Absolute'],
      payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!
    from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
    process.patJetsReapplyJEC = updatedPatJets.clone(
      jetSource = cms.InputTag("slimmedJets"),
      jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
      )
    if(isData):
        process.patJetCorrFactorsReapplyJEC.levels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']
    process.analysisSequence *= process.patJetCorrFactorsReapplyJEC 

def GenSumWeights(process):

  process.sumweights = cms.EDFilter("GenWeightSum")
  
  process.analysisSequence*= process.sumweights

def GenHTCalculator(process):

  process.sumPUP = cms.EDFilter("GenHTCalculatorLHE",
       PartonMultiplicity=cms.untracked.int32(5)
  )

  process.analysisSequence*= process.sumPUP


def triLeptons(process):

  process.TightElectrons = cms.EDFilter("PATElectronSelector",
  							src = cms.InputTag("miniAODElectronVID"),
  							cut = cms.string('pt>10&&abs(eta)<2.5&&abs(userFloat("dZ"))<0.2&&abs(userFloat("dXY"))<0.045&&userFloat("dBRelIso03")<0.3&&userFloat("eleMVAIDnonTrig90")>0&&userInt("eleConversion")==0'),
  							filter = cms.bool(False)
  						)
  						
  process.TightMuons = cms.EDFilter("PATMuonSelector",
  							src = cms.InputTag("miniAODMuonID"),
  							cut = cms.string('pt>10&&abs(eta)<2.4&&abs(userFloat("dZ"))<0.2&&abs(userFloat("dXY"))<0.045&&userInt("mediumID")>0&&userFloat("dBRelIso")<0.3'),
  							filter = cms.bool(False)
  						)

  process.analysisSequence = cms.Sequence(process.analysisSequence*process.TightMuons*process.TightElectrons)
  						
   
def kineWeightsEmbET(process):

  process.load('TauAnalysis/MCEmbeddingTools/embeddingKineReweight_cff')

  process.embeddingKineReweightRECembedding.inputFileName = cms.FileInPath('TauAnalysis/MCEmbeddingTools/data/embeddingKineReweight_ePtGt20tauPtGt18_recEmbedded.root')
  
  process.analysisSequence = cms.Sequence(process.analysisSequence*process.embeddingKineReweightSequenceRECembedding)
  
  
def kineWeightsEmbMT(process):

  process.load('TauAnalysis/MCEmbeddingTools/embeddingKineReweight_cff')

  process.embeddingKineReweightRECembedding.inputFileName = cms.FileInPath('TauAnalysis/MCEmbeddingTools/data/embeddingKineReweight_muPtGt16tauPtGt18_recEmbedded.root')
  
  process.analysisSequence = cms.Sequence(process.analysisSequence*process.embeddingKineReweightSequenceRECembedding)
  						

  						
def applyDefaultSelectionsPT(process):#FIXME THISWILL HVAE TO CHANGE-- not cureently used!!!
  #DONT CHANGE THOSE HERE:: THEY ARE NOT USED FOR YOUR SELECTIONS!!!
  #ONLY FOR SYSTEMATICS . PLEASE CHANGE THEM in YOUR CFG FILE IF REALLY NEEDED
  process.selectedPatTaus = cms.EDFilter("PATTauSelector",
                                           src = cms.InputTag("patOverloadedTaus"),
                                           cut = cms.string('pt>18&&(tauID("byVLooseIsolationMVArun2v1DBoldDMwLT")>0.5)&&tauID("decayModeFinding")&&tauID("againstElectronVLooseMVA6")&&tauID("againstMuonLoose3")'),
                                           filter = cms.bool(False)
  										)  
  process.selectedPatElectrons = cms.EDFilter("PATElectronSelector",
                                           src = cms.InputTag("miniAODElectronVID"),
                                           cut = cms.string('pt>10&&userFloat("eleMVAIDnonTrig90")>0&&userFloat("dBRelIso03")<0.3'),
                                           filter = cms.bool(False)
  										)
  process.selectedPatMuons = cms.EDFilter("PATMuonSelector",
                                           src = cms.InputTag("miniAODMuonID"),
                                           cut = cms.string('pt>10&&userInt("mediumID")>0&&userFloat("dBRelIso")<0.3'),
                                           filter = cms.bool(False)
  										) 
  process.cleanPatJets = cms.EDProducer("PATJetCleaner",
                                           src = cms.InputTag("filteredJets"),#"patMVAEmbeddedJets"
                                           preselection = cms.string('abs(eta)<4.7&&pt>10&&userFloat("idLoose")'),
                                           checkOverlaps = cms.PSet(),
                                           finalCut = cms.string('')
  										)								 									  
  process.selectedObjectsForSyst = cms.Sequence(process.selectedPatTaus+process.selectedPatElectrons+process.selectedPatMuons+process.cleanPatJets)
  process.analysisSequence = cms.Sequence(process.analysisSequence*process.selectedObjectsForSyst)

def tauTriggerMatchMiniAOD(process,triggerProcess,HLT,srcTau):
   strTrig=''
   for i in TriggerPaths:
    if i==TriggerPaths[0]:
      strTrig+='path(\"'+i+'\")'
    else:  
      strTrig+='|| path(\"'+i+'\")'


   process.triggeredPatTaus = cms.EDProducer("TauTriggerMatcherMiniAOD",
                                            src = cms.InputTag(srcTau),
                                            trigEvent = cms.InputTag(HLT),
                                            filtersAND = cms.vstring(
                                                'hltOverlapFilterSingleIsoMu19LooseIsoPFTau20',
                                                'hltOverlapFilterSingleIsoMu21LooseIsoPFTau20',
                                                'hltOverlapFilterSingleIsoEle24WPLooseGsfLooseIsoPFTau20',
                                                'hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau20',
                                                'hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau30'
                                            ),
                                            filters = cms.vstring(
                                                'hltOverlapFilterSingleIsoMu19LooseIsoPFTau20',
                                                'hltOverlapFilterSingleIsoMu21LooseIsoPFTau20',
                                                'hltOverlapFilterSingleIsoEle24WPLooseGsfLooseIsoPFTau20',
                                                'hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau20',
                                                'hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau30'
                                            ),
                                            #bits = cms.InputTag("TriggerResults","","HLT"),
                                            bits = cms.InputTag(HLT,"",triggerProcess),
                                            prescales = cms.InputTag("patTrigger"),
                                            objects = cms.InputTag("slimmedPatTrigger"),#for 2017 analysis
                                            ptCut = cms.int32(10) #too low to affect anything
   )
                                            
   #process.analysisSequence=cms.Sequence(process.analysisSequence*process.preTriggeredPatTaus*process.triggeredPatTaus)
   process.analysisSequence=cms.Sequence(process.analysisSequence*process.triggeredPatTaus)

#'hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07',
#'hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p07',
#'hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07',
#'hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07'     
def muonTriggerMatchMiniAOD(process,triggerProcess,HLT,srcMuon):

   process.triggeredPatMuons = cms.EDProducer("MuonTriggerMatcherMiniAOD",
                                            src = cms.InputTag(srcMuon),#"miniAODMuonID"
                                            trigEvent = cms.InputTag(HLT),
                                            filters = cms.vstring(
                                                'hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07',
                                                'hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p07',        
                                                'hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07',  
                                                'hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07'     
                                            ),
					    filtersAND = cms.vstring(
                                                'hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07',
                                                'hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p07',        
                                                'hltL3crIsoL1sSingleMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p07',  
                                                'hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07'     
					    ),
                                            bits = cms.InputTag(HLT,"",triggerProcess),
                                            #bits = cms.InputTag("TriggerResults","","HLT"),
                                            prescales = cms.InputTag("patTrigger"),
                                            objects = cms.InputTag("slimmedPatTrigger"),#for 2017 analysis
                                            #objects = cms.InputTag("selectedPatTrigger"),
                                            ptCut = cms.int32(0) 
   )
   
   process.analysisSequence*= process.triggeredPatMuons

def electronTriggerMatchMiniAOD(process,triggerProcess,HLT,srcEle):

   process.triggeredPatElectrons = cms.EDProducer("ElectronTriggerMatcherMiniAOD",
                                            src = cms.InputTag(srcEle),#"miniAODElectronVID"
                                            trigEvent = cms.InputTag(HLT),#unused
                                            filters = cms.vstring(
						'hltEle24WPLooseL1SingleIsoEG22erGsfTrackIsoFilter', #2016 ETau HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v2
						'hltEle24WPLooseL1IsoEG22erTau20erGsfTrackIsoFilter', #2016 ETau HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v2
						'hltEle24WPLooseL1IsoEG22erIsoTau26erGsfTrackIsoFilter', #2016 ETau HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v2
						'hltEle25erWPTightGsfTrackIsoFilter' #spring15 ETau
                                            ),
					    filtersAND = cms.vstring(
						'hltEle24WPLooseL1SingleIsoEG22erGsfTrackIsoFilter', #2016 ETau HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v2
						'hltEle24WPLooseL1IsoEG22erTau20erGsfTrackIsoFilter', #2016 ETau HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v2
						'hltEle24WPLooseL1IsoEG22erIsoTau26erGsfTrackIsoFilter', #2016 ETau HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v2
 						'hltEle25erWPTightGsfTrackIsoFilter' #2015D single E 
					    ),
                                            #bits = cms.InputTag("TriggerResults","","HLT"),
                                            bits = cms.InputTag(HLT,"",triggerProcess),
                                            prescales = cms.InputTag("patTrigger"),
                                            objects = cms.InputTag("slimmedPatTrigger"),#for 2017 analysis
                                            #objects = cms.InputTag("selectedPatTrigger"),
                                            ptCut = cms.int32(0) 
   )
  
   process.analysisSequence*= process.triggeredPatElectrons


def tauOverloading(process,src, muons, vtxSrc, gen='prunedGenParticles'):


  process.patOverloadedTaus = cms.EDProducer('PATTauOverloader',
                                        src = cms.InputTag(src),
                                        muons = cms.InputTag(muons),
                                        gen = cms.InputTag(gen),
                                        genHadTaus = cms.InputTag("tauGenJetsSelectorAllHadrons"),
                                        genMuTaus = cms.InputTag("tauGenJetsSelectorMuons"),
                                        genEleTaus = cms.InputTag("tauGenJetsSelectorElectrons"),
                                        vtxSrc = cms.InputTag(vtxSrc)
  )                                        

  process.analysisSequence=cms.Sequence(process.analysisSequence*process.patOverloadedTaus)

def tauEffi(process,src,isData):

  Names = ["MediumIsoPFTau35_Trk_eta2p1","LooseIsoPFTau20_SingleL1","LooseIsoPFTau20"]

  process.tauTriggerEfficiencies = cms.EDProducer('MiniAODTauEffi',
                                        src = cms.InputTag(src),
                                        pruned = cms.InputTag('prunedGenParticles'),
                                        wps = cms.vstring(*Names),
                                        jsonname = cms.string("TauTrigger.json"),
                                        data = cms.bool(isData)
  )                                        
  process.analysisSequence=cms.Sequence(process.analysisSequence*process.tauTriggerEfficiencies)

def selectTauDecayMode(process, taus, cut='pt>10'):
  process.selectTauDM = cms.EDFilter("PATTauSelector",
                                           src = cms.InputTag(taus),
                                           cut = cms.string(cut),
                                           filter = cms.bool(False)
  										)  

  process.analysisSequence=cms.Sequence(process.analysisSequence*process.selectTauDM)

def reRunTaus(process,taus='slimmedTaus'):
        from RecoTauTag.RecoTau.TauDiscriminatorTools import noPrediscriminants
        process.load('RecoTauTag.Configuration.loadRecoTauTagMVAsFromPrepDB_cfi')
        from RecoTauTag.RecoTau.PATTauDiscriminationByMVAIsolationRun2_cff import \
            patDiscriminationByIsolationMVArun2v1raw, patDiscriminationByIsolationMVArun2v1VLoose
        
        process.rerunDiscriminationByIsolationMVArun2v1raw = patDiscriminationByIsolationMVArun2v1raw.clone(
           PATTauProducer = cms.InputTag(taus),
           Prediscriminants = noPrediscriminants,
           loadMVAfromDB = cms.bool(True),
           mvaName = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1"), # name of the training you want to use
           mvaOpt = cms.string("DBoldDMwLT"), # option you want to use for your training (i.e., which variables are used to compute the BDT score)
           requireDecayMode = cms.bool(True),
           verbosity = cms.int32(0)
        )
        
        process.rerunDiscriminationByIsolationMVArun2v1VLoose = patDiscriminationByIsolationMVArun2v1VLoose.clone(
           PATTauProducer = cms.InputTag(taus),    
           Prediscriminants = noPrediscriminants,
           toMultiplex = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw'),
           key = cms.InputTag('rerunDiscriminationByIsolationMVArun2v1raw:category'),
           loadMVAfromDB = cms.bool(True),
           mvaOutput_normalization = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_mvaOutput_normalization"), # normalization fo the training you want to use
           mapping = cms.VPSet(
              cms.PSet(
                 category = cms.uint32(0),
                 cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff90"), # this is the name of the working point you want to use
                 variable = cms.string("pt"),
              )
           )
        )
        
        # here we produce all the other working points for the training
        process.rerunDiscriminationByIsolationMVArun2v1Loose = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
        process.rerunDiscriminationByIsolationMVArun2v1Loose.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff80")
        process.rerunDiscriminationByIsolationMVArun2v1Medium = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
        process.rerunDiscriminationByIsolationMVArun2v1Medium.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff70")
        process.rerunDiscriminationByIsolationMVArun2v1Tight = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
        process.rerunDiscriminationByIsolationMVArun2v1Tight.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff60")
        process.rerunDiscriminationByIsolationMVArun2v1VTight = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
        process.rerunDiscriminationByIsolationMVArun2v1VTight.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff50")
        process.rerunDiscriminationByIsolationMVArun2v1VVTight = process.rerunDiscriminationByIsolationMVArun2v1VLoose.clone()
        process.rerunDiscriminationByIsolationMVArun2v1VVTight.mapping[0].cut = cms.string("RecoTauTag_tauIdMVAIsoDBoldDMwLT2016v1_WPEff40")
        
        # this sequence has to be included in your cms.Path() before your analyzer which accesses the new variables is called.
        process.rerunMvaIsolation2SeqRun2 = cms.Sequence(
           process.rerunDiscriminationByIsolationMVArun2v1raw
           * process.rerunDiscriminationByIsolationMVArun2v1VLoose
           * process.rerunDiscriminationByIsolationMVArun2v1Loose
           * process.rerunDiscriminationByIsolationMVArun2v1Medium
           * process.rerunDiscriminationByIsolationMVArun2v1Tight
           * process.rerunDiscriminationByIsolationMVArun2v1VTight
           * process.rerunDiscriminationByIsolationMVArun2v1VVTight
        )

        # embed rerun MVA IDs
        process.rerunSlimmedTaus = cms.EDProducer(
            "MiniAODTauRerunIDEmbedder",
            src = cms.InputTag(taus),
            idRaw = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1raw"),
            idVLoose = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1VLoose"),
            idLoose = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1Loose"),
            idMedium = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1Medium"),
            idTight = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1Tight"),
            idVTight = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1VTight"),
            idVVTight = cms.InputTag("rerunDiscriminationByIsolationMVArun2v1VVTight"),
        )

        #process.analysisSequence+=process.rerunMvaIsolation2SeqRun2
        process.analysisSequence=cms.Sequence(process.analysisSequence*process.rerunMvaIsolation2SeqRun2*process.rerunSlimmedTaus)

def getAllEventCounters(process,path,onSkim = False):
        stringList = []
        if onSkim:
          stringList.append('processedEvents')

        modules = listModules(path)
    
        for mod in modules:
            if(hasattr(mod,'label')):
                if mod.label().find('Counter') !=-1 :
                    stringList.append(mod.name.value())
        print 'List Of Filters'        
        print stringList
        
        return cms.untracked.vstring(stringList)

def addEventSummary(process,onSkim = False,name = 'summary',path = 'eventSelection'):
    
   process.TFileService = cms.Service("TFileService", fileName = cms.string("analysis.root") )

   summary = cms.EDAnalyzer('EventSummary',
                            src =getAllEventCounters(process,getattr(process,path),onSkim)
   )

   setattr(process,name,summary)
   if onSkim:
        process.EDMtoMEConverter = cms.EDAnalyzer("EDMtoMEConverter",
                                                  Name = cms.untracked.string('EDMtoMEConverter'),
                                                  Verbosity = cms.untracked.int32(1), # 0 provides no output
                                                  # 1 provides basic output
                                                  Frequency = cms.untracked.int32(50),
                                                  convertOnEndLumi = cms.untracked.bool(True),
                                                  convertOnEndRun = cms.untracked.bool(True),
                                                  runInputTag = cms.InputTag('MEtoEDMConverter', 'MEtoEDMConverterRun'),
                                                  lumiInputTag = cms.InputTag('MEtoEDMConverter', 'MEtoEDMConverterLumi')
                                               )
        eventSummaryPath=cms.EndPath(process.EDMtoMEConverter+getattr(process,name))
        setattr(process,name+"Path",eventSummaryPath)
   else:
        eventSummaryPath=cms.EndPath(getattr(process,name))
        setattr(process,name+"Path",eventSummaryPath)



def createGeneratedParticles(process,name,commands):


  refObjects = cms.EDProducer("GenParticlePruner",
    src = cms.InputTag("prunedGenParticles"),
    select = cms.vstring(
    "drop * " 
    )
   )
  refObjects.select.extend(commands)
  setattr(process,name,refObjects)
  process.analysisSequence*= getattr(process,name)




def createGeneratedTaus(process,decayMode,fiducialCuts):
  process.generatedTaus = cms.EDFilter("TauGenJetDecayModeSelector",
                                       src = cms.InputTag("tauGenJets"),
                                       select = cms.vstring(decayMode),
                                       filter = cms.bool(False)
                                       )
  process.generatedTausInAcceptance = cms.EDFilter("GenJetSelector",
                                           src = cms.InputTag("generatedTaus"),
                                           cut = cms.string(fiducialCuts),
                                           filter = cms.bool(False)
                                           )

  process.analysisSequence*= process.generatedTaus
  process.analysisSequence*= process.generatedTausInAcceptance


def goodVertexFilter(process):
  #CHECKME new vertex selection for taus available?
  process.primaryVertexFilter = cms.EDFilter("VertexSelector",
                                        src = cms.InputTag('offlineSlimmedPrimaryVertices'),
                                        cut = cms.string('ndof()>4&&position().rho()<2&&abs(z())<24'),
                                        filter = cms.bool(False)
  )   
  process.analysisSequence*= process.primaryVertexFilter  


def cloneAndReplaceInputTag(process,sequence,oldValue,newValue,postfix):
  #First Clone the sequence
  p = cloneProcessingSnippet(process, sequence, postfix)
  massSearchReplaceAnyInputTag(p,oldValue,newValue )
  modules = listModules(p)

  #Change the labels of the counters
  for mod in modules:
    if(hasattr(mod,'label')):
      if mod.label().find('Counter') !=-1 :
        if(hasattr(mod,'name')):
          newValue = mod.name.value()+postfix
          mod.name=cms.string(newValue)
  return p



def createSystematics(process,sequence,postfix,muScale,eScale,tauScale,jetScale,unclusteredScale,electronresb = 0.0, electronrese = 0.0, oneProngScale = 1.0,oneProngPi0Scale = 1.0, threeProngScale = 1.0):

  #First Clone the sequence
  p = cloneProcessingSnippet(process, sequence, postfix)
  modules = listModules(p)

  #Change the labels of the counters and the smearign modules
  for mod in modules:
    if(hasattr(mod,'label')):
      if mod.label().find('Counter') !=-1 :
        if(hasattr(mod,'name')):
          newValue = mod.name.value()+postfix
          mod.name=cms.string(newValue)
      if mod.label().find('smearedMuons') !=-1 :
          mod.energyScale = cms.double(muScale)
      if mod.label().find('smearedTaus') !=-1 :
          mod.energyScale = cms.double(tauScale)
          mod.oneProngEnergyScale = cms.double(oneProngScale)
          mod.oneProngPi0EnergyScale = cms.double(oneProngPi0Scale)
          mod.threeProngEnergyScale = cms.double(threeProngScale)
      if mod.label().find('smearedElectrons') !=-1 :
          mod.energyScale = cms.double(eScale)
          mod.deltaPtB = cms.double(electronresb)
          mod.deltaPtE = cms.double(electronrese)
      if mod.label().find('smearedJets') !=-1 :
          mod.energyScaleDB = cms.int32(jetScale)
      if mod.label().find('smearedMET') !=-1 :
          mod.unclusteredScale= cms.double(unclusteredScale)
  return cms.Path(p) 





def createRecoilSystematics(process,sequence,postfix,metScale,metResolution):

  #First Clone the sequence
  p = cloneProcessingSnippet(process, sequence, postfix)
  modules = listModules(p)

  #Change the labels of the counters and the smearign modules
  for mod in modules:
    if(hasattr(mod,'label')):
      if mod.label().find('Counter') !=-1 :
        if(hasattr(mod,'name')):
          newValue = mod.name.value()+postfix
          mod.name=cms.string(newValue)
      
  return cms.Path(p) 




def pfMetWithSignficance(process):

    # Get PFMET w/ significance
    process.load("TauAnalysis.CandidateTools.PFMETSignCovMatrixEmbedder_cfi")

    process.metWithSig = process.patMETSignEmbedder.clone(
        src = cms.InputTag("systematicsMET"),
        srcCov = cms.InputTag("pfMEtSignCovMatrix")
    )


    process.analysisSequence = cms.Sequence(
        process.analysisSequence *
        process.metWithSig
    )
 

