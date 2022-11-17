add_executable (Main Main.cpp)

target_link_libraries (Main PUBLIC Application Math Objects Scene)

target_include_directories (Main PUBLIC
							"${PROJECT_BINARY_DIR}"
						   )