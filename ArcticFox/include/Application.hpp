#pragma once

#include <string>

#include "GLFW/glfw3.h"

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

private:
    void Init();
    void Shutdown();

private:
    ApplicationSpecification m_Specification;
    GLFWwindow* m_WindowHandle;
    bool m_Running = false;
};

Application* CreateApplication(int argc, char** argv);

}