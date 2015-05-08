/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CROCKET_H
#define _CROCKET_H
#include "cSprite.h"

#include "asteroidsGame.h"

class cRocket : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);
	int score=0;
	int life=3;

public:
	string Getlife();
	void Restart(bool reset);
	bool endGame();
	bool endGamelife();
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	glm::vec2 getRocketVelocity();				 // Gets the rocket velocity

};
#endif