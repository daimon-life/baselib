if(DEFINED TARGET_NAME)
  set(TARGET ${TARGET_NAME})
else()
  set(TARGET test_baseutil)
endif()


set(CPP_LIST
    test_dylibutil.cpp
)

set(DEP_TARGET_LIST
    baseutil
)

set(WIN_RC_LIST
    resource.h
    test_baseutil.rc
)

if(CMAKE_HOST_WIN32)
  list(APPEND CPP_LIST ${WIN_RC_LIST})
endif()

include_directories(${PROJECT_OUTPUT_INCLUDE_DIR})
foreach(dep_target ${DEP_TARGET_LIST})
  include_directories(${PROJECT_OUTPUT_INCLUDE_DIR}/${dep_target})
endforeach()
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# add target
add_executable(${TARGET} ${CPP_LIST})
# target depend
add_dependencies(${TARGET} ${DEP_TARGET_LIST})
target_link_libraries(${TARGET} ${DEP_TARGET_LIST})

SET_PROPERTY(TARGET ${TARGET} PROPERTY FOLDER "test")
