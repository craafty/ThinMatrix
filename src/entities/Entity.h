#pragma once
#include <glm/glm.hpp>
#include "models/TexturedModel.h"


class Entity {
private:
	TexturedModel model;
	glm::vec3 position;
	float rotX, rotY, rotZ;
	float scale;

public:
	Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	void increasePosition(float dx, float dy, float dz);
	void increaseRotation(float dx, float dy, float dz);

	TexturedModel getModel();
	void setModel(TexturedModel model);
	glm::vec3& getPosition();
	void setPosition(glm::vec3& position);
	float getRotX();
	void setRotX(float rotX);
	float getRotY();
	void setRotY(float rotY);
	float getRotZ();
	void setRotZ(float rotZ);
	float getScale();
	void setScale(float scale);
};