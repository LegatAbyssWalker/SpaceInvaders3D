#pragma once

#include "glm/glm.hpp"

#include "../Functionality/Object.h"
#include "../Functionality/Model.h"
#include "../../Display/GLWindow.h"
#include "../../States/Functionality/State.h"
#include "../../Utilities/Variables.h"

#include <iostream>


class Entity : public Object {
	public:
		Entity(GLWindow& window, std::string const& filePath);

		void render(const glm::mat4 viewMatrix, const glm::mat4& projection);

		bool collision(std::unique_ptr<Entity>& entity1, std::unique_ptr<Entity>& entity2);

	private:
		Model model;
};

