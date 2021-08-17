#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Asteroid.h"
#include <iostream>
#include<string>

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

	//audio
	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("music", "audio/BGM.mp3");
	musicChannel = engine->Get<nc::AudioSystem>()->PlayAudio("music", 1, 1, true);

	//get font from resource system
	int size = 16;
	std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("Fonts/Official.ttf", &size);
	textTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	textTexture->Create(font->CreateSurface("Press Space to Start", nc::Color{ 0, 1, 1 }));
	
	scoreTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	
	std::shared_ptr<nc::Texture> titleTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	titleTexture->Create(font->CreateSurface("Future Triple AAA", nc::Color{ 0, 1, 1 }));

	std::shared_ptr<nc::Texture> gameoverTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	gameoverTexture->Create(font->CreateSurface("GAME OVER", nc::Color{ 1, 0, 0 }));
	
	std::shared_ptr<nc::Texture> healthTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	healthTexture->Create(font->CreateSurface(std::to_string(health), nc::Color{ 1, 1, 1 }));
	
	std::shared_ptr<nc::Texture> livesTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	livesTexture->Create(font->CreateSurface(std::to_string(lives), nc::Color{ 1, 1, 1 }));

	// add font texture to resource system
	engine->Get<nc::ResourceSystem>()->Add("titleTexture", titleTexture);
	engine->Get<nc::ResourceSystem>()->Add("gameoverTexture", gameoverTexture);
	engine->Get<nc::ResourceSystem>()->Add("healthTexture", healthTexture);
	engine->Get<nc::ResourceSystem>()->Add("livesTexture", livesTexture);
	engine->Get<nc::ResourceSystem>()->Add("textTexture", textTexture);
	engine->Get<nc::ResourceSystem>()->Add("scoreTexture", scoreTexture);	

	//Images
	//std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/sf2.png", engine->Get<nc::Renderer>());
	particleTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle02.png", engine->Get<nc::Renderer>());

	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::Transform transform{ {nc::RandomRange(0,800), nc::RandomRange(0,600)}, nc::RandomRange(0,360), 1.0f };
	//	std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform, texture);
	//	scene->AddActor(std::move(actor));
	//}

	//game
	engine->Get<nc::AudioSystem>()->AddAudio("player_fire", "player_fire.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("enemy_fire", "Laser_Shoot.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();

}

void Game::Update()
{
	engine->Update();
	stateTimer += engine->time.deltaTime;

	switch (state)
	{
	case Game::eState::Title:
		
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
		{
			nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();
			std::cout << position.x << std::endl;

			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		//scene->engine->Get<nc::AudioSystem>()->PlayAudio("Music");
		score = 0;
		health = 200;
		lives = 1;
		spawnRate = 1;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{	
		scene->AddActor(std::make_unique<Player>(nc::Transform{ { 400, 200}, 0 , 0.4f }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/Player.png", engine->Get<nc::Renderer>()), 300));

		for (size_t i = 0; i < 3; i++)
		{
			scene->AddActor(std::make_unique<Asteroid>(nc::Transform{ {nc::RandomRange(0.0f, 800.0f), 0.0f, }, nc::RandomRange(0, nc::TwoPi), 0.1f }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/asteroid1.png", engine->Get<nc::Renderer>()), 50));
			scene->AddActor(std::make_unique<Enemy>(nc::Transform{ {nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f), }, nc::RandomRange(0, nc::TwoPi), 0.25f }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/Enemy.png", engine->Get<nc::Renderer>()), 200));
		}
		state = eState::Game;
	}
		break;
	case Game::eState::Game:
		spawnTimer -= engine->time.deltaTime;
		if (spawnTimer <= 0)
		{
			spawnTimer = nc::RandomRange(75.0f, 100.0f);

			for (size_t i = 0; i < spawnRate; i++)
			{
				scene->AddActor(std::make_unique<Asteroid>(nc::Transform{ {nc::RandomRange(0.0f, 800.0f), 0.0f, }, nc::RandomRange(0, nc::TwoPi), 0.1f }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/asteroid1.png", engine->Get<nc::Renderer>()), 100));
				scene->AddActor(std::make_unique<Enemy>(nc::Transform{ {nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f) }, nc::RandomRange(0, nc::TwoPi), 0.25f }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/Enemy.png", engine->Get<nc::Renderer>()), 200));

			}

		}

		/*if (scene->GetActors<Enemy>().size() == 0)
		{
			state = Game::eState::GameOver;
		}*/
		break;
	case Game::eState::GameOver:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
		{
			scene->RemoveAllActors();
			state = eState::StartGame;
		}
		break;
	default:
		break;
	}

	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	//if (engine->Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::Left) == nc::InputSystem::eKeyState::Pressed)
	//{
	//	nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();

	//	// create particle
	//	engine->Get<nc::ParticleSystem>()->Create(position, 10, 1, particleTexture, 150);
	//	engine->Get<nc::ParticleSystem>()->Create(position, 10, 1, particleTexture, 150);

	//	engine->Get<nc::AudioSystem>()->PlayAudio("explosion", 1.0f, nc::RandomRange(0.2f, 1.0f));

	//	musicChannel.SetPitch(nc::RandomRange(0.0f, 1.5f));
	//	std::cout << musicChannel.GetPitch() << std::endl;
	//}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BeginFrame();
	nc::Transform startTransform;
	startTransform.position = { 400, 300 };

	nc::Transform scoret;
	scoret.position = { 50, 40 };

	switch (state)
	{
	case Game::eState::Title:
		{
			nc::Transform t;
			t.position = { 400, 200 };
			engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("titleTexture"), t);
			engine->Get<nc::Renderer>()->Draw(textTexture, startTransform);
		}

		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		{
			// health
			nc::Transform t;
			t.position = { 50, 70 };
			std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("healthTexture");
			std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/Holland.ttf");
			texture->Create(font->CreateSurface(std::to_string(health), nc::Color{ 1, 1, 1 }));
			engine->Get<nc::Renderer>()->Draw(texture, t);
		}

		{
			// lives
			nc::Transform t;
			t.position = { 50, 100 };
			std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("livesTexture");
			std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/Holland.ttf");
			texture->Create(font->CreateSurface(std::to_string(lives), nc::Color{ 1, 1, 1 }));
			engine->Get<nc::Renderer>()->Draw(texture, t);
		}

		engine->Get<nc::Renderer>()->Draw(scoreTexture, scoret);
		break;
	case Game::eState::GameOver:
		if (scene->GetActors<Player>().size() == 0)
		{
				nc::Transform t;
				t.position = { 400, 200 };
				engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("gameoverTexture"), t);
				engine->Get<nc::Renderer>()->Draw(textTexture, startTransform);
		}
		break;
	default:
		break;
	}

	int scoreSize = 14;
	std::shared_ptr<nc::Font> scoreFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/Holland.ttf", &scoreSize);
	scoreTexture->Create(scoreFont->CreateSurface(std::to_string(score), nc::Color{ 1, 1, 1 }));

	engine->Draw(engine->Get<nc::Renderer>());
	scene->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->EndFrame();
}

void Game::OnAddPoints(const nc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const nc::Event& event)
{
	health -= 20;
	
	if (health <= 0 && lives <= 0)
	{
		scene->GetActor<Player>()->destroy = true;
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
		state = eState::GameOver;
		
	}
	else if(health <= 0)
	{
		lives--;
		scene->GetActor<Player>()->destroy = true;
		health = 200;
		scene->AddActor(std::make_unique<Player>(nc::Transform{ { 400, 200}, 0 , 5 }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/Player.png", engine->Get<nc::Renderer>()), 300));
	}
}
