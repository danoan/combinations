#!/bin/bash

SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
PROJECT_ROOT=$(cd $SCRIPT_PATH && cd .. && pwd)
GCOV_FILES=${PROJECT_ROOT}/build-debug/lab/test/coverage/CMakeFiles/test-coverage.dir
COVERAGE_OUTPUT_FOLDER=${PROJECT_ROOT}/.travis/coverage

${PROJECT_ROOT}/build-debug/lab/test/coverage/test-coverage

mkdir -p ${COVERAGE_OUTPUT_FOLDER}
cd ${COVERAGE_OUTPUT_FOLDER}

gcov ${PROJECT_ROOT}/lab/test/coverage/test-coverage.cpp --object-directory ${GCOV_FILES}

lcov --capture --directory ${GCOV_FILES} --output-file test_coverage.info
genhtml test_coverage.info --output-directory report