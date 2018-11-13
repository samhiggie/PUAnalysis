import os

from PUAnalysis.CrabTools.datasets_2017_full import samples
##from PUAnalysis.CrabTools.datasets_2017_data import samples

keys  = samples.viewkeys()    
keylist = list(keys)

for x in range(len(samples)):
    if (os.path.exists(os.getcwd()+"/"+keylist[x]) and os.path.isdir(os.getcwd()+"/"+keylist[x])):
        print keylist[x] + " exists"
    else :
        print keylist[x] + " does not exist"
        os.mkdir(os.getcwd()+"/"+keylist[x])
