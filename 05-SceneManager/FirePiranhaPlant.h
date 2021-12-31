#pragma once
#include "GameObject.h"
#include "FireBullet.h"

#define FIRE_PIRANHAPLANT_UP_HEIGHT 16
#define FIRE_PIRANHAPLANT_ATTACK_ZONE 100

#define FIRE_PIRANHAPLANT_BBOX_WIDTH 16
#define FIRE_PIRANHAPLANT_BBOX_HEIGHT 34

#define GREEN_PIRANHAPLANT_BBOX_HEIGHT 26

#define MAX_ATTACK_ZONE	150
#define MIN_ATTACK_ZONE	100

#define FIRE_PIRANHAPLANT_STATE_UP	1
#define FIRE_PIRANHAPLANT_STATE_DOWN	2

#define ID_ANI_FIREPLANT_LEFT_DOWN		210000
#define ID_ANI_FIREPLANT_RIGHT_DOWN		210001
#define ID_ANI_FIREPLANT_LEFT_UP		210002
#define ID_ANI_FIREPLANT_RIGHT_UP		210003

#define ID_ANI_FIREPLANT_ATTACK_LEFT_DOWN		210004
#define ID_ANI_FIREPLANT_ATTACK_RIGHT_DOWN		210005
#define ID_ANI_FIREPLANT_ATTACK_LEFT_UP			210006
#define ID_ANI_FIREPLANT_ATTACK_RIGHT_UP		210007

#define ID_ANI_GREEN_FIREPLANT_LEFT_DOWN		230000
#define ID_ANI_GREEN_FIREPLANT_RIGHT_DOWN		230001
#define ID_ANI_GREEN_FIREPLANT_LEFT_UP		230002
#define ID_ANI_GREEN_FIREPLANT_RIGHT_UP		230003

#define ID_ANI_GREEN_FIREPLANT_ATTACK_LEFT_DOWN		230004
#define ID_ANI_GREEN_FIREPLANT_ATTACK_RIGHT_DOWN		230005
#define ID_ANI_GREEN_FIREPLANT_ATTACK_LEFT_UP			230006
#define ID_ANI_GREEN_FIREPLANT_ATTACK_RIGHT_UP		230007

#define FIREPLANT				1
#define GREEN_FIRE_PLANT		2

#define VX_BULLET	0.05f
#define VY_BULLET_MARIO_CLOSE	0.03f
#define VY_BULLET_MARIO_FAR	0.05f

class FirePiranhaPlant :
    public CGameObject
{
public:
	float ax;
	float ay;
	int aniId;

	bool isInPipe;

	int PlantType;

	float minY, maxY;

	bool isAttack;
	FireBullet* fireBullet;
	float enemyX, enemyY;
	ULONGLONG CalcAtkTime;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
	
	void CalcAtatckEnemy() {
		if (abs(x - enemyX) <= MAX_ATTACK_ZONE && abs(y - enemyY) <= MAX_ATTACK_ZONE)
		{
			CreateFireBullet();
		}
	}
	void CreateFireBullet()
	{
		float VxBullet, VyBullet,BulletX,BulletY;
		if (abs(x - enemyX) <= MIN_ATTACK_ZONE)
		{
			if (enemyY < y)
				VyBullet = -VY_BULLET_MARIO_FAR;
			else
				VyBullet = VY_BULLET_MARIO_FAR;
		}
		else
		{
			if (enemyY < y)
				VyBullet = -VY_BULLET_MARIO_CLOSE;
			else
				VyBullet = VY_BULLET_MARIO_CLOSE;
		}
		if (enemyX > x)
		{
			VxBullet = VX_BULLET;
			nx = 1;
			float bulletX = x + FIRE_PIRANHAPLANT_BBOX_WIDTH / 2;
			BulletX = bulletX;
		}
		else
		{
			VxBullet = -VX_BULLET;
			nx = -1;
			BulletX = x - (float)FIRE_PIRANHAPLANT_BBOX_WIDTH / 2;
		}
		BulletY = (float)minY - 8;
		if (!fireBullet->isActivate)
		{
			fireBullet->isActivate = true;
			fireBullet->SetPosition(BulletX, BulletY);
			fireBullet->SetSpeed(VxBullet, VyBullet);
		}
	}

	void GetAniFirePlant();
	void GetAniGreenFirePlant();
public:
	void GetEnemyPos(float EnemyX, float EnemyY) {
		enemyX = EnemyX;
		enemyY = EnemyY;
		
	}
	FirePiranhaPlant(float x, float y, int type) :CGameObject(x, y) {
		SetState(FIRE_PIRANHAPLANT_STATE_UP);
		fireBullet = new FireBullet(x, y);
		enemyX = enemyY = 0;
		PlantType = type;
		if (PlantType == FIREPLANT)
		{
			minY = y - FIRE_PIRANHAPLANT_UP_HEIGHT * 2 - FIRE_PIRANHAPLANT_UP_HEIGHT/2;
			maxY = y + FIRE_PIRANHAPLANT_UP_HEIGHT - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
		}
		else {
			minY = y - FIRE_PIRANHAPLANT_UP_HEIGHT * 2 - FIRE_PIRANHAPLANT_UP_HEIGHT / 4;
			maxY = y + FIRE_PIRANHAPLANT_UP_HEIGHT - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
		}
		isInPipe = true;
	};
	virtual void SetState(int state);
};

