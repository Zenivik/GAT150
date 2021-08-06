#pragma once
#include "Framework/System.h"
#include <vector>

namespace nc
{
	class InputSystem : public System
	{
	public:
		enum class eKeyState
		{
			Idle,
			Pressed,
			Held,
			Release
		};

	public:
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

	private:
		std::vector<uint8_t> keyboardState;
		std::vector<uint8_t> prevKeyboardState;
		int numKeys;
	};
}
