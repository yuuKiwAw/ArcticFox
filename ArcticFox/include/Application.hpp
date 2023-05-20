#pragma once

#include "Layer.hpp"

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "GLFW/glfw3.h"
#include "imgui.h"


namespace ArcticFox {

struct ApplicationSpecification {
    std::string Name = "ArcticFox App";
    uint32_t Width = 1600;
    uint32_t Height = 900;
    bool Fullscreen = false;
    bool AutoSize = false;
};

class Application {
public:
    Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
    ~Application();

    static Application& Get();

    void Run();
    void Close();

    void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

    float GetTime();
    int GetFPS();
    GLFWwindow* GetWindowHandle() const;

    template<typename T>
    void PushLayer() {
        static_assert(std::is_base_of<Layer, T>::value, "Not Layer type!");
        m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
    }

    void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

private:
    void Init();
    void Shutdown();

    void CalculateFramesPerSecond();

private:
    ApplicationSpecification m_Specification;
    GLFWmonitor* m_MonitorHandle;
    GLFWwindow* m_WindowHandle;
    bool m_Running = false;

    float m_TimeStep = 0.0f;
    float m_FrameTime = 0.0f;
	float m_LastFrameTime = 0.0f;
    int m_FPS = 0;

    std::vector<std::shared_ptr<Layer>> m_LayerStack;
    std::function<void()> m_MenubarCallback;
};

Application* CreateApplication(int argc, char** argv);
}