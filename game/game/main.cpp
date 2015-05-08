#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "asteroidsGame.h"
#include "Button.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 512;
    const int windowHeight = 512;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\Enemy1.png", "Images\\SmokeyJoe64.png", "Images\\Dave64.png", "Images\\Dead1.png", "Images\\VonHilda1.png", "Images\\Laser1.png" };
	for (int tCount = 0; tCount < 6; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/ActionBackground.wav", "Audio/Laser.wav", "Audio/explosion2.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	// Create vector array of textures

	//This sets the area where the first enemy spawns
	int spawnx = 60;
	int spawny = 32;
	
	for (int astro = 0; astro < 5; astro++)
	{
		if (astro == 1){
		theAsteroids.push_back(new cAsteroid);
		theAsteroids[astro]->setSpritePos(glm::vec2(spawnx, spawny));
		theAsteroids[astro]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
		int randAsteroid = rand() % 4;
		theAsteroids[astro]->setTexture(theGameTextures[0]->getTexture());
		theAsteroids[astro]->setTextureDimensions(theGameTextures[0]->getTWidth(), theGameTextures[0]->getTHeight());
		theAsteroids[astro]->setSpriteCentre();
		theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theAsteroids[astro]->setActive(true);
		theAsteroids[astro]->setMdlRadius();

		//This is the space that seperates each enemy on the x axis on spawn
		spawnx += 100;
		
		
	}

	//This displays the Background Image
	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\Cityscape21.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	cTexture playTxt;
	playTxt.createTexture("Images\\PlayBtn.png");
	Button PlaySprite;
	PlaySprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	PlaySprite.setSpritePos(glm::vec2(1000.0f, 900.0f));
	PlaySprite.setTexture(playTxt.getTexture());
	PlaySprite.setTextureDimensions(playTxt.getTWidth(), playTxt.getTHeight());
	PlaySprite.attachSoundMgr(theSoundMgr);// Attach sound manager to button sprite

	//This Displays the Character image
	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\WackaWackaSpaceMan64.png");
	cRocket rocketSprite;
	rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	rocketSprite.setSpritePos(glm::vec2(262.0f, 480.0f));
	rocketSprite.setTexture(rocketTxt.getTexture());
	rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	rocketSprite.setSpriteCentre();
	rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

	// Attach sound manager to rocket sprite
	rocketSprite.attachSoundMgr(theSoundMgr);

	//declaring score and life
	bool scorelife;
	int score=5;
	int  count = 0;
    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events
		
        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (count == 0){
			spriteBkgd.render();

		}
		else if (count == 1){
			spriteBkgd.render();

			rocketSprite.update(elapsedTime);

			vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin();
			while (asteroidIterator != theAsteroids.end())
			{
				if ((*asteroidIterator)->isActive() == false)
				{
					asteroidIterator = theAsteroids.erase(asteroidIterator);
				}
				else
				{

					(*asteroidIterator)->update(elapsedTime);
					
					(*asteroidIterator)->render();
					++asteroidIterator;
				}
			}

			rocketSprite.render();

			theFontMgr->getFont("Space")->printText(rocketSprite.Getlife().c_str(), FTPoint(0.0f, 1.0f, 0.0f));
			if (rocketSprite.endGame()){
				count = 3;
			}
			if (rocketSprite.endGamelife()){
				count = 4;
			}
		}
		else if (count == 3){
			win;
		}
		else if (count == 4){
			lose;
			
		}
		if (PlaySprite.getPressed() == true){

			count = 1;
			PlaySprite.setPressed(false);

		}
		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success

}
