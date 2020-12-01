add_executable("stl2" main.cpp zadatak.cpp zadatak.h)

add_custom_command(
        TARGET stl2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/src/*.txt
                ${CMAKE_CURRENT_BINARY_DIR})
