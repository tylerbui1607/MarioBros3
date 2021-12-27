#include "HUD.h"
#include "debug.h"
#include "Animations.h"
HUD* HUD::__instance = NULL;

void HUD::Draw()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_HUD)->Draw(Camera::GetInstance()->cam_x + 126, Camera::GetInstance()->cam_y+216);
	if (speedStack)
	{
		if (!MarioIsFlying) {
			for (int i = 0; i < speedStack; i++)
			{
				float startX = 62 + i * 8;
				if (i == 6)
					sprites->Get(ID_SPEED_STACK_P)->Draw(Camera::GetInstance()->cam_x + startX + 4, Camera::GetInstance()->cam_y + 210);
				else
					sprites->Get(ID_SPEED_STACK)->Draw(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + 210);
			}
		}
		else
		{
			CAnimations* animations = CAnimations::GetInstance();
			for (int i = 0; i < speedStack; i++)
			{
				float startX = 62 + i * 8;
				if (i == 6)
					animations->Get(ID_ANI_SPEEDSTACK_MAX_P)->Render(Camera::GetInstance()->cam_x + startX + 4, Camera::GetInstance()->cam_y + 210);
				else
					animations->Get(ID_ANI_SPEEDSTACK_MAX)->Render(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + 210);
			}
		}
	}
}
