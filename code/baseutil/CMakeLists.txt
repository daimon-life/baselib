# target name setting
if(NOT DEFINED TARGET_NAME)
  set(TARGET_NAME baseutil)
endif()


# public header files
set(INC_LIST
    PathUtil.h
    ClipboardUtil.h
    StringUtil.h
    DylibUtil.h
    BaseLog.h
    BaseLogSimple.h
)

# source cpp files
set(CPP_LIST
    RetDefine.h
    PathUtil.cpp
    ClipboardUtil.cpp
    StringUtil.cpp
    DylibUtil.cpp
    BaseLog.cpp
    BaseLogSimple.cpp
)

# group for this target files
string(REGEX REPLACE "([^;]+)" "${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}/\\1" INC_LIST "${INC_LIST}")
string(REGEX REPLACE "([^;]+)" "${PROJECT_SOURCE_DIR}/code/${TARGET_NAME}/\\1" CPP_LIST "${CPP_LIST}")
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
include_directories(${PROJECT_OUTPUT_INCLUDE_DIR}/${TARGET_NAME})


# add target and set target properties
add_library(${TARGET_NAME} ${CPP_LIST} ${INC_LIST})
if (BUILD_SHARED_LIBS)
    set_target_properties(${TARGET_NAME} PROPERTIES
      COMPILE_DEFINITIONS "BUILD_SHARED_LIBS=1")
endif()
#set_target_properties(${TARGET_NAME} PROPERTIES
#PUBLIC_HEADER ${INC_LIST})
      
# disable printf printf_s etc.
if(MSVC)
  add_definitions(/wd4996)
endif()

# group this target to base
SET_PROPERTY(TARGET ${TARGET_NAME} PROPERTY FOLDER "base")

# install
# install library files
INSTALL(TARGETS ${TARGET_NAME}
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib
       PUBLIC_HEADER DESTINATION include
)
# install header files
#INSTALL(DIRECTORY "${PROJECT_SOURCE_DIR}/include/${TARGET_NAME}"
    #DESTINATION "include")
