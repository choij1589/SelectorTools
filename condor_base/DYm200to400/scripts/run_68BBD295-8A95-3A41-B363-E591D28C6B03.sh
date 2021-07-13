#!/bin/sh
cd /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

./Utilities/scripts/makeHistFile.py \
-f /store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-200to400_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/60000/68BBD295-8A95-3A41-B363-E591D28C6B03.root -a ZGen -s None \
--input_tier NanoAOD \
-o /d0/scratch/choij/GenValidation/CMSSW_11_0_0/src/Analysis/SelectorTools/condor_base/DYm200to400/68BBD295-8A95-3A41-B363-E591D28C6B03.root \
--selectorArgs lhe=1 born=1 bare=1 wSignOnly=1 