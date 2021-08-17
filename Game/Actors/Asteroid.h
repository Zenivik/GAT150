#pragma once

#include "Object/Actor.h"

class Asteroid : public nc::Actor
{
public:
	Asteroid(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture } {}

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float speed = 100;
	nc::Vector2 velocity;
};