cmake_minimum_required(VERSION 3.0.0)
project(boost_serial VERSION 0.1.0)

# include_directories(boost)
# add_executable(main main.cpp)
# target_link_libraries(main  ${Boost_LIBRARIES}  pthread) 

# add_executable(test test.cpp)
# target_link_libraries(test  ${Boost_LIBRARIES}  pthread) 

add_executable(drive_control drive_control.cpp)
target_link_libraries(drive_control ${Boost_LIBRARIES}  pthread) 