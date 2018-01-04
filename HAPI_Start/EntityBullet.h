#pragma once
#include "Entity.h"

class Visualisation;

class EntityBullet : public Entity
{
public:
	EntityBullet(std::string spriteID) : Entity(spriteID) { m_alive = false, health = 1; };
	~EntityBullet();

	void Update(World &world, Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return m_side; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

	void Spawn(eSide side, const Vector2 &pos, int damageAmount);

private:
	eSide m_side{ eSide::eNeutral };
	Vector2 GetPos;
};

