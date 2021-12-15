#include "HUD.h"
#include "debug.h"

HUD* HUD::__instance = NULL;

void HUD::Draw()
{
	DebugOut(L"HudX%f HudY%f\n", x, y);
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_HUD)->Draw(Camera::GetInstance()->cam_x + 126, Camera::GetInstance()->cam_y+216);
	if (speedStack)
	{
		for (int i = 0; i < speedStack; i++)
		{
			float startX = 62 + i * 8;
			sprites->Get(ID_SPEED_STACK)->Draw(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + 210);
		}
	}
}
