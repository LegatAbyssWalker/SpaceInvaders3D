#include "Invader.h"

Invader::Invader(GLWindow &window, std::string const& filePath)
	: Entity(window, filePath), window(window) {

}

void Invader::update() {


	if (!isWithinBounds) { setDead(); }
}
