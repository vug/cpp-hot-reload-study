cmake_minimum_required(VERSION 3.31)
project(HotReloadStudy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hot_reload_study
    main.cpp
)

add_library(reloadable_library SHARED
    reloadable_library.cpp
)

cmake_path(SET DLL_DIR "$<TARGET_FILE_DIR:reloadable_library>")
cmake_path(SET DLL_TMP "$<TARGET_FILE:reloadable_library>")
cmake_path(SET DLL_A "${DLL_DIR}/reloadable_library_a.dll")
cmake_path(SET DLL_B "${DLL_DIR}/reloadable_library_b.dll")
cmake_path(SET DLL_TO_COPY_FILE "${CMAKE_BINARY_DIR}/dll_to_copy.txt")
message("DLL_TO_COPY_FILE ${DLL_TO_COPY_FILE}")

add_custom_command(TARGET reloadable_library POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Hi!"
    COMMAND ${CMAKE_COMMAND} 
        -DDLL_TMP=${DLL_TMP} -DDLL_A=${DLL_A} -DDLL_B=${DLL_B} -DDLL_TO_COPY_FILE=${DLL_TO_COPY_FILE}
        -P "${CMAKE_SOURCE_DIR}/choose_dll_version.cmake"
    COMMAND ${CMAKE_COMMAND}
        -DDLL_TMP=${DLL_TMP} -DDLL_TO_COPY_FILE=${DLL_TO_COPY_FILE}
        -P "${CMAKE_SOURCE_DIR}/copy_dll_to_version.cmake"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Bye!"
)
