#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"

void Game::Initialize()
{
	// create engine
	engine = std::make_unique<nc::Engine>(); 
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	//components
	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);

	// create scene
	scene = std::make_unique<nc::Scene>(); 
	scene->engine = engine.get();

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../Resources");

	engine->Get<nc::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));

	/*

	auto actor = nc::ObjectFactory::instance().Create<nc::Actor>("coin");
	actor->transform.position = nc::Vector2{ 700, 500 };
	scene->AddActor(std::move(actor));*/
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

	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	// update score
	auto scoreActor = scene->FindActor("score");
	if (scoreActor)
	{
		scoreActor->GetComponent<nc::TextComponent>()->SetText("score: " + std::to_string(score));
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

void Game::Reset()
{
	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = nc::json::Load("Title.txt", document);
	assert(success);

	scene->Read(document);

	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
	{
		auto title = scene->FindActor("Title");
		title->active = false;


		state = eState::StartGame;
	}
}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = nc::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);

	nc::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = nc::json::Load("map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevel;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	//if (stateTimer >= 1)
	{
		auto player = nc::ObjectFactory::instance().Create<nc::Actor>("Player");
		player->transform.position = { 400, 150 };
		scene->AddActor(std::move(player));

		spawnTimer = 2;
		state = eState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer <= 0)
	{
		spawnTimer = nc::RandomRange(2, 3);
		auto coin = nc::ObjectFactory::instance().Create<nc::Actor>("coin");
		coin->transform.position = { nc::RandomRange(100, 700), 550.0f };
		scene->AddActor(std::move(coin));

		/*auto enemy = nc::ObjectFactory::instance().Create<nc::Actor>("enemy");
		enemy->transform.position = { nc::RandomRange(100, 700), 550.0f };
		scene->AddActor(std::move(enemy));*/
	}

	auto scoreActor = scene->FindActor("score");
	if (scoreActor)
	{
		scoreActor->GetComponent<nc::TextComponent>()->SetText("score: " + std::to_string(score));
	}

}

void Game::PlayerDead()
{
}

void Game::GameOver()
{
}

void Game::OnAddScore(const nc::Event& event)
{
	score += std::get<int>(event.data);
}
