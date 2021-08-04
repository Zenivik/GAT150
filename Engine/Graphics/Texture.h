#pragma once
#include "Resource/Resource.h"
#include "SDL.h"
namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Load(const std::string& name, void* data) override;

	private:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}