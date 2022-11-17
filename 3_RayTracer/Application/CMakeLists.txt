add_library (Application Application.cpp)

target_link_libraries (Application PUBLIC SDL2 SDL2_ttf)

target_include_directories (Application
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )