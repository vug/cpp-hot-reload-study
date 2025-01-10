cmake_minimum_required(VERSION 3.31)
project(HotReloadStudy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hot_reload_study
    main.cpp
)

set(LIB reloadable_library)
add_library(${LIB} SHARED 
  ${LIB}.cpp
)

cmake_path(SET DLL_DIR "$<TARGET_FILE_DIR:${LIB}>")
cmake_path(SET DLL_TMP "$<TARGET_FILE:${LIB}>")
cmake_path(SET DLL_A "${DLL_DIR}/${LIB}_a.dll")
cmake_path(SET DLL_B "${DLL_DIR}/${LIB}_b.dll")
add_custom_command(TARGET ${LIB} POST_BUILD
    COMMAND ${CMAKE_COMMAND} 
        -DDLL_TMP=${DLL_TMP} -DDLL_A=${DLL_A} -DDLL_B=${DLL_B} -DDLL_TO_COPY_FILE=${DLL_TO_COPY_FILE}
        -P "${CMAKE_SOURCE_DIR}/choose_dll_version.cmake"
)
