import subprocess
import sys

if len(sys.argv) > 1:
    subprocess.run(['awk -f grades.awk -d '+sys.argv[1]], shell=True)
else:
    subprocess.run(['awk -f grades.awk'], shell=True)
