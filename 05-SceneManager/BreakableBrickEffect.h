#pragma once
#include "GameObject.h"
#define ID_ANI_EFFECT_BREALABLE_BRICK	10003
class BreakableBrickEffect
{
protected:
	float x, y, vx, vy;
public:

	BreakableBrickEffect(float X, float Y, float Vx, float Vy)
	{
		x = X;
		y = Y;
		vx = Vx;
		vy = Vy;
	}
	void Update(DWORD dt)
	{
		vy += 0.001f *dt;
		x += vx * (float)dt;
		y += vy * (float)dt;
	}
	void Render() {
		CAnimations* animations = CAnimations::GetInstance();
		int aniId = ID_ANI_EFFECT_BREALABLE_BRICK;
		animations->Get(aniId)->Render(x, y);
	}
};

