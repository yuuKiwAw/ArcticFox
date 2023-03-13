#pragma once

extern ArcticFox::Application* ArcticFox::CreateApplication(int argc, char** argv);

namespace ArcticFox {

	int Main(int argc, char** argv) {
			ArcticFox::Application* app = ArcticFox::CreateApplication(argc, argv);
			app->Run();
			delete app;

		return 0;
	}

}

int main(int argc, char** argv) {
    return ArcticFox::Main(argc, argv);
}
