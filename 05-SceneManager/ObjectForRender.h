#pragma once
#include "Animations.h"
#include "Sprites.h"
#include "debug.h"
#define BACKGROUND_TYPE	1
#define CURTAIN_TYPE	2
#define MARIO_BROS3_BLACK_TYPE	3
#define ID_SPRITE_BACKGROUND_TYPE	180720
#define ID_SPRITE_CURTAIN_TYPE	180721
#define ID_SPRITE_MARIO_BROS3_BLACK_TYPE	180722
class ObjectForRender
{
	public:
		bool isAllowRender, isAllowUpdate;
		int type;
		float x, y, vx, vy;
	ObjectForRender(float x, float y, int Type)
	{
		this->x = x;
		this->y = y;
		vx = vy = 0;
		isAllowRender = isAllowUpdate = false;
		type = Type;
	}

	void Update(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
		if (type == MARIO_BROS3_BLACK_TYPE)
		{
			if (vy > 0)
			{
				if (y >= 188/2)
				{
					vy = 0.0f;
					y = 188.0f /2;
				}
			}
		}
	}
	void setSpeed(float Vx, float Vy) {
		this->vx = Vx;
		this->vy = Vy;
	}
	void Render()
	{
		if (type == BACKGROUND_TYPE)
		{
			if (CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_TYPE))
				CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_TYPE)->Draw(256 / 2, 224 / 2 + 8);
		}
		else if (type == CURTAIN_TYPE)
		{
			if (CSprites::GetInstance()->Get(ID_SPRITE_CURTAIN_TYPE))
				CSprites::GetInstance()->Get(ID_SPRITE_CURTAIN_TYPE)->Draw(256 / 2,y +( 187 / 2 + 8));
		}
		else if (type == MARIO_BROS3_BLACK_TYPE)
		{
			if (CSprites::GetInstance()->Get(ID_SPRITE_MARIO_BROS3_BLACK_TYPE))
				CSprites::GetInstance()->Get(ID_SPRITE_MARIO_BROS3_BLACK_TYPE)->Draw(256 / 2, y + 8);
		}
	}
};

