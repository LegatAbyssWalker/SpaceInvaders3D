#pragma once

#include "Entity.h"
#include "../../Display/GLWindow.h"


#include <iostream>
#include <memory>


class Invader : public Entity {
	public:
		Invader(GLWindow& window, std::string const& filePath);

		void update();

		void setDead() { isDead = true;}
		bool isInvaderDead() const { return isDead; }

	private:
		GLWindow& window;

		bool isWithinBounds = true;
		bool isDead = false;

};


