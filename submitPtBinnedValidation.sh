#/bin/sh
./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_ext/210430_183822/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_Incl.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN_LHEZpT-0to50/210415_165619/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG265_ZPt0to50.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN_LHEZpT-50to100/210413_040437/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG265_ZPt50to100.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN_LHEZpT-100to250/210413_040823/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG265_ZPt100to250.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN_LHEZpT-250to400/210413_041130/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG265_ZPt250t400.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN_LHEZpT-400to650/210413_042813/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG265_ZPt400to650.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20/NanoGEN_LHEZpT-650toinf/210413_043259/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG265_ZPt650toinf.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-0to50/210430_021656/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_ZPt0to50.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-50to100/210430_022358/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_ZPt50to100.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-100to250/210430_022645/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_ZPt100to250.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-250to400/210430_022946/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_ZPt250to400.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-400to650/210430_023206/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_ZPt400to650.root --force

./Utilities/scripts/submitMakeHistFileToCondorKNU.py \
-a ZGen -s None \
--se --user sako -d validation/mgEWparamSyncUL20/DYJetsToLL_M-50_amcatnloFxFx_mgEWparamSyncUL20_mg273/NanoGEN_LHEZpT-650toinf/210430_023530/0000 \
--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 theoryLhe=1 \
-o DYm50_MG273_ZPt650toinf.root --force
