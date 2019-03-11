####
#script to plot all the JEC for the HTT analysis 
###

import ROOT
import numpy as np 


jetSyslist = ["Closure", "AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "TimePtEta", "Total"]


fin = ROOT.TFile("ttJEC/tauTau_m_sv.root","READ") 

for entry in fin:
    print entry
    
fin.Close()
