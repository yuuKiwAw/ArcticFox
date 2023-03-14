#include "Application.hpp"

#include <stdio.h>
#include "glm/glm.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static ArcticFox::Application* s_Instance = nullptr;

namespace ArcticFox {
    Application::Application(const ApplicationSpecification& secification)
        : m_Specification(secification)
    {
        s_Instance = this;

        Init();
    }

    Application::~Application() {
        Shutdown();
    }

    Application& Application::Get() {
        return *s_Instance;
    }

    void Application::Run() {
        m_Running = true;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGuiIO& io = ImGui::GetIO();

        // Main loop
        while (!glfwWindowShouldClose(m_WindowHandle) && m_Running) {
		    glfwPollEvents();

            for (auto& layer : m_LayerStack)
                layer->OnUpdate(m_TimeStep);

		    // Start the ImGui frame
		    ImGui_ImplOpenGL3_NewFrame();
		    ImGui_ImplGlfw_NewFrame();
		    ImGui::NewFrame();
            {
                static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

                ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

                const ImGuiViewport *viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

                if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", nullptr, window_flags);
				ImGui::PopStyleVar();

				ImGui::PopStyleVar(2);

                ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("OpenglAppDockspace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

                for (auto& layer : m_LayerStack)
                    layer->OnUIRender();

                ImGui::End();
            }

            // Rendering
			ImGui::Render();
            ImDrawData* main_draw_data = ImGui::GetDrawData();
            const bool main_is_minimized = (main_draw_data->DisplaySize.x <= 0.0f || main_draw_data->DisplaySize.y <= 0.0f);

            if (!main_is_minimized) {
                int display_w, display_h;
                glfwGetFramebufferSize(m_WindowHandle, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
		        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		        glClear(GL_COLOR_BUFFER_BIT);
		        ImGui_ImplOpenGL3_RenderDrawData(main_draw_data);
            }

            // Update and Render additional Platform Windows
            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
            //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
			}

		    glfwSwapBuffers(m_WindowHandle);

            float time = GetTime();
            m_FrameTime = time - m_LastFrameTime;
            m_TimeStep = glm::min<float>(m_FrameTime, 0.0333f);
            m_LastFrameTime = time;
            CalculateFramesPerSecond();
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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

        // Setup ImGui style
	    ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

        // Setup Platform/Renderer backends
	    ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
	    ImGui_ImplOpenGL3_Init("#version 130");
    }

    void Application::Shutdown() {
        for (auto& layer : m_LayerStack)
            layer->OnDetach();
        m_LayerStack.clear();

        // Cleanup
	    ImGui_ImplOpenGL3_Shutdown();
	    ImGui_ImplGlfw_Shutdown();
	    ImGui::DestroyContext();

	    glfwDestroyWindow(m_WindowHandle);
	    glfwTerminate();
    }

    void Application::CalculateFramesPerSecond()
    {
        static float framesPerSecond = 0.0f;
        static float lastTime = 0.0f;
        float currentTime = glfwGetTime();
        ++framesPerSecond;
        if( currentTime - lastTime > 1.0f )
        {
            lastTime = currentTime;
            m_FPS = framesPerSecond;
            framesPerSecond = 0;
        }
    }

    float Application::GetTime() {
        return (float)glfwGetTime();
    }

    int Application::GetFPS() {
        return m_FPS;
    }

    GLFWwindow* Application::GetWindowHandle() const {
        return m_WindowHandle;
    }
}