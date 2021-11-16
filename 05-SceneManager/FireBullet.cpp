#include "FireBullet.h"
#include "Mario.h"

void FireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBULLET_BBOX_WIDTH / 2;
	top = y - FIREBULLET_BBOX_HEIGHT / 2;
	right = left + FIREBULLET_BBOX_WIDTH;
	bottom = top + FIREBULLET_BBOX_WIDTH;
}

void FireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	if (!Camera::GetInstance()->IsInCam(x, y))isActivate = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBullet::Render()
{
	RenderBoundingBox();
}

void FireBullet::OnNoCollision(DWORD dt)
{
}

void FireBullet::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
	if (e->nx || e->ny) {
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		if (mario->GetMarioLevel() == MARIO_LEVEL_BIG) {
			if (mario->untouchable == 0)
			{
				mario->SetLevel(MARIO_LEVEL_SMALL);
				mario->StartUntouchable();
			}
		}
		else if (mario->untouchable == 0)
			mario->SetState(MARIO_STATE_DIE);
	}
}

void FireBullet::SetState(int state)
{
}
