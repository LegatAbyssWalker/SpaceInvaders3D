#pragma once

#include "Camera.h"
#include "../States/Functionality/State.h"
#include "../Display/GLWindow.h"
#include "../Utilities/FileLocations.h"
#include "../Utilities/Variables.h"
#include "../Shaders/Program.h"
#include "../Models/Functionality/Object.h"
#include "../Models/Entities/Entity.h"

#include <iostream>
#include <memory>

class Player {
	public:
		Player(GLWindow& window, glm::vec3 cameraPosition, glm::mat4 projection);

		void keyboardUpdate(Movement movement, GLfloat deltaTime);

		void update();
		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		Camera& getCamera() { return camera; }


	private:
		Movement movement;
		GLWindow& window;

		Camera camera;
		GLfloat lastX = window.getWindow().getSize().x / 2.f;
		GLfloat lastY = window.getWindow().getSize().y / 2.f;
		bool firstMouse = true;
};