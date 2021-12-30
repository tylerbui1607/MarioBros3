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

#define START_RENDER_X 128
#define START_RENDER_Y 94
#define START_RENDER_Y_CHOOSEPLAYER 154
#define START_RENDER_Y_NUMBER 124
#define START_RENDER_Y_BACKGROUND 120

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
	Leaf* leaf = new Leaf(START_RENDER_X, -START_RENDER_Y*2);
	CPlatform* platform;
	ObjectForRender* background = new ObjectForRender(START_RENDER_X, START_RENDER_Y_BACKGROUND,1);
	ObjectForRender* curtain = new ObjectForRender(START_RENDER_X, START_RENDER_Y , 2);
	ObjectForRender* BlackMariobros3 = new ObjectForRender(START_RENDER_X, -START_RENDER_Y , 3);
	ObjectForRender* MainMariobros3 = new ObjectForRender(START_RENDER_X, START_RENDER_Y , 4);
	ObjectForRender* NumberMariobros3 = new ObjectForRender(START_RENDER_X, START_RENDER_Y_NUMBER, 5);
	ObjectForRender* ChoosePlayerMariobros3 = new ObjectForRender(START_RENDER_X, START_RENDER_Y_CHOOSEPLAYER, 6);
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
			curtain->isAllowRender = true;
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
			}
			if (leaf->y > START_RENDER_Y && leaf->x < CGame::GetInstance()->GetBackBufferWidth()+10 && i == 1)
			{
				greenMario->SetState(MARIO_STATE_SIT_RELEASE);
				greenMario->SetState(MARIO_STATE_IDLE);
				greenMario->SetSpeed(0, -0.50f);
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
				if (greenMario->y >= 180)
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
			if (BlackMariobros3->y >= START_RENDER_Y) {
				MainMariobros3->isAllowRender = true;
				NumberMariobros3->isAllowRender = true;
			}
		}
		if (CGame::GetInstance()->SkipIntro)
		{
			isDoneSeq2 = true;
			curtain->isAllowRender = leaf->IsAllowRender = greenMario->IsAllowRender = redMario->IsAllowRender = false;
			NumberMariobros3->isAllowRender = MainMariobros3->isAllowRender = true;
			isDoneSeq2 = true;
			ChoosePlayerMariobros3->isAllowRender = true;
		}
		if (isDoneSeq2)
		{
			CGame::GetInstance()->SkipIntro = true;
			ChoosePlayerMariobros3->isAllowRender = true;
		}
	}
	void Clear();
	void PurgeDeletedObjects();

};

typedef IntroScene* LPINTROSCENE;