#!/bin/bash
#echo "start" > tmpfile1
#wait 10
#exit
if [-e $1] && [-e $2]
   then
   echo "file exist" > tmpfile
fi
cd /home/yzhu/tmpfolder
./heatmapMask $1 $2 $3 $4/result
if [$? -ne 0]
   then
       exit $? 
fi
cd $4/result
zip -9 -y -r -q $5.zip *
mv $5.zip ../../
