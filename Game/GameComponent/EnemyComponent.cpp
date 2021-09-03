#include "EnemyComponent.h"
#include "Engine.h"

using namespace nc;

EnemyComponent::~EnemyComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void EnemyComponent::Update()
{
	Actor* player = owner->scene->FindActor("Player");

	/*if (player)
	{
		Vector2 direction = player->transform.position - owner->transform.position;
		Vector2 force = direction.Normalized() * speed;

		PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
		assert(physicsComponent);

		physicsComponent->ApplyForce(force);
	}*/

	Vector2 direction = owner->transform.position.x += 200;

	if (owner->transform.position.x >= 700)
	{
		Vector2 direction = owner->transform.position.x -= 200;
	}
	if (owner->transform.position.x <= 100)
	{
		Vector2 direction = owner->transform.position.x += 200;
	}
	Vector2 force = direction.Normalized() * speed;

	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);
}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);

	return true;
}

