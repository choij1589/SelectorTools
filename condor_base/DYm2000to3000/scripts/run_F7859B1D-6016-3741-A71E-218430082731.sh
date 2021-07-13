#!/bin/sh
cd /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

./Utilities/scripts/makeHistFile.py \
-f /store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-2000to3000_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/710000/F7859B1D-6016-3741-A71E-218430082731.root -a ZGen -s None \
--input_tier NanoAOD \
-o /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools/condor_base/DYm2000to3000/F7859B1D-6016-3741-A71E-218430082731.root \
--selectorArgs lhe=1 born=1 bare=1 wSignOnly=1 