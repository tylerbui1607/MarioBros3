#pragma once
#include "GameObject.h"
#define LAST_ITEM_BBOX_SIZE 16

#define LAST_ITEM_IS_MUSHROOM 1
#define LAST_ITEM_IS_FLOWER 2
#define LAST_ITEM_IS_STAR 3

#define ID_ANI_LAST_ITEM	17072002
class LastItemObject :
    public CGameObject
{
public:
	int LastItemType;
	bool IsChosen;
	int IsBlocking() { return 0; };
	LastItemObject(float x, float y) : CGameObject(x, y) {
		LastItemType = 0;
		IsChosen = false;
	}
	void Render() {
		if (!IsChosen)
		{
			int aniId = ID_ANI_LAST_ITEM;
			CAnimations* animations = CAnimations::GetInstance();
			if (animations->Get(aniId))
				animations->Get(aniId)->Render(x, y);
		}
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - LAST_ITEM_BBOX_SIZE / 2;
		t = y - LAST_ITEM_BBOX_SIZE / 2;
		r = l + LAST_ITEM_BBOX_SIZE;
		b = t + LAST_ITEM_BBOX_SIZE;
	};

	void SetState(int state) {
	}
};

