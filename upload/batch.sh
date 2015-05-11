#for i in `cat ../../imagelist`; do echo $i; java -cp ./:./mongo.jar writeTilePolygon ../../tile/vadVScd/"$i"_tmp/part-00000 "vadim" "cd" vad:cd "$i"; done
#for i in `cat ../../imagelist`; do echo $i; java -cp ./:./mongo.jar writeTilePolygon ../../tile/yiVScd/"$i"_tmp/part-00000 "yi" "cd" yi:cd "$i"; done
#for i in `cat ../../imagelist`; do echo $i; java -cp ./:./mongo.jar writeTilePolygon ../../tile/yiVSvad/"$i"_tmp/part-00000 "yi" "vadim" yi:vad "$i"; done

#for i in `cat ../../imagelist`; do echo $i; cat ../../new/vadVScd/"$i"/part* | java -cp ./:./mongo.jar writeIntersectPair "$i" vad cd; done

#for i in `cat ../../imagelist`; do echo $i; cat ../../new/yiVScd/"$i"/part* | java -cp ./:./mongo.jar writeIntersectPair "$i" yi cd; done

#for i in `cat ../../imagelist`; do echo $i; cat ../../new/yiVSvad/"$i"/part* | java -cp ./:./mongo.jar writeIntersectPair "$i" yi vad; done

#for i in `cat ../../imagelist`; do if ! grep -q "$i" ./smailllist; then if [ -e ./new2/vadVScd/"$i"_part/tile_dice ]; then echo $i; java -cp ./:./mongo.jar writeHeatmap "$i" tile_dice ./new2/vadVScd/"$i"_part/tile_dice vad:cd:tile_dice; fi; fi; done
#for i in `cat ../../imagelist`; do if ! grep -q "$i" ./smailllist; then if [ -e ./new2/yiVScd/"$i"_part/tile_dice ]; then echo $i; java -cp ./:./mongo.jar writeHeatmap "$i" tile_dice ./new2/yiVScd/"$i"_part/tile_dice yi:cd:tile_dice; fi; fi; done
#for i in `cat ../../imagelist`; do if ! grep -q "$i" ./smailllist; then if [ -e ./new2/yiVSvad/"$i"_part/tile_dice ]; then echo $i; java -cp ./:./mongo.jar writeHeatmap "$i" tile_dice ./new2/yiVSvad/"$i"_part/tile_dice yi:vad:tile_dice; fi; fi; done
for i in `cat ../../imagelist`; do if ! grep -q "$i" ./smailllist; then if [ -e ./new2/vadVScd/"$i"_part/tile_dice ]; then echo $i; java -cp ./:./mongo.jar writeMetadata "$i" vad:cd:tile_dice "Vadim Color Decomposition TILE_DICE"; fi; fi; done
for i in `cat ../../imagelist`; do if ! grep -q "$i" ./smailllist; then if [ -e ./new2/yiVScd/"$i"_part/tile_dice ]; then echo $i; java -cp ./:./mongo.jar writeMetadata "$i" yi:cd:tile_dice "Yi Color Decomposition TILE_DICE"; fi; fi; done
for i in `cat ../../imagelist`; do if ! grep -q "$i" ./smailllist; then if [ -e ./new2/yiVSvad/"$i"_part/tile_dice ]; then echo $i; java -cp ./:./mongo.jar writeMetadata "$i" yi:vad:tile_dice "Yi Vadim TILE_DICE"; fi; fi; done
