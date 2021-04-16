#!/bin/sh
cd /u/user/choij/scratch/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
echo $USER
sample=${1}
process=$(($2 + 1))
SE_USERHOME="/pnfs/knu.ac.kr/data/cms/store/user/choij"
echo $process

#path="/pnfs/knu.ac.kr/data/cms/store/user/sako/validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN/201219_093041/0000"
path="${SE_USERHOME}/DYm50_012j_nlo_ewparams_cp5/RunIICustomize/201216_103125/0000"

if ! [ -d condor_base/${sample} ]
then
	mkdir condor_base/${sample}
fi

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
export LD_PRELOAD="/usr/lib64/libpdcap.so"

./Utilities/scripts/makeHistFile.py \
-f dcap://cluster142.knu.ac.kr/${path}/${sample}_${process}.root \
-a ZGen -s None --input_tier NanoAOD \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
-o condor_base/${sample}/${sample}_${process}.root
