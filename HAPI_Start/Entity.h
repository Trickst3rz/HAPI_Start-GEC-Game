#pragma once
#include"Vector2.h"
#include "Rectangle.h"

#include <HAPI_lib.h>
#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

enum class eSide
{
	ePlayer,
	eEnemy,
	eNeutral,
	eBullet
};

class Visualisation;

class World;

class Rectangle;

class Entity
{
public:
	Entity(std::string spriteID) : Spritename(spriteID) {};

	virtual ~Entity() = 0;

	virtual eSide getSide() const = 0;

	virtual void Update(World &world, Visualisation &vis, float dt) = 0;

	void Render(Visualisation &vis, float s);

	void SetPosition(Vector2 newPos) { m_oldPosition = m_position; m_position = newPos; }

	void SetBackPosition(Vector2 oldPos) { m_position = m_oldPosition; }

	Vector2 GetPosition() const { return m_position; }

	Vector2 GetOldPosition() const { return m_oldPosition; }

	void AddScore(int addScore) { PrevScore = Score, Score = Score + addScore; }

	int GetScore() const { return Score; }

	int GetPrevScore() const { return PrevScore; }

	virtual void CheckCollision(Visualisation &vis, Entity &other);

	bool IsAlive() const { return m_alive; }

	void SetAlive(bool alive) { m_alive = alive; }

	bool IsEnemyOf(eSide a, eSide b);

	bool IsPickupOf(eSide a, eSide b);

	std::string GetSpritename() const { return Spritename; }

	int GetLives() const { return lives; }

	size_t bulletStartIndex{ 0 };

	void TakeDamage(int damageInflicted);

protected:

	int PrevScore{ 0 };
	int Score{ 0 };
	float NoAlpha{ false };
	int lives{ 3 };
	int health{ 100 };
	std::string Spritename; //create getter? make private again
	bool m_alive{ true };
	float m_speed{ 6.0f };
	int curFrameX{ 0 };
	int curFrameY{ 0 };

	int m_damageTaken{ 10 };

	DWORD m_lastTimeUpdatedAnimation{ 0 };
	DWORD m_animationTime{ 50 };

private:
	Vector2 m_position;
	Vector2 m_oldPosition;
};

