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

if ! [[ -v TEST_VERSION ]]
then
    TEST_VERSION='development'
fi

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

cp tests/* -r summary/ || {
    echo "could not copy tests to summary/ folder"
    exit 1
}
cd summary/ || {
    echo "could not move to summary/ folder"
    exit 1
}

# load formating library
source test_format_lib.sh || {
    echo "ERROR: could not source test_format_lib.sh, maybe testlib/ is not added to PATH"
    exit 1
}

echo_section "version: ${TEST_VERSION}"

TEST_FILES=()
TEST_RESULTS=()
TEST_FILENAME_MAX_LEN=0
RETURN_VALUE=0

# Get test files provided as command line arguments if there are any, otherwise
# find all test files in current folder.
if [[ "$#" -gt 0 ]]
then
    for test_file in "$@"
    do
        # Strip directory name from path and keep only file name
        TEST_FILES+=("$(basename "${test_file}")")
    done
else
    TEST_FILES=($(
        find . -regex '\./test_.*\.py' -printf '%f\n'
    ))
fi
for test_file in "${TEST_FILES[@]}"
do
    [[ ${test_file} =~ ^test_(.+).py$ ]]

    test_name=${BASH_REMATCH[1]}
    summary_file="summary_${test_name}.sh"

    python3 "${test_file}"
    return_value="$?"
    #echo "return value: $return_value"
    #echo "test file: $test_file"
    #echo "summary file: $summary_file"
    TEST_RESULTS+=("${return_value}")
    TEST_FILENAME_MAX_LEN=$(("${#test_file}" > "${TEST_FILENAME_MAX_LEN}" \
                              ? "${#test_file}" : "${TEST_FILENAME_MAX_LEN}"))
    RETURN_VALUE=$(("${return_value}" > "${RETURN_VALUE}" \
                     ? "${return_value}" : "${RETURN_VALUE}"))

    if [[ "$return_value" -eq 0 ]] && [[ -f ${summary_file} ]]
    then
        summary_output=summary_${test_name}.html
        bash "${summary_file}" > "${summary_output}" || {
            continue
        }
        xdg-open "${summary_output}"
    fi
done

echo_test_title "TEST RESULTS"

for i in "${!TEST_FILES[@]}"
do
    printf "%s" "${TEST_FILES[i]}"

    space_count=$(("${TEST_FILENAME_MAX_LEN}" - "${#TEST_FILES[i]}" + 4))
    printf "%${space_count}s"

    if [[ "${TEST_RESULTS[i]}" -eq 0 ]]
    then
        echo_ok "TEST PASSED"
    else
        echo_fail "TEST FAILED"
    fi
done

if [[ ${RETURN_VALUE} -le 1 ]]
then
	exit 0
else
	exit "${RETURN_VALUE}"
fi
