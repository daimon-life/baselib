cmake_minimum_required(VERSION 3.3.2)
project(baselib VERSION 1.0.0.0)

# // options
option(BUILD_SHARED_LIBS "Build shared libraries (DLL or So or Dylib)." OFF)

# ---> generate configure files 
# // configure version file
configure_file (
  "${PROJECT_SOURCE_DIR}/build/version.h.in"
  "${PROJECT_SOURCE_DIR}/include/version.h"
)


# ---> targets of package base test 
# // package targets
set(PACKAGE_LIST
    
)

# // base targets
set(BASE_LIST
    baseutil
    baseav
)

# // test targets
set(TEST_LIST
    test_baseutil
)


# ---> check generator
# // check generators are available for project
if(CMAKE_HOST_WIN32)
  if(MSVC AND MSVC_VERSION LESS 1800)
    message(FATAL_ERROR "Visual studio must be 2013 or later .")
  endif()
endif()


# ---> set cmake project
# // configure
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "CMake build type" FORCE)
endif()

# // check architecture of operating system
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  if(CMAKE_HOST_WIN32)
    set(TAEGET_ARCH "x64")
  elseif(CMAKE_HOST_APPLE)
    set(TAEGET_ARCH "x86_64")
  elseif(CMAKE_HOST_UNIX)
    set(TAEGET_ARCH "64bit")
  else()
    message(FATAL_ERROR, "arch of host not support")
  endif()
else()
  if(CMAKE_HOST_WIN32)
    set(TAEGET_ARCH "win32")
  elseif(CMAKE_HOST_APPLE)
    set(TAEGET_ARCH "i386")
  elseif(CMAKE_HOST_UNIX)
    set(TAEGET_ARCH "32bit")
  else()
    message(FATAL_ERROR, "arch of host not support")
  endif()
endif()

# //custom output directory name
set(TARGET_OUTPUT_DIR_PREFIX ${PROJECT_SOURCE_DIR}/target)
if(CMAKE_CONFIGURATION_TYPES)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${config}" config_up)
    set(TARGET_OUTPUT_DIR_NAME ${CMAKE_SYSTEM_NAME}-${TAEGET_ARCH}-${config})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_up} ${TARGET_OUTPUT_DIR_PREFIX}/${TARGET_OUTPUT_DIR_NAME}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_up} ${TARGET_OUTPUT_DIR_PREFIX}/${TARGET_OUTPUT_DIR_NAME}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_up} ${TARGET_OUTPUT_DIR_PREFIX}/${TARGET_OUTPUT_DIR_NAME}/bin)
    set(CMAKE_PDB_OUTPUT_DIRECTORY_${config_up} ${TARGET_OUTPUT_DIR_PREFIX}/${TARGET_OUTPUT_DIR_NAME}/pdb)
    unset(config_up)
  endforeach()
  set(TARGET_OUTPUT_DIR_NAME ${CMAKE_SYSTEM_NAME}-${TAEGET_ARCH}-${CMAKE_CFG_INTDIR})
else()
  set(TARGET_OUTPUT_DIR_NAME ${CMAKE_SYSTEM_NAME}-${TAEGET_ARCH}-${CMAKE_BUILD_TYPE})
endif()
set(TARGET_OUTPUT_DIR ${TARGET_OUTPUT_DIR_PREFIX}/${TARGET_OUTPUT_DIR_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TARGET_OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TARGET_OUTPUT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TARGET_OUTPUT_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${TARGET_OUTPUT_DIR}/pdb)
set(PROJECT_OUTPUT_INCLUDE_DIR     ${PROJECT_SOURCE_DIR}/include)

# include and library directory
include_directories(${PROJECT_OUTPUT_INCLUDE_DIR})
include_directories(${TARGET_OUTPUT_DIR}/include)
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# // rpath
if(NOT CMAKE_HOST_WIN32)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  if(CMAKE_HOST_APPLE)
    cmake_policy(SET CMP0068 OLD)
    set(CMAKE_INSTALL_RPATH "@executable_path")
  elseif(CMAKE_HOST_UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
  else() 
    message(AUTHOR_WARNING "rpath not support")
  endif()
endif()

# // suport c++11
set(CMAKE_CXX_STANDARD 11)

# // Symbol generation
if(CMAKE_HOST_APPLE)
  set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
elseif(CMAKE_HOST_UNIX AND CMAKE_BUILD_TYPE STREQUAL Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# // compile settings
if(MSVC)
  add_definitions(/wd4819 /source-charset:utf-8)
else()
  #add_definitions(-Wall -fvisibility=hidden)
endif()


# ---> load modules
# // load source module
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
foreach(base ${BASE_LIST})
    set(subdirectory code/${base})
    set(TARGET_NAME ${base})
    if(EXISTS ${PROJECT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt)
        add_subdirectory(${subdirectory})
    else()
        message(AUTHOR_WARNING "No CMakeLists.txt found in ${subdirectory}")
    endif()
    unset(subdirectory)
    unset(TARGET_NAME)
endforeach()

# // load test module
foreach(test ${TEST_LIST})
    set(subdirectory test/${test})
    set(TARGET_NAME ${test})
    if(EXISTS ${PROJECT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt)
        add_subdirectory(${subdirectory})
    else()
        message(AUTHOR_WARNING "No CMakeLists.txt found in ${subdirectory}")
    endif()
    unset(subdirectory)
    unset(TARGET_NAME)
endforeach()

# load packets
include(ExternalProject)
foreach(package ${PACKAGE_LIST})
    if(EXISTS ${PROJECT_SOURCE_DIR}/package/${package}.cmake)
        include(${PROJECT_SOURCE_DIR}/package/${package}.cmake)
    else()
        message(AUTHOR_WARNING "No ${package}.cmake found in ${PROJECT_SOURCE_DIR}/package")
    endif()
endforeach()

