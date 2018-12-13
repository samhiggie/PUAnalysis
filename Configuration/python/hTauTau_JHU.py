import FWCore.ParameterSet.Config as cms


#Import tool that creates the cut sequence
from PUAnalysis.Configuration.tools.CutSequenceProducer import *

###############################			Ele-Tau 		###################################
TTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsTT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

#TTanalysisConfigurator.addSmearing('patOverloadedTaus','miniAODMuonID','miniAODElectronVID','filteredJets','slimmedMETs','TT')
#Create di muon pairs for veto purposes
TTanalysisConfigurator.addDiCandidateModule('diMuons','PATMuPairProducer','miniAODMuonID','miniAODMuonID','slimmedMETs','','patOverloadedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "",genParticles='prunedGenParticles')
#veto possible second zpeak
#TTanalysisConfigurator.addSelector('diMuonsOS','PATMuPairSelector','leg1.isPFMuon&&leg2.isPFMuon&&abs(leg1.eta())<3&&abs(leg2.eta())<3&&abs(leg1.userFloat("dZ"))<0.2&&abs(leg2.userFloat("dZ"))<0.2&&abs(leg2.userFloat("dXY"))<0.045&&abs(leg2.userFloat("dXY"))<0.045&&charge==0&&leg1.isGlobalMuon&&leg2.isGlobalMuon&&leg1.pt()>7&&leg2.pt()>7&&leg1.userFloat("dBRelIso")<0.5 &&leg2.userFloat("dBRelIso")<0.5','DiMuonCreation',0,100)
#TTanalysisConfigurator.addSorter('diMuonsOSSorted','PATMuPairSorter')

#Make DiTaus

TTanalysisConfigurator.addDiCandidateModule('diTaus','PATDiTauPairProducer','patOverloadedTaus','patOverloadedTaus','slimmedMETs','patOverloadedTaus','filteredJets',1,9999,text = 'AtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.3,recoMode = "",genParticles='prunedGenParticles')
#TTanalysisConfigurator.addDiCandidateModule('diTaus','PATDiTauPairProducer','smearedTausTT','smearedTausTT','smearedMETTT','smearedTausTT','smearedJetsTT',1,9999,text = 'AtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.3,recoMode = "",genParticles='prunedGenParticles')
TTanalysisConfigurator.addSelector('diTausElePtEta'   ,'PATDiTauPairSelector','leg1.pt()>39.5&&abs(leg1.eta())<2.1&&leg2.pt()>39.5&&abs(leg2.eta())<2.1','TTTauPtEta',1)
TTanalysisConfigurator.addSelector('diTausDecayFound' ,'PATDiTauPairSelector','abs(leg1.userFloat("taudZ"))<0.2&&leg1.tauID("decayModeFinding")>0.5&&abs(leg2.userFloat("taudZ"))<0.2&&leg2.tauID("decayModeFinding")>0.5','TTTauDecayFound',1)
TTanalysisConfigurator.addSelector('diTausStdDecaySel','PATDiTauPairSelector','abs(leg1.charge())==1&&abs(leg2.charge())==1','TTTauStandardDecayFound',1)
TTanalysisConfigurator.addSelector('diTausDRSel'      ,'PATDiTauPairSelector','dR12>0.5','TTTauDRSel',1)
TTanalysisConfigurator.addSelector('diTausIsolatedLoose','PATDiTauPairSelector','leg1.tauID("idVLoose2017v2")>0.5&&leg2.tauID("idVLoose2017v2")>0.5','TTIso1',1)
#TTanalysisConfigurator.addSorter('diTausSorted'       ,'PATDiTauPairSorter')
TTanalysisConfigurator.addSelector('diTausPreSync'    ,'PATDiTauPairSelector','charge==0||abs(charge)==2','TTSync',1)
TTanalysisConfigurator.addSorter(  'diTausSync'       ,'PATDiTauPairSorterByIsoDiTau')

#TTanalysisConfigurator.addSelector('diTausTriggerSelLeg1','PATDiTauPairSelector','leg1.userFloat("hltDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")>0','TTtriggerSelLeg1',1)
#TTanalysisConfigurator.addSelector('diTausTriggerSelLeg2','PATDiTauPairSelector','leg2.userFloat("hltDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg")>0','TTtriggerSelLeg2',1)


TTanalysisConfigurator.addSorter(  'diTausSyncTrig','PATDiTauPairSorterByIsoDiTau')


TTanalysisConfigurator.addSelector('diTausAntiEle' ,'PATDiTauPairSelector','leg1.tauID("againstElectronVLooseMVA6")>0.5&&leg2.tauID("againstElectronVLooseMVA6")>0.5','TTAntiEle',1)
TTanalysisConfigurator.addSelector('diTausAntiMu'  ,'PATDiTauPairSelector','leg1.tauID("againstMuonLoose3")>0.5&&leg2.tauID("againstMuonLoose3")>0.5','TTAntiMu',1)
TTanalysisConfigurator.addSelector('diTausIsolatedTight','PATDiTauPairSelector','leg1.tauID("byVTightIsolationMVArun2v1DBoldDMwLT")>0.5&&leg2.tauID("byVTightIsolationMVArun2v1DBoldDMwLT")>0.5','TTIso_2',1)
TTanalysisConfigurator.addSelector('diTausOS','PATDiTauPairSelector','charge==0','TTOS',1)
TTanalysisConfigurator.addSorter('diTausSortedFinal','PATDiTauPairSorter')
#create the sequence
selectionSequenceTT =TTanalysisConfigurator.returnSequence()

