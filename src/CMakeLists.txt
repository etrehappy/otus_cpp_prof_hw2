cmake_minimum_required(VERSION 3.26)

project(ip_filter_prj)

option(WITH_G_TEST "Whether to build Google test" ON)

set(SOURCE_FILE
    main.cpp
    ip_filter.cpp
    ip_filter.h
)

add_executable(ip_filter ${SOURCE_FILE})

target_compile_options(ip_filter PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX >
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )

set_target_properties(ip_filter PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

if(WITH_G_TEST)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()

if(MSVC)
		set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ip_filter)        
        set(CMAKE_VS_DEBUGGER_COMMAND_ARGUMENTS "< ../src/ip_filter.tsv")		
endif()

if(MSVC)
    set(RUN_COMMAND powershell -Command "Get-Content ${CMAKE_SOURCE_DIR}\\ip_filter.tsv | ${CMAKE_BINARY_DIR}\\Debug\\ip_filter.exe")
else()
    set(RUN_COMMAND ip_filter < ${CMAKE_SOURCE_DIR}/ip_filter.tsv)
endif()

add_custom_target(run
    COMMAND ${RUN_COMMAND}
    DEPENDS ip_filter    
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}   
    COMMENT "##### Running with ip_filter.tsv #####"
)