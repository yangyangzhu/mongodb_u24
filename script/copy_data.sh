#!/bin/bash
for j in 0 1 2 3 4 5 6 7 8 9;
do
filename=imagelist_0$j
number=$(($j+1))
hostname=node0
if [ ${number} == "10" ]
then 
    hostname=${hostname}${number}
else
    hostname=${hostname}0${number}
fi
echo $filename
echo $hostname
for i in `cat ${filename}`; 
do echo $i;
   scp -r /data/shared/yigao/lggAndGbm/"$i" yangyang@${hostname}:/data2/yangyang/data/algo_v1/;
   scp -r /data/shared/yigao/gbmAndLggFor20150527_de4824/gbmLggFor20150527/"$i" yangyang@${hostname}:/data2/yangyang/data/algo_v1a/
done 
done
#cp ${filename} /data2/yangyang/
#cp copy_data.sh /data2/yangyang
