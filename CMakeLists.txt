cmake_minimum_required(VERSION 3.24.2)
project(Mind)

# C++ Configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG -Og)
set(CMAKE_CXX_FLAGS_RELEASE -O3)
cmake_host_system_information(
	RESULT MAX_THREADS
	QUERY NUMBER_OF_LOGICAL_CORES
)

if(MAX_THREADS EQUAL 1)
	set(NPROCS 1)
else()
	math(EXPR NPROCS "${MAX_THREADS} - 1")
endif()

# Mind Configuration
set(MIND mind)
set(MIND_TEST test_mind)
set(MIND_CLI ${CMAKE_SOURCE_DIR}/tools/mind.cpp)
set(MIND_TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(MIND_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Mind Dependencies
include(ExternalProject)

# # Crypto++
set(cryptopp_PREFIX ${CMAKE_SOURCE_DIR}/thirdparty/cryptopp)
set(cryptopp_INCLUDE_DIR ${cryptopp_PREFIX}/src)
set(cryptopp_SOURCE_DIR ${cryptopp_PREFIX}/src/cryptopp)
set(cryptopp_LIB_DIR ${cryptopp_PREFIX}/src/cryptopp)

# ## Crypto++ Install
ExternalProject_Add(
	cryptopp
	PREFIX ${cryptopp_PREFIX}
	URL "https://github.com/weidai11/cryptopp/archive/refs/tags/CRYPTOPP_8_7_0.zip"
	URL_HASH "SHA256=6055ab314ff4daae9490ddfb3fbcf107bc94a556401ed42f756fa5f7cd8c6510"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -C ${cryptopp_SOURCE_DIR} -j${NPROCS}
	BUILD_IN_SOURCE 1
	BUILD_ALWAYS 0
	INSTALL_COMMAND ""
)

# # Google Test
set(googletest_PREFIX ${CMAKE_SOURCE_DIR}/thirdparty/googletest)
set(googletest_INCLUDE_DIR ${googletest_PREFIX}/src/googletest/googletest/include)
set(googlemock_INCLUDE_DIR ${googletest_PREFIX}/src/googletest/googlemock/include)
set(googletest_SOURCE_DIR ${googletest_PREFIX}/src/googletest)
set(googletest_LIB_DIR ${googletest_PREFIX}/src/googletest/lib)

# ## Google Test Install
ExternalProject_Add(
	googletest
	PREFIX ${googletest_PREFIX}
	URL "https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip"
	URL_HASH "SHA256=ffa17fbc5953900994e2deec164bb8949879ea09b411e07f215bfbb1f87f4632"
	CONFIGURE_COMMAND ${CMAKE_COMMAND} ${googletest_SOURCE_DIR}
	BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -C ${googletest_SOURCE_DIR} -j${NPROCS}
	BUILD_IN_SOURCE 1
	BUILD_ALWAYS 0
	INSTALL_COMMAND ""
)

# Mind CLI
add_executable(${MIND} ${MIND_CLI})

# Mind Add Include Directories
target_include_directories(
	${MIND}
	PUBLIC
	${MIND_INCLUDE_DIR}
	PRIVATE
	${cryptopp_INCLUDE_DIR}
)

# Mind Add Link Libraries
target_link_libraries(
	${MIND}
	PRIVATE
	${cryptopp_LIB_DIR}/libcryptopp.a
)

# Mind Testing
enable_testing()
include(GoogleTest)
add_subdirectory(${MIND_TEST_DIR})
