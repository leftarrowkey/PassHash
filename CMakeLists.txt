include(FetchContent)
include(CheckIncludeFiles)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PassHash CXX)

check_include_files(crypt.h HAS_CRYPT)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

if(NOT HAS_CRYPT)
	FetchContent_Declare(
		ow_crypt
		GIT_REPOSITORY https://github.com/openwall/crypt_blowfish
		GIT_TAG        3354bb81eea489e972b0a7c63231514ab34f73a0
	)
endif()

add_library(PassHash pass_hash.cpp)
if(NOT HAS_CRYPT)
	target_link_libraries(PassHash ow_crypt)
endif()
