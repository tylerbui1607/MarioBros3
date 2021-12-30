#pragma once
#include "Game.h"
#include"Mario.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Coin.h"
#include "Platform.h"
#include "Camera.h"
#include "Map.h"
#include "ColorBox.h"
#include "Koopas.h"
#include "Pipe.h"
#include "BreakableBrick.h"
#include "PortalOfPipe.h"
#include "PiranhaPlant.h"
#include "ObjectForRender.h"
#include "Leaf.h"
#include "Goomba.h"
#define Sequence1MaxTime	1400

class IntroScene :
    public CScene
{
protected:
	// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;




	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);


	void LoadAssets(LPCWSTR assetFile);

public:
	CMario* redMario;
	CMario* greenMario;
	Leaf* leaf = new Leaf(256 / 2, -100);
	CGoomba* goomba = new CGoomba(256/2-52,-500,1);
	CPlatform* platform;
	ObjectForRender* background = new ObjectForRender(0,0,1);
	ObjectForRender* curtain = new ObjectForRender(0, 0, 2);
	ObjectForRender* BlackMariobros3 = new ObjectForRender(0, -188, 3);
	ULONGLONG SequenceTime;
	IntroScene(int id, LPCWSTR filePath);
	bool isDoneSeq1,isDoneSeq2, isFirstJump;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	int i = 1;
	void ScriptIntro()
	{
	
		if (SequenceTime == 0)
			SequenceTime = GetTickCount64();
		if (!isDoneSeq1)
		{
			if(GetTickCount64()-SequenceTime >= Sequence1MaxTime )
			isDoneSeq1 = true;
			curtain->setSpeed(0, -0.07f);
		}
		if (isDoneSeq1 && !isDoneSeq2)
		{
			float vx, vy;
			redMario->GetSpeed(vx, vy);
			if (vx == 0 && i == 1)
			{
				redMario->SetState(MARIO_STATE_WALKING_RIGHT);
				greenMario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 1500 && !isFirstJump)
			{
				redMario->SetState(MARIO_STATE_JUMP);
				isFirstJump = true;
			}
			redMario->IsAllowRender = true;
			greenMario->IsAllowRender = true;
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 1000)
			{
				redMario->IsAllowUpdate = true;
				greenMario->IsAllowUpdate = true;
			}
			if (greenMario->x <= CGame::GetInstance()->GetBackBufferWidth() / 2 && i == 1)
			{
				if(!greenMario->CheckIsSitting() && i== 1)
				greenMario->SetState(MARIO_STATE_SIT);
			}
			if (redMario->x >= CGame::GetInstance()->GetBackBufferWidth() / 2 && vy >= 0)
			{
				BlackMariobros3->setSpeed(0, 0.25f);
				leaf->IsAllowUpdate = true;
				leaf->IsAllowRender = true;
				goomba->IsAllowRender = true;
				goomba->IsAllowUpdate = true;
			}
			if (leaf->y > 96 && i == 1)
			{
				if (greenMario->y > 170)
				{
					greenMario->SetState(MARIO_STATE_SIT_RELEASE);
					greenMario->SetState(MARIO_STATE_IDLE);
					greenMario->SetSpeed(0, -0.40f);
				}
				i = 2;
			}
			if (redMario->x >= CGame::GetInstance()->GetBackBufferWidth() / 2 - 10) {
				if (redMario->y >= 180 - 30)
				{
					redMario->SetMaxVx(0.15f);
					redMario->SetSpeed(0.15f, -0.5f);
				}
			}
			if (greenMario->GetMarioLevel() == MARIO_LEVEL_RACOON && !greenMario->CheckMarioIsOnPlatform() && i < 4)
			{
				if (i == 2)
				{
					greenMario->SetSpeed(-0.02f, 0);
					i++;
				}
				if (greenMario->y >= 168)
				{
					i++;
					greenMario->SetState(MARIO_STATE_WALKING_RIGHT);
				}
				else 
					greenMario->SetState(MARIO_STATE_SLOW_FALLING);
			}
			if (greenMario->x > CGame::GetInstance()->GetBackBufferWidth() + 24)
			{
				isDoneSeq2 = true;
			}
		}
		if (isDoneSeq2)
			CGame::GetInstance()->InitiateSwitchScene(2);
	}
	void Clear();
	void PurgeDeletedObjects();

};

typedef IntroScene* LPINTROSCENE;