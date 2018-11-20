#!/usr/bin/env python
import ROOT
import re
from array import array
from collections import OrderedDict
import varCfgPlotter
import argparse
import os

parser = argparse.ArgumentParser(
    "Create pre/post-fit plots for SM HTT")
parser.add_argument(
    "--isLog",
    type=int,
    action="store",
    dest="isLog",
    default=1,
    help="Plot Log Y? (Integers 0, false, 1 true)")
parser.add_argument(
    "--channel",
    action="store",
    dest="channel",
    default="tt",
    help="Which channel to run over? (et, mt, em, tt)")
parser.add_argument(
    "--prefix",
    action="store",
    dest="prefix",
    default="",
    help="Provide prefix for TDirectory holding histograms such as 'prefit_' or postfin_'.  Default is '' and will search in CHANNEL_0jet, CHANNEL_boosted, CHANNEL_VBF")
parser.add_argument(
    "--higgsSF",
    type=int,
    action="store",
    dest="higgsSF",
    default=1.00,
    help="Provide the Scale Factor for the SM-Higgs signals.  100x is default")
parser.add_argument(
    "--inputFile",
    action="store",
    dest="inputFile",
    help="Provide the relative path to the target input file")
args = parser.parse_args()

channel = args.channel
isLog = args.isLog
prefix = args.prefix
categories = varCfgPlotter.getCategories( channel, prefix )
higgsSF = args.higgsSF
fileName = args.inputFile
if fileName == None :
    fileName = varCfgPlotter.getFile( channel )
assert (fileName != None), "Please provide a file name"

print "\nPlotting for:"
print " -- Channel:",channel
print " -- Plot", "Log" if isLog else "Linear"
print " -- Plotting for categories:"
for cat in categories :
    print "     -- ",cat
print " -- Using Higgs Scale Factor:",higgsSF
print " -- Target file:",fileName,"\n"



file = ROOT.TFile( fileName, "r" )
print file

# Category map for the LaTeX naming of histograms
catMap = {
    "em" : "e#mu",
    "et" : "e#tau_{h}",
    "mt" : "#mu#tau_{h}",
    "tt" : "#tau_{h}#tau_{h}",
}

def add_lumi():
    lowX=0.78
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    lumi.AddText("35.9 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.11
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.20
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    #lumi.AddText("Preliminary")
    return lumi

def make_legend():
	#if isLog:
	#   output = ROOT.TLegend(0.12, 0.05, 0.92, 0.25, "", "brNDC")
        #   output.SetNColumns(5)
	#else:
        #   output = ROOT.TLegend(0.0, 0.0, 1.0, 1.0, "", "brNDC")
	#   output.SetNColumns(2)
        output = ROOT.TLegend(0.0, 0.02, 1.0, 0.9, "", "brNDC")
        #output = ROOT.TLegend(0.2, 0.1, 0.47, 0.65, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        #output.SetFillStyle(0)
        output.SetFillColor(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        output.SetTextSize(0.10)
        return output

def make_legend_sub():
        output = ROOT.TLegend(0.0, 0.35, 1.0, 0.95, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillColor(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        output.SetTextSize(0.10)
        return output

# Can use to return all hists in a dir
def get_Keys_Of_Class( file_, dir_, class_ ) :
    keys = []
    d = file_.Get( dir_ )
    allKeys = d.GetListOfKeys()

    #print "keys of class"
    for k in allKeys :
        if k.GetClassName() == class_ :
            keys.append( k )

    return keys

binMap = varCfgPlotter.getBinMap()

ROOT.gStyle.SetFrameLineWidth(1)
ROOT.gStyle.SetLineWidth(1)
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(True)

c=ROOT.TCanvas("canvas","",0,0,1800,1000)
c.cd()


adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.4)

infoMap = varCfgPlotter.getInfoMap( higgsSF, channel )
bkgs = varCfgPlotter.getBackgrounds()
signals = varCfgPlotter.getSignals()


for cat in categories:
    print "Plotting for:",cat
    
    # Get list of the keys to hists in our category directory
    #if channel == "tt" :
    #    histKeys = get_Keys_Of_Class( file, cat, "TH1D" )
    #else :
    #    histKeys = get_Keys_Of_Class( file, cat, "TH1F" )
    histKeys = get_Keys_Of_Class( file, cat, "TH1F" )
    
    # Get nominal shapes for all processes
    initHists = {}
    for key in histKeys :
        if "_CMS_" in key.GetName() : continue
        # skip the higgs mass +/-
        if "120" in key.GetName() or "130" in key.GetName() : continue
        initHists[ key.GetName() ] = key.ReadObj()
    
        # to merge later, we need clearly defined under and overflow bins
        #print initHists[ key.GetName() ]
        #initHists[ key.GetName() ].ClearUnderflowAndOverflow()
    

    # Check for a few fundamental histos
    assert (initHists["data_obs"] != None), "Where's your data hist?!"
    assert (initHists["ZTT"] != None), "Where's your ZTT hist?!"
    #for sig in signals :
    #    assert (initHists[sig] != None), "Where's your %s?!" % sig

    
    nBins = initHists["data_obs"].GetXaxis().GetNbins()
    total = initHists["TotalBkg"]
    signal= initHists["TotalSig"]
    signal.SetLineColor(2)
    signal.SetLineWidth(2)
    signal_tostack=signal.Clone()
    signal_tostack.SetLineColor(2)#FIXME
    signal_tostack.SetFillColor(2)
    signal_tostack.SetLineWidth(1)
    binWidth = initHists["data_obs"].GetBinWidth(1)
    # FIXME, we could look at variable binning, but that ontop of
    # unrolled histograms would be a bit much

    
    # Make the final hists, some initial shapes need to be merged
    hists = {}
    for name, val in infoMap.iteritems() :
        #hists[ name ] = ROOT.TH1F( name+cat, val[1], nBins, 0, nBins*binWidth )
	hists[ name ] = initHists["data_obs"].Clone()
        hists[ name ].Scale(0)
        hists[ name ].Sumw2()
        for toAdd in val[0] :
            if not toAdd in initHists :
                print toAdd," not in your file: %s, directory, %s" % (file, cat)
                continue
            hists[ name ].Add( initHists[ toAdd ] )
    
        if name not in signals :
            hists[ name ].SetFillColor(ROOT.TColor.GetColor( val[3] ) )
            hists[ name ].SetLineColor(ROOT.TColor.GetColor( val[3] ))
	    #hists[ name ].SetLineColor(ROOT.TColor.GetColor( val[3] ) )
        
    
    # Set aesthetics

    for k in range(1,hists["data_obs"].GetSize()-1):
       if hists["data_obs"].GetBinContent(k)==0:
           hists["data_obs"].SetBinError(k,1.8)

    hists["data_obs"].GetXaxis().SetTitle("")
    hists["data_obs"].GetXaxis().SetTitleSize(0)
    hists["data_obs"].GetXaxis().SetNdivisions(505)
    hists["data_obs"].GetYaxis().SetLabelFont(42)
    hists["data_obs"].GetYaxis().SetLabelOffset(0.01)
    hists["data_obs"].GetYaxis().SetLabelSize(0.06)
    hists["data_obs"].GetYaxis().SetTitleSize(0.085)
    hists["data_obs"].GetYaxis().SetTitleOffset(0.56)
    hists["data_obs"].GetYaxis().SetTickLength(0.012)
    hists["data_obs"].SetTitle("")
    hists["data_obs"].GetYaxis().SetTitle("Events/bin")
    hists["data_obs"].SetMarkerStyle(20)
    hists["data_obs"].SetMarkerSize(2)
    hists["data_obs"].SetLineWidth(2)
    for sig in signals :
        hists[ sig ].SetLineColor(2)#ROOT.TColor.GetColor( infoMap[ sig ][3] ))
        hists[ sig ].SetLineWidth(2)
    
    #errorBand=hists["ZTT"].Clone()
    #for bkg in bkgs :
    #    if bkg == "ZTT" : continue
    #    errorBand.Add(hists[bkg])
    errorBand=total.Clone()
    errorBandSB=errorBand.Clone()
    errorBandSB.Sumw2()
    errorBandSB.Add(signal)

    eps=0.00000000001

    bkg_noerror=errorBand.Clone()
    for l in range(1,errorBand.GetSize()-1):
       bkg_noerror.SetBinError(l,0)
    sqrt_bkg=[(errorBand.GetBinContent(1))**0.5]
    for l in range(1,errorBand.GetSize()-1):
       sqrt_bkg.append((errorBand.GetBinContent(l))**0.5+eps)
       #sqrt_bkg.append(1.0)

    subtrac=hists["data_obs"].Clone()
    subtrac.Add(bkg_noerror,-1)
    #subtrac.Divide(bkg_noerror)
    subtrac_sig=signal.Clone()
    #subtrac_sig.Divide(bkg_noerror)
    subtrac_sig.SetLineColor(2)
    subtrac_bkg=errorBand.Clone()
    subtrac_bkg.Add(bkg_noerror,-1)
    #subtrac_bkg.Divide(bkg_noerror)

    #for l in range(1,errorBand.GetSize()-1):
    #    print l,sqrt_bkg[l],errorBand.GetBinContent(l)
    #	subtrac.SetBinContent(l,subtrac.GetBinContent(l)/sqrt_bkg[l])
    #    subtrac.SetBinError(l,subtrac.GetBinError(l)/sqrt_bkg[l])
    #    subtrac_sig.SetBinContent(l,subtrac_sig.GetBinContent(l)/sqrt_bkg[l])
    #    subtrac_sig.SetBinError(l,subtrac_sig.GetBinError(l)/sqrt_bkg[l])
    #    subtrac_bkg.SetBinContent(l,subtrac_bkg.GetBinContent(l)/sqrt_bkg[l])
    #    subtrac_bkg.SetBinError(l,subtrac_bkg.GetBinError(l)/sqrt_bkg[l])

    for l in range(1,errorBand.GetSize()-1):
        print l,sqrt_bkg[l],errorBand.GetBinContent(l)
        subtrac.SetBinContent(l,subtrac.GetBinContent(l)/total.GetBinError(l))
        subtrac.SetBinError(l,subtrac.GetBinError(l)/total.GetBinError(l))
        subtrac_sig.SetBinContent(l,subtrac_sig.GetBinContent(l)/total.GetBinError(l))
        subtrac_sig.SetBinError(l,subtrac_sig.GetBinError(l)/total.GetBinError(l))
        subtrac_bkg.SetBinContent(l,subtrac_bkg.GetBinContent(l)/total.GetBinError(l))
        subtrac_bkg.SetBinError(l,subtrac_bkg.GetBinError(l)/total.GetBinError(l))
    
    # Build our stack
    stack=ROOT.THStack("stack","stack")
    for bkg in bkgs :
        stack.Add( hists[bkg] )
    stack.Add(signal_tostack)
    
    errorBand.SetMarkerSize(0)
    errorBand.SetFillColor(new_idx)
    #errorBand.SetFillStyle(2008)
    errorBand.SetLineColor(1)

    errorBandSB.SetMarkerSize(0)
    errorBandSB.SetFillColor(new_idx)
    #errorBandSB.SetFillStyle(2008)
    errorBandSB.SetLineColor(1)

    subtrac_bkg.SetMarkerSize(0)
    subtrac_bkg.SetFillColor(new_idx)
    #subtrac_bkg.SetFillStyle(2008)
    subtrac_bkg.SetLineWidth(1)
    
    pad1 = ROOT.TPad("pad1","pad1",0,0.40,0.88,1)
    pad1.Draw()
    pad1.cd()
    pad1.SetFillColor(0)
    pad1.SetBorderMode(0)
    pad1.SetBorderSize(10)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad1.SetLeftMargin(0.10)
    pad1.SetRightMargin(0.05)
    pad1.SetTopMargin(0.122)
    pad1.SetBottomMargin(0.026)
    pad1.SetFrameFillStyle(0)
    pad1.SetFrameLineStyle(0)
    pad1.SetFrameLineWidth(2)
    pad1.SetFrameBorderMode(0)
    pad1.SetFrameBorderSize(10)
    if isLog and ("_19999_" not in cat):
        pad1.SetLogy()
    
    hists["data_obs"].GetXaxis().SetLabelSize(0)
    hists["data_obs"].SetMaximum(hists["data_obs"].GetMaximum()*1.35)
    hists["data_obs"].SetMinimum(0.0)
    if isLog and ("_1999_" not in cat):
        hists["data_obs"].SetMaximum(hists["data_obs"].GetMaximum()*5.35)
        hists["data_obs"].SetMinimum(0.05)
	if ("_1_" in cat and "em" not in cat):
	    hists["data_obs"].SetMinimum(1)
        if ("_2_" in cat):
            hists["data_obs"].SetMinimum(0.1)
    for k in range(1,hists["data_obs"].GetSize()-1):
        s=0.0
        for sig in signals :
            s += hists[sig].GetBinContent(k)
        b=0.0
        for bkg in bkgs :
            b += hists[bkg].GetBinContent(k)
        if (b<0):
            b=0.000001
        #if (0.0000001*s/(0.0000001+s+b)**0.5 > 0.2):
        #   hists["data_obs"].SetBinContent(k,100000000)
        #   hists["data_obs"].SetBinError(k,0)
    hists["data_obs"].Draw("e0p")
    stack.Draw("histsame")
    errorBandSB.Draw("e2same")
    for sig in signals :
        hists[ sig ].Scale(higgsSF)
        hists[ sig ].Draw("histsame")
    hists["data_obs"].Draw("e0psame")
    
    
    # Add the nice pretty gray lines to deliniate
    # where out higgs_pt / mjj bins start/stop
    line=[]
    label=[]
    nx=0
    ny=0
    if not ("_tt_1" in cat):
        nx = binMap[channel][cat]["nx"]
        ny = binMap[channel][cat]["ny"]
    for z in range(1, nx+1):
        if channel == "tt" and (cat == "tt_0jet" or "_tt_1" in cat): continue # tt_0jet not unrolled!
        line.append(ROOT.TLine(z*ny,0,z*ny,hists["data_obs"].GetMaximum()))
        line[z-1].SetLineStyle(3)
        line[z-1].Draw("same")
        posx=0.102+0.85*(z-1)/nx
        label.append(ROOT.TPaveText(posx, 0.73, posx+0.15, 0.73+0.155, "NDC"))
        
        # Label each unrolled bin
        if ("_et_1" in cat or "_mt_1" in cat): 
           label[z-1].AddText(str(binMap[channel][cat]["binning"][z-1]))
        #else : 
	#   label[z-1].AddText(binMap[channel][cat]["name"]+" > "+str(binMap[channel][cat]["binning"][z-1])+" GeV")
        elif z<nx :
           label[z-1].AddText(str(binMap[channel][cat]["binning"][z-1])+" < "+ binMap[channel][cat]["name"]+" < "+str(binMap[channel][cat]["binning"][z])+" GeV")
	else :
           label[z-1].AddText(binMap[channel][cat]["name"]+" > "+str(binMap[channel][cat]["binning"][z-1])+" GeV")
        label[z-1].SetBorderSize(   0 )
        label[z-1].SetFillStyle(    0 )
        label[z-1].SetTextAlign(   12 )
        label[z-1].SetTextSize ( 0.05 )
	if ("_et_2" in cat or "_mt_2" in cat or "_em_2" in cat):
	   label[z-1].SetTextSize ( 0.04 )
        label[z-1].SetTextColor(    1 )
        label[z-1].SetTextFont (   42 )
        label[z-1].Draw("same")
    
    
    l1=add_lumi()
    l1.Draw("same")
    l2=add_CMS()
    l2.Draw("same")
    l3=add_Preliminary()
    l3.Draw("same")
    
    pad1.RedrawAxis()
    
    categ  = ROOT.TPaveText(0.45, 0.865, 0.60, 0.865+0.155, "NDC")
    categ.SetBorderSize(   0 )
    categ.SetFillStyle(    0 )
    categ.SetTextAlign(   12 )
    categ.SetTextSize ( 0.06 )
    categ.SetTextColor(    1 )
    categ.SetTextFont (   42 )
    if "0jet" in cat: 
        categ.AddText(catMap[channel]+", 0 jet")
    if "_1_" in cat:
        categ.AddText(catMap[channel]+", 0 jet")
    elif "boosted" in cat:
        categ.AddText(catMap[channel]+", Boosted")
    elif "_2_" in cat:
        categ.AddText(catMap[channel]+", Boosted")
    elif "VBF" in cat:
        categ.AddText(catMap[channel]+", VBF")
    elif "vbf" in cat:
        categ.AddText(catMap[channel]+", VBF")
    elif "_3_" in cat:
        categ.AddText(catMap[channel]+", VBF")
    categ.Draw("same")
    
    c.cd()
    pad2 = ROOT.TPad("pad2","pad2",0,0,0.88,0.40);
    pad2.SetTopMargin(0.05);
    pad2.SetBottomMargin(0.55);
    pad2.SetLeftMargin(0.10);
    pad2.SetRightMargin(0.05);
    pad2.SetTickx(1)
    pad2.SetTicky(1)
    pad2.SetFrameLineWidth(2)
    #pad2.SetGridx()
    pad2.SetGridy()
    pad2.Draw()
    pad2.cd()
    h1=hists["data_obs"].Clone()
    #h1.SetMaximum(1.8)#FIXME(1.5)
    #h1.SetMinimum(0.2)#FIXME(0.5)
    #subtrac.SetMaximum(max(2.1,1.1*subtrac.GetMaximum()))#FIXME(1.5)
    subtrac.SetMaximum(1.1*subtrac.GetMaximum())
    subtrac.SetMinimum(1.1*subtrac.GetMinimum())#FIXME(0.5)
    #if channel == "tt" and (cat == "tt_0jet" or "tt_2" in cat):
    #    subtrac.SetMaximum(1.5)
    #if channel == "et" and (cat == "et_0jet" or "et_2" in cat):
    #    subtrac.SetMaximum(0.8)
    #if channel == "mt" and (cat == "et_0jet" or "mt_3" in cat):
    #    subtrac.SetMaximum(2.8)
    #if channel == "em" and (cat == "em_0jet" or "em_3" in cat):
    #    subtrac.SetMaximum(0.7)
    h1.SetMarkerStyle(20)
    h3=errorBand.Clone()
    hwoE=errorBand.Clone()
    for iii in range (1,hwoE.GetSize()-2):
      hwoE.SetBinError(iii,0)
    h3.Sumw2()
    h1.Sumw2()
    h1.SetStats(0)
    h1.Divide(hwoE)
    h3.Divide(hwoE)
    subtrac.GetXaxis().SetTitle("2D bin number")
    subtrac.GetXaxis().SetTitle("m_{#tau#tau} (GeV)")
    if (channel == "em" or channel=="et" or channel=="mt") and ("_1_" in cat):
       subtrac.GetXaxis().SetTitle("m_{vis} (GeV)")
    subtrac.LabelsOption("v","X")
    subtrac.GetXaxis().SetLabelOffset(0.02)
    subtrac.GetXaxis().SetLabelSize(0.06)
    if channel == "tt" and ("tt_2" in cat or "tt_3" in cat):
       subtrac.GetXaxis().SetBinLabel(1,"0-40")
       subtrac.GetXaxis().SetBinLabel(2,"40-60")
       subtrac.GetXaxis().SetBinLabel(3,"60-70")
       subtrac.GetXaxis().SetBinLabel(4,"70-80")
       subtrac.GetXaxis().SetBinLabel(5,"80-90")
       subtrac.GetXaxis().SetBinLabel(6,"90-100")
       subtrac.GetXaxis().SetBinLabel(7,"100-110")
       subtrac.GetXaxis().SetBinLabel(8,"110-120")
       subtrac.GetXaxis().SetBinLabel(9,"120-130")
       subtrac.GetXaxis().SetBinLabel(10,"130-150")
       subtrac.GetXaxis().SetBinLabel(11,"150-200")
       subtrac.GetXaxis().SetBinLabel(12,"200-250")
       subtrac.GetXaxis().SetBinLabel(13,"0-40")
       subtrac.GetXaxis().SetBinLabel(14,"40-60")
       subtrac.GetXaxis().SetBinLabel(15,"60-70")
       subtrac.GetXaxis().SetBinLabel(16,"70-80")
       subtrac.GetXaxis().SetBinLabel(17,"80-90")
       subtrac.GetXaxis().SetBinLabel(18,"90-100")
       subtrac.GetXaxis().SetBinLabel(19,"100-110")
       subtrac.GetXaxis().SetBinLabel(20,"110-120")
       subtrac.GetXaxis().SetBinLabel(21,"120-130")
       subtrac.GetXaxis().SetBinLabel(22,"130-150")
       subtrac.GetXaxis().SetBinLabel(23,"150-200")
       subtrac.GetXaxis().SetBinLabel(24,"200-250")
       subtrac.GetXaxis().SetBinLabel(25,"0-40")
       subtrac.GetXaxis().SetBinLabel(26,"40-60")
       subtrac.GetXaxis().SetBinLabel(27,"60-70")
       subtrac.GetXaxis().SetBinLabel(28,"70-80")
       subtrac.GetXaxis().SetBinLabel(29,"80-90")
       subtrac.GetXaxis().SetBinLabel(30,"90-100")
       subtrac.GetXaxis().SetBinLabel(31,"100-110")
       subtrac.GetXaxis().SetBinLabel(32,"110-120")
       subtrac.GetXaxis().SetBinLabel(33,"120-130")
       subtrac.GetXaxis().SetBinLabel(34,"130-150")
       subtrac.GetXaxis().SetBinLabel(35,"150-200")
       subtrac.GetXaxis().SetBinLabel(36,"200-250")
       subtrac.GetXaxis().SetBinLabel(37,"0-40")
       subtrac.GetXaxis().SetBinLabel(38,"40-60")
       subtrac.GetXaxis().SetBinLabel(39,"60-70")
       subtrac.GetXaxis().SetBinLabel(40,"70-80")
       subtrac.GetXaxis().SetBinLabel(41,"80-90")
       subtrac.GetXaxis().SetBinLabel(42,"90-100")
       subtrac.GetXaxis().SetBinLabel(43,"100-110")
       subtrac.GetXaxis().SetBinLabel(44,"110-120")
       subtrac.GetXaxis().SetBinLabel(45,"120-130")
       subtrac.GetXaxis().SetBinLabel(46,"130-150")
       subtrac.GetXaxis().SetBinLabel(47,"150-200")
       subtrac.GetXaxis().SetBinLabel(48,"200-250")

    if (channel == "em") and ("_1_" in cat):
       subtrac.GetXaxis().SetBinLabel(1,"0-50")
       subtrac.GetXaxis().SetBinLabel(2,"50-55")
       subtrac.GetXaxis().SetBinLabel(3,"55-60")
       subtrac.GetXaxis().SetBinLabel(4,"60-65")
       subtrac.GetXaxis().SetBinLabel(5,"65-70")
       subtrac.GetXaxis().SetBinLabel(6,"70-75")
       subtrac.GetXaxis().SetBinLabel(7,"75-80")
       subtrac.GetXaxis().SetBinLabel(8,"80-85")
       subtrac.GetXaxis().SetBinLabel(9,"85-90")
       subtrac.GetXaxis().SetBinLabel(10,"90-95")
       subtrac.GetXaxis().SetBinLabel(11,"95-100")
       subtrac.GetXaxis().SetBinLabel(12,"100-400")
       subtrac.GetXaxis().SetBinLabel(13,"0-50")
       subtrac.GetXaxis().SetBinLabel(14,"50-55")
       subtrac.GetXaxis().SetBinLabel(15,"55-60")
       subtrac.GetXaxis().SetBinLabel(16,"60-65")
       subtrac.GetXaxis().SetBinLabel(17,"65-70")
       subtrac.GetXaxis().SetBinLabel(18,"70-75")
       subtrac.GetXaxis().SetBinLabel(19,"75-80")
       subtrac.GetXaxis().SetBinLabel(20,"80-85")
       subtrac.GetXaxis().SetBinLabel(21,"85-90")
       subtrac.GetXaxis().SetBinLabel(22,"90-95")
       subtrac.GetXaxis().SetBinLabel(23,"95-100")
       subtrac.GetXaxis().SetBinLabel(24,"100-400")
       subtrac.GetXaxis().SetBinLabel(25,"0-50")
       subtrac.GetXaxis().SetBinLabel(26,"50-55")
       subtrac.GetXaxis().SetBinLabel(27,"55-60")
       subtrac.GetXaxis().SetBinLabel(28,"60-65")
       subtrac.GetXaxis().SetBinLabel(29,"65-70")
       subtrac.GetXaxis().SetBinLabel(30,"70-75")
       subtrac.GetXaxis().SetBinLabel(31,"75-80")
       subtrac.GetXaxis().SetBinLabel(32,"80-85")
       subtrac.GetXaxis().SetBinLabel(33,"85-90")
       subtrac.GetXaxis().SetBinLabel(34,"90-95")
       subtrac.GetXaxis().SetBinLabel(35,"95-100")
       subtrac.GetXaxis().SetBinLabel(36,"100-400")

    if (channel == "mt" or channel=="et") and ("_1_" in cat):
       subtrac.GetXaxis().SetBinLabel(1,"0-60")
       subtrac.GetXaxis().SetBinLabel(2,"60-65")
       subtrac.GetXaxis().SetBinLabel(3,"65-70")
       subtrac.GetXaxis().SetBinLabel(4,"70-75")
       subtrac.GetXaxis().SetBinLabel(5,"75-80")
       subtrac.GetXaxis().SetBinLabel(6,"80-85")
       subtrac.GetXaxis().SetBinLabel(7,"85-90")
       subtrac.GetXaxis().SetBinLabel(8,"90-95")
       subtrac.GetXaxis().SetBinLabel(9,"95-100")
       subtrac.GetXaxis().SetBinLabel(10,"100-105")
       subtrac.GetXaxis().SetBinLabel(11,"105-110")
       subtrac.GetXaxis().SetBinLabel(12,"110-400")
       subtrac.GetXaxis().SetBinLabel(13,"0-60")
       subtrac.GetXaxis().SetBinLabel(14,"60-65")
       subtrac.GetXaxis().SetBinLabel(15,"65-70")
       subtrac.GetXaxis().SetBinLabel(16,"70-75")
       subtrac.GetXaxis().SetBinLabel(17,"75-80")
       subtrac.GetXaxis().SetBinLabel(18,"80-85")
       subtrac.GetXaxis().SetBinLabel(19,"85-90")
       subtrac.GetXaxis().SetBinLabel(20,"90-95")
       subtrac.GetXaxis().SetBinLabel(21,"95-100")
       subtrac.GetXaxis().SetBinLabel(22,"100-105")
       subtrac.GetXaxis().SetBinLabel(23,"105-110")
       subtrac.GetXaxis().SetBinLabel(24,"110-400")
       subtrac.GetXaxis().SetBinLabel(25,"0-60")
       subtrac.GetXaxis().SetBinLabel(26,"60-65")
       subtrac.GetXaxis().SetBinLabel(27,"65-70")
       subtrac.GetXaxis().SetBinLabel(28,"70-75")
       subtrac.GetXaxis().SetBinLabel(29,"75-80")
       subtrac.GetXaxis().SetBinLabel(30,"80-85")
       subtrac.GetXaxis().SetBinLabel(31,"85-90")
       subtrac.GetXaxis().SetBinLabel(32,"90-95")
       subtrac.GetXaxis().SetBinLabel(33,"95-100")
       subtrac.GetXaxis().SetBinLabel(34,"100-105")
       subtrac.GetXaxis().SetBinLabel(35,"105-110")
       subtrac.GetXaxis().SetBinLabel(36,"110-400")

    if (channel == "mt" or channel=="et" or channel=="em") and ("_3_" in cat):
       subtrac.GetXaxis().SetBinLabel(1,"0-95")
       subtrac.GetXaxis().SetBinLabel(2,"95-115")
       subtrac.GetXaxis().SetBinLabel(3,"115-135")
       subtrac.GetXaxis().SetBinLabel(4,"135-155")
       subtrac.GetXaxis().SetBinLabel(5,"155-400")
       subtrac.GetXaxis().SetBinLabel(6,"0-95")
       subtrac.GetXaxis().SetBinLabel(7,"95-115")
       subtrac.GetXaxis().SetBinLabel(8,"115-135")
       subtrac.GetXaxis().SetBinLabel(9,"135-155")
       subtrac.GetXaxis().SetBinLabel(10,"155-400")
       subtrac.GetXaxis().SetBinLabel(11,"0-95")
       subtrac.GetXaxis().SetBinLabel(12,"95-115")
       subtrac.GetXaxis().SetBinLabel(13,"115-135")
       subtrac.GetXaxis().SetBinLabel(14,"135-155")
       subtrac.GetXaxis().SetBinLabel(15,"155-400")
       subtrac.GetXaxis().SetBinLabel(16,"0-95")
       subtrac.GetXaxis().SetBinLabel(17,"95-115")
       subtrac.GetXaxis().SetBinLabel(18,"115-135")
       subtrac.GetXaxis().SetBinLabel(19,"135-155")
       subtrac.GetXaxis().SetBinLabel(20,"155-400")

    if (channel == "mt" or channel=="et" or channel=="em") and ("_2_" in cat):
       subtrac.GetXaxis().SetBinLabel(1,"0-80")
       subtrac.GetXaxis().SetBinLabel(2,"80-90")
       subtrac.GetXaxis().SetBinLabel(3,"90-100")
       subtrac.GetXaxis().SetBinLabel(4,"100-110")
       subtrac.GetXaxis().SetBinLabel(5,"110-120")
       subtrac.GetXaxis().SetBinLabel(6,"120-130")
       subtrac.GetXaxis().SetBinLabel(7,"130-140")
       subtrac.GetXaxis().SetBinLabel(8,"140-150")
       subtrac.GetXaxis().SetBinLabel(9,"150-160")
       subtrac.GetXaxis().SetBinLabel(10,"160-300")
       subtrac.GetXaxis().SetBinLabel(11,"0-80")
       subtrac.GetXaxis().SetBinLabel(12,"80-90")
       subtrac.GetXaxis().SetBinLabel(13,"90-100")
       subtrac.GetXaxis().SetBinLabel(14,"100-110")
       subtrac.GetXaxis().SetBinLabel(15,"110-120")
       subtrac.GetXaxis().SetBinLabel(16,"120-130")
       subtrac.GetXaxis().SetBinLabel(17,"130-140")
       subtrac.GetXaxis().SetBinLabel(18,"140-150")
       subtrac.GetXaxis().SetBinLabel(19,"150-160")
       subtrac.GetXaxis().SetBinLabel(20,"160-300")
       subtrac.GetXaxis().SetBinLabel(21,"0-80")
       subtrac.GetXaxis().SetBinLabel(22,"80-90")
       subtrac.GetXaxis().SetBinLabel(23,"90-100")
       subtrac.GetXaxis().SetBinLabel(24,"100-110")
       subtrac.GetXaxis().SetBinLabel(25,"110-120")
       subtrac.GetXaxis().SetBinLabel(26,"120-130")
       subtrac.GetXaxis().SetBinLabel(27,"130-140")
       subtrac.GetXaxis().SetBinLabel(28,"140-150")
       subtrac.GetXaxis().SetBinLabel(29,"150-160")
       subtrac.GetXaxis().SetBinLabel(30,"160-300")
       subtrac.GetXaxis().SetBinLabel(31,"0-80")
       subtrac.GetXaxis().SetBinLabel(32,"80-90")
       subtrac.GetXaxis().SetBinLabel(33,"90-100")
       subtrac.GetXaxis().SetBinLabel(34,"100-110")
       subtrac.GetXaxis().SetBinLabel(35,"110-120")
       subtrac.GetXaxis().SetBinLabel(36,"120-130")
       subtrac.GetXaxis().SetBinLabel(37,"130-140")
       subtrac.GetXaxis().SetBinLabel(38,"140-150")
       subtrac.GetXaxis().SetBinLabel(39,"150-160")
       subtrac.GetXaxis().SetBinLabel(40,"160-300")
       subtrac.GetXaxis().SetBinLabel(41,"0-80")
       subtrac.GetXaxis().SetBinLabel(42,"80-90")
       subtrac.GetXaxis().SetBinLabel(43,"90-100")
       subtrac.GetXaxis().SetBinLabel(44,"100-110")
       subtrac.GetXaxis().SetBinLabel(45,"110-120")
       subtrac.GetXaxis().SetBinLabel(46,"120-130")
       subtrac.GetXaxis().SetBinLabel(47,"130-140")
       subtrac.GetXaxis().SetBinLabel(48,"140-150")
       subtrac.GetXaxis().SetBinLabel(49,"150-160")
       subtrac.GetXaxis().SetBinLabel(50,"160-300")
       subtrac.GetXaxis().SetBinLabel(51,"0-80")
       subtrac.GetXaxis().SetBinLabel(52,"80-90")
       subtrac.GetXaxis().SetBinLabel(53,"90-100")
       subtrac.GetXaxis().SetBinLabel(54,"100-110")
       subtrac.GetXaxis().SetBinLabel(55,"110-120")
       subtrac.GetXaxis().SetBinLabel(56,"120-130")
       subtrac.GetXaxis().SetBinLabel(57,"130-140")
       subtrac.GetXaxis().SetBinLabel(58,"140-150")
       subtrac.GetXaxis().SetBinLabel(59,"150-160")
       subtrac.GetXaxis().SetBinLabel(60,"160-300")

    subtrac.GetXaxis().SetLabelSize(0.07)
    subtrac.GetYaxis().SetLabelSize(0.08)
    subtrac.GetYaxis().SetTickLength(0.012)
    #subtrac.GetYaxis().SetTitle("#frac{(Obs.-Bkg.)}{#sqrt{Bkg.}}")
    subtrac.GetYaxis().SetTitle("#frac{(Obs. - bkg.)}{Bkg. unc.}")
    subtrac.GetYaxis().SetNdivisions(5)
    
    subtrac.GetXaxis().SetTitleSize(0.15)
    subtrac.GetYaxis().SetTitleSize(0.10)
    subtrac.GetYaxis().SetTitleOffset(0.4)
    subtrac.GetXaxis().SetTitleOffset(1.65)
    subtrac.GetXaxis().SetLabelSize(0.09)
    if ("em_3" in cat or "et_3" in cat or "mt_3" in cat or "em_1" in cat or "et_1" in cat or "mt_1" in cat):
      subtrac.GetXaxis().SetLabelSize(0.11)
    subtrac.GetYaxis().SetLabelSize(0.11)
    subtrac.GetXaxis().SetTitleFont(42)
    subtrac.GetYaxis().SetTitleFont(42)
    
    #h1.Draw("e0psame")
    #h3.Draw("e2same")
    subtrac.Draw("e0p")
    subtrac.LabelsOption("v","X")
    subtrac.Draw("e0p")
    subtrac_bkg.Draw("e2same")
    subtrac_sig.Draw("histsame")
    subtrac.Draw("e0psame")
    
    line2=[]
    for z in range(1,nx):
        line2.append(ROOT.TLine(z*ny,subtrac.GetMinimum(),z*ny,subtrac.GetMaximum()))
        line2[z-1].SetLineStyle(3)
        line2[z-1].Draw("same")
    
    
    c.cd()
    pad1.Draw()

    c.cd()

    pad3 = ROOT.TPad("pad3","pad3",0.86,0.40,1.0,1)
    pad3.Draw()
    pad3.cd()
    pad3.SetFillColor(0)
    pad3.SetBorderMode(0)
    pad3.SetBorderSize(10)
    pad3.SetTickx(1)
    pad3.SetTicky(1)
    pad3.SetTopMargin(0.122)
    pad3.SetBottomMargin(0.026)
    pad3.SetFrameFillStyle(0)
    pad3.SetFrameLineStyle(0)
    pad3.SetFrameLineWidth(2)
    pad3.SetFrameBorderMode(0)
    pad3.SetFrameBorderSize(10)

    errorBand.SetLineColor(1)
    legend=make_legend()
    legend.AddEntry(hists["data_obs"],"Observed","epl")
    legend.AddEntry(signal_tostack,"H#rightarrow#tau#tau (#mu = 1.09)","f")
    for name, val in infoMap.iteritems() :
        if not name=="H125" and not name=="data_obs":
           legend.AddEntry(hists[name], val[1], val[2])
	print name
    legend.AddEntry(errorBand,"Total unc.","f")
    legend.AddEntry(signal,"H#rightarrow#tau#tau (#mu = 1.09)","l")
    legend.Draw()

    c.cd()

    pad4 = ROOT.TPad("pad4","pad4",0.86,0.0,1.0,0.4)
    pad4.Draw()
    pad4.cd()
    pad4.SetFillColor(0)
    pad4.SetBorderMode(0)
    pad4.SetBorderSize(10)
    pad4.SetTickx(1)
    pad4.SetTicky(1)
    pad4.SetTopMargin(0.122)
    pad4.SetBottomMargin(0.026)
    pad4.SetFrameFillStyle(0)
    pad4.SetFrameLineStyle(0)
    pad4.SetFrameLineWidth(2)
    pad4.SetFrameBorderMode(0)
    pad4.SetFrameBorderSize(10)

    legend_sub=make_legend_sub()
    legend_sub.AddEntry(subtrac,"#frac{Obs. - bkg.}{Bkg. unc.}","elp")
    legend_sub.AddEntry(subtrac_sig,"#frac{H#rightarrow#tau#tau}{Bkg. unc.}","l")
    legend_sub.AddEntry(errorBand,"Bkg. unc.","f")
    legend_sub.Draw()

    ROOT.gPad.RedrawAxis()
    
    c.Modified()
    if not os.path.exists( 'plots' ) : os.makedirs( 'plots' )
    if isLog:
       c.SaveAs("plots/unroll_log_"+cat+".pdf")
       c.SaveAs("plots/unroll_log_"+cat+".png")
    else:
       c.SaveAs("plots_linear/unroll_"+cat+".pdf")
       c.SaveAs("plots_linear/unroll_"+cat+".png")
    
    

