#pragma once
#include "GameObject.h"
#include "FireBullet.h"

#define FIRE_PIRANHAPLANT_UP_HEIGHT 16


#define PIRANHAPLANT_BBOX_WIDTH 16
#define PIRANHAPLANT_BBOX_HEIGHT 24


#define PIRANHAPLANT_STATE_UP	1
#define PIRANHAPLANT_STATE_DOWN	2

#define ID_ANI_PLANT		220000


class PiranhaPlant :
	public CGameObject
{
public:
	float ax;
	float ay;
	int aniId;

	float minY, maxY;
	bool isInPipe;
	bool isAttack;
	ULONGLONG CalcAtkTime = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };

	void GetAniPlant();
public:

	PiranhaPlant(float x, float y) :CGameObject(x, y) {
		isInPipe = true;
		isAttack = false;
		minY = y - FIRE_PIRANHAPLANT_UP_HEIGHT - FIRE_PIRANHAPLANT_UP_HEIGHT/2;
		maxY = y + FIRE_PIRANHAPLANT_UP_HEIGHT - 12;
		SetState(PIRANHAPLANT_STATE_UP);
	};
	virtual void SetState(int state);
};

