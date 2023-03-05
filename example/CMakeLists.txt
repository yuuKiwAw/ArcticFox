project(example)

add_executable(example_ArcticFox_App
    "src/main.cpp"
)

target_link_libraries(example_ArcticFox_App PRIVATE ArcticFox)