#include "Asteroid.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Engine.h"

void Asteroid::Update(float dt)
{

	nc::Vector2 acceleration;
	acceleration += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);
	//nc::Vector2 gravity = (nc::Vector2{ 400, 300 } - transform.position).Normalized() * 300;
	nc::Vector2 gravity = nc::Vector2::down * 100;
	acceleration += gravity;

	velocity += acceleration * dt;
	transform.position += velocity * dt;

	//velocity *= 0.985f;

	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	Actor::Update(dt);
}

void Asteroid::OnCollision(Actor* actor)
{

	if (dynamic_cast<Enemy*>(actor) || (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy"))
	{
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 2, 1, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle02.png", scene->engine->Get<nc::Renderer>()), 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
		actor->destroy = true;
		this->destroy = true;
	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")
	{
		actor->destroy = true;
	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
	{
		actor->destroy = true;
	}

}
