cmake_minimum_required(VERSION 3.15)

Project(ApproximateDRAMandSRAM)

find_package(OpenCV REQUIRED)

find_package(FMT REQUIRED)

message(STATUS "Opnecv ;ibrary status: ")
message(STATUS "> version: ${OpenCV_VERSION} ")
message(STATUS "libraries: ${OpenCV_LIBS} ")
message(STATUS "> include: ${OpenCV_INCLUDE_DIRS}  ")

include_directories(${OpenCV_INCLUDE_DIRS}) 

aux_source_directory(. ALL_SRCS)
add_executable(main ${ALL_SRCS})

target_link_libraries(main
PUBLIC 
${OpenCV_LIBS}
fmt::fmt
)