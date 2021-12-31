#include "HUD.h"
#include "debug.h"
#include "Animations.h"
HUD* HUD::__instance = NULL;

void HUD::Draw()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_HUD)->Draw(Camera::GetInstance()->cam_x + HUD_X, Camera::GetInstance()->cam_y + HUD_Y);
	if (speedStack)
	{
		if (!MarioIsFlying) {
			for (int i = 0; i < speedStack; i++)
			{
				float startX = HUD_START_SPEED_STACK_X + i * 8;
				if (i == 6)
					sprites->Get(ID_SPEED_STACK_P)->Draw(Camera::GetInstance()->cam_x + startX + 4, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
				else
					sprites->Get(ID_SPEED_STACK)->Draw(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
			}
		}
		else
		{
			CAnimations* animations = CAnimations::GetInstance();
			for (int i = 0; i < speedStack; i++)
			{
				float startX = HUD_START_SPEED_STACK_X + (float)i * 8;
				if (i == 6)
					animations->Get(ID_ANI_SPEEDSTACK_MAX_P)->Render(Camera::GetInstance()->cam_x + startX + 4, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
				else
					animations->Get(ID_ANI_SPEEDSTACK_MAX)->Render(Camera::GetInstance()->cam_x + startX, Camera::GetInstance()->cam_y + HUD_SPEED_STACK_Y);
			}
		}
	}
}
