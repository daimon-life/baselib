if(DEFINED TARGET_NAME)
  set(TARGET ${TARGET_NAME})
else()
  set(TARGET baseutil)
endif()


set(CPP_LIST
    RetDefine.h
    PathUtil.cpp
    ClipboardUtil.cpp
    StringUtil.cpp
    DylibUtil.cpp
    BaseLog.cpp
)

include_directories(${PROJECT_OUTPUT_INCLUDE_DIR})
include_directories(${PROJECT_OUTPUT_INCLUDE_DIR}/${TARGET})

# add target
add_library(${TARGET} STATIC ${CPP_LIST})

# disable printf printf_s etc.
if(MSVC)
  add_definitions(/wd4996)
endif()

SET_PROPERTY(TARGET ${TARGET} PROPERTY FOLDER "base")
