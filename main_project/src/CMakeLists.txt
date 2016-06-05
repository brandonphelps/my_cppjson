
include_directories(${Parser_SOURCE_DIR}/main_project/include)
aux_source_directory(. SOURCE)

add_executable(${TARGET} ${SOURCE})
