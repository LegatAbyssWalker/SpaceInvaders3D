#pragma once

#include "../../States/Functionality/State.h"
#include "../../States/Functionality/StateMachine.h"
class StateMachine;

#include <iostream>
#include <array>
#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "../../Utilities/FileLocations.h"
#include "../../Utilities/Variables.h"
#include "../../Utilities/Random.h"
#include "../../Display/GLWindow.h"

#include "../../Player/Player.h"
#include "../../Managers/InvaderManager.h"
#include "../../Models/Entities/Shield.h"

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& window, bool replace = true);

		void keyboardInput(sf::Keyboard::Key& key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		GLWindow& window;
		sf::Event sfEvent;
		sf::Clock clock;
		GLfloat deltaTime = 0, lastFrame = 0;


		std::unique_ptr<Player> player = nullptr;
		std::unique_ptr<InvaderManager> invaderManager = nullptr;

		std::vector<std::unique_ptr<Shield>> shieldVector;
};

