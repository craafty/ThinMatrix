#pragma once
#include <glm/glm.hpp>

class Light {
private:
	glm::vec3 position;
	glm::vec3 color;

public:
	Light(glm::vec3 position, glm::vec3 color);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getColor();
	void setColor(glm::vec3 color);
};