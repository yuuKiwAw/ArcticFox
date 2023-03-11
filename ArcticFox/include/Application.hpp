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
};

class Application {
public:
    Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
    ~Application();

    void Run();
    void Close();

    float GetTime();

    template<typename T>
    void PushLayer() {
        static_assert(std::is_base_of<Layer, T>::value, "Not Layer type!");
        m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
    }

    void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

private:
    void Init();
    void Shutdown();

private:
    ApplicationSpecification m_Specification;
    GLFWwindow* m_WindowHandle;
    bool m_Running = false;

    float m_TimeStep = 0.0f;
    float m_FrameTime = 0.0f;
	float m_LastFrameTime = 0.0f;

    std::vector<std::shared_ptr<Layer>> m_LayerStack;
};

Application* CreateApplication(int argc, char** argv);
}