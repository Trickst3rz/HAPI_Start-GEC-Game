#pragma once
#include "Entity.h"

class Rectangle;

class Vector2;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update(Visualisation &vis, float deltaTime) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	Vector2 vect;
	
	Vector2 nextPos;

	int PrevTime = 0;
};

