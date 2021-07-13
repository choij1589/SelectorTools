#!/bin/sh
cd /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

./Utilities/scripts/makeHistFile.py \
-f /store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1/100000/B8504CE5-35E5-7144-8EC3-3B9DE616B566.root -a ZGen -s None \
--input_tier NanoAOD \
-o /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools/condor_base/DYm50_ext/B8504CE5-35E5-7144-8EC3-3B9DE616B566.root \
--selectorArgs lhe=1 born=1 bare=1 wSignOnly=1 