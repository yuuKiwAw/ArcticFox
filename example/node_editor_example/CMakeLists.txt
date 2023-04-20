project(node_editor_example)

add_executable(basic_example "basic_example.cpp")
target_link_libraries(basic_example PRIVATE ArcticFox)

add_executable(widgets_example "widgets_example.cpp")
target_link_libraries(widgets_example PRIVATE ArcticFox)