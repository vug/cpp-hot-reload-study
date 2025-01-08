message("Hi from script 2!")

message("Reading ${DLL_TO_COPY_FILE} file...")
file(STRINGS "${DLL_TO_COPY_FILE}" DLL_TO_COPY)

message("Copying ${DLL_TMP} to ${DLL_TO_COPY}...")
file(COPY_FILE ${DLL_TMP} ${DLL_TO_COPY})
# COMMAND ${CMAKE_COMMAND} -E copy "${DLL_TMP}" "${DLL_TO_COPY_FILE}"

message("Bye from script 2!")