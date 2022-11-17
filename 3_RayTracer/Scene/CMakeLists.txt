add_subdirectory (Objects)
add_subdirectory (Figures)

add_library (Scene Scene.cpp)

target_link_libraries (Scene PUBLIC Application Objects Figures)

target_include_directories (Scene
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )