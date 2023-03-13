#include "Application.hpp"
#include "EntryPoint.hpp"

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

ArcticFox::Application* ArcticFox::CreateApplication(int argc, char** argv) {
	ArcticFox::Application* app = new ArcticFox::Application();
    app->PushLayer<ExampleLayer>();
    app->PushLayer<ExampleLayer2>();

	return app;
}