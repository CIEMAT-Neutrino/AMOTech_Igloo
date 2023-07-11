cmake_minimum_required(VERSION 3.8...3.18)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES
	"*.mac")

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(Igloo Igloo.cc ${sources} ${headers})
target_link_libraries(Igloo ${Geant4_LIBRARIES})


add_custom_target(Simulation DEPENDS Igloo)
