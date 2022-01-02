import os
os.system('curl https://www.google.com/ | grep -Eo "<div" | wc')
