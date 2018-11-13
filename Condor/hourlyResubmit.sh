#!/bin/sh
for i in {1..24}
do
    sleep 2h
    nohup bash sub2017Data.sh --resubmit-failed-jobs >>logResubmitDataScript2
    nohup bash sub2017MC.sh --resubmit-failed-jobs >>logResubmitMCScript2
done
