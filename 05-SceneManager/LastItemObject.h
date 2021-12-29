#pragma once
#include "GameObject.h"
#include "debug.h"
#define LAST_ITEM_BBOX_SIZE 16

#define LAST_ITEM_IS_MUSHROOM 1
#define LAST_ITEM_IS_FLOWER 2
#define LAST_ITEM_IS_STAR 3

#define ID_ANI_LAST_ITEM	17072002

#define ID_ANI_END_WORLD_TEXT_MUSHROOM	17072003
#define ID_ANI_END_WORLD_TEXT_FLOWER	17072004
#define ID_ANI_END_WORLD_TEXT_STAR	17072005
class LastItemObject :
    public CGameObject
{
public:
	int LastItemType;
	bool IsChosen;
	DWORD ChangeItemTime;
	int IsBlocking() { return 0; };
	LastItemObject(float x, float y) : CGameObject(x, y) {
		LastItemType = 0;
		IsChosen = false;
		ChangeItemTime = 0;
	}
	void Render() {
		if (!IsChosen)
		{
			int aniId = ID_ANI_LAST_ITEM;
			CAnimations* animations = CAnimations::GetInstance();
			if (animations->Get(aniId))
				animations->Get(aniId)->Render(x, y);
		}
		else if (IsChosen)
		{
			int aniId = ID_ANI_LAST_ITEM + LastItemType;
			CAnimations* animations = CAnimations::GetInstance();
			if (animations->Get(aniId))
				animations->Get(aniId)->Render(x, y - 52);
		}
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		if (!IsChosen)
		{
			if (ChangeItemTime == 0)
				ChangeItemTime = GetTickCount64();
			else if (GetTickCount64() - ChangeItemTime >= 100 && GetTickCount64() - ChangeItemTime < 200)
			{
				LastItemType = LAST_ITEM_IS_MUSHROOM;
			}
			else if (GetTickCount64() - ChangeItemTime >= 200 && GetTickCount64() - ChangeItemTime < 300)
			{
				LastItemType = LAST_ITEM_IS_FLOWER;
			}
			else if (GetTickCount64() - ChangeItemTime >= 300 && GetTickCount64() - ChangeItemTime < 400)
			{
				LastItemType = LAST_ITEM_IS_STAR;
				ChangeItemTime = 0;
			}
		}
		if (CGame::GetInstance()->resetLastItem)
		{
			CGame::GetInstance()->resetLastItem = IsChosen = false;
			ChangeItemTime = 0;
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		if (!IsChosen)
		{
			l = x - LAST_ITEM_BBOX_SIZE / 2;
			t = y - LAST_ITEM_BBOX_SIZE / 2;
			r = l + LAST_ITEM_BBOX_SIZE;
			b = t + LAST_ITEM_BBOX_SIZE;
		}
	};

	void SetState(int state) {
		
	}
};

