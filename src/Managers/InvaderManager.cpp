#include "InvaderManager.h"

InvaderManager::InvaderManager(GLWindow& window)
	: window(window) {

	// Creates invaders
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

}

void InvaderManager::update() {
	removeEntities();


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
}

void InvaderManager::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	for (auto& invader : invaderVector) { invader->render(viewMatrix, projection); }
}

bool InvaderManager::collisions(std::unique_ptr<Entity>& entity) {
	return false;
}

void InvaderManager::handleCollisions() {

}

void InvaderManager::removeEntities() {
	auto invaderEnd = std::remove_if(invaderVector.begin(), invaderVector.end(), [](std::unique_ptr<Invader>& invader) {
		return invader->isInvaderDead();
	});
	invaderVector.erase(invaderEnd, invaderVector.end());
}
