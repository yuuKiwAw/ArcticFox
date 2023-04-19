project (imgui_node_editor)

set (IMGUI_NODE_EDITOR_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING INTERNAL FORCE)

set (IMGUI_NODE_EDITOR_HEADS
    ${CMAKE_CURRENT_SOURCE_DIR}/crude_json.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_canvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_bezier_math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_extra_math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor.h
    CACHE STRING INTERNAL FORCE
)

set (IMGUI_NODE_EDITOR_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/crude_json.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_bezier_math.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_extra_math.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_api.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor_internal.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_node_editor.cpp
    CACHE STRING INTERNAL FORCE
)