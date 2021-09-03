#include "PickupComponent.h"
#include "Engine.h"

using namespace nc;

PickupComponent::~PickupComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PickupComponent::Update()
{

}

void PickupComponent::OnCollisionEnter(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "Player"))
	{
		owner->destroy = true;
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
		Event event;
		event.name = "add_score";
		event.data = 100;

		owner->scene->engine->Get<EventSystem>()->Notify(event);
	}
}

bool PickupComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value)
{
	return true;
}
