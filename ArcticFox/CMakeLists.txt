project(ArcticFox VERSION 0.0.1)

if(WIN32)
    message(STATUS "WIN32 EXPORT ALL SYMBOLS")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(PackageName "ArcticFox")

set(IMGUI_GLFW_BACKENDS
    "../third_part/imgui/backends/imgui_impl_glfw.h"
    "../third_part/imgui/backends/imgui_impl_glfw.cpp"
    "../third_part/imgui/backends/imgui_impl_opengl3.h"
    "../third_part/imgui/backends/imgui_impl_opengl3.cpp"
    "../third_part/imgui/backends/imgui_impl_opengl3_loader.h")
aux_source_directory("../third_part/imgui" IMGUI_SRC)
aux_source_directory(src SRC_DIR)
add_library(ArcticFox SHARED ${IMGUI_SRC} ${IMGUI_GLFW_BACKENDS} ${SRC_DIR})

target_include_directories(ArcticFox PRIVATE include)
target_include_directories(ArcticFox PRIVATE ../third_part)
target_include_directories(ArcticFox PRIVATE ../third_part/glfw/include)
target_include_directories(ArcticFox PRIVATE ../third_part/glm)
target_include_directories(ArcticFox PRIVATE ../third_part/imgui)

if(WIN32)
    target_link_libraries(ArcticFox PRIVATE opengl32.lib)
elseif(LINUX)
    target_link_libraries(ArcticFox PRIVATE GL)
endif()
target_link_libraries(ArcticFox PRIVATE glfw)

# Create generated files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ArcticFoxConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(EXPORT ${PROJECT_NAME}
    FILE ArcticFoxConfig.cmake
    DESTINATION share/${PROJECT_NAME}
)

# Install files
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(export_runtime_path bin)
    set(export_library_path lib)
    set(export_archive_path lib)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(export_runtime_path debug/bin)
    set(export_library_path debug/lib)
    set(export_archive_path debug/lib)
endif()

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${export_runtime_path}
    LIBRARY DESTINATION ${export_library_path}
    ARCHIVE DESTINATION ${export_archive_path}
)

install(DIRECTORY include/ DESTINATION include/ArcticFox)
install(
    FILES    
        "../third_part/imgui/imgui.h"
        "../third_part/imgui/imconfig.h"
        "../third_part/imgui/imgui_internal.h"
        "../third_part/imgui/imstb_rectpack.h"
        "../third_part/imgui/imstb_textedit.h"
        "../third_part/imgui/imstb_truetype.h"
    DESTINATION
        include/imgui
    )

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/ArcticFoxConfigVersion.cmake
    DESTINATION
        share/${PROJECT_NAME}
    )