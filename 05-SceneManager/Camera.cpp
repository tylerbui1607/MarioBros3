#include "Camera.h"
#include "Camera.h"
#include "Game.h"
#include "debug.h"
Camera* Camera::__instance = NULL;
Camera::Camera()
{
	cam_y = CAM_Y_SCENE_1_1;
	cam_vy = 0.0;
	MarioIsOnPlatForm = MarioIsFlying = MarioIsInHiddenMap = false;
	MarioX = MarioY = Mariovx = Mariovy = cam_x = cam_vx = 0;
}



void Camera::Update(DWORD dt)
{
	float cx, cy;
	
	cx = MarioX;
	cy = MarioY;

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	if (CGame::GetInstance()->current_scene != 1)
	{
		if (cx < 0) cx = 0;
		if (cx + game->GetBackBufferWidth() >= 2816.0f)cx = 2816.0f - game->GetBackBufferWidth();
		if (!MarioIsInHiddenMap)
		{
			if (MarioIsFlying)
			{
				if (MarioY - CGame::GetInstance()->GetBackBufferHeight() / 2 < CAM_Y_SCENE_1_1)
				{
					if (MarioY - CGame::GetInstance()->GetBackBufferHeight() / 2 < 50)
					{
						Camera::GetInstance()->cam_y = 50;
						cam_vy = 0;
					}
					else if (!MarioIsOnPlatForm)
					{
						Camera::GetInstance()->cam_vy = Mariovy;
					}
					else {
						cam_vy = 0;
					}
				}
				else { Camera::GetInstance()->cam_y = CAM_Y_SCENE_1_1; cam_vy = 0; }
				Camera::GetInstance()->SetCamPosX(cx);
			}
			else
			{
				if (cam_y < 240)
				{
					if (MarioY - CGame::GetInstance()->GetBackBufferHeight() / 2 < 50)
					{
						Camera::GetInstance()->cam_y = 50;
						cam_vy = 0;
					}
					else if (!MarioIsOnPlatForm && Mariovy > 0)
					{
						Camera::GetInstance()->cam_vy = Mariovy;
					}
					else
					{
						cam_vy = 0;
					}
					Camera::GetInstance()->SetCamPosX(cx);
				}
				else {
					Camera::GetInstance()->SetCamPos(cx, CAM_Y_SCENE_1_1);
					cam_vy = 0;
				}
			}
		}
		else {
			Camera::GetInstance()->SetCamPos(cx, CAM_Y_HIDDEN_SCENE);
		}
	}
	else
	{
		Camera::GetInstance()->SetCamPos(0, 0);
	}
	cam_y += cam_vy * dt;
}
