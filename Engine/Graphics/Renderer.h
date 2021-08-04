#pragma once
#include "Framework/System.h"
#include "SDL.h"
#include <string>

namespace nc
{
	class Renderer : public System
	{
	public:
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		void Create(const std::string& name, int width, int height);
		void BeginFrame();
		void EndFrame();

		friend class Texture;

	private:
		SDL_Renderer* renderer = nullptr;
		SDL_Window* window = nullptr;
	};
}