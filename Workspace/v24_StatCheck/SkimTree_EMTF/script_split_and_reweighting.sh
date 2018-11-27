#!bin/bash

source script_splitData_EMTFBug.sh >&script_splitData_EMTFBug.log
echo "Split: finished"

source script_addNVtxAndGenWeight.sh >&script_addNVtxAndGenWeight.log
echo "reweighting: finished"

echo "done"
