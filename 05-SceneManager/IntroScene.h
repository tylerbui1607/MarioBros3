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
#define SequencePlusTime	1500

#define START_RENDER_X 128
#define START_RENDER_Y 94
#define START_RENDER_Y_CHOOSEPLAYER 154
#define START_RENDER_Y_NUMBER 124
#define START_RENDER_Y_BACKGROUND 120

#define CURTAIN_SPEED 0.07f
#define MARIO_BROS_3_BLACK_SPEED 0.25f
#define GREENMARIO_JUMP_SPEED	0.5f
#define GREENMARIO_SPEED_VX_RUN_OUT_SCENE	0.02f
#define REDMARIO_MAXVX	0.15f

#define POINT_TO_JUMP_REDMARIO	150
#define REDMARIO_JUMP_SPEED	0.5f

#define GREENMARIO_OUT_SCENE_X	24
#define GREENMARIO_OUT_SCENE_Y	180

#define SECTION_2	2
#define SECTION_4	4

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
	ObjectForRender* background = new ObjectForRender(START_RENDER_X, START_RENDER_Y_BACKGROUND, BACKGROUND_TYPE);
	ObjectForRender* curtain = new ObjectForRender(START_RENDER_X, START_RENDER_Y , CURTAIN_TYPE);
	ObjectForRender* BlackMariobros3 = new ObjectForRender(START_RENDER_X, -START_RENDER_Y , MARIO_BROS3_BLACK_TYPE);
	ObjectForRender* MainMariobros3 = new ObjectForRender(START_RENDER_X, START_RENDER_Y, MARIO_BROS3_MAIN_TYPE);
	ObjectForRender* NumberMariobros3 = new ObjectForRender(START_RENDER_X, START_RENDER_Y_NUMBER, MARIO_BROS3_NUMBER_TYPE);
	ObjectForRender* ChoosePlayerMariobros3 = new ObjectForRender(START_RENDER_X, START_RENDER_Y_CHOOSEPLAYER, MARIO_BROS3_CHOOSE_PLAYER_TYPE);
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
			curtain->setSpeed(0, -CURTAIN_SPEED);
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
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + SequencePlusTime && !isFirstJump)
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
			//set black mario bros 3 fall down
			if (redMario->x >= CGame::GetInstance()->GetBackBufferWidth() / 2 && vy >= 0)
			{
				BlackMariobros3->setSpeed(0, MARIO_BROS_3_BLACK_SPEED);
				leaf->IsAllowUpdate = true;
				leaf->IsAllowRender = true;
			}
			if (leaf->y > START_RENDER_Y && leaf->x < CGame::GetInstance()->GetBackBufferWidth() && i == 1)
			{
				greenMario->SetState(MARIO_STATE_SIT_RELEASE);
				greenMario->SetState(MARIO_STATE_IDLE);
				greenMario->SetSpeed(0, -GREENMARIO_JUMP_SPEED);
				i = 2;
			}
			if (redMario->x >= CGame::GetInstance()->GetBackBufferWidth() / 2) {
				if (redMario->y >= POINT_TO_JUMP_REDMARIO)
				{
					redMario->SetMaxVx(REDMARIO_MAXVX);
					redMario->SetSpeed(REDMARIO_MAXVX, -REDMARIO_JUMP_SPEED);
				}
			}
			if (greenMario->GetMarioLevel() == MARIO_LEVEL_RACOON && !greenMario->CheckMarioIsOnPlatform() && i < SECTION_4)
			{
				if (i == SECTION_2)
				{
					greenMario->SetSpeed(-GREENMARIO_SPEED_VX_RUN_OUT_SCENE, 0);
					i++;
				}
				if (greenMario->y >= GREENMARIO_OUT_SCENE_Y)
				{
					i++;
					greenMario->SetState(MARIO_STATE_WALKING_RIGHT);
				}
				else 
					greenMario->SetState(MARIO_STATE_SLOW_FALLING);
			}
			if (greenMario->x > CGame::GetInstance()->GetBackBufferWidth() + GREENMARIO_OUT_SCENE_X)
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