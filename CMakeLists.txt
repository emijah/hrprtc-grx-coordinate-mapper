cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
set(CMAKE_MODULE_PATH ../../cmake_modules/ CACHE STRING "set path to cmake_modules")

####
## settings for OpenRTM and OpenHRP
##
include(FindPkgConfig)
include(CheckIncludeFiles)
find_package(OpenRTM REQUIRED)
find_package(OpenHRP REQUIRED)
include_directories(${OPENRTM_INCLUDE_DIRS})
link_directories(${OPENRTM_LIBRARY_DIRS})
include_directories(${OPENHRP_INCLUDE_DIRS})
link_directories(${OPENHRP_LIBRARY_DIRS})
include_directories(/opt/grx/include)

if(QNXNTO)
  include_directories(/usr/pkg/include)
  set(NO_COMP true)
else()
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__LINUX__")
endif()
endif(QNXNTO)

include(GenerateStubSkel)

generate_stub_skel(CoordinateMapperService)
#generate_hrpsys_stub_skel_wrapper(JointDataTypes)

set(comp_sources CoordinateMapperServiceSk.cpp CoordinateMapper.cpp mapper.cpp)
add_library(CoordinateMapper SHARED ${comp_sources})
target_link_libraries(CoordinateMapper)
set_target_properties(CoordinateMapper PROPERTIES PREFIX "")

if(NO_COMP)
  set(target CoordinateMapper)
else()
  add_executable(CoordinateMapperComp CoordinateMapperComp.cpp ${comp_sources})
  target_link_libraries(CoordinateMapperComp)
  set(target CoordinateMapper CoordinateMapperComp)
endif()

install(TARGETS ${target}
  RUNTIME DESTINATION bin CONFIGURATIONS Release Debug
  LIBRARY DESTINATION lib CONFIGURATIONS Release Debug
)

if(ENABLE_COMMERCIAL)
  target_link_libraries(CoordinateMapper certify)
  target_link_libraries(CoordinateMapperComp certify)
endif()
