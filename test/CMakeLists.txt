file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${TEST_TARGET} ${TEST_SOURCES})

add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

target_link_libraries(${TEST_TARGET} PUBLIC ${LIB_TARGET} gtest)