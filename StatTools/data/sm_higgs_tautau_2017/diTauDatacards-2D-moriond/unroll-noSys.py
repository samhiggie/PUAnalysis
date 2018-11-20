#!/usr/bin/env python
import ROOT
import re
from array import array

islog=1

def add_lumi():
    lowX=0.7
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.08)
    lumi.SetTextFont (   42 )
    lumi.AddText("2017, 41.3 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.11
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.1)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.18
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
	if islog:
	   output = ROOT.TLegend(0.12, 0.05, 0.92, 0.25, "", "brNDC")
           output.SetNColumns(5)
	else:
           output = ROOT.TLegend(0.55, 0.3, 0.92, 0.75, "", "brNDC")
	   output.SetNColumns(2)
        #output = ROOT.TLegend(0.2, 0.1, 0.47, 0.65, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        #output.SetFillStyle(0)
        output.SetFillColor(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetFrameLineWidth(3)
ROOT.gStyle.SetLineWidth(3)
ROOT.gStyle.SetOptStat(0)

c=ROOT.TCanvas("canvas","",0,0,1800,600)
c.cd()

file=ROOT.TFile("htt_tt.inputs-sm-13TeV-2D.root","r")
file1D=ROOT.TFile("htt_tt.inputs-sm-13TeV-1D.root","recreate")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["tt_0jet","tt_boosted","tt_vbf"] 
cat=["tt_0jet","tt_boosted","tt_vbf"]
ncat=3

for i in range (0,ncat):
   Data2D=file.Get(categories[i]).Get("data_obs")
   QCD2D=file.Get(categories[i]).Get("QCD")
   W2D=file.Get(categories[i]).Get("W") 
   TT2D=file.Get(categories[i]).Get("TT")
   TTJ2D=file.Get(categories[i]).Get("TTJ")
   TTT2D=file.Get(categories[i]).Get("TTT")
   VV2D=file.Get(categories[i]).Get("VV")
   VVT2D=file.Get(categories[i]).Get("VVT")
   VVJ2D=file.Get(categories[i]).Get("VVJ")
   DYB2D=file.Get(categories[i]).Get("ZL")
   DYS2D=file.Get(categories[i]).Get("ZTT")
   qqH2D=file.Get(categories[i]).Get("qqH125")
   ggh2D=file.Get(categories[i]).Get("ggH125")
   #qqH1302D=file.Get(categories[i]).Get("qqH130")
   #ggh1302D=file.Get(categories[i]).Get("ggH130")
   #qqH1202D=file.Get(categories[i]).Get("qqH120")
   #ggh1202D=file.Get(categories[i]).Get("ggH120")
   #WH1202D=file.Get(categories[i]).Get("WH120")
   WH1252D=file.Get(categories[i]).Get("WH125")
   #WH1302D=file.Get(categories[i]).Get("WH130")
   #ZH1202D=file.Get(categories[i]).Get("ZH120")
   ZH1252D=file.Get(categories[i]).Get("ZH125")
   #ZH1302D=file.Get(categories[i]).Get("ZH130")
      #ggH_WW1202D=file.Get(categories[i]).Get("ggH_WW120")
      #ggH_WW1252D=file.Get(categories[i]).Get("ggH_WW125")
      #ggH_WW1302D=file.Get(categories[i]).Get("ggH_WW130")
      #qqH_WW1202D=file.Get(categories[i]).Get("qqH_WW120")
      #qqH_WW1252D=file.Get(categories[i]).Get("qqH_WW125")
      #qqH_WW1302D=file.Get(categories[i]).Get("qqH_WW130")
      
   
   nx=Data2D.GetXaxis().GetNbins()
   ny=Data2D.GetYaxis().GetNbins()

   Data=ROOT.TH1F("data_obs","data_obs",nx*ny,0,nx*ny)
   QCD=ROOT.TH1F("QCD","QCD",nx*ny,0,nx*ny)
   W=ROOT.TH1F("W","W",nx*ny,0,nx*ny)
   TT=ROOT.TH1F("TT","TT",nx*ny,0,nx*ny)
   TTT=ROOT.TH1F("TTT","TTT",nx*ny,0,nx*ny)
   TTJ=ROOT.TH1F("TTJ","TTJ",nx*ny,0,nx*ny)

################################   
   VV=ROOT.TH1F("VV","VV",nx*ny,0,nx*ny)
   VVT=ROOT.TH1F("VVT","VVT",nx*ny,0,nx*ny)
   VVJ=ROOT.TH1F("VVJ","VVJ",nx*ny,0,nx*ny)
   DYB=ROOT.TH1F("ZL","ZL",nx*ny,0,nx*ny)
   DYS=ROOT.TH1F("ZTT","ZTT",nx*ny,0,nx*ny)
   qqH=ROOT.TH1F("qqH125","qqH125",nx*ny,0,nx*ny)
   ggh=ROOT.TH1F("ggH125","ggH125",nx*ny,0,nx*ny)
   #qqH120=ROOT.TH1F("qqH120","qqH120",nx*ny,0,nx*ny)
   #ggh120=ROOT.TH1F("ggH120","ggH120",nx*ny,0,nx*ny)
   #qqH130=ROOT.TH1F("qqH130","qqH130",nx*ny,0,nx*ny)
   #ggh130=ROOT.TH1F("ggH130","ggH130",nx*ny,0,nx*ny)
   #WH120=ROOT.TH1F("WH120","WH120",nx*ny,0,nx*ny)
   WH125=ROOT.TH1F("WH125","WH125",nx*ny,0,nx*ny)
   #WH130=ROOT.TH1F("WH130","WH130",nx*ny,0,nx*ny)
   #ZH120=ROOT.TH1F("ZH120","ZH120",nx*ny,0,nx*ny)
   ZH125=ROOT.TH1F("ZH125","ZH125",nx*ny,0,nx*ny)
   #ZH130=ROOT.TH1F("ZH130","ZH130",nx*ny,0,nx*ny)
   
   l=0
   for j in range(1,nx+1):
     for k in range(1,ny+1):
	l=l+1
        n = Data2D.GetBin(j,k);
	Data.SetBinContent(l,Data2D.GetBinContent(n))
        QCD.SetBinContent(l,QCD2D.GetBinContent(n))
        W.SetBinContent(l,W2D.GetBinContent(n))
        TT.SetBinContent(l,TT2D.GetBinContent(n))
        TTJ.SetBinContent(l,TTJ2D.GetBinContent(n))
        TTT.SetBinContent(l,TTT2D.GetBinContent(n))
        
        ##########
        VV.SetBinContent(l,VV2D.GetBinContent(n))
        VVT.SetBinContent(l,VVT2D.GetBinContent(n))
        VVJ.SetBinContent(l,VVJ2D.GetBinContent(n))
        DYB.SetBinContent(l,DYB2D.GetBinContent(n))
        DYS.SetBinContent(l,DYS2D.GetBinContent(n))
        qqH.SetBinContent(l,qqH2D.GetBinContent(n))
        ggh.SetBinContent(l,ggh2D.GetBinContent(n))
        #qqH120.SetBinContent(l,qqH1202D.GetBinContent(n))
        #ggh120.SetBinContent(l,ggh1202D.GetBinContent(n))
        #qqH130.SetBinContent(l,qqH1302D.GetBinContent(n))
        #ggh130.SetBinContent(l,ggh1302D.GetBinContent(n))
        #WH120.SetBinContent(l,WH1202D.GetBinContent(n))
        WH125.SetBinContent(l,WH1252D.GetBinContent(n))
        #WH130.SetBinContent(l,WH1302D.GetBinContent(n))
        #ZH120.SetBinContent(l,ZH1202D.GetBinContent(n))
        ZH125.SetBinContent(l,ZH1252D.GetBinContent(n))
        #ZH130.SetBinContent(l,ZH1302D.GetBinContent(n))
        Data.SetBinError(l,Data2D.GetBinError(n))
        QCD.SetBinError(l,QCD2D.GetBinError(n))
        W.SetBinError(l,W2D.GetBinError(n))
        TT.SetBinError(l,TT2D.GetBinError(n))
        TTT.SetBinError(l,TTT2D.GetBinError(n))
        TTJ.SetBinError(l,TTJ2D.GetBinError(n))
        VV.SetBinError(l,VV2D.GetBinError(n))
        VVT.SetBinError(l,VVT2D.GetBinError(n))
        VVJ.SetBinError(l,VVJ2D.GetBinError(n))
        DYB.SetBinError(l,DYB2D.GetBinError(n))
        DYS.SetBinError(l,DYS2D.GetBinError(n))

        qqH.SetBinError(l,qqH2D.GetBinError(n))
        ggh.SetBinError(l,ggh2D.GetBinError(n))
        #qqH120.SetBinError(l,qqH1202D.GetBinError(n))
        #ggh120.SetBinError(l,ggh1202D.GetBinError(n))
        #qqH130.SetBinError(l,qqH1302D.GetBinError(n))
        #ggh130.SetBinError(l,ggh1302D.GetBinError(n))
        #WH120.SetBinError(l,WH1202D.GetBinError(n))
        WH125.SetBinError(l,WH1252D.GetBinError(n))
        #WH130.SetBinError(l,WH1302D.GetBinError(n))
        #ZH120.SetBinError(l,ZH1202D.GetBinError(n))
        ZH125.SetBinError(l,ZH1252D.GetBinError(n))
        #ZH130.SetBinError(l,ZH1302D.GetBinError(n))

   mydir=file1D.mkdir(cat[i])
   mydir.cd()
   Data.Write()
   QCD.Write()
   W.Write()
   VV.Write()
   VVT.Write()
   VVJ.Write()
   TT.Write()
   TTT.Write()
   TTJ.Write()

   DYB.Write()
   DYS.Write()
   #ggh120.Write()
   #qqH120.Write()
   #ggh130.Write()
   #qqH130.Write()

########
   ggh.Write()
   qqH.Write()
   #ggh120.Write()
   #qqH120.Write()
   #ggh130.Write()
   #qqH130.Write()
   #WH120.Write()
   WH125.Write()
   #WH130.Write()
   #ZH120.Write()
   ZH125.Write()
   #ZH130.Write()

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.075)
   Data.GetYaxis().SetTitleOffset(0.56)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events/bin")

   QCD.SetFillColor(ROOT.TColor.GetColor("#ffccff"))
   VV.SetFillColor(ROOT.TColor.GetColor("#12cadd"))
   W.SetFillColor(ROOT.TColor.GetColor("#de5a6a"))
   TT.SetFillColor(ROOT.TColor.GetColor("#9999cc"))
   DYB.SetFillColor(ROOT.TColor.GetColor("#4496c8"))
   DYS.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))
   ggh.SetLineColor(ROOT.TColor.GetColor("#5911ff"))
   qqH.SetLineColor(ROOT.TColor.GetColor("#4faf4e"))
   ggh.SetLineWidth(4)
   qqH.SetLineWidth(4)

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   QCD.SetLineColor(1)
   W.SetLineColor(1)
   TT.SetLineColor(1)
   DYS.SetLineColor(1)
   DYB.SetLineColor(1)
   VV.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)

   errorBand=QCD.Clone()
   errorBand.Add(VV)
   errorBand.Add(TT)
   errorBand.Add(W)
   errorBand.Add(DYB)
   errorBand.Add(DYS)

   stack=ROOT.THStack("stack","stack")
   stack.Add(QCD)
   stack.Add(W)
   stack.Add(VV)
   stack.Add(TT)
   stack.Add(DYB)
   stack.Add(DYS)

   errorBand.SetMarkerSize(0)
   errorBand.SetFillColor(new_idx)
   errorBand.SetFillStyle(3001)
   errorBand.SetLineWidth(1)

   pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
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
   pad1.SetFrameLineWidth(3)
   pad1.SetFrameBorderMode(0)
   pad1.SetFrameBorderSize(10)
   if islog:
      pad1.SetLogy()

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(Data.GetMaximum()*1.35)
   Data.SetMinimum(0.0)
   if islog:
      Data.SetMaximum(Data.GetMaximum()*5.35)
      Data.SetMinimum(0.01)
   for k in range(1,Data.GetSize()-1):
        s=qqH.GetBinContent(k)+ggh.GetBinContent(k)
        b=VV.GetBinContent(k)+DYS.GetBinContent(k)+DYB.GetBinContent(k)+W.GetBinContent(k)+QCD.GetBinContent(k)+TT.GetBinContent(k)+0.0000001
        if (b<0):
            b=0.000001
        #if (10*s/((b+0.09*b*0.09*b)**0.5) > 0.5):
	if (2*s/(s+b)**0.5 > 0.2):
            Data.SetBinContent(k,100000000)
            Data.SetBinError(k,100000000)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   qqH.Scale(100)
   ggh.Scale(100)
   qqH.Draw("histsame")
   ggh.Draw("histsame")
   Data.Draw("esame")

   pthbins=[0,100,150,200,250,300,350]
   mjjbins=[300,700,1100,1500]
   tauptbins=[15,25,35,45,55]
   line=[]
   label=[]
   for z in range(1,nx):
      line.append(ROOT.TLine(z*ny,0,z*ny,Data.GetMaximum()))
      line[z-1].SetLineStyle(3)
      line[z-1].Draw("same")


   legende=make_legend()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(DYS,"Z#rightarrow#tau_{#mu}#tau_{h}","f")
   legende.AddEntry(DYB,"DY others","f")
   legende.AddEntry(TT,"t#bar{t}+jets","f")
   legende.AddEntry(VV,"Diboson","f")
   legende.AddEntry(W,"Electroweak","f")
   legende.AddEntry(QCD,"QCD multijet","f")
   legende.AddEntry(qqH,"qqH 125 (X100)","l")
   legende.AddEntry(ggh,"ggh 125 (X100)","l")
   legende.AddEntry(errorBand,"Stat. uncertainty","f")
   #legende.Draw()

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
   categ.SetTextSize ( 0.08 )
   categ.SetTextColor(    1 )
   categ.SetTextFont (   42 )
   if i==0: 
    categ.AddText("#tau#tau, no jet")
   elif i==1:
    categ.AddText("#tau#tau, boosted")
   elif i==2:
    categ.AddText("#tau#tau, VBF")
   categ.Draw("same")

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.10);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.SetFrameLineWidth(3)
   #pad2.SetGridx()
   pad2.SetGridy()
   pad2.Draw()
   pad2.cd()
   h1=Data.Clone()
   h1.SetMaximum(1.8)#FIXME(1.5)
   h1.SetMinimum(0.2)#FIXME(0.5)
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
   h1.GetXaxis().SetTitle("2D bin number")#(#vec{p_{T}(#mu)}+#vec{p_{T}(#tau)})/(p_{T}(#mu)+p_{T}(#tau))")
   #h1.GetXaxis().SetTitle("N_{charged}")
   h1.GetXaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetTitle("Obs./Exp.")
   #h1.GetXaxis().SetNdivisions(505)
   h1.GetYaxis().SetNdivisions(5)

   h1.GetXaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleOffset(0.26)
   h1.GetXaxis().SetTitleOffset(1.04)
   h1.GetXaxis().SetLabelSize(0.11)
   h1.GetYaxis().SetLabelSize(0.11)
   h1.GetXaxis().SetTitleFont(42)
   h1.GetYaxis().SetTitleFont(42)

   h1.Draw("ep")
   h3.Draw("e2same")

   line2=[]
   for z in range(1,nx):
      line2.append(ROOT.TLine(z*ny,0.2,z*ny,1.8))
      line2[z-1].SetLineStyle(3)
      line2[z-1].Draw("same")


   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   if islog:
      c.SaveAs("unroll_log_"+categories[i]+".pdf")
      c.SaveAs("unroll_log_"+categories[i]+".png")
   else:
      c.SaveAs("unroll_"+categories[i]+".pdf")
      c.SaveAs("unroll_"+categories[i]+".png")






