#pragma once
#include "Entity.h"

class Player : public Entity {
public:
	Player(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	void move();

private:
	static const float RUN_SPEED;
	static const float TURN_SPEED;
	static const float GRAVITY;
	static const float JUMP_POWER;
	static const float TERRAIN_HEIGHT;

	float currentSpeed;
	float currentTurnSpeed;
	float upwardsSpeed;
	bool isInAir;

	void checkInputs();
	void jump();
};