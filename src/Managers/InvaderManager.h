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
#include "../Models/Entities/Bullet.h"
#include "../Models/Entities/Shield.h"


class InvaderManager {
	public:
		InvaderManager(GLWindow& window);

		void update();
		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		std::unique_ptr<Invader> playerBulletCollision(std::unique_ptr<Player>& player);
		bool invaderBulletCollision(std::unique_ptr<Player>& player);
		bool invaderCollision(std::unique_ptr<Player>& player);
		
		void removeEntities();

		std::unique_ptr<Bullet>& getBullet(int type) { return bulletVector[type]; }


	private:
		glm::mat4 test;

		GLWindow& window;
		std::array<Random<>, 2> random;

		std::vector<std::unique_ptr<Invader>> invaderVector;
		std::vector<std::unique_ptr<Bullet>> bulletVector;


		int invaderMax = 0;
		int invadersLeft = invaderMax;
		int shooter = 0;

		bool towardsPositiveX = false;
		bool towardsNegativeY = false;
		int downTick = 0;
		int downTickMax = 100;
};


