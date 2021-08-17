#pragma once
// systems
#include "Audio/AudioSystem.h"

// core
#include "Core/Utilities.h"
#include "Core/FileSystem.h"
#include "Core/Timer.h"


// input
#include "Input/InputSystem.h"

// math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

// graphics
//#include "Graphics/Shapes.h"
#include "Graphics/Font.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/ParticleSystem.h"

// objects
#include "Object/Actor.h"
#include "Object/Scene.h"

// components
#include "Component/SpriteComponent.h"
#include "Component/PhysicsComponent.h"

// Framework
#include "Framework/EventSystem.h"

// Resource
#include "Resource/ResourceSystem.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace nc
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}