#pragma once
#include "Entity.h"

class Rectangle;

class EntityEnemy : public Entity
{
public:
	EntityEnemy(std::string spriteID) : Entity(spriteID) {};
	~EntityEnemy();

	void Update(Visualisation &vis, float deltaTime) override final;

	eSide getSide() const override final { return eSide::eEnemy; }

	bool CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect) override final;

	Rectangle m_temp;
	Rectangle m_enemyRect;
	
private:
	//Rectangle m_enemyRect;

	
};

