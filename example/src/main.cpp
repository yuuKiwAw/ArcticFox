#include <iostream>
#include "Application.hpp"

ArcticFox::Application* app = new ArcticFox::Application();

class ExampleLayer : public ArcticFox::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello ArcticFox");
		if (ImGui::Button("Button")) {

        }
		ImGui::End();
	}
};

class ExampleLayer2 : public ArcticFox::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello ArcticFox2");
		if (ImGui::Button("Button")) {

        }
		ImGui::End();
	}
};

int main(int argc, char** argv) {
    app->PushLayer<ExampleLayer>();
    app->PushLayer<ExampleLayer2>();
    app->Run();
    delete app;

    return 0;
}