#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Framework/System.h"
#include <vector>

namespace nc
{
	class Renderer;
	class Texture;

	class ParticleSystem : public GraphicsSystem
	{
	public:
	struct Particle
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		std::shared_ptr<Texture> texture;
		float lifetime;
		bool isActive{ false };

		static bool IsNotActive(Particle particle) { return particle.isActive == false; }
	};
	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(Renderer* renderer) override;

		void Create(const Vector2& position, size_t count, float lifetime, std::shared_ptr<Texture> texture, float speed);
		void Create(const Vector2& position, size_t count, float lifetime, std::shared_ptr<Texture> texture, float speed, float angle, float angleRange);

	private:
		std::vector<Particle> particles;
	};

	
	
}