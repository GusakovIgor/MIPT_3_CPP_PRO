add_library (Events Events.cpp)

target_link_libraries (Events PUBLIC SDL2 Math)

target_include_directories (Events
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )