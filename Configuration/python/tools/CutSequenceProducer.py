import FWCore.ParameterSet.Config as cms
import sys

metCalibration = cms.PSet(
                   applyCalibration = cms.bool(False),
                   calibrationScheme = cms.string("BothLegs"),
                   responseU1   = cms.string("1.33223-0.917782*x"),
                   responseU2   = cms.string("-0.013"),
                   resolutionU1 = cms.string("11.1566+0.0654529*x+0.000124436*x*x"),
                   resolutionU2 = cms.string("11.1235+0.0449872*x-6.39822e-5*x*x"),
                   responseMCU1   = cms.string("1.26247-0.950094*x"),
                   responseMCU2   = cms.string("-0.00544907"),
                   resolutionMCU1 = cms.string("10.6449+0.0436475*x+3.07554e-5*x*x"),
                   resolutionMCU2 = cms.string("10.5649+0.0225853*x-5.81371e-5*x*x")
)



def getInstanceName(obj, pyNameSpace = None, process = None):
    if process is not None:
         return obj.label()
    else:
         if pyNameSpace is not None:
               for name, ref in pyNameSpace.items():
                    if ref is obj : return name
         else:
               for pyModule in sys.modules.values():
                    for name, ref in pyModule.__dict__.items():
                        if ref is obj : return name
    return None


class CutSequenceProducer(cms._ParameterTypeBase):


    #init functions get the input collection to the cut sequence
    def __init__(self,initialCounter,pyModuleName,pyNameSpace) :
        self.input = ''
        self.pyModuleName = pyModuleName,
        self.pyNameSpace = pyNameSpace




       #Add the first Counter
        counter  = cms.EDProducer("EventCounter")
        counter.name=cms.string(initialCounter)
        counter.setLabel(initialCounter)
        pyModule = sys.modules[self.pyModuleName[0]]
        if pyModule is None:
            raise ValueError("'pyModuleName' Parameter invalid")
        setattr(pyModule,initialCounter+'Counter',counter)
        self.sequence=counter


    def addDiCandidateModule(self,moduleName,moduleType, src1,src2,met,taus,jets,min = 1,max=9999,text = '',leadingObjectsOnly = False,dR = 0.3,recoMode = "",genParticles = 'genTaus'):
               dicand  = cms.EDProducer(moduleType)
               dicand.useLeadingTausOnly = cms.bool(False)
               dicand.srcLeg1 = cms.InputTag(src1)
               dicand.srcLeg2 = cms.InputTag(src2)
               dicand.srcJets = cms.InputTag(jets)
               dicand.dRmin12 = cms.double(dR)
               dicand.srcMET = cms.InputTag(met)
               dicand.srcTaus = cms.InputTag(taus)
               dicand.srcPrimaryVertex = cms.InputTag("offlineSlimmedPrimaryVertices")
               dicand.srcBeamSpot = cms.InputTag("offlineBeamSpot")
               dicand.srcGenParticles = cms.InputTag(genParticles)
               dicand.recoMode = cms.string("")
               dicand.verbosity = cms.untracked.int32(0)
               dicand.doSVreco = cms.bool(False)
               dicand.metCalibration = metCalibration
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)

               self.sequence*=dicand

               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(min)
               filter.maxNumber = cms.uint32(max)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if text is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(text)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter



    def addCrossCleanerModule(self,moduleName,moduleType,min = 1,max=9999,text = '',dR = 0.1):
               dicand  = cms.EDProducer(moduleType)
               dicand.src = cms.InputTag(self.input)
               dicand.dR = cms.double(dR)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(min)
               filter.maxNumber = cms.uint32(max)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if text is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(text)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter

################################################################################
#####		Gen Particle Studies				       	   #####
################################################################################
    def addGenBSelector(self,moduleName):
			dicand  = cms.EDProducer('PATMuTauGenBJetSel')
			dicand.src = cms.InputTag(self.input)
			dicand.srcPrimaryVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
                        dicand.genParticles = cms.InputTag("genParticles")
                        dicand.jets = cms.InputTag("cleanPatJets")                  
			
			pyModule = sys.modules[self.pyModuleName[0]]
			if pyModule is None:
			 raise ValueError("'pyModuleName' Parameter invalid")
			setattr(pyModule,moduleName,dicand)
			self.sequence*=dicand
			self.input=moduleName



                   
 
                   
################################################################################
#####		Extra Lepton Veto	               		################
################################################################################
#currently used

    def addMuTauLVeto(self,moduleName,srcEle,srcMu):
			dicand  = cms.EDProducer('PATMuTauLVeto')
			dicand.src = cms.InputTag(self.input)
			dicand.srcE = cms.InputTag(srcEle)
			dicand.srcM = cms.InputTag(srcMu)
			dicand.hasMu = cms.bool(True)
			dicand.hasEle = cms.bool(False)
			
			pyModule = sys.modules[self.pyModuleName[0]]
			if pyModule is None:
			 raise ValueError("'pyModuleName' Parameter invalid")
			setattr(pyModule,moduleName,dicand)
			self.sequence*=dicand
			self.input=moduleName

               
    def addEleTauLVeto(self,moduleName,srcEle,srcMu):
			dicand  = cms.EDProducer('PATElecTauLVeto')
			dicand.src = cms.InputTag(self.input)
			dicand.srcE = cms.InputTag(srcEle)
			dicand.srcM = cms.InputTag(srcMu)
			dicand.hasMu = cms.bool(False)
			dicand.hasEle = cms.bool(True)
			
			pyModule = sys.modules[self.pyModuleName[0]]
			if pyModule is None:
			 raise ValueError("'pyModuleName' Parameter invalid")
			setattr(pyModule,moduleName,dicand)
			self.sequence*=dicand
			self.input=moduleName
               
                  
    
    def addDiTauLVeto(self,moduleName,srcEle,srcMu):
			dicand  = cms.EDProducer('PATDiTauLVeto')
			dicand.src = cms.InputTag(self.input)
			dicand.srcE = cms.InputTag(srcEle)
			dicand.srcM = cms.InputTag(srcMu)
			dicand.hasMu = cms.bool(False)
			dicand.hasEle = cms.bool(False)
			
			pyModule = sys.modules[self.pyModuleName[0]]
			if pyModule is None:
			 raise ValueError("'pyModuleName' Parameter invalid")
			setattr(pyModule,moduleName,dicand)
			self.sequence*=dicand
			self.input=moduleName
               


    def setSRC(self,src):
               self.input=src

    def addCandidateMETModule(self,moduleName,moduleType, srcLeptons,srcMET,srcJets,min = 1,max=9999,text = ''):
               dicand  = cms.EDProducer(moduleType)
               dicand.srcLeptons = cms.InputTag(srcLeptons)
               dicand.srcMET = cms.InputTag(srcMET)
               dicand.srcJets = cms.InputTag(srcJets)
               dicand.verbosity = cms.untracked.int32(0)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,dicand)
               self.sequence*=dicand
               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(min)
               filter.maxNumber = cms.uint32(max)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if text is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(text)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter

    def addSorter(self,moduleName,moduleType):
               selector  = cms.EDProducer(moduleType)
               selector.src = cms.InputTag(self.input)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,selector)

               self.sequence*=selector

               self.input=moduleName

    def addGeneric(self,moduleName,moduleType):
               selector  = cms.EDProducer(moduleType)
               selector.src = cms.InputTag(self.input)
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,selector)
               self.sequence*=selector
               self.input=moduleName


    def addSelector(self,moduleName,moduleType,cut,summaryText = None,minFilter = 1, maxFilter  = 9999):
               selector  = cms.EDFilter(moduleType)
               selector.src = cms.InputTag(self.input)
               selector.cut = cms.string(cut)
               selector.filter = cms.bool(False)

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,moduleName,selector)

               self.sequence*=selector

               self.input=moduleName

               #Create the Filter

               filter  = cms.EDFilter("PATCandViewCountFilter")
               filter.minNumber = cms.uint32(minFilter)
               filter.maxNumber = cms.uint32(maxFilter)
               filter.src = cms.InputTag(moduleName)
               filterName = moduleName+'Filter'
               filter.setLabel(filterName)
               #Register the filter in the namespace
               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,filterName,filter)
               self.sequence*=filter

          #now the counter
               if summaryText is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(summaryText)
                   counterName = moduleName+'Counter'
                   counter.setLabel(counterName)
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,counterName,counter)
                   self.sequence*=counter


    def addSmearing(self,taus,muons,electrons,jets,mets,mpost=''):
          smearedTaus = cms.EDProducer("SmearedTauProducer",
                                       src = cms.InputTag(taus),
                                       smearMCParticle = cms.bool(False),
                                       module_label = cms.string("CRAP"),
                                       energyScale  = cms.double(1.00),
                                       oneProngEnergyScale     = cms.double(1.00),
                                       oneProngPi0EnergyScale  = cms.double(1.00),
                                       threeProngEnergyScale   = cms.double(1.00),
                                       deltaEta     = cms.double(0.0),
                                       deltaPhi     = cms.double(0.0),
                                       deltaPtB     = cms.double(0.0),
                                       deltaPtE     = cms.double(0.0),
                                       smearConstituents = cms.bool(False),
                                       hadronEnergyScale = cms.double(1.0),
                                       gammaEnergyScale = cms.double(1.0)
                                       )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedTaus'+mpost,smearedTaus)
          self.sequence*=smearedTaus


          #add a post MET tau
          smearedTausID = cms.EDProducer("SmearedTauProducer",
                                       src = cms.InputTag('slimmedTaus'),
                                       smearMCParticle = cms.bool(False),
                                       module_label = cms.string("CRAP"),
                                       energyScale  = cms.double(1.0),
                                       oneProngEnergyScale     = cms.double(1.00),
                                       oneProngPi0EnergyScale  = cms.double(1.00),
                                       threeProngEnergyScale   = cms.double(1.00),
                                       deltaEta     = cms.double(0.0),
                                       deltaPhi     = cms.double(0.0),
                                       deltaPtB     = cms.double(0.0),
                                       deltaPtE     = cms.double(0.0),
                                       smearConstituents = cms.bool(False),
                                       hadronEnergyScale = cms.double(1.0),
                                       gammaEnergyScale = cms.double(1.0)
                                       )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedTausID'+mpost,smearedTausID)
          self.sequence*=smearedTausID



          smearedMuons = cms.EDProducer("SmearedMuonProducer",
                                        src = cms.InputTag(muons),
                                        smearMCParticle = cms.bool(False),
                                        module_label = cms.string("CRAP"),
                                        energyScale  = cms.double(1.0),
                                        deltaEta     = cms.double(0.0),
                                        deltaPhi     = cms.double(0.0),
                                        deltaPtB     = cms.double(0.0),
                                        deltaPtE     = cms.double(0.0)
                                        )


          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedMuons'+mpost,smearedMuons)
          self.sequence*=smearedMuons

          smearedMuonsID = cms.EDProducer("SmearedMuonProducer",
                                        src = cms.InputTag('slimmedMuons'),
                                        smearMCParticle = cms.bool(False),
                                        module_label = cms.string("CRAP"),
                                        energyScale  = cms.double(1.0),
                                        deltaEta     = cms.double(0.0),
                                        deltaPhi     = cms.double(0.0),
                                        deltaPtB     = cms.double(0.0),
                                        deltaPtE     = cms.double(0.0)
                                        )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedMuonsID'+mpost,smearedMuonsID)
          self.sequence*=smearedMuonsID


          smearedElectrons = cms.EDProducer("SmearedElectronProducer",
                                            src = cms.InputTag(electrons),
                                            smearMCParticle = cms.bool(False),
                                            module_label = cms.string("CRAP"),
                                            energyScale  = cms.double(1.0),
                                            deltaEta     = cms.double(0.0),
                                            deltaPhi     = cms.double(0.0),
                                            deltaPtB     = cms.double(0.0),
                                            deltaPtE     = cms.double(0.0)
                                            )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedElectrons'+mpost,smearedElectrons)
          self.sequence*=smearedElectrons

          smearedElectronsID = cms.EDProducer("SmearedElectronProducer",
                                            src = cms.InputTag('slimmedElectrons'),
                                            smearMCParticle = cms.bool(False),
                                            module_label = cms.string("CRAP"),
                                            energyScale  = cms.double(1.0),
                                            deltaEta     = cms.double(0.0),
                                            deltaPhi     = cms.double(0.0),
                                            deltaPtB     = cms.double(0.0),
                                            deltaPtE     = cms.double(0.0)
                                            )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedElectronsID'+mpost,smearedElectronsID)
          self.sequence*=smearedElectronsID

          smearedJets = cms.EDProducer("SmearedJetProducer",
                                       src = cms.InputTag(jets),#slimmedJets
                                       smearMCParticle = cms.bool(False),
                                       module_label = cms.string("CRAP"),
                                       energyScale  = cms.double(1.0),
                                       energyScaleDB= cms.int32(0),
                                       deltaEta     = cms.double(0.0),
                                       deltaPhi     = cms.double(0.0),
                                       deltaPtB     = cms.double(0.0),
                                       deltaPtE     = cms.double(0.0)
                                       )

          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedJets'+mpost,smearedJets)
          self.sequence*=smearedJets


          smearedMET = cms.EDProducer('METRecalculator',
                                      met = cms.InputTag(mets),
                                      originalObjects = cms.VInputTag(cms.InputTag('slimmedMuons'),
                                                                      cms.InputTag('slimmedElectrons'),
                                                                      cms.InputTag('slimmedTaus'),
                                                                      cms.InputTag('cleanPatJets')
                                                                      #cms.InputTag("smearedJets"+mpost)#FIXME
                                                                      ),
                                      smearedObjects = cms.VInputTag(cms.InputTag("smearedMuonsID"+mpost),
                                                                     cms.InputTag("smearedElectronsID"+mpost),
                                                                     cms.InputTag("smearedTausID"+mpost),
                                                                     cms.InputTag("smearedJets"+mpost)
                                                                 ),
                                      unclusteredScale = cms.double(1.0),
                                      threshold   = cms.double(0.)
                                      )
          pyModule = sys.modules[self.pyModuleName[0]]
          if pyModule is None:
              raise ValueError("'pyModuleName' Parameter invalid")
          setattr(pyModule,'smearedMET'+mpost,smearedMET)
          self.sequence*=smearedMET


    def addHLT(self,path,triggerProcess,summaryText = ''): # THIS IS A TRAP> NOT CURRENTLY USED ANYWHERE! CHECK NTPLES FOR TRIGGERFILLER
               hltSkimmer = cms.EDFilter("HLTHighLevel",
                          TriggerResultsTag = cms.InputTag("TriggerResults","",triggerProcess),
                          HLTPaths = cms.vstring(path),           # provide list of HLT paths (or patterns) you want
                          eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
                          andOr = cms.bool(True),             # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
                          throw = cms.bool(False)    # throw exception on unknown path names
               )

               pyModule = sys.modules[self.pyModuleName[0]]
               if pyModule is None:
                 raise ValueError("'pyModuleName' Parameter invalid")
               setattr(pyModule,'hltSkimmer',hltSkimmer)
               self.sequence*=hltSkimmer

          #now the counter
               if summaryText is not '':
                   counter  = cms.EDProducer("EventCounter")
                   counter.name=cms.string(summaryText)
                   counter.setLabel('hltSkimmerCounter')
                   pyModule = sys.modules[self.pyModuleName[0]]
                   if pyModule is None:
                       raise ValueError("'pyModuleName' Parameter invalid")
                   setattr(pyModule,'hltSkimmerCounter',counter)
                   self.sequence*=counter


    def returnSequence(self):
        return cms.Sequence(self.sequence)
