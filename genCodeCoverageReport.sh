#!/bin/bash

lcov --zerocounters --directory build/CMakeFiles/test_html_server.dir
sleep 1
./build/test_html_server
sleep 1
lcov --capture --directory build/CMakeFiles/test_html_server.dir/src --output-file html_server.info

genhtml html_server.info --output-directory CODE_COVERAGE
