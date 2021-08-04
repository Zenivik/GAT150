#include "Engine.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

int main(int, char**)
{
	nc::Engine engine;
	engine.Startup();

	engine.Get<nc::Renderer>()->Create("GAT150", 800, 600);

	std::cout << nc::GetFilePath() << std::endl;
	nc::SetFilePath("../Resources");
	std::cout << nc::GetFilePath() << std::endl;
		
	std::shared_ptr<nc::Texture> texture = engine.Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine.Get<nc::Renderer>());

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Get<nc::Renderer>()->BeginFrame();
		
		engine.Get<nc::Renderer>()->EndFrame();

		/*for (size_t i = 0; i < 50; i++)
		{
			SDL_Rect src{ 32, 64, 32, 64 };
			SDL_Rect dest{ nc::RandomRangeInt(0,800), nc::RandomRangeInt(0,800), 16, 24 };
			SDL_RenderCopy(renderer, texture, &src, &dest);
		}*/
			
	}
	
	SDL_Quit();

	return 0;
}