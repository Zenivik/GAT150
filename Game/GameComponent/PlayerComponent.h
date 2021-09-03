#pragma once

#include "Component/Component.h"
#include "Framework/EventSystem.h"
#include <list>

class PlayerComponent : public nc::Component
{

	void Create();
	std::unique_ptr<Object> Clone() const { return std::make_unique<PlayerComponent>(*this); }
	virtual void Update() override;

	virtual void OnCollisionEnter(const nc::Event& event);
	virtual void OnCollisionExit(const nc::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

public:
	virtual ~PlayerComponent();
	float speed{ 0 };

private:
	std::list<nc::Actor*> contacts;
};
