cmake_minimum_required (VERSION 2.4.6)
include ($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_BUILD_TYPE Debug)
set (ROS_BUILD_TYPE Debug)
add_definitions (-Wall -pipe)
rosbuild_init ()
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#rosbuild_genmsg()
#rosbuild_gensrv()

##################################################
# detection of Meka / RTAI code

include (CheckIncludeFileCXX)

include_directories (/usr/realtime/include)

if (M3_DIR)
  list (APPEND CMAKE_REQUIRED_INCLUDES ${M3_DIR}/src ${M3_DIR})
  include_directories (${M3_DIR}/src ${M3_DIR})
  ###  link_directories (${M3_DIR}/lib ${M3_DIR})
endif (M3_DIR)
check_include_file_cxx (m3/shared_mem/torque_shm_sds.h HAVE_M3_SHM_HEADER)
if (${HAVE_M3_SHM_HEADER})
  message ("---- good: found Meka / RTAI")
  set (HAVE_M3 TRUE)
  add_definitions (-DHAVE_M3)
else (${HAVE_M3_SHM_HEADER})
  message ("**** bad: Meka / RTAI not found, cannot build M3 controller")
endif (${HAVE_M3_SHM_HEADER})

if (HAVE_M3)
  rosbuild_add_library (m3_base_ctrl
    src/rt_util.cpp
    include/m3_base_ctrl/basecontroller.h
    )

  rosbuild_add_executable (servo src/servo.cpp)
  target_link_libraries (servo m3_base_ctrl)

endif (HAVE_M3)
