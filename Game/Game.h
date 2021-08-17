#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool isQuit() { return quit; }

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const nc::Event& event);
	void OnPlayerDead(const nc::Event& event);
	
public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	bool quit{ false };
	eState state = eState::Title;
	float stateTimer = 0.0f;

	size_t score = 0;
	size_t health = 0;
	size_t lives = 0;
	size_t spawnRate = 0;
	size_t spawnTimer= 5;

	nc::AudioChannel musicChannel;
	std::shared_ptr<nc::Texture> particleTexture;
	std::shared_ptr<nc::Texture> textTexture;
	std::shared_ptr<nc::Texture> scoreTexture;
};