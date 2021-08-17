#pragma once
#include "Object/Actor.h"

class Projectile : public nc::Actor
{
public:
	Projectile(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture } {}

	void Update(float dt) override;

private:
	float lifetime{ 1.5 };
	float speed = 300;
};