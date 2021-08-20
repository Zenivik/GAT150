#include "Game.h"

void Game::Initialize()
{
	// create engine
	engine = std::make_unique<nc::Engine>(); 
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	// create scene
	scene = std::make_unique<nc::Scene>(); 
	scene->engine = engine.get();

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../Resources");


	// actors
	std::unique_ptr<nc::Actor> actor = std::make_unique <nc::Actor>(nc::Transform{ nc::Vector2{400, 300}, 0, 1 });
	{
		auto component = nc::ObjectFactory::instance().Create<nc::SpriteAnimationComponent>("SpriteAnimationComponent");
		//nc::SpriteAnimationComponent* component = actor->AddComponent<nc::SpriteAnimationComponent>();
		component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/sparkle.png", engine->Get<nc::Renderer>());
		component->fps = 30;
		component->numFramesX = 8;
		component->numFramesY = 8;
		actor->AddComponent(std::move(component));
	}

	//std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(nc::Transform( nc::Vector2{ 400, 300 }, 0, 1 ));
	//{
	//	nc::SpriteComponent* component = actor->AddComponent<nc::SpriteComponent>();
	//	component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/sparkle.png", engine->Get<nc::Renderer>());
	//	actor->AddComponent(std::move(component));
	//}

	{
		nc::PhysicsComponent* component = actor->AddComponent<nc::PhysicsComponent>();
		//component->ApplyForce(nc::Vector2::right * 200);
	}
	scene->AddActor(std::move(actor));



}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BeginFrame();
	
	engine->Draw(engine->Get<nc::Renderer>());
	scene->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->EndFrame();
}
