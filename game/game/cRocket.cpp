/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"


void cRocket::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRocket::update(float deltaTime)
{
 
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 50.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 50.0f;
	}
	
	if (m_InputMgr->isKeyDown(int('A')))
	{
		spriteScaling += 0.2f;
	}
	if (m_InputMgr->isKeyDown(int('S')))
	{
		spriteScaling -= 0.2f;
	}


	//spritePos2D += spriteTranslation * deltaTime;
	setBoundingRect(&boundingRect);

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		// Add new bullet sprite to the vector array
		if (theRocketBullets.size() - 1 != 0){
		theRocketBullets.push_back(new cBullet);
		int numBullets = theRocketBullets.size() - 1;
		theRocketBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x , spritePos2D.y));
		theRocketBullets[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		theRocketBullets[numBullets]->setTexture(theGameTextures[5]->getTexture());
		theRocketBullets[numBullets]->setTextureDimensions(theGameTextures[5]->getTWidth(), theGameTextures[5]->getTHeight());
		theRocketBullets[numBullets]->setSpriteCentre();
		theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		theRocketBullets[numBullets]->setActive(true);
		theRocketBullets[numBullets]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}}

	// This section prevents the player from moving off the screen, limits their movement range
	//if the player goes beyond the screen on the right, move back to the left
	if (spritePos2D.x > 512)
	{
		spritePos2D.x -= 100.0f;
	}
	//if the player goes beyond the screen on the left, move back to the right
	if (spritePos2D.x  < 0)
	{
		spritePos2D.x += 100.0f;
	}

	/*
	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}
	*/

	/* 
	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;
	*/

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin(); bulletIterartor != theRocketBullets.end(); ++bulletIterartor)
	{
		(*bulletIterartor)->update(deltaTime);
		for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				score += 1;
				(*asteroidIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
			}
			
		}
	}
	for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator){
		(*asteroidIterator)->update(deltaTime);
	if ((*asteroidIterator)->getSpritePos().y > 597.5){
				life -= 1;
			}
	}
	

	vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin();
	while (bulletIterartor != theRocketBullets.end())
	{
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else if ((*bulletIterartor)->getSpritePos().y<0){
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*bulletIterartor)->render();
			++bulletIterartor;
		}
	}
}
/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cRocket::getRocketVelocity()
{
	return rocketVelocity;
}
string cRocket::Getlife()
{
	stringstream output;
	output << "Lives: " << life<<"   Score:  "<<score;
	return output.str();
}

bool cRocket::endGame(){
	if (score == 5)
	{
		return true;
	}
	else {
		false;
	}

}
bool cRocket::endGamelife(){
	if (life == 0)
	{
		return true;
	}
	else {
		false;
	}

}

void cRocket::Restart(bool reset){
	if (reset){
		score = 0;
		vector<cBullet*>::iterator bulletIterator = theRocketBullets.begin();
		while (bulletIterator != theRocketBullets.end()){
			bulletIterator = theRocketBullets.erase(bulletIterator);
		}
	}
}

