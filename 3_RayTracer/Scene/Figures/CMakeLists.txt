add_subdirectory (Materials)

add_library (Figures Figures.cpp)

target_link_libraries (Figures PUBLIC Application Math Objects Materials)

target_include_directories (Figures
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )