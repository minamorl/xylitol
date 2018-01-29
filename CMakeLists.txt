cmake_minimum_required(VERSION 3.9)

# set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(xylitol VERSION 1.0.0 LANGUAGES CXX)

# Compiler
if(NOT CMAKE_TOOLCHAIN_FILE)
  message("no toolchain specified; autodetecting...")
endif()


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "configuration: ${CMAKE_BUILD_TYPE}")


# options
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# globals
add_definitions(-DBOOST_HAS_ICU=1)
set(XYLITOL_MODULES_PATH "${PROJECT_SOURCE_DIR}/modules")
set(XYLITOL_DATA_PATH "${PROJECT_SOURCE_DIR}/data")


# libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(ICU REQUIRED icu-uc)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# -----------------------------------------
# build deps
include(ExternalProject)
set(XYLITOL_EXT_PREFIX "${CMAKE_BINARY_DIR}/ext")
set(XYLITOL_RPATH_ORIGIN "\$ORIGIN/../lib")

ExternalProject_Add(
  boost
  PREFIX           "${XYLITOL_EXT_PREFIX}"

  URL "https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2"
  URL_HASH SHA256=5721818253e6a0989583192f96782c4a98eb6204965316df9f5ad75819225ca9

  # ... or just skip copying.
  # DOWNLOAD_COMMAND  ""

  UPDATE_COMMAND    ""
  PATCH_COMMAND     ""

  CONFIGURE_COMMAND
    "./bootstrap.sh"
    "--with-toolset=clang"
    "--without-libraries=mpi,graph_parallel,python,wave,fiber,coroutine,serialization,test,context"
    "--prefix=${CMAKE_BINARY_DIR}"

  BUILD_IN_SOURCE TRUE
  BUILD_COMMAND
    "./b2"
    "toolset=clang"
    "link=shared" "runtime-link=shared" "threading=multi" "variant=release"
    "address-model=64"
    # "instruction-set=${XYLITOL_ARCH}" # specify CPU arch for more optimization (deployment purpose)
    "cxxflags=-std=c++17"
    "linkflags=-std=c++17"
    "dll-path=\"'${XYLITOL_RPATH_ORIGIN}'\""
    "-q" # halt at first error
    # "-a" # full rebuild
    "-j5" # parallel build jobs
    # "--without-mpi"
    "-sICU_PATH=/usr/lib/x86_64-linux-gnu"
    "--prefix=${CMAKE_BINARY_DIR}"
    "install"

  INSTALL_COMMAND ""
)

set(XYLITOL_ALL_BOOST_LIBRARIES "")

function(alc_init_boost component_name boost_libs)
  set(tmp "")
  foreach(lib IN LISTS boost_libs)
    if(NOT "${lib}" IN_LIST XYLITOL_ALL_BOOST_LIBRARIES)
      list(APPEND XYLITOL_ALL_BOOST_LIBRARIES "${lib}")
      set(XYLITOL_ALL_BOOST_LIBRARIES "${XYLITOL_ALL_BOOST_LIBRARIES}" PARENT_SCOPE)
      add_library(boost_${lib} SHARED IMPORTED)
      set_target_properties(
        boost_${lib} PROPERTIES
        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/libboost_${lib}.so"
      )
    endif()

    list(
      APPEND
      tmp
      "boost_${lib}"
    )
  endforeach()
  set(${component_name}_BOOST_LIBRARIES ${tmp} PARENT_SCOPE)
endfunction()

# end deps
# -----------------------------------------

# Global build config
add_definitions(
  -DBOOST_LOG_DYN_LINK
  -DBOOST_STACKTRACE_DYN_LINK
  -DBOOST_STACKTRACE_USE_ADDR2LINE
  # "-DBOOST_USER_CONFIG=\"${PROJECT_SOURCE_DIR}/include/alc/detail/boost_user_config.hpp\""
)

set(
  CMAKE_CXX_FLAGS
  "-Wall -Wextra -Werror -pedantic-errors"
)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0") # -fno-inline -pg
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_DEBUG_POSTFIX d)

# -------------------------------

# subdirectories
# add_subdirectory(src)
alc_init_boost(
  ALC
  "log;date_time;thread;chrono;atomic;program_options;filesystem;regex;iostreams;locale;system"
)

add_executable(
  xylitol
  "${PROJECT_SOURCE_DIR}/src/main.cpp" # your source files here
)

target_include_directories(
  xylitol PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(
  xylitol SYSTEM PUBLIC
  "${CMAKE_BINARY_DIR}/include"
)

target_link_libraries(
  xylitol
  ${XYLITOL_BOOST_LIBRARIES}
  m # libm
  ${CMAKE_THREAD_LIBS_INIT}
  rt # librt
)

set_target_properties(
  xylitol
  PROPERTIES
  OUTPUT_NAME xylitol
  COMPILE_DEFINITIONS ""
)
add_dependencies( # cmake target dependencies
  xylitol
  boost
)
# -------------------------------

# tests
# include(CTest)
# add_subdirectory(test)
