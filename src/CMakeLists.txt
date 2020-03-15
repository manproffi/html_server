
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Boost 1.65.0 COMPONENTS system regex)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(html_server main.cpp ReversePolishNotation.cpp)
	target_link_libraries(html_server ${Boost_LIBRARIES})
endif()
