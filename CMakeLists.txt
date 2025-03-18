include(FetchContent)
include(CheckIncludeFiles)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PassHash CXX)

option(FORCE_OW_CRYPT OFF)

check_include_files(crypt.h HAS_CRYPT)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

if(NOT HAS_CRYPT OR FORCE_OW_CRYPT)
	message("using ow crypt")
	FetchContent_Declare(
		ow_crypt
		GIT_REPOSITORY https://github.com/openwall/crypt_blowfish.git
		GIT_TAG        3354bb81eea489e972b0a7c63231514ab34f73a0
	)
endif()

if(HAS_CRYPT AND NOT FORCE_OW_CRYPT)
	add_library(PassHash pass_hash.cpp)
	target_link_libraries(PassHash crypt)
else()
	add_library(
		PassHash
		pass_hash.cpp
		${ow_crypt_SOURCE_DIR}/crypt_blowfish.c
		${ow_crypt_SOURCE_DIR}/crypt_gensalt.c
		${ow_crypt_SOURCE_DIR}/wrapper.c
		${ow_crypt_SOURCE_DIR}/x86.S
	)
endif()
target_include_directories(
	PassHash PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
