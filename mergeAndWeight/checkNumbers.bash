

jobID=2019_Jul20-try2-v8JEC
for dir in data_m_A data_m_B data_m_C data_m_C
do
    pyth=$(ls /nfs_scratch/ojalvo/${jobID}_$dir*/*/*.py |wc -l)
    root=$(ls /hdfs/store/user/ojalvo/${jobID}_$dir*/*.root |wc -l)
    rootdiv=$(( 100*root ))
    percent=0
    if [ $pyth -gt 0 ]
	then
	percent=$(( rootdiv / pyth ))
	echo $dir " Number of pyth files: " $pyth "          Number of root files: " $root " Percent Complete: "$percent "%"
    else
	echo "NO FILES GENERATED FOR "$dir" SOMETHING REALLY BAD HAPPENED!!!"
    fi

done

jobID=2019_Jul19
for dir in ggH125  vbfH125 WHplus WHminus ZH ttH DYJ DY1 DY2 DY3 DY4 EWKWminus2j EWKWPlus2j EWKZ2j_2 EWKZ2j_2nu ST_tw_a ST_tW_t ST_t_t ST_t_at TT_2l2nu TT_had TT_sl WJ_lnu W1J_lnu W2J_lnu W3J_lnu W4J_lnu WW WZ ZZ
do
    pyth=$(ls /nfs_scratch/ojalvo/${jobID}_$dir*/*/*.py |wc -l)
    root=$(ls /hdfs/store/user/ojalvo/${jobID}_$dir*/*.root |wc -l)
    rootdiv=$(( 100*root ))
    percent=0
    if [ $pyth -gt 0 ]
	then
	percent=$(( rootdiv / pyth ))
	echo $dir " Number of pyth files: " $pyth "          Number of root files: " $root " Percent Complete: "$percent "%"
    else
	echo "NO FILES GENERATED FOR "$dir" SOMETHING REALLY BAD HAPPENED!!!"
    fi

done

