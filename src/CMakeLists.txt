
include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES main.cpp ReversePolishNotation.cpp)

find_package(Boost 1.65.0 COMPONENTS system regex)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(html_server ${SOURCE_FILES})
	target_link_libraries(html_server ${Boost_LIBRARIES})
endif()
