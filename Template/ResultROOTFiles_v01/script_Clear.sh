#!/bin/bash

rm *.zip
rm *.root
rm -rf ROOTFiles
rm -rf Summary
rm *.log
rm SingleBin/*.pdf
rm SingleBin/*.root

echo "+++++++++++++++++++++++++++++++++"
echo "the directory is cleaned"
echo "run the command below:"
echo "source summary.sh >&summary.log"
echo "+++++++++++++++++++++++++++++++++"

