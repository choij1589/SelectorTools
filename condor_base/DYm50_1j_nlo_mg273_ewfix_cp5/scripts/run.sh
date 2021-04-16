#!/bin/sh
cd /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
export LD_PRELOAD="/usr/lib64/libpdcap.so"

./Utilities/scripts/makeHistFile.py \
-f dcap://cluster142.knu.ac.kr//pnfs/knu.ac.kr/data/cms/store/user/choij/DYm50_1j_nlo_ewparams_cp5/RunIICustomize/210211_134243/0000//DYm50_1j_nlo_mg273_ewfix_cp5_${process}.root \
-a ZGen -s None --input_tier NanoAOD \
--selectorArgs lhe=1 wSignOnly=1 theoryLhe=1  \
-o condor_base/DYm50_1j_nlo_mg273_ewfix_cp5/temp/DYm50_1j_nlo_mg273_ewfix_cp5_${process}.root
