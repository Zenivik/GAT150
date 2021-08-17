#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	Enemy(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture } {}

	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float speed = 100;
	float fireTimer = 0;
	float fireRate = 2;
};