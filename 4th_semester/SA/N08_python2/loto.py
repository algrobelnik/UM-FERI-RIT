import subprocess
import sys

if len(sys.argv) > 2:
    subprocess.run(['awk -v NUM='+sys.argv[1]+' -v MAX_NUM='+sys.argv[2]+' -f loto.awk'], shell=True)
else:
    subprocess.run(['awk -f loto.awk'], shell=True)
