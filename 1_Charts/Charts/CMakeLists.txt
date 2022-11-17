add_library (Charts Charts.cpp)

target_link_libraries (Charts PUBLIC Math Application)

target_include_directories (Charts
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )