#include "Application.hpp"
#include "EntryPoint.hpp"
#include "Input/Input.hpp"
#include "imgui/imgui.h"
#include "Widgets/imfilebrowser.h"
#include "Widgets/toggle_button.h"

class ExampleLayer : public ArcticFox::Layer
{
private:
	ImGui::FileBrowser fileDialog = ImGui::FileBrowser();

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
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		static bool toggle_btn_status;
		ToggleButton("target btn", &toggle_btn_status);
		// select file dialog
		if (ImGui::Button("Select File")) {
			fileDialog.SetFlags(0);
			fileDialog.SetTitle("Select file");
			fileDialog.SetTypeFilters({".txt"});
			fileDialog.Open();
        }

		// select folder dialog
		if (ImGui::Button("Select Folder")) {
			fileDialog.SetFlags(ImGuiFileBrowserFlags_SelectDirectory);
			fileDialog.SetTitle("Select folder");
			fileDialog.Open();
		}

		// demo window
		ImGui::ShowDemoWindow();
		ImGui::End();

		fileDialog.Display();
		if (fileDialog.HasSelected()) {
			std::cout << fileDialog.GetSelected().string() << std::endl;
			fileDialog.ClearSelected();
		}
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
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});

	return app;
}