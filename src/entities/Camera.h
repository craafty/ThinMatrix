#pragma once
#include "Player.h"
#include <glm/glm.hpp>

class Camera {
private:
	Player& player;
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;
	float distanceFromPlayer;
	float angleAroundPlayer;
	float lastMouseY;
	float lastMouseX;
public:
	Camera(Player& player);
	void move();
	glm::vec3 getPosition();
	float getPitch();
	float getYaw();
	float getRoll();
	//void calculateZoom();
	void calculatePitch();
	void calculateAngleAroundPlayer();
	float calculateHorizontalDistance();
	float calculateVerticalDistance();
	void calculateCameraPosition(float horizDistance, float verticDistance);
};