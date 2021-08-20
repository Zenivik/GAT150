#pragma once
#include "SpriteComponent.h"
#include <SDL.h>

namespace nc
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	public:
		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		int frame{ 0 }, fps{ 0 }, numFramesX{ 0 }, numFramesY{ 0 };

		float frameTimer{ 0 }, frameTime{ 0 };

		SDL_Rect rect;
	};
}