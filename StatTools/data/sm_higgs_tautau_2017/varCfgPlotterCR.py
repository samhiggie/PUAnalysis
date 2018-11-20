### Nov 13, 2016
### File to store all of the configurations for the
### SM HTT postfit/postfit plotter
###
###
# FIXME FIXME FIXME
# Once the most updated root files are uploaded, the default paths can be set
# in getFile()
# ETau, MuTau and EMu need to double check getBinMap() whic
# provides the number of times unrolled and number of mass bins per
# unroll and labeling

from collections import OrderedDict

def getCategories( channel="tt", prefix="" ) :
    preCategories=["_10_","_11_","_13_","_14_"]
    if channel=="ttbar":
        preCategories=["_1_"]
    elif channel=="tt":
        preCategories=["_10_","_11_","_12_"]
    categories=["htt_"+channel+cat+"13TeV_postfit" for cat in preCategories]
    return categories

# Provide standard mapping to our files
# this can be overridden with --inputFile
def getFile( channel ) :
    fileMap = {
        "et" : "shapes/USCMS/htt_et.inputs-sm-13TeV-mvis.root", # Not up to date
        "mt" : "shapes/USCMS/htt_mt.inputs-sm-13TeV-mvis.root", # Not up to date
        "em" : "emu_unrolled.root", # Not saved publically
        #"em" : "shapes/USCMS/htt_em.inputs-sm-13TeV-mvis.root", # Not up to date
        "tt" : "tautau.root",
        "ttbar" : "shapes/USCMS/htt_tt.inputs-sm-13TeV-svfitmass2D.root", # Not up to date
    }
    return fileMap[ channel ]

def getInfoMap( higgsSF, channel ) :
    if channel == "mt" : sub = ("h", "#mu") 
    if channel == "et" : sub = ("h", "e")
    if channel == "em" or channel=="ttbar" : sub = ("e", "#mu")
    if channel == "tt" : sub = ("h", "h")
    
    infoMap = OrderedDict()
    # Name : Add these shapes [...], legend name, leg type, fill color
    infoMap["data_obs"] = [["data_obs",],"Observed","elp",1]
    if channel=="ttbar":
       infoMap["ZTT"] = [["ZTT","EWKZ"],"Z#rightarrow#tau#tau","f","#ffcc66"]
    else:
       infoMap["ZTT"] = [["ZTT"],"Z#rightarrow#tau#tau","f","#ffcc66"]
    infoMap["ZJ"] = [["ZJ","ZL",],"Z#rightarrow#mu#mu/ee","f","#4496c8"]
    if channel == "em" or channel=="ttbar":
        # This is intentional and will not be changed
        infoMap["TT"] = [["TT",],"t#bar{t}+jets","f","#9999cc"]
    else :
        infoMap["TT"] = [["TTT","TTJ",],"t#bar{t}+jets","f","#9999cc"]
    infoMap["W"] = [["W",],"W+jets","f","#de5a6a"]
    infoMap["QCD"] = [["QCD",],"QCD multijet","f","#ffccff"]
    if channel == "tt" :
        infoMap["VV"] = [["VVT","VVJ",],"Diboson","f","#12cadd"]
    else:
        infoMap["VV"] = [["VV",],"Others","f","#12cadd"]
    return infoMap


def getBackgrounds() :    
    bkgs=["VV","QCD", "W", "TT", "ZJ", "ZTT"]
    return bkgs

def getSignals() :
    signals=[]
    return signals

# Labeling map, this provides, for each channel
# and category :
# unrolling binning in "binning"
# the number of times unrolled in a variable "nx"
# the number of mass bins per unroll "ny"
# and labeling for the divider lines
def getBinMap() :
    binMap = {
        "em" : {
            "htt_em_1_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 12,
                "binning" : [15,20,25,30,35,40],
                "name" : "p_{T}(#mu)",
            },
            "htt_em_2_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 10,
                "binning" : [0,100,150,200,250,300],
                "name" : "p_{T}^{#tau#tau}",
            },
            "htt_em_3_13TeV_postfit" : { # FIXME vbf --> VBF when ready
                "nx" : 1,
                "ny" : 5,
                "binning" : [300,700,1100,1500],
                "name" : "m_{jj}",
            },
        }, # end 'em'
        "mt" : {
            "htt_mt_10_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 12,
                "binning" : ["1 prong","1 prong + #pi^{0}", "3 prongs"],
                "name" : "p_{T}(#tau_{h})",
            },
            "htt_mt_11_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 10,
                "binning" : [0,100,150,200,250,300],
                "name" : "p_{T}^{#tau#tau}",
            },
            "htt_mt_12_13TeV_postfit" : { 
                "nx" : 1,
                "ny" : 5,
                "binning" : [300,700,1100,1500],
                "name" : "m_{jj}",
            },
            "htt_mt_13_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 12,
                "binning" : ["1 prong","1 prong + #pi^{0}", "3 prongs"],
                "name" : "p_{T}(#tau_{h})",
            },
            "htt_mt_14_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 10,
                "binning" : [0,100,150,200,250,300],
                "name" : "p_{T}^{#tau#tau}",
            },
            "htt_mt_15_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 5,
                "binning" : [300,700,1100,1500],
                "name" : "m_{jj}",
            },
        }, # end 'mt'
        "et" : {
            "htt_et_10_13TeV_postfit" : {
                "nx" : 3,
                "ny" : 12,
                "binning" : ["1 prong","1 prong + #pi^{0}", "3 prongs"],
                "name" : "p_{T}(#tau_{h})",
            },
            "htt_et_11_13TeV_postfit" : {
                "nx" : 6,
                "ny" : 10,
                "binning" : [0,100,150,200,250,300],
                "name" : "p_{T}^{#tau#tau}",
            },
            "htt_et_12_13TeV_postfit" : { 
                "nx" : 4,
                "ny" : 5,
                "binning" : [300,700,1100,1500],
                "name" : "m_{jj}",
            },
            "htt_et_13_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 12,
                "binning" : ["1 prong","1 prong + #pi^{0}", "3 prongs"],
                "name" : "p_{T}(#tau_{h})",
            },
            "htt_et_14_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 10,
                "binning" : [0,100,150,200,250,300],
                "name" : "p_{T}^{#tau#tau}",
            },
            "htt_et_15_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 5,
                "binning" : [300,700,1100,1500],
                "name" : "m_{jj}",
            },
        }, # end 'et'
        "tt" : {
            "htt_tt_10_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 30,
                "binning" : [0,],
                "name" : "N/A",
            },
            "htt_tt_11_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 12,
                "binning" : [0,100,170,300],
                "name" : "p_{T}^{#tau#tau}",
            },
            "htt_tt_12_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 12,
                "binning" : [0,300,500,800],
                "name" : "m_{jj}",
            },
        }, # end 'tt'
        "ttbar" : {
            "htt_ttbar_1_13TeV_postfit" : {
                "nx" : 1,
                "ny" : 30,
                "binning" : [0,],
                "name" : "N/A",
            },
	}
    }
    return binMap

