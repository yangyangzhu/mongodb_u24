#! /bin/bash

START=$(date +%s)
#for i in `cat imagelist`; do ./download.sh -e "yi-vadim:yi-s48" -i $i; done
#for i in `cat imagelist`; do ./download.sh -e "/liz:vanner:sbu_definiens:2-13-2105/vanner/sbu_definiens/2-13-2015/00:00:00" -i $i; done
#for i in `cat imagelist`; do ./download.sh -e "vadim-yi-colordecomposition:vadim-s48" -i $i; done
for i in `cat imagelist`; do ./download.sh -e "vadim-alg:vadim-s48:thresh_post_mask" -i $i; done
END=$(date +%s)
DIFF=$(( $END - $START ))
echo "Total time cost: $DIFF seconds"

