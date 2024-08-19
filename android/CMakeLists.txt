cmake_minimum_required(VERSION 3.4.1)

project(react-native-phi3)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES
    ../cpp/lib/*.cpp
    cpp-adapter.cpp
)

# add main library
add_library(react-native-phi3 SHARED)

target_sources(react-native-phi3 PRIVATE ${SOURCE_FILES})

# Specifies a path to native header files.
include_directories(
    ../cpp/lib/onnx/include/
    ../cpp/lib/onnx/example/
)

# define libraries sources
# PROJECT_SOURCE_DIR is the directory where CMakeLists.txt located
# android gradle requires abi to be placed at./src/main/jniLibs
target_link_directories(react-native-phi3 PRIVATE ./src/main/jniLibs/${CMAKE_ANDROID_ARCH_ABI})

# link onnxruntime-ai lib to react-native-phi3
target_link_libraries(react-native-phi3 PRIVATE 
    onnxruntime-genai
    onnxruntime
)
