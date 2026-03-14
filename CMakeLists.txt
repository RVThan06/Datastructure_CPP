cmake_minimum_required(VERSION 3.20) # [cite: 1]

# --- Project Meta Information ---
project(DataStructs
    VERSION 1.0.0
    DESCRIPTION "A modern C++20 Header-Only Data Structures Library"
    LANGUAGES CXX
)

# --- Top Level Check ---
# Check if this project is being built directly or included by another project[cite: 2].
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(DATASTRUCTS_IS_TOP_LEVEL ON)
else()
    set(DATASTRUCTS_IS_TOP_LEVEL OFF)
endif()

# --- Options ---
# You (Top Level) -> Default ON
# User (Subdirectory) -> Default OFF [cite: 3]
option(DATASTRUCTS_BUILD_TESTS "Build unit tests" OFF)
option(DATASTRUCTS_BUILD_EXAMPLES "Build example applications" ${DATASTRUCTS_IS_TOP_LEVEL})
option(DATASTRUCTS_BUILD_SANDBOX "Build local sandbox executable" ${DATASTRUCTS_IS_TOP_LEVEL})

# --- C++ Standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Library Definition ---
add_library(datastructs INTERFACE)

# --- Include Directories ---
target_include_directories(datastructs INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# --- Compiler Warnings ---
if(MSVC)
    target_compile_options(datastructs INTERFACE
        /W4
        /permissive-
    )
else()
    # GCC/Clang Strict Flags [cite: 4]
    target_compile_options(datastructs INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion   # Warns on unsigned/signed mix [cite: 5]
        -Weffc++
    )
endif()

# --- Subdirectories (Conditional) ---
# The EXISTS check ensures CMake doesn't fail if the folders aren't created yet.
if(DATASTRUCTS_BUILD_TESTS)
    enable_testing()
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
        add_subdirectory(tests)
    endif()
endif()

if(DATASTRUCTS_BUILD_EXAMPLES)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples")
        add_subdirectory(examples)
    endif()
endif()

# --- Sandbox Executable ---
if(DATASTRUCTS_BUILD_SANDBOX AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(Sandbox src/main.cpp)

    # Link the library to the sandbox [cite: 6]
    target_link_libraries(Sandbox PRIVATE datastructs)

    # Allow sandbox to include its own local headers if needed
    target_include_directories(Sandbox PRIVATE src)
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Set the input and output paths for the Doxyfile
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)

    # Create a custom 'docs' target
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen..."
        VERBATIM
    )
    message(STATUS "Doxygen found: 'docs' target created.")
else()
    message(STATUS "Doxygen not found. Documentation will not be generated.")
endif()
