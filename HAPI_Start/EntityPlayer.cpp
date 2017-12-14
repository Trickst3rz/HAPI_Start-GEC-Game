#include "EntityPlayer.h"
#include "Rectangle.h"
#include "Visualisation.h"

EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::CheckCollision(Visualisation &vis, Entity &other)
{
	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Vector2 newPos{ GetPosition() };

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect (vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));

	Rectangle CollisionRect(thisRect);

	Rectangle EnemyCollisionRect(otherRect);

	int w{ thisRect.width() };

	thisRect.left += w / 10;

	thisRect.right += w / 10;

	w;

	int h{ thisRect.height() };

	thisRect.top += h / 10;

	thisRect.bottom += h / 10;

	EnemyCollisionRect.Translate(other.GetPosition().x, other.GetPosition().y);
	
	CollisionRect.Translate(GetPosition().x, GetPosition().y);

	Vector2 temp;

	//temp.x = m_position.x - w;

	//temp.y = m_position.y - h;

	if (CollisionRect.CheckCollision(EnemyCollisionRect) == true)
	{
		//std::cout << "Collision detected!" << std::endl;
		pos = oldPos;
		//nextPos.x = temp.x;
		//nextPos.y = temp.y;
		//GetPosition() = GetOldPosition();


		//nextPos.x = std::max(0, std::min((int)m_position.x, 1000 - thisRect.width() - 1));
		//nextPos.y = std::max(0, std::min((int)m_position.y, 1000 - thisRect.height() - 1));
		//CollisionRect.ClipTo(m_enemyRect);
		//return true;
	}

	
		
	//m_position = nextPos;
	CollisionRect.Translate(-GetPosition().x, -GetPosition().y);
	EnemyCollisionRect.Translate(-other.GetPosition().x, -other.GetPosition().y);
	//m_position.x = nextPos.x;
	//m_position.y = nextPos.y;
}

void EntityPlayer::Update(Visualisation &vis)
{
	//m_position = nextPos;
	

	//oldPos = m_position;
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
		PrevTime = ElapsedTime;
		if (HAPI.GetTime() - m_lastTimeUpdated >= m_time)
		{
			//Moves sprite with WASD keys
			if (keyData.scanCode['W'])
				pos.y -= m_speed;

			if (keyData.scanCode['S'])
				pos.y += m_speed;

			if (keyData.scanCode['A'])
				pos.x -= m_speed;

			if (keyData.scanCode['D'])
				pos.x += m_speed;

			if (!(vect.x == 0 && vect.y == 0))
			{
				vect.x = m_speed * (vect.x / (vect.Length()));
				vect.y = m_speed * (vect.y / (vect.Length()));

				pos.x += vect.x;
				pos.y += vect.y;

			}

			if (controllerData.isAttached)
			{

				if (Deadzone < LeftThumbX)
					pos.x += m_speed;

				if (-Deadzone > LeftThumbX)
					pos.x -= m_speed;

				if (-Deadzone > LeftThumbY)
					pos.y += m_speed;

				if (Deadzone < LeftThumbY)
					pos.y -= m_speed;

				if (!(vect.x == 0 && vect.y == 0))
				{
					vect.x = m_speed *(vect.x / (vect.Length()));
					vect.y = m_speed *(vect.y / (vect.Length()));

					pos.x += vect.x;
					pos.y += vect.y;

				}
			}
			m_lastTimeUpdated = HAPI.GetTime();
		}

		SetPosition(pos);

		float HorseElapsedTime = HAPI.GetTime() - PrevTime;

		if (PrevTime + 150 < HorseElapsedTime)
		{
			PrevTime = HorseElapsedTime;

			curFrameX++;

			if (curFrameX >= vis.GetNumframesX(Spritename))
			{
				curFrameX = 0;

				curFrameY += 1;
			}

			if (curFrameY >= vis.GetNumframesY(Spritename))
			{
				curFrameY = 0;
				curFrameX = 0;

			}
		}
}
