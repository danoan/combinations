#!/bin/sh

PROJECT_DIR=$(realpath $1)
BUILD_PATH=${PROJECT_DIR}/build-release
INSTALL_PATH=${PROJECT_DIR}/export


sh ${PROJECT_DIR}/.travis/build-combinations.sh \
$BUILD_PATH \
$INSTALL_PATH \
~/Sources/boost_1_69_0 \
~/Sources/boost_1_69_0/stage/lib \
release

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${INSTALL_PATH}/lib

${INSTALL_PATH}/test/bin/test-eager-recursive
${INSTALL_PATH}/test/bin/test-lazy-nonrecursive
${INSTALL_PATH}/test/bin/test-lazy-recursive
${INSTALL_PATH}/test/bin/test-range
${INSTALL_PATH}/test/bin/test-multiple-resolver
${INSTALL_PATH}/test/bin/test-fundamental-combinator

