#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_SMALL_COIN 90000
#define ID_ANI_BIG_COIN 80005

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define SMALL_COIN	1
#define BIG_COIN	2

class CCoin : public CGameObject {
	int coinType = 1;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		coinType = SMALL_COIN;
	}
	CCoin(float X, float Y, int type)
	{
		x = X;
		y = Y;
		coinType = type;
	}
	void Render();
	void Update(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};