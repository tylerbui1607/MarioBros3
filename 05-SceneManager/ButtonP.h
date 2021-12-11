#pragma once
#include "GameObject.h"

#define OBJTYPE_BUTTON_P	16
#define BUTTON_SIZE	16

#define BUTTON_P_STATE_PUSHED 1

#define BUTTON_PUSHED_HEIGHT	7
class ButtonP :
    public CGameObject
{
public:
	static ButtonP* __instance;

	static ButtonP* GetInstance()
	{
		if (__instance == NULL) __instance = new ButtonP();
		return __instance;
	}
	ButtonP() ;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void SetState(int state);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }

public:
	bool isPushed;
	bool isCreated;
};

