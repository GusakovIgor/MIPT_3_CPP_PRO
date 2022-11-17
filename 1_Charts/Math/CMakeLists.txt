add_library (Math Math.cpp)

target_link_libraries (Math PUBLIC SDL2 SDL2_ttf)

target_include_directories (Math
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )