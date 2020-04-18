#pragma once

#include "States/Functionality/State.h"
#include "States/Functionality/StateMachine.h"
class StateMachine;

#include "States/GameStates/PlayingState.h"

class Game {
	public:
		Game() = default;

		void run();

	private:
		std::unique_ptr<GLWindow> window = nullptr;
		StateMachine machine;
};

