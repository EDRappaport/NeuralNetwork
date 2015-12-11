cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(feretfaceinputprocessor)

find_package( OpenCV REQUIRED )

include_directories("./include/pugixml-1.7/src")
add_subdirectory(include/pugixml-1.7/src)

add_executable(feretfaceinputprocessor main.cpp Recording.hpp Recording.cpp)
target_link_libraries( feretfaceinputprocessor ${OpenCV_LIBS})
target_link_libraries( feretfaceinputprocessor pugixml)


add_executable(initialNetBuilder InitialNetBuilder.cpp)

install(TARGETS initialNetBuilder RUNTIME DESTINATION bin)
install(TARGETS feretfaceinputprocessor RUNTIME DESTINATION bin)
