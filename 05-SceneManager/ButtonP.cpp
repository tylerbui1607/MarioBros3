#include "ButtonP.h"
#include "debug.h"
ButtonP* ButtonP::__instance = NULL;
ButtonP::ButtonP()
{
	isPushed = false;
	objType = OBJTYPE_BUTTON_P;
}

void ButtonP::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isPushed)
	{
		top = y - BUTTON_PUSHED_HEIGHT / 2;
		bottom = top + BUTTON_PUSHED_HEIGHT;
	}
	else {
		top = y - BUTTON_SIZE / 2;
		bottom = top + BUTTON_SIZE;
	}
	left = x - BUTTON_SIZE / 2;
	right = left + BUTTON_SIZE;
}

void ButtonP::Update(DWORD dt)
{
	
}

void ButtonP::Render()
{
	if(isCreated)
	RenderBoundingBox();
	DebugOut(L"hello\n");
}

void ButtonP::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BUTTON_P_STATE_PUSHED:
		isPushed = true;
		y += (BUTTON_SIZE - BUTTON_PUSHED_HEIGHT) / 2;
		break;
	}
}
