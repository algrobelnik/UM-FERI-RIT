if ! [[ -v TESTLIB_PATH ]]
then
    source testlib.sh || {
        echo "could not load testlib.sh"
        exit 1
    }
fi

printHeader "Izhod funkcije izris"

if [[ -f result.png ]]
then
    {
        echo "<div><img src=\"data:image/png;base64,"
        base64 result.png
        echo "\" alt=\"rezultat preizkusa\" />"
        echo "</div>"

        printWarning "Izhod preizkusa najden, rezultat bo preverjen ročno"
    }
else
    echo "Izhod preizkusa \"result.png\" ni mogoče najti."
    printFail "Rezultat preizkusa ni bil shranjen"
fi


printFooter
