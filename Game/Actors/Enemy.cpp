#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt)
{

	if (scene->GetActor<Player>())
	{
		nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);

		float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (dt * 3);

		float angle = nc::Vector2::Angle(direction.Normalized(), forward);

		fireTimer -= dt;
		if (fireTimer <= 0 && angle < nc::DegToRad(10))
		{
			fireTimer = fireRate;

			nc::Transform t = transform;
			t.scale = 0.2f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/EnemyLaser.png", scene->engine->Get<nc::Renderer>()), 600.0f);
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("enemy_fire");
		}
		
	}

	transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		destroy = true;

		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 4, 1, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle01.png", scene->engine->Get<nc::Renderer>()), 100);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<nc::EventSystem>()->Notify(event);

	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;
	}
}
