cmake_minimum_required(VERSION 2.6)

project(avl_tree)
include_directories(inc src test)

set(root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/bin)

if("${ARC}" STREQUAL "x64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++11")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wcast-qual -Wextra -Wfloat-equal")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wcast-qual -Wextra -Wfloat-equal")
endif()

if(DEFINED OS)
	if("S{OS}" STREQUAL "_UNIX_")
		if("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors -ggbb")
		endif()
		add_definition(-D_UNIX_)
		set(binary_ext "")
		
		find_package(Threads)
		
		if(Threads_FOUND)
		    	message ("Thread library was found")
		else()
		    	message (FATAL_ERROR "Cannot find Threads package")
                endif()

                link_libraries(pthread)
	elseif()
		set(binary_ext "exe")
	endif()
endif()

if(DEFINED _LIMIT_)
	add_definitions(-D_LIMIT_=${_LIMIT_})
endif()

find_package(GTest)
if(GTest_FOUND)
    message("Google Test library was found")
else()
    message(FATAL_ERROR "Cannot find Google Test package")
endif()

link_libraries(gtest)

file(GLOB HEADER_FILES "*.h" "*.hpp")
file(GLOB SOURCE_FILES "*.cpp")

set(HEADER_FILES ${HEADER_FILES})
set(SOURCE_FILES ${SOURCE_FILES})

set(REQUIRED_LIBRARIES
    pthread
    gtest)

add_executable(avl_tree ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(avl_tree PRIVATE ${EXTRA_LIBS} ${REQUIRED_LIBRARIES})

