
include_directories(${CppJson_SOURCE_DIR}/main_project/include)
aux_source_directory(. SOURCE)

# add_executable(${TARGET} ${SOURCE})

add_library(cppjson SHARED ${SOURCE})

# export(TARGETS ${TARGET} FILE ${CMAKE_BINARY_DIR}/cppjsonConfig.cmake)
