#!/bin/bash

source script_Skim_2016Data.sh >&script_Skim_2016Data.log
echo "script_Skim_2016Data.sh: done"

source script_reweight_2016MC_beforeFix.sh >&script_reweight_2016MC_beforeFix.log
echo "script_reweight_2016MC_beforeFix.sh: done"

source script_reweight_2016MC_afterFix.sh >&script_reweight_2016MC_afterFix.log
echo "script_reweight_2016MC_afterFix.sh: done"

