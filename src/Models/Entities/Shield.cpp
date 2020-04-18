#include "Shield.h"

Shield::Shield(GLWindow &window, std::string const &modelLocation)
: Entity(window, modelLocation) {

}

void Shield::update(std::unique_ptr<Entity>& playerBullet, std::unique_ptr<Entity>& invaderBullet) {
	if (collision(playerBullet, invaderBullet)) {
		std::cout << "TEst\n";
	}
}

