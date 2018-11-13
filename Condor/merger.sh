#Script to merge the root files 
#Run in directory that contains the names of all the samples... 
for d in */;
do 
    if ["$d" == "forIsobel"]; then 
        echo skipping "$d" ...
        continue 
    fi  
    if ["$d" == "OldJobs"]; then 
        echo skipping "$d" ...
        continue 
    fi 
    echo Merging Root Files 
    echo in directory "$d"
    cd "$d"/.
    dname=${PWD##*/}
    echo NewFile "$dname.root"
    hadd -k "$dname.root" crab_*/*/*/analysis*.root  
    cd ..
done
