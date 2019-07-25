#!/bin/bash

BUILD_PATH=$(realpath $1)
TEST_BASE_PATH=${BUILD_PATH}/lab/test
TEST_TECHNIQUES_BASE_PATH=${BUILD_PATH}/lab/benchmark/techniques
EXAMPLE_BASE_PATH=${BUILD_PATH}/lab/example

${TEST_BASE_PATH}/core/fundamental-combinator/test-fundamental-combinator
${TEST_BASE_PATH}/core/multiple-resolver/test-multiple-resolver
${TEST_BASE_PATH}/core/multithread/test-multithread
${TEST_BASE_PATH}/core/range/test-range


${TEST_TECHNIQUES_BASE_PATH}/eager-recursive/lab/test/test-eager-recursive
${TEST_TECHNIQUES_BASE_PATH}/lazy-nonrecursive/lab/test/test-lazy-nonrecursive
${TEST_TECHNIQUES_BASE_PATH}/lazy-recursive/lab/test/test-lazy-recursive


${EXAMPLE_BASE_PATH}/core/multiple-combinator/example-multiple-combinator
${EXAMPLE_BASE_PATH}/core/single/example-single
${EXAMPLE_BASE_PATH}/core/multithread/example-multithread

