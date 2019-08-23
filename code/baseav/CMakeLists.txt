# target name setting
if(DEFINED TARGET_NAME)
  set(TARGET ${TARGET_NAME})
else()
  set(TARGET baseav)
endif()


# extern header files
set(INC_LIST
)

# source cpp files for target
set(CPP_LIST
    audioutil.cpp
)

# group for this target files
string(REGEX REPLACE "([^;]+)" "${PROJECT_SOURCE_DIR}/include/${TARGET}/\\1" INC_LIST "${INC_LIST}")
string(REGEX REPLACE "([^;]+)" "${PROJECT_SOURCE_DIR}/code/${TARGET}/\\1" CPP_LIST "${CPP_LIST}")
foreach(file ${INC_LIST} ${CPP_LIST})
  string(REGEX REPLACE "^${PROJECT_SOURCE_DIR}/(.*)/.*$" "\\1" groupname ${file})
  if(WIN32)
    string(REGEX REPLACE "/" "\\\\" groupname ${groupname})
  endif()
  source_group(${groupname} FILES ${file})
  unset(groupname)
endforeach()


# include directories setting for target
include_directories(${PROJECT_OUTPUT_INCLUDE_DIR})
include_directories(${PROJECT_OUTPUT_INCLUDE_DIR}/${TARGET})


# add target
add_library(${TARGET} STATIC ${CPP_LIST} ${INC_LIST})


# disable printf printf_s etc.
if(MSVC)
  add_definitions(/wd4996)
endif()

# group this target to base
SET_PROPERTY(TARGET ${TARGET} PROPERTY FOLDER "base")
