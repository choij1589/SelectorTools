import argparse
import os, sys
import shutil

# get arguments
parser = argparse.ArgumentParser()
parser.add_argument("-a", default=None, required=True, type=str, help="analysis name")
parser.add_argument("-s", default=None, required=True, type=str, help="?")
parser.add_argument("-f", default=None, required=True, type=str, help="xrootd path")
parser.add_argument("-d", default=None, required=True, type=str, help="base directory name")
parser.add_argument("--input_tier", default="NanoAOD", required=False, type=str, help="input tier")
parser.add_argument("--selectorArgs", default="None", required=False, type=str, nargs="+", help="selector arguments")
parser.add_argument("--force", default=False, action="store_true", help="overwrite output file")
args = parser.parse_args()

# set variables
PWD = os.getcwd()
BASEDIR_PATH = f"{PWD}/condor_base/{args.d}"
selector_args = ""
if not args.selectorArgs == None:
	for arg in args.selectorArgs:
		selector_args += arg + " "

suffix = args.f.split("/")[-1].split(".")[0]

# make base directory
try:
	os.listdir(BASEDIR_PATH)
except:
	os.mkdir(BASEDIR_PATH)
	os.mkdir(f"{BASEDIR_PATH}/output")
	os.mkdir(f"{BASEDIR_PATH}/error")
	os.mkdir(f"{BASEDIR_PATH}/log")
	os.mkdir(f"{BASEDIR_PATH}/scripts")

print(f"//==== INFO: Selector output will be stored in {BASEDIR_PATH}")

condor_jdl = f"""Universe		= vanilla
Executable           = run_{suffix}.sh
GetEnv               = false

WhenToTransferOutput = On_Exit_Or_Evict
ShouldTransferFiles  = yes
want_graceful_removal = true
request_memory       = 2000
request_disk         = 2048000
use_x509userproxy = True

# stop jobs from running if they blow up in size or memory
periodic_hold        = (DiskUsage/1024 > 10.0*2000 ||  ImageSize/1024 > RequestMemory*2)

+JobFlavour = "workday"
arguments             = $(Process)
output                = {BASEDIR_PATH}/output/job_{suffix}.out
error                 = {BASEDIR_PATH}/error/job_{suffix}.err
log                   = {BASEDIR_PATH}/log/job_{suffix}.log

queue 1"""

run = f"""#!/bin/sh
cd {PWD}
process=$(($1 + 1))

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

./Utilities/scripts/makeHistFile.py \\
-f {args.f} -a {args.a} -s {args.s} \\
--input_tier {args.input_tier} \\
-o {BASEDIR_PATH}/{suffix}.root \\
"""
if not selector_args == "":
	run += f"""--selectorArgs {selector_args}"""

with open(f"{BASEDIR_PATH}/scripts/condor_{suffix}.jdl", "w") as f:
	f.write(condor_jdl)
with open(f"{BASEDIR_PATH}/scripts/run_{suffix}.sh", "w") as f:
	f.write(run)

# submit
os.chdir(f"{BASEDIR_PATH}/scripts")
os.system(f"condor_submit condor_{suffix}.jdl")
