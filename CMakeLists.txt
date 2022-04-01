cmake_minimum_required(VERSION 3.5.0)
project(boost_serial VERSION 0.1.0)

find_package(Boost REQUIRED ) #去找到Boost库的头文件和库文件

# add_executable(main main.cpp)
# target_link_libraries(main   pthread) 

# add_executable(test test.cpp)
# target_link_libraries(test   pthread) 

add_executable(drive_control drive_control.cpp)
target_include_directories(drive_control  PRIVATE  ${Boost_INCLUDE_DIRS}) #drive_control 只用到boost的头文件
target_link_libraries(drive_control   pthread) #drive_control 用到了多线程编程，需要链接pthread库
