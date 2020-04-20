#include "InvaderManager.h"

InvaderManager::InvaderManager(GLWindow& window)
	: window(window) {

	// Invaders
	int selected = 0;
	for (int x = 1; x < 4; x++) {
		for (int y = 5; y < 8; y++) {
			for (int z = 0; z < 3; z++) {
				invaderVector.emplace_back(new Invader(window, INVADER_MODEL_LOCATION));
				invaderVector[selected]->setModelPosition(glm::vec3(x, y, z));
				invaderVector[selected]->setScale(glm::vec3(0.3));
				selected++;
			}
		}
	}

	invaderMax = invaderVector.size();

	BulletType type[2] = {
		BulletType::INVADER_SLOW_TYPE,
		BulletType::INVADER_FAST_TYPE
	};

	// Bullets
	for (int i = 0; i < 2; i++) {
		bulletVector.emplace_back(new Bullet(window, BULLET_MODEL_LOCATION));
		bulletVector[i]->setModelPosition(glm::vec3(DORMANT_LOCATION));
		bulletVector[i]->setScale(glm::vec3(0.01, 0.1, 0.01));
		bulletVector[i]->setType(type[i]);
	}
}

void InvaderManager::update() {
	removeEntities();


	// Invaders 
	for (auto& invader : invaderVector) {
		glm::vec3 movementVector(0);

		// Bounds
		if (invader->getModelPosition().x >= X_BORDER_MAX) { towardsPositiveX = false; towardsNegativeY = true; }
		if (invader->getModelPosition().x <= X_BORDER_MIN) { towardsPositiveX = true;  towardsNegativeY = true; }
		
		// Horizontal movement
		if (towardsPositiveX)  { movementVector.x += INVADER_SPEED; }
		if (!towardsPositiveX) { movementVector.x -= INVADER_SPEED; }

		// Vertical movement
		if (towardsNegativeY) {
			downTick++;
			if (downTick <= downTickMax) { movementVector.y -= INVADER_SPEED; }
			else { downTick = 0; towardsNegativeY = false; }
		}


		if (!invader->isInvaderDead()) {
			invader->update();
			invader->move(movementVector);
		}
	}


	// Bullets
	for (auto& bullet : bulletVector) {
		bullet->update();

		// Shooting
		glm::vec3 movementVector(0.f);
		movementVector.y -= bullet->getSpeed();
		bullet->move(movementVector);

		// Bounds
		if (bullet->getModelPosition().y <= Y_BORDER_MIN ) { bullet->setModelPosition(glm::vec3(DORMANT_LOCATION)); }
	}

	if (invaderVector.size() > 1) { shooter = random[0].getInt(0, invaderVector.size() - 1); }
	else { shooter = 0; }

	if (invaderVector[shooter]->isInvaderDead() == false) {
		// Check if the bullet is slow or both
		// Slow bullet
		if (invaderVector.size() >= invaderMax / 2) {
			if (bulletVector[0]->getModelPosition().x == DORMANT_LOCATION) {
				bulletVector[0]->setModelPosition(glm::vec3(invaderVector[shooter]->getModelPosition()));
			}
		}

		// Both
		else {
			int randomBullet = random[1].getInt(0, 1);

			if (bulletVector[randomBullet]->getModelPosition().x == DORMANT_LOCATION) {
				bulletVector[randomBullet]->setModelPosition(glm::vec3(invaderVector[shooter]->getModelPosition()));
			}
		}
	}

	std::cout << "X: " << bulletVector[0]->getModelPosition().x << '\n';
	std::cout << "Y: " << bulletVector[0]->getModelPosition().y << '\n';
	std::cout << "Z: " << bulletVector[0]->getModelPosition().z << "\n\n";

	/*
	if (invaderVector.size() > 1) { shooter = random[0].getInt(0, invaderVector.size() - 1); }
	else { shooter = 0; }

	// Determining which invader is shooting
	if (invaderVector[shooter]->isInvaderDead() == false) {
		// Decides on using 1 or 2 bullets
		// Fast bullet
		if (invaderVector.size() <= invaderAmount / 2.0 ) {
			int bulletType = random[1].getInt(1, 2);

			if (bulletVector[bulletType]->getModelPosition() == glm::vec3(DORMANT_LOCATION)) {
				bulletVector[bulletType]->setModelPosition(invaderVector[shooter]->getModelPosition());
			}
		}

		// Slow bullet
		else {
			if (bulletVector[0]->getModelPosition() == glm::vec3(DORMANT_LOCATION)) {
				bulletVector[0]->setModelPosition(invaderVector[shooter]->getModelPosition());
			}
		}
	}
	else { shooter++; }

	std::cout << "X: " << bulletVector[0]->getModelPosition().x << '\n';	
	std::cout << "Y: " << bulletVector[0]->getModelPosition().y << '\n';
	std::cout << "Z: " << bulletVector[0]->getModelPosition().z << "\n\n";
	*/


}

void InvaderManager::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	for (auto& invader : invaderVector) { invader->render(viewMatrix, projection); }
	for (auto& bullet : bulletVector) { bullet->render(viewMatrix, projection); }
}

std::unique_ptr<Invader> InvaderManager::playerBulletCollision(std::unique_ptr<Player>& player) {
	return std::unique_ptr<Invader>();
}

bool InvaderManager::invaderBulletCollision(std::unique_ptr<Player>& player) {
	// Invader collides with player bullet
	return false;
}

bool InvaderManager::invaderCollision(std::unique_ptr<Player>& player) {
	// Player collides with invader / invaderbullet
	return false;
}


void InvaderManager::removeEntities() {
	auto invaderEnd = std::remove_if(invaderVector.begin(), invaderVector.end(), [](std::unique_ptr<Invader>& invader) {
		return invader->isInvaderDead();
	});
	invaderVector.erase(invaderEnd, invaderVector.end());
}
