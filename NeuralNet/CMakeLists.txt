cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(neuralnet)

include_directories(.)
add_library(lib Node.hpp Node.cpp ThreeLayerNetwork.hpp ThreeLayerNetwork.cpp Example.hpp Example.cpp ExampleContainer.hpp ExampleContainer.cpp InputHelper.hpp InputHelper.cpp)

add_executable(neuralnetTrain NeuralNetsTrain.cpp)
target_link_libraries(neuralnetTrain lib)

add_executable(neuralnetTest NeuralNetsTest.cpp)
target_link_libraries(neuralnetTest lib)

install(TARGETS neuralnetTrain RUNTIME DESTINATION bin)
install(TARGETS neuralnetTest RUNTIME DESTINATION bin)

