cmake_minimum_required(VERSION 3.26)

project(tests_prj)

set(SOURCE_FILE
    ../ip_filter.cpp
    ../ip_filter.h
)

set(TEST_FILES
    tests.cpp
)

find_package(GTest)

if(GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    cmake_policy(SET CMP0135 NEW)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip  
        #URL "C:/Libraries/GTest/googletest-main.zip"         
    )
    #For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(tests ${TEST_FILES} ${SOURCE_FILE})

target_link_libraries(tests PRIVATE 
    gtest 
    gtest_main
)

target_compile_options(tests PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX >
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )

set_target_properties(tests PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(tests tests)

if(MSVC)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)		
endif()
