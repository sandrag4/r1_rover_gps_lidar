cmake_minimum_required(VERSION 3.8)
project(r1_rover_vel)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(mavros_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

set(dependencies
    rclcpp
    mavros_msgs
    geometry_msgs
)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/r1_rover_vel/RoverVelNode.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

add_executable(r1_rover_vel_main src/r1_rover_vel_main.cpp)
ament_target_dependencies(r1_rover_vel_main ${dependencies})
target_link_libraries(r1_rover_vel_main ${PROJECT_NAME})

install(TARGETS
  r1_rover_vel_main
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(${dependencies})
ament_package()
