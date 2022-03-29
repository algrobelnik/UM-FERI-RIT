import subprocess
import sys

if len(sys.argv) > 1:
    subprocess.run(['./factorial.sh '+sys.argv[1]], shell=True)
else:
    subprocess.run(['./factorial.sh'], shell=True)
