#!/bin/sh

for i in {1..12}
do
     nohup bash sub2018Data-LT.sh --resubmit-failed-jobs >> logResubmit-DATA-2019_Jul20-try2-v8JEC
     sleep 2h
done
