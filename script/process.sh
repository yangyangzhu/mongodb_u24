#!/bin/bash

# This script is used for generating heatmaps from output mask images of two algoritms.
# To Use this script, you should have all the image stored in the local disk where the script exists. 
# The folders are ./data/algo_v1/ and ./data/algo_v1a. 
# You also have to create a folder for store the result heatmaps. Use ./data/output.
# In the folder, you should prepare a list of all the images you need to process,
#   which are represented by the folder names of all the images stored in algo_v1 and algo_v2.
#   Name the list like imagelistXX.
# Also a list of all the meta data of the images named images.list.
#   Organized as image.caseid,width,height,cancer_type. One line stand for one image.
# The last thing you need is the binary to computer the heatmaps. Copy the "heatmaps" to this folder.
# After you have done all the things above, just run ./process.sh


start=`date +%s`

for i in `cat imagelist*`;
do
  echo $i
  if [ -d ./data/output/"$i" ]; then
    rm -r ./data/output/"$i"/*
  else
    mkdir ./data/output/"$i"
  fi
  IFS='.' read -a array <<< "$i"
  #echo "${array[0]}"
  line=$(grep ${array[0]} ./images.meta)
  #echo "$line"
  IFS=',' read -a parameters <<< "${line[0]}"
  rm tmpfilelist1
  rm tmpfilelist2
  ls ./data/algo_v1/"$i" > tmpfilelist1
  #wc -l tmpfilelist1 
  ls ./data/algo_v1a/"$i" >> tmpfilelist1
  #wc -l tmpfilelist1
  cat tmpfilelist1 | sort | uniq > tmpfilelist2
  #wc -l tmpfilelist2
  for j in `cat tmpfilelist2`; 
  do 
    ./heatmaps ./data/algo_v1/"$i"/"$j" ./data/algo_v1a/"$i"/"$j" 512 ${parameters[1]} ${parameters[2]} ${parameters[3]} ./data/output/"$i"
  done
done
runtime=$((end-start))
echo "$runtime"
