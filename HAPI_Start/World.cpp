#include "World.h"
#include "Visualisation.h"
#include "EntityPlayer.h"
#include "EntityBackground.h"
#include "EntityScrollingBackground.h"
#include "EntityEnemy.h"
#include "EntityExplosion.h"
#include "Vector2.h"
#include <HAPI_lib.h>
#include <algorithm>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

World::~World()
{
	delete m_vis;

	for (auto p : m_entity)
		delete p;
	
}

void World::run()
{
	m_vis = new Visualisation;

	if (!m_vis->initialise(screenWidth, screenHeight, "Intergalactic War"))
		return;

	if (!LoadLevel())
		return;

	Update();
}

bool World::LoadLevel()
{
	//Loads all the sprites

	if (!m_vis->CreateSprite("player", "Data\\idleSpriteV2.png", 4, 1))
		return false;

	if (!m_vis->CreateSprite("enemy", "Data\\player.png"))
		return false;

	if (!m_vis->CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", 5, 3))
		return false;

	if (!m_vis->CreateSprite("background", "Data\\FullStarBackground.png"))
		return false;
	
	/*EntityBackground *newBackground = new EntityBackground("background");
	m_entity.push_back(newBackground);

	newBackground->SetPosition(Vector2(0, 0));

	EntityScrollingBackground *newSecondBackground = new EntityScrollingBackground("background");
	m_entity.push_back(newSecondBackground);*/

	//newSecondBackground->SetPosition(Vector2(0, -800));

	EntityPlayer *newPlayer = new EntityPlayer("player");
	m_entity.push_back(newPlayer);

	newPlayer->SetPosition(Vector2(0, 0));
	//newPlayer->LoadRectangle(*m_vis);

	EntityEnemy *enemy = new EntityEnemy("enemy");
	m_entity.push_back(enemy);

	enemy->SetPosition(Vector2(400, 600));

	EntityExplosion *horse = new EntityExplosion("horse");
	m_entity.push_back(horse);

	horse->SetPosition(Vector2(100, 100));

	return true;

}

void World::Update()
{

	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);

	double currentTime = HAPI.GetTime();

	double t = 0.0;

	double dt = 1 / 60.0;

	

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		double newTime = HAPI.GetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		m_vis->ClearToColour(HAPI.GetScreenPointer(), screenWidth, screenHeight, HAPI_TColour(0, 0, 0));

		while (frameTime > 0.0)
		{
			float deltaTime = std::min(frameTime, dt);
			for (auto p : m_entity)
				p->Update(*m_vis, deltaTime);
				
			frameTime -= deltaTime;
			t += deltaTime;
		}

		for (size_t i = 0; i < m_entity.size(); i++)
		{
			for (size_t j = i + 1; j < m_entity.size(); j++)
			{
				m_entity[i]->CheckCollision(*m_vis, *m_entity[j]);
			}
		}

		for (auto p : m_entity)
			p->Render(*m_vis);
	}
}
