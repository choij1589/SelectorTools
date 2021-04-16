for i in {38..50}
do
	./Utilities/scripts/makeHistFile.py \
	-f /u/user/choij/SE_UserHome/DYm50_012j_nlo_ewparams_UL_cp5/NANOGEN_${i}.root \
	-a ZGen -s None --input_tier NanoAOD \
	--selectorArgs lhe=1 prefsr=1 born=1 bare=1 wSignOnly=1 \
	-o DYm50_Output/output_${i}.root
done
