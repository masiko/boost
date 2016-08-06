cmake_minimum_required (VERSION 2.6)

project(boost_timer)

set(ENV{Boost_DIR})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system thread filesystem)

add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)

find_package(OpenCV REQUIRED)
add_executable(boost_timer boost_timer.cpp)
target_link_libraries( boost_timer ${Boost_LIBS} )
target_link_libraries( boost_timer ${OpenCV_LIBS} )


