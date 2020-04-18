#include "Bullet.h"

Bullet::Bullet(GLWindow& window, std::string const& fileLocation)
	: Entity(window, fileLocation), window(window) {
}

void Bullet::update() {
	switch (bulletType) {
		case BulletType::PLAYER_TYPE:
			bulletSpeed = PLAYER_BULLET_SPEED;
			break;

		case BulletType::INVADER_SLOW_TYPE:
			bulletSpeed = INVADER_BULLET_SLOW_SPEED;
			break;

		case BulletType::INVADER_FAST_TYPE:
			bulletSpeed = INVADER_BULLET_FAST_SPEED;
			break;
	}
}
