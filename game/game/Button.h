#ifndef _BUTTON_H
#define _BUTTON_H
#include "cSprite.h"
#include "asteroidsGame.h"


class Button : public cSprite
{
private:


	bool pressed;

public:

	Button();

	void update(float deltaTime);//check presssed
	bool getPressed();//return press
	void setPressed(bool value);//set pressed

};
#endif
