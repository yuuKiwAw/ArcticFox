project(third_part)

set(IMGUI_GLFW_BACKENDS
    "imgui/backends/imgui_impl_glfw.h"
    "imgui/backends/imgui_impl_glfw.cpp"
    "imgui/backends/imgui_impl_opengl3.h"
    "imgui/backends/imgui_impl_opengl3.cpp"
    "imgui/backends/imgui_impl_opengl3_loader.h")
aux_source_directory(imgui IMGUI_SRC)
add_library(imgui
    ${IMGUI_SRC}
    ${IMGUI_GLFW_BACKENDS})

add_subdirectory(glfw)

target_include_directories(imgui PUBLIC imgui)