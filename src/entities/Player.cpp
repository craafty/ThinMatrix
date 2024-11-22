#include "Player.h"
#include "Player.h"
#include "renderEngine/DisplayManager.h"
#include <glad/glad.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float Player::RUN_SPEED = 20.0f;
const float Player::TURN_SPEED = 160.0f;
const float Player::GRAVITY = -50.0f;
const float Player::JUMP_POWER = 30.0f;
const float Player::TERRAIN_HEIGHT = 0.0f;

Player::Player(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale) : 
    Entity(model, position, rotX, rotY, rotZ, scale), currentSpeed(0), currentTurnSpeed(0), upwardsSpeed(0), isInAir(false)
{
}

void Player::move()
{
    checkInputs();
    increaseRotation(0, currentTurnSpeed * DisplayManager::getFrameTimeSeconds(), 0);
    float distance = currentSpeed * DisplayManager::getFrameTimeSeconds();
    float dx = distance * std::sin(glm::radians(getRotY()));
    float dz = distance * std::cos(glm::radians(getRotY()));
    increasePosition(dx, 0, dz);
    upwardsSpeed += GRAVITY * DisplayManager::getFrameTimeSeconds();
    increasePosition(0, upwardsSpeed * DisplayManager::getFrameTimeSeconds(), 0);
    if (getPosition().y < TERRAIN_HEIGHT) {
        upwardsSpeed = 0;
        isInAir = false;
        getPosition().y = TERRAIN_HEIGHT;
    }
}

void Player::checkInputs()
{
    GLFWwindow* window = DisplayManager::getWindow();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        DisplayManager::closeDisplay();
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        currentSpeed = RUN_SPEED;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        currentSpeed = -RUN_SPEED;
    }
    else {
        currentSpeed = 0;
    }


    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        currentTurnSpeed = -TURN_SPEED;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        currentTurnSpeed = TURN_SPEED;
    }
    else {
        currentTurnSpeed = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        jump();
    }
}

void Player::jump()
{
    if (!isInAir) {
        upwardsSpeed = JUMP_POWER;
        isInAir = true;
    }
}
