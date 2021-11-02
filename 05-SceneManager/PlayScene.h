#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Item.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> Bricks;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void AddItemToQBrick(LPGAMEOBJECT obj) {
		QuestionBrick* QBrick = dynamic_cast<QuestionBrick*>(obj);
		CMario* mario = dynamic_cast<CMario*>(player);
		float BrickX, BrickY;
		obj->GetPosition(BrickX, BrickY);

		if (QBrick->readyInnitItem )
		{
			if (mario->GetMarioLevel() < MARIO_LEVEL_BIG)
			{
				Mushroom* mushroom = new Mushroom(BrickX, BrickY);
				mushroom->SetState(MUSHROOOM_STATE_BEING_INNITED);
				objects.push_back(mushroom);
				QBrick->innitItemSuccess = true;
			}
		}
	}

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

