add_executable (Main Main.cpp)

target_link_libraries (Main PUBLIC Application Charts)

target_include_directories (Main PUBLIC
							"${PROJECT_BINARY_DIR}"
						   )