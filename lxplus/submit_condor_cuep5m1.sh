#!/bin/sh

./Utilities/scripts/submitMakeHistFileToCondor.py \
 	-f DYm50_0j_nlo_cuep5m1 -a ZGen -s None --input_tier NanoAOD \
 	-d /afs/cern.ch/work/c/choij/SelectorSubmit/Submit_DYm50_0j_nlo_cuep5m1 \
 	-n 5 -q longlunch --removeUnmerged \
 	--merge /eos/home-c/choij/EPR/SelectorOutput/DrellYan/DYm50_0j_nlo_cuep5m1.root 1.0 \
	--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
	--submit --force --local

./Utilities/scripts/submitMakeHistFileToCondor.py \
    -f DYm50_1j_nlo_cuep5m1 -a ZGen -s None --input_tier NanoAOD \
    -d /afs/cern.ch/work/c/choij/SelectorSubmit/Submit_DYm50_1j_nlo_cuep5m1 \
    -n 5 -q longlunch --removeUnmerged \
    --merge /eos/home-c/choij/EPR/SelectorOutput/DrellYan/DYm50_1j_nlo_cuep5m1.root 1.0 \
    --selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
    --submit --force --local

./Utilities/scripts/submitMakeHistFileToCondor.py \
    -f DYm50_2j_nlo_cuep5m1 -a ZGen -s None --input_tier NanoAOD \
    -d /afs/cern.ch/work/c/choij/SelectorSubmit/Submit_DYm50_2j_nlo_cuep5m1 \
    -n 5 -q longlunch --removeUnmerged \
    --merge /eos/home-c/choij/EPR/SelectorOutput/DrellYan/DYm50_2j_nlo_cuep5m1.root 1.0 \
    --selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
    --submit --force --local

./Utilities/scripts/submitMakeHistFileToCondor.py \
    -f DYm50_012j_nlo_cuep5m1 -a ZGen -s None --input_tier NanoAOD \
    -d /afs/cern.ch/work/c/choij/SelectorSubmit/Submit_DYm50_012j_nlo_cuep5m1 \
    -n 5 -q workday --removeUnmerged \
    --merge /eos/home-c/choij/EPR/SelectorOutput/DrellYan/DYm50_012j_nlo_cuep5m1.root 1.0 \
    --selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
    --submit --force --local
