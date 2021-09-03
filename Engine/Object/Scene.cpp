#include "Scene.h"
#include "Actor.h"
#include "Engine.h"

namespace nc
{
	void Scene::Update(float dt)
	{
		// add new actors
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();

		// update actors 
		for (auto& actor : actors)
		{
			actor->Update(dt);
		}

		// destroy actor
		auto iter = actors.begin();
		while (iter != actors.end())
		{
			if ((*iter)->destroy)
			{
				iter = actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
	void Scene::Draw(Renderer* renderer)
	{
		std::for_each(actors.begin(), actors.end(), [renderer](auto& actor) { actor->Draw(renderer); });
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor.get()->scene = this;
		actor->Initialize();

		newActors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor)
	{

	}

	void Scene::RemoveAllActors()
	{
		actors.clear();
	}

	Actor* Scene::FindActor(const std::string& name)
	{
		for (auto& actor : actors)
		{
			if (actor->name == name) return actor.get();
		}
		return nullptr;
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("actors") && value["actors"].IsArray())
		{
			for (auto& actorvalue : value["actors"].GetArray())
			{
				std::string type;
				JSON_READ(actorvalue, type);

				bool prototype = false;
				JSON_READ(actorvalue, prototype);

				auto actor = ObjectFactory::instance().Create<Actor>(type);
				if (actor)
				{
					actor->scene = this;
					actor->Read(actorvalue);

					if (prototype)
					{
						std::string name = actor->name;
						ObjectFactory::instance().RegisterPrototype<Actor>(name, std::move(actor));
					}
					else
					{
						AddActor(std::move(actor));
					}

				}
			}
		}

		return true;
	}
}

