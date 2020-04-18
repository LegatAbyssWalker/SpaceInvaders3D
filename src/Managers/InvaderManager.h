#pragma once

#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <array>

#include "../Display/GLWindow.h"
#include "../Models/Entities/Invader.h"
#include "../Player/Player.h"
#include "../Models/Entities/Entity.h"
#include "../Utilities/Random.h"


class InvaderManager {
	public:
		InvaderManager(GLWindow& window);

		void update();
		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		bool collisions(std::unique_ptr<Entity>& entity);
		void handleCollisions();

		void removeEntities();

	private:
		GLWindow& window;
		Random<> random;

		std::vector<std::unique_ptr<Invader>> invaderVector;

		bool towardsPositiveX = false;
		bool towardsNegativeY = false;
		int downTick = 0;
		int downTickMax = 100;
};


