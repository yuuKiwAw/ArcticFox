project(ArcticFox VERSION 0.0.1)

if(WIN32)
    message(STATUS "WIN32 EXPORT ALL SYMBOLS")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(PackageName "ArcticFox")

aux_source_directory(src SRC_DIR)
add_library(ArcticFox SHARED ${IMGUI_SRC} ${IMGUI_NODE_EDITOR_SRC} ${SRC_DIR})

target_include_directories(ArcticFox PRIVATE include)
target_include_directories(ArcticFox PRIVATE ${CMAKE_SOURCE_DIR}/third_part/glfw/include)
target_include_directories(ArcticFox PRIVATE ${CMAKE_SOURCE_DIR}/third_part/glm)
target_include_directories(ArcticFox PRIVATE ${IMGUI_PATH})
target_include_directories(ArcticFox PRIVATE ${IMGUI_NODE_EDITOR_PATH})

if(WIN32)
    target_link_libraries(ArcticFox PRIVATE opengl32.lib)
elseif(LINUX)
    target_link_libraries(ArcticFox PRIVATE GL)
elseif(APPLE)
    target_link_libraries(ArcticFox PRIVATE "-framework OpenGL")
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
    DESTINATION lib/cmake/${PROJECT_NAME}
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
install(FILES ${IMGUI_HEADS} DESTINATION include/imgui)
install(FILES ${IMGUI_NODE_EDITOR_HEADS} DESTINATION include/imgui_node_editor)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/ArcticFoxConfigVersion.cmake
    DESTINATION
        lib/cmake/${PROJECT_NAME}
    )