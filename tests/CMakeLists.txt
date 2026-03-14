# ------------------------------------------------------------------------------
# 1. Fetch GoogleTest automatically
# ------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
# [FIX] Force extracted files to have the current timestamp.
  # This suppresses the CMP0135 warning and ensures correct rebuilding.
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows/MinGW: Prevent GoogleTest from overriding standard compiler settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Download and make the GTest targets available to our project
FetchContent_MakeAvailable(googletest)

# ------------------------------------------------------------------------------
# 2. Build Test Executables
# ------------------------------------------------------------------------------
# Find all .cpp files in the tests/ directory
file(GLOB TEST_SOURCES "*.cpp")

foreach(test_source ${TEST_SOURCES})
    # Extract the name (e.g., "test_vector.cpp" -> "test_vector")
    get_filename_component(test_name ${test_source} NAME_WE)

    # Create the test executable
    add_executable(${test_name} ${test_source})

    # Link your library AND the GoogleTest framework
    target_link_libraries(${test_name}
        PRIVATE
        datastructs         # Your headers, C++20 flags, and strict warnings
        GTest::gtest_main   # GoogleTest framework + an automatic main() function
    )

    # Register the test with CTest (CMake's built-in test runner)
    include(GoogleTest)
    gtest_discover_tests(${test_name})

    message(STATUS "Registered Test Suite: ${test_name}")
endforeach()
