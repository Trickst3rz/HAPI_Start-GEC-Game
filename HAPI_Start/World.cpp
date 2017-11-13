#include "World.h"
#include "Visualisation.h"
#include "UI.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

void World::Update(int width, int height, std::string name)
{
	Visualisation visual;

	UI ui;

	if (!visual.initialise(width, height, name))
		return;

	

	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	if (!visual.CreateSprite("starBackground", "Data\\FullStarBackground.png"))
		return;

	if (!visual.CreateSprite("player", "Data\\player.png"))
		return;

	if (!visual.CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", numFramesX, numFramesY))
		return;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

		visual.ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));

		visual.RenderNoAlphaSprite("starBackground", ScrollPosX, ScrollPosY);
		visual.RenderNoAlphaSprite("starBackground", SecondScrollPosX, SecondScrollPosY);
		visual.RenderSprite("horse", 100, 100, curFrameX, curFrameY);
		visual.RenderSprite("player", playerPosX, playerPosY);
		
		//int elapsedTime = HAPI.GetTime() - prevTime;
		int playerElapsedTime = HAPI.GetTime() - playerPrevTime;
		int elapsedTime = HAPI.GetTime() - prevTime;
		ScrollPosY += 1;
		SecondScrollPosY += 1;

		if(prevTime +  1000/30 < elapsedTime)
		{
			prevTime = elapsedTime;

			curFrameX += 1;
		


			if (curFrameX >= numFramesX)
			{
				curFrameX = 0;
				curFrameY += 1;
			}

			if (curFrameY >= numFramesY)
			{
				curFrameY = 0;
				curFrameX = 0;
			}
		}

		//visual.ScrollingBackground(ScrollPosX, ScrollPosY, SecondScrollPosX, SecondScrollPosY); /////////GET WORKING

		if (ScrollPosY > visual.m_screenRect.bottom)
		{
			ScrollPosY = 0;
			SecondScrollPosY = -800;
		}
		
		//ui.KeyboardInput(keyData, playerPosX, playerPosY, elapsedTime, prevTime);

		

		if (playerPrevTime + 10 < playerElapsedTime)
		{
			playerPrevTime = playerElapsedTime;
			float playerSpeed = 5;

			//Moves sprite with WASD keys
			if (keyData.scanCode['W'])
				playerPosY-= playerSpeed;

			if (keyData.scanCode['S'])
				playerPosY+= playerSpeed;

			if (keyData.scanCode['A'])
				playerPosX-= playerSpeed;

			if (keyData.scanCode['D'])
				playerPosX+= playerSpeed;
		}
		

		if (playerPosY < height - 200 && playerPosX < width - 200 && playerPosY > 200 && playerPosX > 200)
		{
			HAPI.SetControllerRumble(0, 40000, 40000);
		}
		else
		{
			HAPI.SetControllerRumble(0, 0, 0);
		}

		if (controllerData.isAttached)
		{
			//Gets the values of left thumb x, y and deadzone
			int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
			int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
			int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

			float speed = 5;

			float translateX = 0;
			float translateY = 0;

			if (Deadzone < LeftThumbX)
				translateX +=speed;

			if (-Deadzone > LeftThumbX)
				translateX -= speed;

			if (-Deadzone > LeftThumbY)
				translateY += speed;

			if (Deadzone < LeftThumbY)
				translateY -= speed;

			if (!(translateX == 0 && translateY == 0))
			{

				float sqrRoot = sqrt((translateX*translateX) + (translateY*translateY));

				translateX = speed*(translateX / sqrRoot);
				translateY = speed*( translateY / sqrRoot);

				playerPosX += translateX;
				playerPosY += translateY;

				std::cout << LeftThumbX << LeftThumbY << std::endl;
			}
		}

	
	}
}