add_library (Materials Materials.cpp)

target_link_libraries (Materials PUBLIC Application)

target_include_directories (Materials
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )