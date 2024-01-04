project(example)

include_directories(../ArcticFox/include)
include_directories(../third_part/glfw/include)
include_directories(../third_part/glm)
include_directories(../third_part)
include_directories(../third_part/imgui)

add_executable(simple_app "simple_app.cpp")
target_link_libraries(simple_app PRIVATE ArcticFox)
