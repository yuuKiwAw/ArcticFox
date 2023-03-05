#include <iostream>
#include "Application.hpp"

int main(int argc, char** argv) {
    ArcticFox::Application* app = new ArcticFox::Application();
    app->Run();
    delete app;

    return 0;
}