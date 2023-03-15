project(example)

add_executable(example_ArcticFox_App
    "src/main.cpp"
)

target_link_libraries(example_ArcticFox_App PRIVATE ArcticFox)

target_include_directories(example_ArcticFox_App PRIVATE ../ArcticFox/include)
target_include_directories(example_ArcticFox_App PRIVATE ../third_part/glm)
target_include_directories(example_ArcticFox_App PRIVATE ../third_part/imgui)