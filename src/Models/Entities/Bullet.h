#pragma once

#include "Entity.h"
#include "../../Display/GLWindow.h"
#include "../../Utilities/Variables.h"


enum class BulletType {
	PLAYER_TYPE,
	INVADER_SLOW_TYPE,
	INVADER_FAST_TYPE
};

class Bullet : public Entity {
	public:
		Bullet(GLWindow& window, std::string const& fileLocation);

		void update();

		GLfloat getSpeed() const { return bulletSpeed; }

		void setType(BulletType bulletType) { this->bulletType = bulletType; }
		BulletType getType() const { return bulletType; }


	private:
		GLWindow& window;
		BulletType bulletType;

		GLfloat bulletSpeed;
};

