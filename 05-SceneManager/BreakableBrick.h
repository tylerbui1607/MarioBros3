#pragma once
#include "GameObject.h"
class BreakableBrick :
    public CGameObject
{
public:
	int startY;
	bool readyInnitItem;
	bool innitItemSuccess;
	int Item;
	CCoin* coin;
	bool InitCoin;
	DWORD coinUpTime;

	QuestionBrick(float x, float y, int item) : CGameObject(x, y) {
		startY = y;
		InitCoin = readyInnitItem = innitItemSuccess = false;
		Item = item;
		coinUpTime = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {

		if (startY - y >= QUESTION_BRICK_UP)
			vy = -vy;
		if (vy > 0 && y >= startY) {
			SetState(QUESTION_BRICK_STATE_INNITED);
		}
		if (InitCoin)
		{
			if (coinUpTime == 0)
			{
				coin = new CCoin(x, y - 16);
				coin->SetSpeed(0, -COIN_UP_VY);
				coinUpTime = GetTickCount64();
			}
			else if (GetTickCount64() - coinUpTime >= 700) {
				coinUpTime = 0;
				InitCoin = false;
			}
			coin->Update(dt);
		}

		if (!readyInnitItem)y += vy * dt;

	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;

	};

	void SetState(int state) {
		switch (state) {
		case QUESTION_BRICK_STATE_START_INNIT:
			if (vy == 0)
				vy = -QUESTION_BRICK_VY;
			break;
		case QUESTION_BRICK_STATE_INNITED:
			vy = 0;
			y = startY;
			readyInnitItem = true;
			break;
		default:break;
		}
	}
};

