#/bin/sh
./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se -d DYm50_012j_nlo_ewparams_cp5/RunIICustomize/210211_134120/0000/ \
--selectorArgs lhe=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_012j_nlo_mg273_ewfix_cp5.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se -d DYm50_0j_nlo_ewparams_cp5/RunIICustomize/210211_134202/0000/ \
--selectorArgs lhe=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_0j_nlo_mg273_ewfix_cp5.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se -d DYm50_1j_nlo_ewparams_cp5/RunIICustomize/210211_134243/0000/ \
--selectorArgs lhe=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_1j_nlo_mg273_ewfix_cp5.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se -d DYm50_2j_nlo_ewparams_cp5/RunIICustomize/210211_134327/0000/ \
--selectorArgs lhe=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_2j_nlo_mg273_ewfix_cp5.root --force
