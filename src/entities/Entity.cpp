#include "Entity.h"

Entity::Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale) :
	model(model), position(position), rotX(rotX), rotY(rotY), rotZ(rotZ), scale(scale) {}

void Entity::increasePosition(float dx, float dy, float dz)
{
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz)
{
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}

TexturedModel Entity::getModel()
{
	return model;
}

void Entity::setModel(TexturedModel model)
{
	this->model = model;
}

glm::vec3& Entity::getPosition()
{
	return position;
}

void Entity::setPosition(glm::vec3& position)
{
	this->position = position;
}

float Entity::getRotX()
{
	return rotX;
}

void Entity::setRotX(float rotX)
{
	this->rotX = rotX;
}

float Entity::getRotY()
{
	return rotY;
}

void Entity::setRotY(float rotY)
{
	this->rotY = rotY;
}

float Entity::getRotZ()
{
	return rotZ;
}

void Entity::setRotZ(float rotZ)
{
	this->rotZ = rotZ;
}

float Entity::getScale()
{
	return scale;
}

void Entity::setScale(float scale)
{
	this->scale = scale;
}