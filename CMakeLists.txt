cmake_minimum_required(VERSION 3.24.2)
project(Mind)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG -Og)
set(CMAKE_CXX_FLAGS_RELEASE -Ofast)

set(APP mind)

# Mind CLI
add_executable(${APP} tools/mind.cpp)

# # Mind unit tests
# add_executable(${APP} tools/mind.cpp)

# Crypto++
set(cryptopp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cryptopp)
set(cryptopp_INCLUDE_DIR ${cryptopp_DIR}/src/cryptopp)
set(cryptopp_SOURCE_DIR ${cryptopp_DIR}/src/cryptopp)
set(cryptopp_LIB_DIR ${cryptopp_DIR}/src/cryptopp)

ExternalProject_Add(
  cryptopp
  PREFIX ${cryptopp_DIR}
  URL https://github.com/weidai11/cryptopp/archive/refs/tags/CRYPTOPP_8_7_0.zip
  URL_HASH SHA256=6055ab314ff4daae9490ddfb3fbcf107bc94a556401ed42f756fa5f7cd8c6510
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -C ${cryptopp_SOURCE_DIR}
  BUILD_IN_SOURCE 1
  BUILD_ALWAYS 0
  INSTALL_COMMAND ""
)

# Google Test
set(googletest_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest)
set(googletest_INCLUDE_DIR ${googletest_DIR}/src/googletest/googletest/include/gtest)
set(googlemock_INCLUDE_DIR ${googlemock_DIR}/src/googletest/googlemock/include/gmock)
set(googletest_SOURCE_DIR ${googletest_DIR}/src/googletest)
set(googletest_LIB_DIR ${googletest_DIR}/src/googletest/lib)

ExternalProject_Add(
  googletest
  PREFIX ${googletest_DIR}
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
  URL_HASH SHA256=ffa17fbc5953900994e2deec164bb8949879ea09b411e07f215bfbb1f87f4632
  CONFIGURE_COMMAND ${CMAKE_COMMAND} ${googletest_SOURCE_DIR}
  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -C ${googletest_SOURCE_DIR}
  BUILD_IN_SOURCE 1
  BUILD_ALWAYS 0
  INSTALL_COMMAND ""
)

target_include_directories(
  ${APP}
  PUBLIC include/mind
  INTERFACE
  ${cryptopp_INCLUDE_DIR}
  ${googletest_INCLUDE_DIR}
  ${googlemock_INCLUDE_DIR}
)

target_link_libraries(
  ${APP}
  PRIVATE
  ${cryptopp_LIB_DIR}/libcryptopp.a
  ${googletest_LIB_DIR}/libgtest.a
  ${googletest_LIB_DIR}/libgmock.a
  ${googletest_LIB_DIR}/libgtest_main.a
  ${googletest_LIB_DIR}/libgmock_main.a
)
