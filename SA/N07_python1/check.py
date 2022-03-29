import subprocess
import sys

if len(sys.argv) > 1:
    subprocess.run(['./check.sh '+sys.argv[1]], shell=True)
else:
    subprocess.run(['./check.sh'], shell=True)
