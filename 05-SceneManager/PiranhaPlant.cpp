#include "PiranhaPlant.h"

void PiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_UP:
		vy = -0.05f;
		CalcAtkTime = GetTickCount64();
		break;
	case PIRANHAPLANT_STATE_DOWN:
		vy = 0.05f;
		CalcAtkTime = GetTickCount64();
		break;
	default:
		break;
	}
}

	void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
		top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
		right = left + PIRANHAPLANT_BBOX_WIDTH;
		bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
	}

	void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		y += vy * dt;
		if (vy < 0) {
			if (y <= minY) {
				vy = 0;
				y = minY;
			}
		}
		else if (vy > 0) {
			if (y >= maxY) {
				vy = 0;
				y = maxY;
			}
		}
		
		if (state == PIRANHAPLANT_STATE_UP) {
			if (x == CGame::GetInstance()->pipeX && y > (minY + FIRE_PIRANHAPLANT_UP_HEIGHT + 8))
				vy = 0;
			else if (GetTickCount64() - CalcAtkTime >= 2000) {
				SetState(PIRANHAPLANT_STATE_DOWN);
			}
		}
		else {
			if (GetTickCount64() - CalcAtkTime >= 1000) {
				SetState(PIRANHAPLANT_STATE_UP);
			}
		}
	}

	void PiranhaPlant::Render()
	{
		int aniId = ID_ANI_PLANT;
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(aniId)->Render(x, y);
	}
