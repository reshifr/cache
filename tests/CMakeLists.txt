cmake_minimum_required(VERSION 3.24.2)
project(Mind)

# Mind CLI
file(GLOB_RECURSE TEST_SOURCES ${MIND_TEST_DIR}/*.cpp)
add_executable(${MIND_TEST} ${TEST_SOURCES})

# Mind Test Add Include Directories
target_include_directories(
	${MIND_TEST}
	PUBLIC
	${MIND_INCLUDE_DIR}
	PRIVATE
	${cryptopp_INCLUDE_DIR}
	${googletest_INCLUDE_DIR}
	${googlemock_INCLUDE_DIR}
)

# Mind Test Add Link Libraries
target_link_libraries(
	${MIND_TEST}
	PRIVATE
	${cryptopp_LIB_DIR}/libcryptopp.a
	${googletest_LIB_DIR}/libgtest.a
	${googletest_LIB_DIR}/libgmock.a
	${googletest_LIB_DIR}/libgtest_main.a
	${googletest_LIB_DIR}/libgmock_main.a
)

gtest_discover_tests(${MIND_TEST})
