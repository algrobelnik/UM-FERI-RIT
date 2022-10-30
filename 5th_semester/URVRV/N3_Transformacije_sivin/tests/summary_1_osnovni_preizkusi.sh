#!/usr/bin/env bash
if ! [[ -v TESTLIB_PATH ]]
then
    source testlib.sh || {
        echo "could not load testlib.sh"
        exit 1
    }
fi

printHeader "Rezultati izenačevanja histograma"

echo "<p>Vhodna slika</p>"
echo "<div><img src=\"data:image/png;base64,"
base64 input.png
echo "\" alt=\"originalna slika\"/>"
echo "</div>"

for res_ind in 1 2 3 4
do
    echo "<div>"
    if [[ -f result_${res_ind}.png ]] 
    then
        {
            echo "<p></p>"
            echo "<div><img src=\"data:image/png;base64,"
            base64 result_${res_ind}.png
            echo "\" alt=\"izenačevanje histogramov, primer ${res_ind}\" />"
            echo "</div>"

            printWarning "Rezultat bo preverjen ročno."
        }
    else
        echo "Izhod preizkusa \"result${res_ind}.png\" ni mogoče najti."
        printFail "Izhod preizkusa ni bil shranjen."
    fi
    echo "</div>"
done

printFooter
