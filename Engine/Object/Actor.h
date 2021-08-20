#pragma once
#include "Object.h"
#include "Component/Component.h"
#include "Math/Transform.h"
#include <vector>
#include <memory>

namespace nc
{
	class Scene;
	class Renderer;

	class Actor : public Object
	{
	public:
		Actor() {}
		Actor(const Transform& transform) : transform{ transform } {}

		virtual void Initialize() {}

		virtual void Update(float dt);
		virtual void Draw(Renderer* renderer);

		virtual void OnCollision(Actor* actor) {}
		void AddChild(std::unique_ptr<Actor> actor);

		float GetRadius();

		void AddComponent(std::unique_ptr<Component> component);
		template<class T>
		T* AddComponent();

	public:
		bool destroy{ false };
		std::string tag;

		Transform transform;
		Scene* scene{ nullptr };

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;
		
		std::vector<std::unique_ptr<Component>> components;
	};

	template<class T>
	inline T* Actor::AddComponent()
	{
		std::unique_ptr<T> component = std::make_unique<T>();
		component->owner = this;
		components.push_back(std::move(component));

		return dynamic_cast<T*>(components.back().get());
	}
}