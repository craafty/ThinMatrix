#include "Camera.h"
#include "renderEngine/DisplayManager.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(Player& player) : player(player), position(400.0f, 10.0f, 400.0f), pitch(20), yaw(0), roll(0),
distanceFromPlayer(50), angleAroundPlayer(0), lastMouseX(0), lastMouseY(0) {}

void Camera::move() {
    calculatePitch();
    calculateAngleAroundPlayer();
    float horizontalDistance = calculateHorizontalDistance();
    float verticalDistance = calculateVerticalDistance();
    calculateCameraPosition(horizontalDistance, verticalDistance);
    yaw = 180 - (player.getRotY() + angleAroundPlayer);
}

glm::vec3 Camera::getPosition()
{
	return position;
}

float Camera::getPitch()
{
	return pitch;
}

float Camera::getYaw()
{
	return yaw;
}

float Camera::getRoll()
{
	return roll;
}

void Camera::calculatePitch()
{
    GLFWwindow* window = DisplayManager::getWindow();
    float PITCH_SENSITIVITY = 1.0f;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double currentMouseY;
        glfwGetCursorPos(window, nullptr, &currentMouseY);

        double deltaY = lastMouseY - currentMouseY;
        pitch += deltaY * PITCH_SENSITIVITY;

        if (pitch < 1.0f) pitch = 1.0f;
        if (pitch > 90.0f) pitch = 90.0f;

        lastMouseY = currentMouseY;
    }
}

void Camera::calculateAngleAroundPlayer() {
    GLFWwindow* window = DisplayManager::getWindow();
    float ANGLE_SENSITIVITY = 1.0f;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double currentMouseX;
        glfwGetCursorPos(window, &currentMouseX, nullptr);

        float deltaX = static_cast<float>(currentMouseX - lastMouseX);
        float angleChange = deltaX * ANGLE_SENSITIVITY;
        angleAroundPlayer -= angleChange;

        lastMouseX = currentMouseX;
    }
}

float Camera::calculateHorizontalDistance()
{
    return (float)(distanceFromPlayer * std::cos(glm::radians(pitch)));
}

float Camera::calculateVerticalDistance()
{
    return (float)(distanceFromPlayer * std::sin(glm::radians(pitch)));
}

void Camera::calculateCameraPosition(float horizDistance, float verticDistance)
{
    float theta = player.getRotY() + angleAroundPlayer;
    float offsetX = (float)(horizDistance * std::sin(glm::radians(theta)));
    float offsetZ = (float)(horizDistance * std::cos(glm::radians(theta)));
    position.x = player.getPosition().x - offsetX;
    position.z = player.getPosition().z - offsetZ;
    position.y = player.getPosition().y + verticDistance;

}