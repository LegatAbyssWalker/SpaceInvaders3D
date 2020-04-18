#include "Player.h"

Player::Player(GLWindow& window, glm::vec3 cameraPosition, glm::mat4 projection)
	: window(window) {

	// Camera
	camera = Camera(cameraPosition, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, PLAYER_SPEED, 0.3f);

	// Bullet
	bullet = std::make_unique<Bullet>(window, BULLET_MODEL_LOCATION);
	bullet->setScale(glm::vec3(0.01, 0.1, 0.01));
	bullet->setModelPosition(glm::vec3(DORMANT_LOCATION));
	bullet->setType(BulletType::PLAYER_TYPE);
}

void Player::keyboardUpdate(Movement movement, GLfloat deltaTime) {
	// Camera event updates
	camera.processKeyboard(movement, deltaTime);

	if (movement == Movement::SHOOTING) { shooting = true; }
}


void Player::update() {
	camera.processMouseMovement(window);
	bullet->update();

	// Shooting
	glm::vec3 movementVector(0.f);
	movementVector.y += bullet->getSpeed();

	if (shooting && (bullet->getModelPosition() == glm::vec3(DORMANT_LOCATION))) { bullet->setModelPosition(camera.getPosition()); }
	bullet->move(movementVector);


	// Bullet bounds
	if (bullet->getModelPosition().y >= Y_BORDER_MAX) {
		shooting = false;
		bullet->move(glm::vec3(0));
		bullet->setModelPosition(glm::vec3(DORMANT_LOCATION));
	}





	// Collision with XZ walls

}

void Player::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	bullet->render(viewMatrix, projection);
}
