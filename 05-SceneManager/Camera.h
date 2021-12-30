#pragma once
#include <Windows.h>
#include "Utils.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
class Camera
{
public:
	float Mariovx, Mariovy=0, MarioX, MarioY;
	float cam_x, cam_y, cam_vx, cam_vy =0;
	int AutoMove = 0;
	bool MarioIsOnPlatForm, MarioIsFlying, MarioIsInHiddenMap;
public:

	static Camera* __instance;

	static Camera* GetInstance()
	{
		if (__instance == NULL) __instance = new Camera();
		return __instance;
	}
	Camera();



	void GetMarioInfo(float vx, float vy, float x, float y, bool isonplatform, bool isflying, bool IsInHiddenMap)
	{
		Mariovy = vy;
		MarioX = x;
		MarioY = y;
		MarioIsOnPlatForm = isonplatform;
		MarioIsFlying = isflying;
		MarioIsInHiddenMap = IsInHiddenMap;
	}
	bool IsInCam(float objX, float objY)
	{
		return !(objX < cam_x-100 || objX - cam_x>SCREEN_WIDTH+100 || objY < cam_y || objY - cam_y > SCREEN_HEIGHT);
	}
	void SetCamPos(float x, float y) {
		cam_x = x;
		cam_y = y;
	};	
	float GetCamPosX()
	{
		return cam_x;
	}
	float GetCamPosY()
	{
		return cam_y;
	}

	void GetCamPos(float& x, float& y) {
		x = cam_x;
		y = cam_y;
	}
	void FollowMario(float marrioVy) {
		cam_vy = Mariovy;
	}
	void SetCamPosX(float x)
	{
		cam_x = x;
	}
	void Update( DWORD dt);
};

