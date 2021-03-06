#include "tdrstyle.C" 
#include "CMS_lumi.C" 

void applyStyle(TH1F* h, Color_t fill, Color_t line,int fillStyle)
{
	h->SetFillColor(fill);
	h->SetLineColor(line);
	h->SetFillStyle(fillStyle);
	h->SetLineWidth(2);
}


void applySignalStyle(TH1F* h)
{
	h->SetFillStyle(0);
	h->SetLineWidth(3);
	h->SetLineColor(kBlue+2);
	h->SetLineStyle(2);
}


void applyDATAStyle(TH1F* h)
{
	h->SetMarkerStyle(20.);
	h->SetMarkerSize(1.0);
	h->SetLineWidth(2.0);
	h->SetLineColor(kBlack);
}

void convertToDNDM(TH1F* histo) {
	for(int i=1;i<=histo->GetNbinsX();++i) {
		histo->SetBinContent(i,histo->GetBinContent(i)/histo->GetXaxis()->GetBinWidth(i));
		histo->SetBinError(i,histo->GetBinError(i)/histo->GetXaxis()->GetBinWidth(i));
	}
}



void makeDiTauStack(TString name,TString file,TString dir,int s,TString labelX,TString units = "GeV",bool left=false,TString channel = "",TString json = "Golden",bool log = false,bool dndm=false,bool doRatio = false)
{
	setTDRStyle();

	writeExtraText = true;       // if extra text
	extraText  = "Preliminary";  // default extra text is "Preliminary"
	lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
	lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
	lumi_sqrtS = "13 TeV";
	//if (json=="Golden") lumi_13TeV = channel+"    36.1 fb^{-1}, 2016";
	//if (json=="Golden") lumi_13TeV = channel+"    41.8 fb^{-1}, 2017";
	if (json=="Golden") lumi_13TeV = channel+"    60.02 fb^{-1}, 2018";

	int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 


	float xR=0.65; //legend parameters
	if(left) xR=0.2;//legend parameters

	int H = 600;
	int W = 600;

	int H_ref = 600;
	int W_ref = 600;

	// references for T, B, L, R
	float T = 0.08*H_ref;
	float B = 0.12*H_ref; 
	float L = 0.16*W_ref;
	float R = 0.04*W_ref;

	//margins for inbetween the pads in a ratio plot
	float B_ratio = 0.1*H_ref; 
	float T_ratio = 0.03*H_ref; 

	//margin required for lebal on bottom of raito plot
	float B_ratio_label = 0.3*H_ref; 


	TCanvas * c = new TCanvas(name,name,50,50,W,H);
	c->SetFillColor(0);
	c->SetBorderMode(0);
	c->SetFrameFillStyle(0);
	c->SetFrameBorderMode(0);

	if (!doRatio) {
		c->SetLeftMargin     (L/W);
		c->SetRightMargin    (R/W);
		c->SetTopMargin      (T/H);
		c->SetBottomMargin   (B/H);
	}

	c->cd();

	TPad * ratioPad = new TPad("pad2","",0.0,0.0,1.0,0.29);
	TPad * plotPad = new TPad("pad1","",0.0016,0.291,1.0,1.0);
	if(doRatio){

		plotPad->SetTicks(0,0);
		plotPad->SetLeftMargin  (L/W);
		plotPad->SetRightMargin (R/W);
		plotPad->SetTopMargin   (T/H);
		plotPad->SetBottomMargin(B_ratio/H); 
		plotPad->SetFillColor(0);
		plotPad->SetBottomMargin(0);


		ratioPad->SetLeftMargin  (L/W);
		ratioPad->SetRightMargin (R/W);
		ratioPad->SetTopMargin   (T_ratio/H);
		ratioPad->SetTopMargin   (0.007);
		ratioPad->SetBottomMargin(B_ratio_label/H);
		ratioPad->SetGridy(1);
		ratioPad->SetFillColor(4000);

	}
	else{
	  plotPad = new TPad("pad1","",0.0,0.03,1.0,1.0);

		plotPad->SetLeftMargin     (L/W);
		plotPad->SetRightMargin    (R/W);
		plotPad->SetTopMargin      (T/H);
		plotPad->SetBottomMargin   (B/H);
	}

	plotPad->Draw();
	plotPad->cd();

	TFile *f = new TFile(file);


	TH1F * data = (TH1F*)(f->Get(dir+"/data_obs"));
	if (dndm) convertToDNDM(data);
	applyDATAStyle(data);

	//TH1F * QCD = (TH1F*)(f->Get(dir+"/QCD"));
	//if (dndm) convertToDNDM(QCD);
	//applyStyle(QCD,kMagenta-10,1,1001);

	TH1F * QCD = (TH1F*)(f->Get(dir+"/jetFakes"));
	if (dndm) convertToDNDM(QCD);
	applyStyle(QCD,kSpring+6,1,1001);

	TH1F * ttbar = (TH1F*)(f->Get(dir+"/TT"));
	if (dndm) convertToDNDM(ttbar);
	applyStyle(ttbar,kBlue-8,1,1001);
	std::cout<<"here1"<<std::endl;


	TH1F * ZEE = 0;
	if(f->Get(dir+"/ZL")!=0){
	  std::cout<<"here 2"<<std::endl;
	  ZEE = (TH1F*)(f->Get(dir+"/ZL"));	  	
	  if (dndm) convertToDNDM(ZEE);
	  applyStyle(ZEE,kAzure-9,1,1001);	
	}
	//if(f->Get(dir+"/ZL")!=0&&f->Get(dir+"/ZLL")==0)
	//	TH1F * ZEE = (TH1F*)(f->Get(dir+"/ZL"));
	//FIXME
	//if(f->Get(dir+"/ZJ")!=0&&f->Get(dir+"/ZLL")==0)
	//ZEE->Add((TH1F*)(f->Get(dir+"/ZJ")));
	std::cout<<"here 3"<<std::endl;

	//FIXME
	//TH1F * ZTT = (TH1F*)(f->Get(dir+"/embedded"));
	TH1F * ZTT = (TH1F*)(f->Get(dir+"/ZTT"));
	if (dndm) convertToDNDM(ZTT);
	applyStyle(ZTT,kOrange-4,1,1001);

	TH1F * EWK = (TH1F*)(f->Get(dir+"/W"));
	EWK->Add((TH1F*)(f->Get(dir+"/VV")));
	if (dndm) convertToDNDM(EWK);
	applyStyle(EWK,kRed-6,1,1001);


	TH1F *signal=0;


	//more signal styles to be added later
	if(s==3) {
		TH1F * SM = (TH1F*)(f->Get(dir+"/ggH125"));
		TH1F * SMVBF = (TH1F*)(f->Get(dir+"/qqH125"));
		TH1F *sm = SM;
		SMVBF->Scale(1); //cross section = 0.236 pb-1
		sm->Scale(1); // cross section = 2.768 pb-1
		sm->Add(SMVBF);

		sm->Scale(10); // 5X Standard Model
	        //TH1F * SM2 = (TH1F*)(f->Get(dir+"/qqH125"));
		//TH1F *sm2 = SM2;
		//sm2->Scale(100);//FIXME
		//sm->Add(sm2);
		sm->SetLineStyle(2);

		signal=sm;

		if (dndm) convertToDNDM(signal);

		applySignalStyle(signal);
	}

	THStack *hs = new THStack("hs","");
	//hs->SetLineWidth(2);
	std::cout<<"draw qcd"<<std::endl;
       	hs->Add(QCD);
	std::cout<<"draw ttbar"<<std::endl;
	hs->Add(ttbar);
	hs->Add(EWK);

	//if(channel == "#tau_{e}#tau_{h}") hs->Add(ZEE);
	//if(channel == "#tau_{#mu}#tau_{h}") 
	//if(ZEE!=0)
	std::cout<<"draw zee"<<std::endl;
	hs->Add(ZEE);
	hs->Add(ZTT);

	//if(s>0&(!log))
	//  hs->Add(signal);
	//if(sm) {
	//  TH1F * SM = (TH1F*)(f->Get(dir+"/ggH125"));
	//  SM->Add((TH1F*)(f->Get(dir+"/qqH125")));
	//  applyStyle(SM,kGray+2,1,3005);
	//  hs->Add(SM);
	// }
	//  else {
	//  hs->Add(MSSM);

	if(data->GetMaximum()*1.2+sqrt(data->GetMaximum())>hs->GetMaximum()) {
		float max=0.0;
		if(data->GetMaximum()>hs->GetMaximum())
			max=data->GetMaximum();
		else
			max=hs->GetMaximum();

		if(log) {
			max*=10;
			hs->SetMinimum(0.5);
		}
		hs->SetMaximum(max*1.5+sqrt(data->GetMaximum()));

	}
	else{
		hs->SetMaximum(hs->GetMaximum()*1.8);
	}
	if(dndm)       hs->SetMinimum(0.001);


	hs->Draw("HIST");

	if(doRatio){
		hs->GetXaxis()->SetLabelSize(0);
	}
	else
	{
		if(units!="")
			hs->GetXaxis()->SetTitle(labelX+" ["+units+"]");
		else
			hs->GetXaxis()->SetTitle(labelX);
	}

	hs->GetYaxis()->SetTitle("Events");
	hs->GetYaxis()->SetTitleOffset(1);

	if(dndm)
		hs->GetYaxis()->SetTitle("dN/d"+labelX);

	if(s>0)
		signal->Draw("HIST,SAME");

	data->Draw("e,SAME");


	c->cd();

	if(doRatio){
		TH1F * data2 = (TH1F*)data->Clone("data");
		TH1F * mc = (TH1F*)(ttbar);
		mc->Add(QCD);
		mc->Add(EWK);
		mc->Add(ZTT);
		if (channel =="#tau_{e}#tau_{h}") mc->Add(ZEE);
		if (channel =="#tau_{#mu}#tau_{h}") mc->Add(ZEE);

		double xmin = mc->GetXaxis()->GetXmin();
		double xmax = mc->GetXaxis()->GetXmax();
		TLine *line = new TLine(xmin,1.0,xmax,1.0);
		line->SetLineWidth(1);
		line->SetLineColor(kBlack);

		ratioPad->Draw();
		ratioPad->cd();

		data2->Divide(data2,mc);

		data2->SetMarkerStyle(20);
		data2->SetTitleSize  (0.12,"Y");
		data2->SetTitleOffset(0.40,"Y");
		data2->SetTitleSize  (0.12,"X");
		data2->SetLabelSize  (0.10,"X");
		data2->SetLabelSize  (0.08,"Y");
		data2->GetYaxis()->SetRangeUser(0.62,1.38);
		data2->GetYaxis()->SetNdivisions(305);
		data2->GetYaxis()->SetTitle("Obs/Exp   ");

		//What does this do
		//->this affects the stat box style
		//gStyle->SetOptTitle(0);


		if (units!="")
			data2->GetXaxis()->SetTitle(labelX+" ["+units+"]");
		else
			data2->GetXaxis()->SetTitle(labelX);

		data2->Draw("P");
		line->Draw();

	}

	c->cd();
	plotPad->cd(); 

	TLegend *l = new TLegend(xR,0.55,xR+0.28,0.9);


	l->AddEntry(ZTT,"Z#rightarrow#tau#tau","F");
	//if(channel == "#tau_{e}#tau_{h}") l->AddEntry(ZEE,"Z#rightarrowee","F");
	//if(channel == "#tau_{#mu}#tau_{h}") l->AddEntry(ZEE,"Z#rightarrow#mu#mu","F");
	if(ZEE!=0)
	  l->AddEntry(ZEE,"Z#rightarrowll","F");
	l->AddEntry(EWK,"Electroweak","F");
	l->AddEntry(QCD,"jet#rightarrow#tau_{h}","F");
	l->AddEntry(ttbar,"t#bar{t}","F");


	if(log){
		if(s==3)
			l->AddEntry(signal,"10xSM H(125)#rightarrow#tau#tau","L");
	}
	else{
		if(s==3)
			l->AddEntry(signal,"10xSM H(125)#rightarrow#tau#tau","F");
	}

	l->SetBorderSize(0);
	l->SetFillColor(0);
	l->SetFillStyle (0);

	l->Draw();


	float factor=0.0;
	if(left) factor = 1./2.2;
	else factor = 1.05;

	float xL = hs->GetXaxis()->GetXmin()+(hs->GetXaxis()->GetXmax()-hs->GetXaxis()->GetXmin())*xR*factor;
	float yL = hs->GetMaximum()*0.35;

	if(log)
		yL = hs->GetMaximum()*0.35;

	float offsetF=yL-0.1*hs->GetMaximum();
	float offsetFF=yL-0.2*hs->GetMaximum();

	if(log) {

		offsetF=yL/2.;
		offsetFF=yL/5.;

	}

	//now in CMS_lumi
	/*
	//TLatex latex;
	//latex.SetNDC();
	//if(doRatio)
	//	latex.SetTextSize(0.05);
	//else
	//	latex.SetTextSize(0.04);
	//latex.SetTextAlign(11);
	//latex.SetTextFont(42);
	// latex.DrawLatex(0.20,0.94,"CMS Preliminary 2015, 40 pb^{-1}, #sqrt{s} = 13 TeV      "+channel);
	//latex.DrawLatex(0.20,0.94,"CMS Preliminary 2015D, ~130 pb^{-1}, #sqrt{s} = 13 TeV      "+channel);
	*/
	//CMS_lumi(plotPad,4,11);
	plotPad->Draw();
	//plotPad->SetBottomMargin(0.017);
	CMS_lumi(plotPad,4,11);
	if(log)
	  plotPad->SetLogy();

	 //c->RedrawAxis(); 
	c->SaveAs(name+".png");
	c->SaveAs(name+".pdf");
	c->SaveAs(name+".root");

}



