#include "Entity.h"


Entity::Entity(GLWindow& window, std::string const& filePath)
	: model(filePath, window), Object(window) {
}

void Entity::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	program->useProgram();

	// Model matrix
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scaleValue);
	modelMatrix = glm::rotate(modelMatrix, getRotationAngle(), getRotationAxis());

	// Uniforms
	program->setMat4("model", modelMatrix);
	program->setMat4("view", viewMatrix);
	program->setMat4("projection", projection);

	// Model rendering
	model.renderModel(program);
}

bool Entity::collision(std::unique_ptr<Entity>& entity1, std::unique_ptr<Entity>& entity2) {
	bool collisionX = entity1->getModelPosition().x + entity1->getSize().x >= entity2->getModelPosition().x &&
					  entity2->getModelPosition().x + entity2->getSize().x >= entity1->getModelPosition().x;

	bool collisionY = entity1->getModelPosition().y + entity1->getSize().y >= entity2->getModelPosition().y &&
	                  entity2->getModelPosition().y + entity2->getSize().y >= entity1->getModelPosition().y;


	bool collisionZ = entity1->getModelPosition().z + entity1->getSize().z >= entity2->getModelPosition().z &&
	                  entity2->getModelPosition().z + entity2->getSize().z >= entity1->getModelPosition().z;


	return collisionX && collisionY && collisionZ;
}
