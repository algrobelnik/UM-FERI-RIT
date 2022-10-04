#!/bin/bash
TMPFILES=($(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX) $(mktemp /tmp/tmp-XXXXX))
sorted=$(ls -cr /tmp/tmp-* | tail -n 5)
for tmp in ${sorted[@]}; do
  echo -e "$tmp\ntemp file" >> $tmp
  cat $tmp
done
rm ${TMPFILES[@]}
