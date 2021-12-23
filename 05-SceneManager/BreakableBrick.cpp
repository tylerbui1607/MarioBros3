#include "BreakableBrick.h"

void BreakableBrick::Render()
{
	int aniId = -1;
	CAnimations* animations = CAnimations::GetInstance();
	if (state == BREAKABLE_BRICK_STATE_BREAK_DOWN)
	{
		piece1->Render();
		piece2->Render();
		piece3->Render();
		piece4->Render();
	}
	else if (objType == OBJECT_TYPE_COIN)
	{
		aniId = ID_ANI_COIN;
		animations->Get(aniId)->Render(x, y);
	}
	else {
		aniId = ID_ANI_BREAKABLE_BRICK;
		if (buttonCreated)
			aniId = ID_ANI_BREAKABLE_BRICK_IS_UP;
		animations->Get(aniId)->Render(x, y);
	}
	
}
