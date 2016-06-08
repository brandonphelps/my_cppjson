
include_directories(${CppJson_SOURCE_DIR}/main_project/include)
aux_source_directory(. SOURCE)

# add_executable(${TARGET} ${SOURCE})

add_library(cppjson SHARED ${SOURCE})

target_include_directories(cppjson PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

export(TARGETS cppjson FILE ${CMAKE_BINARY_DIR}/cppjsonConfig.cmake)
