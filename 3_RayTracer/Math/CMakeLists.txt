add_library (Math Math.cpp)

# target_compile_options (Math PUBLIC -O3)

target_include_directories (Math
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
						   )