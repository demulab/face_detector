#!/bin/sh

if [ $# -ne 1 ]; then
    echo "Usage: run-face-detector.sh textfile"
    exit 1
fi  

IFS=$'\n'
#ファイルを配列に読み込む
file=(`cat "$1"`)

ln=0
for line in "${file[@]}"; do
    ln=`expr $ln + 1`
    rosrun face_detector face_detector_main.py "$line" 
done
