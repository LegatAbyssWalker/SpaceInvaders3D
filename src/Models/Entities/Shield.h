#pragma once

#include "Entity.h"
#include "Invader.h"
#include "../../Display/GLWindow.h"
#include "../../Player/Player.h"

#include <iostream>

#include <memory>


class Shield : public Entity {
	public:
		Shield(GLWindow& window, std::string const& modelLocation);

		void update(std::unique_ptr<Entity>& playerBullet, std::unique_ptr<Entity>& invaderBullet);

	private:
		const unsigned int maxLife = 10;
		int currentLife = maxLife;
};


