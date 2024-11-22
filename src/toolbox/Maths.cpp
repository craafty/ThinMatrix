#include "Maths.h"
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <glm/gtx/string_cast.hpp>


glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale)
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

	return matrix;
}

glm::mat4 Maths::createViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix(1.0f);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 negativeCameraPos = -camera.getPosition();
	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);
	return viewMatrix;
}

