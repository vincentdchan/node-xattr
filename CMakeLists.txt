cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (node-xattr)
include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES
  "src/mac_utils.h"
  "src/mac_utils.mm"
  "src/workers.h"
  "src/node_xattr.cc"
  "src/mac/GMAvailability.h"
  "src/mac/GMFinderInfo.h"
  "src/mac/GMFinderInfo.m"
  "src/mac/GMResourceFork.h"
  "src/mac/GMResourceFork.m"
)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

if (APPLE)
  set (MACOSX_DEPLOYMENT_TARGET "10.12")
  set (CMAKE_OSX_DEPLOYMENT_TARGET "10.12")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-arc")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc")
  set_property(
    TARGET ${PROJECT_NAME}
    APPEND_STRING
    PROPERTY COMPILE_FLAGS "-fobjc-arc"
  )
  # target_link_libraries(${PROJECT_NAME}
  #   "-framework AppKit"
  #   "-framework CoreServices"
  #   "-framework Security"
  # )
endif()

# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# define NPI_VERSION
add_definitions(-DNAPI_VERSION=3)
