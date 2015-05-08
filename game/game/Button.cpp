
#include "Button.h"
Button::Button(){
	pressed = false;
}


void Button::update(float deltaTime){
	//get mouse click
	if (m_InputMgr->getLeftMouseBtn()){
		//check area clicked = the button 
		glm::vec2 areaClicked = glm::vec2(m_InputMgr->getMouseXPos(), m_InputMgr->getMouseYPos());
		if (areaClicked.x > spritePos2D.x - (textureWidth / 2) && areaClicked.x<spritePos2D.x + (textureWidth / 2) && areaClicked.y>spritePos2D.y - (textureHeight / 2) && areaClicked.y < spritePos2D.y + (textureHeight / 2)){
			pressed = true;
			//play the click sound
			m_SoundMgr->getSnd("Click")->playAudio(AL_TRUE);
		}
	}
}//retun button pressed
bool Button::getPressed(){
	return pressed;
}//set button
void Button::setPressed(bool value){
	pressed = value;
}