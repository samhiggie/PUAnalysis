#!/bin/sh
sleep 12h
for i in {1..36}
do
    sleep 2h
    nohup bash sub2018MC-LT.sh --resubmit-failed-jobs >> logResubmit-MC-2019_Jul20-try2-v8JEC
done
