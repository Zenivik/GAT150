#include "InputSystem.h"
#include "SDL.h"

namespace nc
{
	void InputSystem::Startup()
	{
		const uint8_t* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);

	}
	void InputSystem::Shutdown()
	{

	}
	void InputSystem::Update(float dt)
	{

	}
	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		return eKeyState();
	}
	bool InputSystem::IsKeyDown(int id)
	{
		return false;
	}
	bool InputSystem::IsPreviousKeyDown(int id)
	{
		return false;
	}
}