#! /bin/bash

usage(){
  echo -e "run.sh [options]\n \
  -e execution_id, --execution=execution_id \t execution id of the documents\n \
  -i image_id, --image=image_id \t\t image id that you want to retrieve\n \
  -f file_name, --file=file_name \t\t tsv file where you want to save the data"
  exit 1
}

# Default values

execution_id="/tahsin:kurc:tcga_analysis:12-03-2104/tahsin/tcga.analysis/12-03-2014/00:00:00"
image="TCGA-HN-A2NL-01A-01-TSA"
saving_file=""

while :
do
    case $1 in
        -h | --help | -\?)
          usage;
          exit 0
          ;;
        -e | --execution)
          execution_id=$2
          shift 2
          ;;
        --execution=*)
          execution_id=${1#*=}
          shift
          ;;
        -i | --image)
          image=$2
          shift 2
          ;;
        --image=*)
          image=${1#*=}
          shift
          ;;
        -f | --file)
          saving_file=$2
          shift 2
          ;;
        --file=*)
          saving_file=${1#*=}
          shift
          ;;
 
        --)
          shift
          break
          ;;
        -*)
          echo "Unknown option: $1" >&2
          shift
          ;;
        *) # Done
          break
          ;;
    esac
done

echo "execution_id:  $execution_id"
echo "image_name:  $image"

if [ $saving_file="" ]
then
  saving_file=$image
fi

START=$(date +%s)
echo "Starting retrieve ..."
mongo nfs011:27015 --eval "var execution_id=\"$execution_id\", image=\"$image\"" retrive_image.js > .tmp_file
echo "Retrieve finished. Saving to $saving_file.tsv ..."
awk 'NR > 2 { print }' .tmp_file > $saving_file.tsv
rm .tmp_file
echo "Saving finished."
END=$(date +%s)
DIFF=$(( $END - $START ))
number=`grep -c ^  $saving_file.tsv`
echo "Total objects retrieved: $number. Time cost: $DIFF seconds."
