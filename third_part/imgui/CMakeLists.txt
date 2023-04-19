project (imgui VERSION 1.89.5)

set (IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING INTERNAL FORCE)

set (IMGUI_HEADS
	${CMAKE_CURRENT_SOURCE_DIR}/imgui.h
	${CMAKE_CURRENT_SOURCE_DIR}/imconfig.h
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_internal.h
	${CMAKE_CURRENT_SOURCE_DIR}/imstb_rectpack.h
	${CMAKE_CURRENT_SOURCE_DIR}/imstb_textedit.h
	${CMAKE_CURRENT_SOURCE_DIR}/imstb_truetype.h
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.h
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.h
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3_loader.h
	CACHE STRING INTERNAL FORCE
)

set (IMGUI_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.cpp
	CACHE STRING INTERNAL FORCE
)
