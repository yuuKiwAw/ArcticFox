#include "Application.hpp"

#include <stdio.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace ArcticFox {
    Application::Application(const ApplicationSpecification& secification)
        : m_Specification(secification)
    {
        Init();
    }

    Application::~Application() {
        Shutdown();
    }

    void Application::Run() {
        m_Running = true;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Main loop
        while (!glfwWindowShouldClose(m_WindowHandle) && m_Running) {
		    glfwPollEvents();

		    // Start the ImGui frame
		    ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplGlfw_NewFrame();
		    ImGui::NewFrame();

			ImGui::Render();

		    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		    glClear(GL_COLOR_BUFFER_BIT);

		    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		    glfwSwapBuffers(m_WindowHandle);
        }
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::Init() {
        glfwSetErrorCallback(glfw_error_callback);
	    if (!glfwInit())
            return;

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        m_WindowHandle = glfwCreateWindow(m_Specification.Width, m_Specification.Height, m_Specification.Name.c_str(), NULL, NULL);
        if (m_WindowHandle== NULL)
		    return ;
        glfwMakeContextCurrent(m_WindowHandle);
        glfwSwapInterval(1);

        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
	    ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup ImGui style
	    ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
	    ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
	    ImGui_ImplOpenGL3_Init("#version 130");
    }

    void Application::Shutdown() {
        // Cleanup
	    ImGui_ImplOpenGL3_Shutdown();
	    ImGui_ImplGlfw_Shutdown();
	    ImGui::DestroyContext();

	    glfwDestroyWindow(m_WindowHandle);
	    glfwTerminate();
    }
}