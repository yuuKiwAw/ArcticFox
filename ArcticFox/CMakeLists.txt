if(WIN32)
    message(STATUS "WIN32 EXPORT ALL SYMBOLS")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(IMGUI_GLFW_BACKENDS
    "../third_part/imgui/backends/imgui_impl_glfw.h"
    "../third_part/imgui/backends/imgui_impl_glfw.cpp"
    "../third_part/imgui/backends/imgui_impl_opengl3.h"
    "../third_part/imgui/backends/imgui_impl_opengl3.cpp"
    "../third_part/imgui/backends/imgui_impl_opengl3_loader.h")
aux_source_directory("../third_part/imgui" IMGUI_SRC)
aux_source_directory(src SRC_DIR)
add_library(ArcticFox SHARED ${IMGUI_SRC} ${IMGUI_GLFW_BACKENDS} ${SRC_DIR})

target_include_directories(ArcticFox PUBLIC include)
target_include_directories(ArcticFox PUBLIC ../third_part/glm)
target_include_directories(ArcticFox PUBLIC ../third_part/imgui)

target_link_libraries(ArcticFox PUBLIC glfw opengl32.lib)