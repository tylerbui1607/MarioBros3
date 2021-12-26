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
#define Sequence1MaxTime	2000

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
	CMario* redMario = new CMario(0, 0);
	CMario* greenMario = new CMario(0, 0);
	CPlatform* platform = new CPlatform(8,424,16,16,39,51000,52000,53000);
	DWORD SequenceTime;
	IntroScene(int id, LPCWSTR filePath);
	bool isDoneSeq1,isDoneSeq2, isFirstJump;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void ScriptIntro()
	{
		if (SequenceTime == 0)
			SequenceTime = GetTickCount64();
		if (!isDoneSeq1)
		{
			if(GetTickCount64()-SequenceTime >= Sequence1MaxTime )
			isDoneSeq1 = true;
		}
		if (isDoneSeq1 && !isDoneSeq2)
		{
			
			redMario->SetState(MARIO_STATE_WALKING_RIGHT);
			greenMario->SetState(MARIO_STATE_WALKING_LEFT);
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 2000 && !isFirstJump)
			{
				redMario->SetState(MARIO_STATE_JUMP);
				isFirstJump = true;
			}
			redMario->IsAllowRender = true;
			greenMario->IsAllowRender = true;
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 1500)
			{
				redMario->IsAllowUpdate = true;
				greenMario->IsAllowUpdate = true;
			}
		}
	}
	void Clear();
	void PurgeDeletedObjects();

};

typedef IntroScene* LPINTROSCENE;