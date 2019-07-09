####
#script to plot all the JEC for the HTT analysis 
###

import ROOT
import numpy as np 
import argparse



def applyStyle(h, fill, line, fillStyle):
	h.SetFillColor(fill)
	h.SetLineColor(line)
	h.SetFillStyle(fillStyle)
	h.SetLineWidth(2)

def applySignalStyleUp(h,color):
	h.SetFillStyle(4050)
	h.SetLineWidth(3)
	h.SetLineColor(color)
	h.SetFillColorAlpha(color,0.15)
	h.SetLineStyle(2)

def applySignalStyleDown(h,color):
	h.SetFillStyle(4050)
	h.SetLineWidth(3)
	h.SetLineColor(color)
	h.SetFillColorAlpha(color,0.15)
	h.SetLineStyle(3)

def applySignalStyle(h,color):
	h.SetFillStyle(0)
	h.SetLineWidth(3)
	h.SetLineColor(color)
	h.SetLineStyle(2)


def applyDATAStyle(h):
	h.SetMarkerStyle(20)
	h.SetMarkerSize(1)
	h.SetLineWidth(2)
	h.SetLineColor(ROOT.kBlack)

def makeplotsUpDown(fin,string,sigup,sigdown,bkgup,bkgdown,othersup,othersdown,canvas,legend,counter):
    #print "tt_inclusive/"+string
    h = fin.Get("tt_inclusive/"+string) 
    #print "Entries ",h.GetEntries()
    key = string.split("_CMS_")[0]
    sys = string.split("_CMS_")[1]
    #print "found source ",key
    flag=0
    
    # not using 1001 for filling -> not all graphs are drawn for systematics ... so no stack
    if("13TeVUp" in sys):
        if("ggH" in key):
            #applyStyle(h,ROOT.kBlue+2,,1001)
            applySignalStyleUp(h,ROOT.kBlue+2)
            h.Scale(10.)
            sigup.Add(h)
            l.AddEntry(h,key+" up","F")
        elif("qqH" in key):
            #applyStyle(h,ROOT.kRed+2,1,1001)
            applySignalStyleUp(h,ROOT.kRed+2)
            h.Scale(10.)
            sigup.Add(h)
            l.AddEntry(h,key+" up","F")
    
        #elif("ZH" in key):
        #    applySignalStyleUp(h,ROOT.kGreen+2)
        #    sigup.Add(h)
        #elif("WH" in key):
        #    applySignalStyleUp(h,ROOT.kGreen-2)
        #    sigup.Add(h)
        #elif("ttH" in key):
        #    applySignalStyleUp(h,ROOT.kBlack+2)
        #    sigup.Add(h)
        elif("ZL" in key):
            applyStyle(h,ROOT.kAzure-9,1,1001)
            bkgup.Add(h)
            l.AddEntry(h,key+" up","F")
        #elif("QCD" in key):
        #    applyStyle(h,ROOT.kMagenta-10,1,3004)
        #    bkgup.Add(h)
        elif("ZTT" in key):
            applyStyle(h,ROOT.kOrange-4,1,1001)
            bkgup.Add(h)
            print "systematic ",sys," ZTT entries ",h.GetEntries()
            l.AddEntry(h,key+" up","F")
        #elif(("W_" in key)or("VV_" in key)):
        #    tmp = fin.Get("tt_inclusive/"+string) 
        #    #print "found Diboson adding for EWK"
        #    if(flag==1):
        #        applyStyle(h,ROOT.kMagenta-10,1,3004)
        #        #print "adding for EWK"
        #        tmp.Add(h)
        #        bkgup.Add(tmp)
        #        flag=0
        #    flag=1
        #elif("TTT_" in key):
        #    applyStyle(h,ROOT.kRed-9,1,3004)
        #    bkgup.Add(h)
        #else:
        #    #print "What are you???"
        #    counter=counter+1
        #    applyStyle(h,counter+33,1,3004)
        #    othersup.Add(h)

    if("13TeVDown" in sys):
        if("ggH" in key):
            applySignalStyleDown(h,ROOT.kBlue+2)
            h.Scale(10.)
            sigdown.Add(h)
            l.AddEntry(h,key+" down","F")
        elif("qqH" in key):
            applySignalStyleDown(h,ROOT.kRed+2)
            h.Scale(10.)
            sigdown.Add(h)
            l.AddEntry(h,key+" down","F")
        #elif("ZH" in key):
        #    applySignalStyleDown(h,ROOT.kGreen+2)
        #    sigdown.Add(h)
        #elif("WH" in key):
        #    applySignalStyleDown(h,ROOT.kGreen-2)
        #    sigdown.Add(h)
        #elif("ttH" in key):
        #    applySignalStyleDown(h,ROOT.kBlack+2)
        #    sigdown.Add(h)
        elif("ZL" in key):
            applyStyle(h,ROOT.kAzure-9,1,3345)
            bkgdown.Add(h)
            l.AddEntry(h,key+" down","F")
        #elif("QCD" in key):
        #    applyStyle(h,ROOT.kMagenta-10,1,3005)
        #    bkgdown.Add(h)
        elif("ZTT" in key):
            applyStyle(h,ROOT.kOrange-4,1,3345)
            bkgdown.Add(h)
            print "systematic ",sys," ZTT entries ",h.GetEntries()
            l.AddEntry(h,key+" down","F")
        #elif(("W_" in key)or("VV_" in key)):
        #    tmp = fin.Get("tt_inclusive/"+string) 
        #    #print "found Diboson adding for EWK"
        #    if(flag==1):
        #        applyStyle(h,ROOT.kMagenta-10,1,3005)
        #        #print "adding for EWK"
        #        tmp.Add(h)
        #        bkgdown.Add(tmp)
        #        flag=0
        #    flag=1
        #elif("TTT_" in key):
        #    applyStyle(h,ROOT.kRed-9,1,3005)
        #    bkgdown.Add(h)
        #else:
        #    #print "What are you???"
        #    counter=counter+1
        #    applyStyle(h,counter+33,1,3005)
        #    othersdown.Add(h)
        #l.AddEntry(h,key,"F")
    
    c.cd()
    #h.Draw("same,hist")

    return
def makeplots(fin,string,sig,bkg,other,canvas,legend,counter):
    #print "tt_inclusive/"+string
    h = fin.Get("tt_inclusive/"+string) 
    #print "Entries ",h.GetEntries()
    key = string.split("_CMS_")[0]
    sys = string.split("_CMS_")[1]
    #print "found source ",key
    flag=0
    
    # not using 1001 for filling -> not all graphs are drawn for systematics ... so no stack
    if("ggH" in key):
        applySignalStyle(h,ROOT.kBlue+2)
        sig.Add(h)
    elif("qqH" in key):
        applySignalStyle(h,ROOT.kRed+2)
        sig.Add(h)
    elif("ZH" in key):
        applySignalStyle(h,ROOT.kGreen+2)
        sig.Add(h)
    elif("WH" in key):
        applySignalStyle(h,ROOT.kGreen-2)
        sig.Add(h)
    elif("ttH" in key):
        applySignalStyle(h,ROOT.kBlack+2)
        sig.Add(h)
    elif("ZL" in key):
        applyStyle(h,ROOT.kAzure-9,1,1001)
        bkg.Add(h)
    elif("QCD" in key):
        applyStyle(h,ROOT.kMagenta-10,1,1001)
        bkg.Add(h)
    elif("ZTT" in key):
        applyStyle(h,ROOT.kOrange-4,1,1001)
        bkg.Add(h)
        print "systematic ",sys," ZTT entries ",h.GetEntries()
    elif(("W_" in key)or("VV_" in key)):
        tmp = fin.Get("tt_inclusive/"+string) 
        #print "found Diboson adding for EWK"
        if(flag==1):
            applyStyle(h,ROOT.kMagenta-10,1,1001)
            #print "adding for EWK"
            tmp.Add(h)
            bkg.Add(tmp)
            flag=0
        flag=1
    elif("TTT_" in key):
        applyStyle(h,ROOT.kRed-9,1,3004)
        bkg.Add(h)
    else:
        #print "What are you???"
        counter=counter+1
        applyStyle(h,counter+33,1,3005)
        other.Add(h)
    
    c.cd()
    #h.Draw("same,hist")
    l.AddEntry(h,key,"F")

    return

def makeplotsOld(fin,sys):
    

    ggH  = fin.Get("tt_inclusive/"+"ggH125_CMS_"+sys) 
    qqH  = fin.Get("tt_inclusive/"+"qqH125_CMS_"+sys) 
    ZH   = fin.Get("tt_inclusive/"+"ZH125_CMS_"+sys) 
    WH   = fin.Get("tt_inclusive/"+"WH125_CMS_"+sys) 
    W    = fin.Get("tt_inclusive/"+"W_CMS_"+sys) 
    ttH  = fin.Get("tt_inclusive/"+"ttH125_CMS_"+sys) 
    VVJ  = fin.Get("tt_inclusive/"+"VVJ_CMS_"+sys) 
    VVT  = fin.Get("tt_inclusive/"+"VVT_CMS_"+sys) 
    ZTT  = fin.Get("tt_inclusive/"+"ZTT_CMS_"+sys) 
    ZL  = fin.Get("tt_inclusive/"+"ZL_CMS_"+sys) 
    ZJ  = fin.Get("tt_inclusive/"+"ZJ_CMS_"+sys) 
    TTJ  = fin.Get("tt_inclusive/"+"ZTT_CMS_"+sys) 
    TTT  = fin.Get("tt_inclusive/"+"ZTT_CMS_"+sys) 
    TT    = fin.Get("tt_inclusive/"+"TT_CMS_"+sys) 
    #plot unshifted distributions?
    #QCD  = fin.Get("tt_inclusive/"+"QCD") 
    #data = fin.Get("tt_inclusive/"+"data_obs") 

    ggH.Add(qqH)
    #W.Add(VV)

    #applying styles ...
    applyStyle(W,ROOT.kRed-6,1,0)
    #applyDATAStyle(data)
    applySignalStyle(ggH,ROOT.kBlue+2)
    applyStyle(WH,ROOT.kBlue,1,0)
    applyStyle(ZH,ROOT.kBlue+1,1,0)
    applyStyle(ZL,ROOT.kAzure-9,1,0)
    applyStyle(ZJ,ROOT.kAzure-1,1,0)
    applyStyle(ZTT,ROOT.kOrange-10,1,0)
    applyStyle(TT,ROOT.kBlue-8,1,0)
    applyStyle(TTT,ROOT.kBlue-6,1,0)
    applyStyle(TTJ,ROOT.kBlue-4,1,0)
    applyStyle(ttH,ROOT.kBlue-4,1,0)

    #hs = ROOT.THStack()
    #hs.SetName("hs_{0}".format(sys))
    #hs.Add()

    c = ROOT.TCanvas("c_{0}".format(sys),"c_{0}".format(sys),50,50,600,600)
    c.SetFillColor(0);
    c.SetBorderMode(0);
    c.SetFrameFillStyle(0);
    c.SetFrameBorderMode(0);
    c.cd()
    l = ROOT.TLegend(0.65,0.55,0.2+0.28,0.9)
    #l.AddEntry(ZTT,"Z#rightarrow#tau#tau","F")
    #l.AddEntry(ZEE,"Z#rightarrowll","F")
    #l.AddEntry(EWK,"Electroweak","F")
    #l.AddEntry(QCD,"QCD","F")
    l.AddEntry(ttbar,"t#bar{t}","F")
    l.AddEntry(WH, "WH","F")
    l.AddEntry(ZH, "ZH","F")
    l.AddEntry(ZL, "ZL","F")
    l.AddEntry(ZJ, "ZJ","F")
    l.AddEntry(ZTT,"ZTT","F")
    l.AddEntry(TT,"TT","F")
    l.AddEntry(TTT,"TTT","F")
    l.AddEntry(TTJ,"TTJ","F")
    l.AddEntry(ttH,"ttH","F")




    l.AddEntry(ggH,"10xSM H(125)#rightarrow#tau#tau","L")

    l.SetBorderSize(0)
    l.SetFillColor(0)
    l.SetFillStyle (0)
    l.Draw()

    ttbar.Draw("same")
    WH.Draw("same")
    ZH.Draw("same")
    ZL.Draw("same")
    ZJ.Draw("same")
    ZTT.Draw("same")
    TT.Draw("same")
    TTT.Draw("same")
    TTJ.Draw("same")
    ttH.Draw("same")


    c.SaveAs("out/{0}.png".format(sys))
    ttbar.Delete()
    WH.Delete()
    ZH.Delete()
    ZL.Delete()
    ZJ.Delete()
    ZTT.Delete()
    TT.Delete()
    TTT.Delete()
    TTJ.Delete()
    ttH.Delete()
    return



parser = argparse.ArgumentParser()
parser.add_argument("--updown","-ud",action='store_true',default=False,help="place the up and down variations on the same plot")
args = parser.parse_args()

jetSyslist = ["Closure", "AbsoluteFlavMap", "AbsoluteMPFBias", "AbsoluteScale", "AbsoluteStat", "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal", "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF", "SinglePionECAL", "SinglePionHCAL", "TimePtEta", "Total"]
#jetSyslist = ["PileUpPtEC1"]

ROOT.gROOT.SetBatch(1)
fin = ROOT.TFile("ttJEC/tauTau_m_sv.root","READ") 
tkeys = fin.Get("tt_inclusive").GetListOfKeys()
systDict={}
#bkg = ROOT.THStack("FlavorQCD","FlavorQCD")
#sig = ROOT.TH1F()
#data = fin.Get("tt_inclusive/data_obs")
#applyDATAStyle(data)

for tkey in tkeys:
    #print tkey.GetName()
    #if(("FlavorQCD" in tkey.GetName())and(("Up" in tkey.GetName()))):
    for sys in jetSyslist:
        
        if args.updown==True:
            if(sys in tkey.GetName()):
                if not(systDict.has_key(sys)):
                    systDict[sys]=[]
                #systDict[sys+"_Up"]=(tkey.GetName().split("_CMS_")[1])
                systDict[sys].append(tkey.GetName())
    
       
        else:
            if(( sys in tkey.GetName())and(("_13TeVUp" in tkey.GetName()))):
                if not(systDict.has_key(sys+"_Up")):
                    systDict[sys+"_Up"]=[]
                #systDict[sys+"_Up"]=(tkey.GetName().split("_CMS_")[1])
                systDict[sys+"_Up"].append(tkey.GetName())
            if(( sys in tkey.GetName())and(("_13TeVDown" in tkey.GetName()))):
                if not(systDict.has_key(sys+"_Down")):
                    systDict[sys+"_Down"]=[]
                #systDict[sys+"_Down"]=(tkey.GetName().split("_CMS_")[1])
                systDict[sys+"_Down"].append(tkey.GetName())
                #makeplots(bkg,sig,data)    
                #if not(systDict.has_key("FlavorQCD_Up")):
                #    systDict["FlavorQCD_Up"]=[]
                #systDict["FlavorQCD_Up"].append((tkey.GetName()).replace("FlavorQCD",""))

print "The systematics! ",systDict
for sys in systDict:
    if args.updown==True:
        bkgup = ROOT.THStack()
        sigup = ROOT.THStack()
        othersup = ROOT.THStack()
        bkgdown = ROOT.THStack()
        sigdown = ROOT.THStack()
        othersdown = ROOT.THStack()

        bkgup.SetTitle("{0}".format(sys))
        sigup.SetTitle("sig_{0}".format(sys))
        othersup.SetTitle("others_{0}".format(sys))
        bkgup.SetName("bkg_{0}".format(sys))
        sigup.SetName("sig_{0}".format(sys))
        othersup.SetName("others_{0}".format(sys))

        bkgdown.SetTitle("{0}".format(sys))
        sigdown.SetTitle("sig_{0}".format(sys))
        othersdown.SetTitle("others_{0}".format(sys))
        bkgdown.SetName("bkg_{0}".format(sys))
        sigdown.SetName("sig_{0}".format(sys))
        othersdown.SetName("others_{0}".format(sys))
        #makeplots(fin,systDict[sys])

        c = ROOT.TCanvas("c_{0}".format(sys),"c_{0}".format(sys),50,50,600,600)
        c.SetFillColor(0);
        c.SetBorderMode(0);
        c.SetFrameFillStyle(0);
        c.SetFrameBorderMode(0);
        #c.SetLogy();
        c.cd()
        l = ROOT.TLegend(0.65,0.55,0.2+0.28,0.9)
        #l = ROOT.TLegend()
        counter=0
        for key in systDict[sys]:
            makeplotsUpDown(fin,key,sigup,sigdown,bkgup,bkgdown,othersup,othersdown,c,l,counter)
        bkgup.Draw("HIST")
        #othersup.Draw("HIST,SAME")
        bkgdown.Draw("HIST,SAME")
        sigup.Draw("HIST,SAME")
        sigdown.Draw("HIST,SAME")
        
        #othersdown.Draw("HIST,SAME")
        bkgup.GetXaxis().SetTitle("m_{#tau#tau}")
        bkgup.GetYaxis().SetTitle("Events")

        l.Draw()
        c.SaveAs("out/{0}.png".format(sys))
        bkgup.Delete()
        sigup.Delete()
        othersup.Delete()
        bkgdown.Delete()
        sigdown.Delete()
        othersdown.Delete()
        l.Delete()
        c.Delete()
    else:
        bkg = ROOT.THStack()
        sig = ROOT.THStack()
        others = ROOT.THStack()

        bkg.SetTitle("{0}".format(sys))
        sig.SetTitle("sig_{0}".format(sys))
        others.SetTitle("others_{0}".format(sys))
        bkg.SetName("bkg_{0}".format(sys))
        sig.SetName("sig_{0}".format(sys))
        others.SetName("others_{0}".format(sys))
    
        #makeplots(fin,systDict[sys])
        c = ROOT.TCanvas("c_{0}".format(sys),"c_{0}".format(sys),50,50,600,600)
        c.SetFillColor(0);
        c.SetBorderMode(0);
        c.SetFrameFillStyle(0);
        c.SetFrameBorderMode(0);
        #c.SetLogy();
        c.cd()
        l = ROOT.TLegend(0.65,0.55,0.2+0.28,0.9)
        #l = ROOT.TLegend()
        counter=0
        for key in systDict[sys]:
            makeplots(fin,key,sig,bkg,others,c,l,counter)
        bkg.Draw("HIST")
        sig.Draw("HIST,SAME")
        others.Draw("HIST,SAME")
        bkg.GetXaxis().SetTitle("m_{#tau#tau}")
        bkg.GetYaxis().SetTitle("Events")

        l.Draw()
        c.SaveAs("out/{0}.png".format(sys))
        bkg.Delete()
        sig.Delete()
        others.Delete()
        l.Delete()
        c.Delete()


    
#print systDict 
fin.Close()
