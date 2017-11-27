#include "World.h"
#include "Visualisation.h"
#include "EntityPlayer.h"
#include "UI.h"
#include "Vector2.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

World::~World()
{
	delete m_vis;

	for (auto &p : m_entity)
		delete p;
	
}

void World::run(int width, int height, std::string name)
{
	
}

void World::LoadLevel()
{
	
	if (!m_vis->CreateSprite("player", "Data\\player.png"))
		return;
	
	EntityPlayer *newEntity = new EntityPlayer("player");
	
	newEntity->SetPosition(200, 200);

	m_entity.push_back(newEntity);

}

void World::Update(int width, int height, std::string name)
{

	m_vis = new Visualisation;

	if (!m_vis->initialise(width, height, name))
		return;

	LoadLevel();

	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	if (!m_vis->CreateSprite("starBackground", "Data\\FullStarBackground.png"))
		return;

	//if (!m_vis->CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", playerEntity.numFramesX, playerEntity.numFramesY))
//		return;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		m_vis->ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));
		
		m_vis->RenderNoAlphaSprite("starBackground", ScrollPosX, ScrollPosY);
		m_vis->RenderNoAlphaSprite("starBackground", SecondScrollPosX, SecondScrollPosY);
//		m_vis->RenderSprite("horse", 100, 100, playerEntity.curFrameX, playerEntity.curFrameY);
		//m_vis->RenderSprite("player", playerEntity.playerPosX, playerEntity.playerPosY);

		for (auto p : m_entity)
		{
			p->Render(m_vis);
			p->Update();
		}

		int elapsedTime = HAPI.GetTime() - prevTime;
		ScrollPosY += 1;
		SecondScrollPosY += 1;

		//visual.ScrollingBackground(ScrollPosX, ScrollPosY, SecondScrollPosX, SecondScrollPosY); /////////GET WORKING

		if (ScrollPosY > m_vis->m_screenRect.bottom)
		{
			ScrollPosY = 0;
			SecondScrollPosY = -800;
		}
	}
}
