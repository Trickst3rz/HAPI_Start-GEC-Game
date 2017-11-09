#pragma once
#include <unordered_map>
#include "Rectangle.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Sprite;

class Rectangle;

class Visualisation
{
public:
	~Visualisation();

	bool initialise(int width, int height, std::string name);

	void ClearToColour(BYTE* screen, int width, int height, HAPI_TColour colour);

	bool CreateSprite(const std::string &name, const std::string &filename, int width, int height);

	void RenderSprite(const std::string &name, int posX, int posY);

	void RenderNoAlphaSprite(const std::string & name, int posX, int posY);

private:
	std::unordered_map<std::string, Sprite*> m_spritemap;

	Rectangle m_screenRect;

	//Rectangle m_textureRect;

	BYTE *m_screenPnter;

	//BYTE *m_texturePnter;
};
