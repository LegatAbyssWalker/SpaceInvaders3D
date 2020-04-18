#include "PlayingState.h"

PlayingState::PlayingState(StateMachine &machine, GLWindow &window, bool replace)
	: State(machine, window, replace), window(window) {

	// Player
	player = std::make_unique<Player>(window, glm::vec3(X_BORDER_MIN, 0, Z_BORDER_MIN), window.getPerspectiveMatrix());


	// Shields
	glm::vec3 shieldPositions[6] = {
			glm::vec3(1.0, 4.0, 0.5),
			glm::vec3(1.0, 4.0, 1.5),
			glm::vec3(5.0, 4.0, 0.5),
			glm::vec3(5.0, 4.0, 1.5),
			glm::vec3(9.0, 4.0, 0.5),
			glm::vec3(9.0, 4.0, 1.5),
	};

	for (int i = 0; i < 6; i++) {
		shieldVector.emplace_back(new Shield(window, SHIELD_MODEL_LOCATION));
		shieldVector[i]->setModelPosition(shieldPositions[i]);
		shieldVector[i]->setScale(glm::vec3(0.3));
	}


	// InvaderManager
	invaderManager = std::make_unique<InvaderManager>(window);


	// Window
	this->window.setMouseVisible(false);
}

void PlayingState::keyboardInput(sf::Keyboard::Key &key, bool isPressed) {
	if (key == sf::Keyboard::Escape) { machine.quit(); }
}

void PlayingState::updateEvents() {
	while (window.getWindow().pollEvent(sfEvent)) {
		auto keyCode = sfEvent.key.code;
		switch (sfEvent.type) {
			case sf::Event::Resized:
				this->window.setViewPort(glm::vec2(0), glm::vec2(sfEvent.size.width, sfEvent.size.height));
				break;

			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::KeyPressed:
				keyboardInput(keyCode, true);
				break;

			case sf::Event::KeyReleased:
				keyboardInput(keyCode, false);
				break;
		}

		// Keyboard
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	 { player->keyboardUpdate(Movement::FORWARD,  deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	 { player->keyboardUpdate(Movement::LEFT,     deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	 { player->keyboardUpdate(Movement::BACKWARD, deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	 { player->keyboardUpdate(Movement::RIGHT,    deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { player->keyboardUpdate(Movement::SHOOTING, deltaTime); }

		// REMOVE
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  { player->keyboardUpdate(Movement::UP,   deltaTime); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { player->keyboardUpdate(Movement::DOWN, deltaTime); }
	}
}

void PlayingState::update() {
	GLfloat now = clock.getElapsedTime().asSeconds();
	deltaTime = now - lastFrame;
	lastFrame = now;


	// Player
	player->update();

	
	// Shields
	for (auto& shield : shieldVector) {
		// shield->update(player->getBullet(), invaderManager->getBullet());
	}


	// InvaderManager
	invaderManager->update();

}

void PlayingState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 1.f, 1.f, 1.f);


	player->render(player->getCamera().calculateViewMatrix(), window.getPerspectiveMatrix());
	invaderManager->render(player->getCamera().calculateViewMatrix(), window.getPerspectiveMatrix());

	for (auto& shield : shieldVector) { shield->render(player->getCamera().calculateViewMatrix(), window.getPerspectiveMatrix()); }



	window.swapBuffers();
}
