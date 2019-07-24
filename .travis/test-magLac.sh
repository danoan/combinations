#!/bin/bash

INSTALL_PATH=$(realpath $1)
TEST_BIN_ROOT=${INSTALL_PATH}/test/bin
EXAMPLE_BIN_ROOT=${INSTALL_PATH}/example/bin

${TEST_BIN_ROOT}/test-eager-recursive
${TEST_BIN_ROOT}/test-fundamental-combinator
${TEST_BIN_ROOT}/test-lazy-nonrecursive
${TEST_BIN_ROOT}/test-lazy-recursive
${TEST_BIN_ROOT}/test-multiple-resolver
${TEST_BIN_ROOT}/test-multithread
${TEST_BIN_ROOT}/test-range


${EXAMPLE_BIN_ROOT}/example-multiple-combinator
${EXAMPLE_BIN_ROOT}/example-single
${EXAMPLE_BIN_ROOT}/example-multithread

