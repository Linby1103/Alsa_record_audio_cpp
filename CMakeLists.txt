#指定cmake最小版本
cmake_minimum_required(VERSION 3.1)
project (TestAlsa)
set(SOURCES 
    cpp/AlsaCaptureAudio.cpp
    cpp/testAlsa.cpp
    )
    
#链接alsa库    
link_libraries(-lasound)
add_executable(${PROJECT_NAME} ${SOURCES})
#头文件
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include 
    )