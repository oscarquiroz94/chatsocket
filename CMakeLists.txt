cmake_minimum_required(VERSION 3.16)

project(ws_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Fetch standalone Asio (header-only)
FetchContent_Declare(
	asio
	GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
	GIT_TAG asio-1-30-2
)

# Fetch websocketpp (header-only)
FetchContent_Declare(
	websocketpp
	GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
	GIT_TAG 0.8.2
)

# Populate dependencies
FetchContent_MakeAvailable(asio)
FetchContent_MakeAvailable(websocketpp)

# Create INTERFACE targets if packages don't provide them
# Asio (standalone) doesn't define a target by default, so add one
if(NOT TARGET asio::asio)
	add_library(asio_interface INTERFACE)
	add_library(asio::asio ALIAS asio_interface)
	FetchContent_GetProperties(asio)
	if(NOT asio_POPULATED)
		FetchContent_Populate(asio)
	endif()
	target_include_directories(asio_interface INTERFACE ${asio_SOURCE_DIR}/asio/include)
endif()

# websocketpp may not define a target; ensure one exists
if(NOT TARGET websocketpp::websocketpp)
	add_library(websocketpp INTERFACE)
	add_library(websocketpp::websocketpp ALIAS websocketpp)
	FetchContent_GetProperties(websocketpp)
	if(NOT websocketpp_POPULATED)
		FetchContent_Populate(websocketpp)
	endif()
	target_include_directories(websocketpp INTERFACE ${websocketpp_SOURCE_DIR})
endif()

# Build outputs to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Executables
add_executable(ws_server src/server.cpp)
add_executable(ws_client src/client.cpp)

# Definitions for standalone Asio
foreach(tgt IN ITEMS ws_server ws_client)
	target_compile_definitions(${tgt} PRIVATE ASIO_STANDALONE _WEBSOCKETPP_CPP11_STL_)
	target_link_libraries(${tgt} PRIVATE asio::asio websocketpp::websocketpp)
	if(UNIX)
		target_link_libraries(${tgt} PRIVATE pthread)
	endif()
endforeach()