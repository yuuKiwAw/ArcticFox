aux_source_directory(src SRC_DIR)
add_library(ArcticFox ${SRC_DIR})

target_include_directories(ArcticFox PUBLIC include)
target_link_libraries(ArcticFox PRIVATE glfw imgui opengl32.lib)