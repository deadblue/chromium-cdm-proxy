project(proxy)

aux_source_directory(src/common SRC_FILES)
aux_source_directory(src/api SRC_FILES)
aux_source_directory(src/proxy SRC_FILES)
aux_source_directory(src SRC_FILES)

add_library(proxy SHARED ${SRC_FILES})
target_link_libraries(proxy PRIVATE dl)
target_compile_options(proxy PRIVATE -fPIC -fvisibility=hidden)
