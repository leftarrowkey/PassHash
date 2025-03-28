include(FetchContent)
include(CheckIncludeFiles)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PassHash CXX)

option(FORCE_OW_CRYPT OFF)

if(NOT FORCE_OW_CRYPT)
	check_include_files(crypt.h HAS_CRYPT)
else()
	set(HAS_CRYPT FALSE)
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

if(HAS_CRYPT)
	add_library(PassHash pass_hash.cpp)
	target_link_libraries(PassHash crypt)
else()
	message("using ow crypt")
	FetchContent_Declare(
		ow_crypt
		GIT_REPOSITORY https://github.com/openwall/crypt_blowfish.git
		GIT_TAG        3354bb81eea489e972b0a7c63231514ab34f73a0
	)
	FetchContent_MakeAvailable(ow_crypt)
	add_library(
		PassHash
		pass_hash.cpp
		${ow_crypt_SOURCE_DIR}/crypt_blowfish.c
		${ow_crypt_SOURCE_DIR}/crypt_gensalt.c
		${ow_crypt_SOURCE_DIR}/wrapper.c
		${ow_crypt_SOURCE_DIR}/x86.S
	)
	target_include_directories(
		PassHash PRIVATE ${ow_crypt_SOURCE_DIR}
	)
endif()
target_include_directories(
	PassHash PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
