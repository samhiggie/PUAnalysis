import FWCore.ParameterSet.Config as cms


#Import tool that creates the cut sequence
from PUAnalysis.Configuration.tools.CutSequenceProducer import *

###############################			Ele-Tau 		###################################
TTanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsTT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

#TTanalysisConfigurator.addSmearing('patOverloadedTaus','miniAODMuonID','miniAODElectronVID','filteredJets','slimmedMETsModifiedMET','TT')
#Create di muon pairs for veto purposes
TTanalysisConfigurator.addDiCandidateModule('diMuons','PATMuPairProducer','miniAODMuonID','miniAODMuonID','slimmedMETsModifiedMET','','filteredJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "",genParticles='prunedGenParticles')

#Make DiTaus

TTanalysisConfigurator.addDiCandidateModule('diTaus','PATDiTauPairProducer','patOverloadedTaus','patOverloadedTaus','slimmedMETsModifiedMET','patOverloadedTaus','filteredJets',1,9999,text = 'AtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.3,recoMode = "",genParticles='prunedGenParticles')
TTanalysisConfigurator.addSelector('diTausElePtEta'   ,'PATDiTauPairSelector','leg1.pt()>40.&&abs(leg1.eta())<2.1&&leg2.pt()>40.&&abs(leg2.eta())<2.1','TTTauPtEta',1)
TTanalysisConfigurator.addSelector('diTausDecayFound' ,'PATDiTauPairSelector','abs(leg1.userFloat("taudZ"))<0.2&&leg1.tauID("decayModeFinding")>0.5&&abs(leg2.userFloat("taudZ"))<0.2&&leg2.tauID("decayModeFinding")>0.5','TTTauDecayFound',1)
TTanalysisConfigurator.addSelector('diTausStdDecaySel','PATDiTauPairSelector','abs(leg1.charge())==1&&abs(leg2.charge())==1','TTTauStandardDecayFound',1)
TTanalysisConfigurator.addSelector('diTausDRSel'      ,'PATDiTauPairSelector','dR12>0.5','TTTauDRSel',1)
#VV Loose criterion for the sync
TTanalysisConfigurator.addSelector('diTausIsolatedVVLoose','PATDiTauPairSelector','leg1.tauID("idVVLoose2017v2")>0.5&&leg2.tauID("idVVLoose2017v2")>0.5','TTIso1',1)
TTanalysisConfigurator.addSelector('diTausSync'    ,'PATDiTauPairSelector','charge==0||abs(charge)==2','TTSync',1)

TTanalysisConfigurator.addSorter(  'diTausSyncTrig','PATDiTauPairSorterByIsoDiTau')


#create the sequence
selectionSequenceTT =TTanalysisConfigurator.returnSequence()

