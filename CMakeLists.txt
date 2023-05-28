cmake_minimum_required(VERSION 3.24.2)
project(Mind)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG -Og)
set(CMAKE_CXX_FLAGS_RELEASE -Ofast)

set(APP mind)

# # Mind CLI
add_executable(${APP} tools/mind.cpp)

# Crypto++
set(cryptopp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cryptopp)
set(cryptopp_SOURCE_DIR ${cryptopp_DIR}/src/cryptopp)
set(cryptopp_INCLUDE_DIR ${cryptopp_DIR}/src/cryptopp)

ExternalProject_Add(
  cryptopp
  PREFIX ${cryptopp_DIR}
  URL https://github.com/weidai11/cryptopp/archive/refs/tags/CRYPTOPP_8_7_0.zip
  URL_HASH SHA256=6055ab314ff4daae9490ddfb3fbcf107bc94a556401ed42f756fa5f7cd8c6510
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
  BUILD_IN_SOURCE 1
  BUILD_ALWAYS 0
  INSTALL_COMMAND ""
)

target_include_directories(
  ${APP}
  PUBLIC include/mind
  INTERFACE ${cryptopp_INCLUDE_DIR}
)

target_link_libraries(
  ${APP}
  PRIVATE ${cryptopp_SOURCE_DIR}/libcryptopp.a
)
