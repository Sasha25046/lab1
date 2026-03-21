cd /workspaces/lab1
rm -rf build
mkdir build
cd build
cmake ..
make
./run_tests

lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch

lcov --remove coverage.info '/usr/*' '*/gtest/*' --output-file coverage.info --ignore-errors mismatch

genhtml coverage.info --output-directory coverage_report --ignore-errors mismatch