#!/usr/bin/env bash

# check if necesary folders are present
[[ -f  test_config.sh ]] || {
    echo "ERROR: could not find test_config.sh, are you in a project directory?"
    exit 1
}
[[ -d src ]] || {
    echo "ERROR: could not find src/ folder, are you in a project directory?"
    exit 1
}
[[ -d tests ]] || {
    echo "ERROR: could not find tests/ folder, are you in a project directory?"
    exit 1
}

# load task specific test configuration 
source test_config.sh


# clean-up summary folder
if [[ -d summary ]]
then
    rm -r summary/ || {
        echo "could not cleanup summary/ folder"
        exit 1
    }
fi

mkdir summary/ || {
    echo "could not create summary/ folder"
    exit 1
}

if [[ -d tests/test_data/ ]] 
then
    cp -r tests/test_data/ summary/
fi

cd summary/ || {
    echo "could not move to tests/ dir"
    exit 1
}

for test_file in ../tests/test_*.py
do
    [[ ${test_file} =~ ^\.\./tests/test_(.+).py$ ]]

    test_name=${BASH_REMATCH[1]}
    summary_file="../tests/summary_${test_name}.sh"

    python3 "${test_file}" || {
        continue
    }

    if [[ -f ${summary_file} ]]
    then
        summary_output=summary_${test_name}.html
        bash "${summary_file}" > "${summary_output}" || {
            continue
        }
        xdg-open "${summary_output}"
    fi

done

