#pragma once

#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"

#define ID_SPRITE_HUD	170720
#define ID_SPEED_STACK	170721
#define ID_SPEED_STACK_P	170722

#define ID_ANI_SPEEDSTACK_MAX	17072000
#define ID_ANI_SPEEDSTACK_MAX_P	17072001


#define HUD_X	126
#define HUD_Y	216
#define HUD_SPEED_STACK_Y	210
#define HUD_START_SPEED_STACK_X	62.0f
class HUD
{
public:

	static HUD* __instance;

	static HUD* GetInstance()
	{
		if (__instance == NULL) __instance = new HUD();
		return __instance;
	}
public:
	float x = 0, y = 0;
	bool MarioIsFlying;
	int speedStack;
	HUD() {
		speedStack = 0;
		MarioIsFlying = false;
	};
	~HUD();
	void Draw();
	void setPos(float X, float Y) {
		x = X;
		y = Y;
	}
};

