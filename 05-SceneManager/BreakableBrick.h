#pragma once
#include "GameObject.h"
#include "Coin.h"
#include "ButtonP.h"

#define BRICK_BBOX_WIDTH	16
#define BRICK_BBOX_HEIGHT	16
#define BREAKABLE_BRICK_STATE_TRANSFORMS_COIN	1
#define BREAKABLE_BRICK_STATE_BREAK_DOWN	2
#define BREAKABLE_BRICK_STATE_CREATE_BUTTON	3
#define COIN_STATE_TRANSFORMS_BRICK	4

#define OBJECT_TYPE_BREAKABLE_BRICK	30
#define OBJECT_TYPE_COIN	31

#define ID_ANI_COIN 80005
#define ID_ANI_BREAKABLE_BRICK 

#define BREAKBLE_BRICK_VY	0.05f
class BreakableBrick :
    public CGameObject
{
public:
	int isBlocking;
	int startY;
	bool InitCoin;
	DWORD ChangeBackToBrickTime;
	bool haveButton;
	bool buttonCreated, isBreakDown;
	BreakableBrick(float x, float y, bool HaveButton) : CGameObject(x, y) {
		startY = y;
		haveButton = HaveButton;
		objType = OBJECT_TYPE_BREAKABLE_BRICK;
		buttonCreated = false;
		vy = 0;
		InitCoin = isBreakDown = false;
		isBlocking = 1; 
	}
	void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return isBlocking; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		y += vy * dt;
		if (startY - y >= 5 && vy < 0)
		{
			vy = -vy;
		}
		if (vy > 0 && y >= startY)
		{
			y = startY;
			vy = 0;
		}
		if (!haveButton)
		{
			if (ButtonP::GetInstance()->isPushed && !InitCoin)
			{
				SetState(BREAKABLE_BRICK_STATE_TRANSFORMS_COIN);
			}
		}
		if (InitCoin)
		{
			if (GetTickCount64() - ChangeBackToBrickTime >= 5000)
				SetState(COIN_STATE_TRANSFORMS_BRICK);
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		if (!isBreakDown)
		{
			l = x - BRICK_BBOX_WIDTH / 2;
			t = y - BRICK_BBOX_HEIGHT / 2;
			r = l + BRICK_BBOX_WIDTH;
			b = t + BRICK_BBOX_HEIGHT;
		}
	};

	void SetState(int state) {
		switch (state) {
		case BREAKABLE_BRICK_STATE_TRANSFORMS_COIN:
			objType = OBJECT_TYPE_COIN;
			ChangeBackToBrickTime = GetTickCount64();
			isBlocking = 0;
			InitCoin = true;
			break;
		case BREAKABLE_BRICK_STATE_BREAK_DOWN:
			isBreakDown = true;
			break;
		case BREAKABLE_BRICK_STATE_CREATE_BUTTON:
			buttonCreated = true;
			vy = -BREAKBLE_BRICK_VY;
			ButtonP::GetInstance()->SetPosition(x, y - BRICK_BBOX_HEIGHT);
			ButtonP::GetInstance()->isCreated = true;
			break;
		case COIN_STATE_TRANSFORMS_BRICK:
			objType = OBJECT_TYPE_BREAKABLE_BRICK;
			isBlocking = 1;
			break;
		default:break;
		}
		CGameObject::SetState(state);
	}
};

