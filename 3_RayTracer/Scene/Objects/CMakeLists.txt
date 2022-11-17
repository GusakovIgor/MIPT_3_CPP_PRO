add_library (Objects Objects.cpp)

target_link_libraries (Objects PUBLIC Application Math)

target_include_directories (Objects
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )