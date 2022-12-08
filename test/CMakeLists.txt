enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(gdk_tests "")

add_subdirectory(nodes)

target_link_libraries(gdk_tests gdk GTest::gtest_main)
target_include_directories(gdk_tests PUBLIC "${GTEST_INCLUDE_DIRS}")
gtest_discover_tests(gdk_tests)
