if(DEFINED TARGET_NAME)
  set(TARGET ${TARGET_NAME})
else()
  set(TARGET baseutil)
endif()


set(CPP_LIST
    PathUtil.cpp
    ClipboardUtil.h
    ClipboardUtil.cpp
    StringUtil.h
    StringUtil.cpp
)

# add target
add_library(${TARGET} STATIC ${CPP_LIST})

SET_PROPERTY(TARGET ${TARGET} PROPERTY FOLDER "bases")
