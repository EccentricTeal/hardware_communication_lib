cmake_minimum_required(VERSION 2.8.3)
project(hardware_communication_lib)

find_package(catkin REQUIRED COMPONENTS
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES shipcon
#  CATKIN_DEPENDS roscpp rospy rqt_gui rqt_gui_py std_msgs message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(udpcom SHARED
  src/udp_recv.cc
  src/udp_send.cc
)
add_library(serialcom SHARED
  src/serialcom.cc
)


#############
## Install ##
#############
install(
  TARGETS udpcom serialcom
  #TARGETS serialcom
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
install(
  DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)