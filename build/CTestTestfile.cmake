# CMake generated Testfile for 
# Source directory: /home/luc/atm
# Build directory: /home/luc/atm/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_all "unit_tests")
subdirs("third_party/gtest")
