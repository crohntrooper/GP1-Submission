/*
=================
cBullet.h
- Header file for class definition - SPECIFICATION
- Header file for the Bullet class which is a child of cSprite class
=================
*/
#ifndef _CBULLET_H
#define _CBULLET_H
#include "cSprite.h"


class cBullet : public cSprite
{
private:
	glm::vec2 bulletVelocity = glm::vec2(0.0f, 0.0f);

public:
	//cBullet(vector<cTexture*> tileTextList)

	void render();		// Default render function
	void update(float deltaTime);		//Update bullet method
	void setBulletVelocity(glm::vec2 bulletVel);   // Sets bullet velocity
	glm::vec2 getBulletVelocity();				 // Gets the bullet velocity
	void renderCollisionBox();				
};
#endif