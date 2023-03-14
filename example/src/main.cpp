#include "Application.hpp"
#include "EntryPoint.hpp"
#include "Input/Input.hpp"

class ExampleLayer : public ArcticFox::Layer
{
public:
	virtual void OnUpdate(float ts) override
	{
		if (ArcticFox::Input::IsKeyDown(ArcticFox::KeyCode::Escape)) {
			printf("Pressed Espace\n");
		}
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello ArcticFox");
		// ImGui::Text("FPS: %d", ArcticFox::Application::Get().GetFPS());
		// ImGui::Text("FPS:%.1f", ImGui::GetIO().Framerate);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (ImGui::Button("Button")) {

        }
		ImGui::ShowDemoWindow();
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
	ArcticFox::ApplicationSpecification appSpec;
	appSpec.Name = "ArcticFox Example";
	appSpec.Width = 800;
	appSpec.Height = 600;

	ArcticFox::Application* app = new ArcticFox::Application(appSpec);
    app->PushLayer<ExampleLayer>();
    app->PushLayer<ExampleLayer2>();

	return app;
}