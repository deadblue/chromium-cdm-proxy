project(loader)

aux_source_directory(src SRC_FILES)

add_executable(loader ${SRC_FILES})

target_link_libraries(loader PRIVATE dl)
