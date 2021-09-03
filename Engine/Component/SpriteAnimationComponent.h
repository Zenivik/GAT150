#pragma once
#include "SpriteComponent.h"
#include <map>
#include <SDL.h>

namespace nc
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	private:
		struct Sequence
		{
			int fps{ 0 };
			int startFrame{ 0 };
			int endFrame{ 0 };
		};

	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<SpriteAnimationComponent>(*this); }

		void Update() override;
		void Draw(Renderer* renderer) override;

		void StartSequence(const std::string& name);

		// Inherited via SpriteComponent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		
	public:
		int frame{ 0 }, fps{ 0 }, numFramesX{ 0 }, numFramesY{ 0 };

		int startFrame{ 0 };
		int endFrame{ 0 };

		float frameTimer{ 0 }, frameTime{ 0 };

		std::map<std::string, Sequence> sequences;
		std::string sequenceName;

	};
}