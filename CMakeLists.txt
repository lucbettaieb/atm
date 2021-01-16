cmake_minimum_required (VERSION 3.5)
project (atm)

find_package (Threads REQUIRED)

add_library(atm
  atm.cpp
  account.cpp
  machine.cpp
)

add_executable(simulator 
  simulator.cpp
)

target_link_libraries(simulator
  atm
  ${CMAKE_THREAD_LIBS_INIT}
)

add_subdirectory(third_party/gtest)
enable_testing()

add_executable(unit_tests unit_tests.cpp)

target_link_libraries(unit_tests
  atm
  GTest::GTest
  GTest::Main
)

add_test(test_all unit_tests)
