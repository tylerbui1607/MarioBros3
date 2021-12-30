#pragma once
#include "GameObject.h"

#define FIREBULLET_BBOX_WIDTH	8
#define FIREBULLET_BBOX_HEIGHT	8

#define ID_ANI_FIREBULLET	1607200

class FireBullet :
    public CGameObject
{
public:


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	
	virtual void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);
public:
	bool isActivate;
	FireBullet(float x, float y) :CGameObject(x, y) {
		isActivate = false;
	};
	void SetState(int state);
};

