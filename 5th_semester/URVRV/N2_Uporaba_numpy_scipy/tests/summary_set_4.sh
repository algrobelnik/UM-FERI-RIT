#!/usr/bin/env bash
if ! [[ -v TESTLIB_PATH ]]
then
    source testlib.sh || {
        echo "could not load testlib.sh"
        exit 1
    }
fi

printHeader "Rezultat pretvorbe slik (sklop 4)"

if [[ -f output.png ]] && [[ -f reference.png ]]
then
    {
        echo "<p>Vrnjena slika:</p>"
        echo "<div><img src=\"data:image/png;base64,"
        base64 output.png
        echo "\" alt=\"Rezultat pretvorbe\" />"
        echo "</div>"
        echo "<p>Pričakovan rezultat:</p>"
        echo "<div><img src=\"data:image/png;base64,"
        base64 reference.png
        echo "\" alt=\"Pričakovana slika\" />"
        echo "</div>"

        printWarning "Izhod preizkusa najden, rezultat bo preverjen ročno"
    }
else
    echo "Izhodov preizkusa \"output.png\" in \"reference.png\" ni mogoče najti."
    printFail "Izhod preizkusa ni bil shranjen"
fi


printFooter
