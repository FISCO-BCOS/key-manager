#------------------------------------------------------------------------------
# Top-level CMake file for FISCO-BCOS.
# ------------------------------------------------------------------------------
# This file is part of FISCO-BCOS.
#
# FISCO-BCOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# FISCO-BCOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
#
# (c) 2016-2018 fisco-dev contributors.
#------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4)
set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})

project(KeyManager VERSION "2.0")

add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -g -Wall")

# install dependencies
include(ProjectMHD)
include(ProjectCryptopp)
include(ProjectJsonCpp)
include(ProjectJsonRpcCpp)
include(ProjectTASSL)

aux_source_directory(. DIR_SRCS)

include_directories(libutils)
include_directories(${MHD_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIR})
include_directories(${JSONRPCCPP_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(libutils)

message(${JSONRPCCPP_INCLUDE_DIR})
message(${JSONCPP_INCLUDE_DIR})
message(${CURL_INCLUDE_DIR})
message(${MHD_INCLUDE_DIR})

set(EXE_NAME "key-manager")
add_executable(${EXE_NAME} ${DIR_SRCS})

target_link_libraries(${EXE_NAME} utils Cryptopp stdc++ JsonRpcCpp::Server JsonRpcCpp::Client JsonRpcCpp::Common)
target_link_libraries(${EXE_NAME} procps)
