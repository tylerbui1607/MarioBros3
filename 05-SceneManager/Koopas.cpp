#include "Koopas.h"
#include "debug.h"
#include "QuestionBrick.h"
#include "Goomba.h"
#include "BreakableBrick.h"
void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isHold)
	{
		if (state != KOOPAS_STATE_DIE_BY_SHELL)
		{
			if (!InShell) {
				top = y - KOOPAS_BBOX_HEIGHT / 2;
				bottom = top + KOOPAS_BBOX_HEIGHT;
			}
			else {
				top = y - KOOPAS_BBOX_HIDDEN / 2;
				bottom = top + KOOPAS_BBOX_HIDDEN;
			}
			left = x - KOOPAS_BBOX_WIDTH / 2;
			right = left + KOOPAS_BBOX_WIDTH;
		}
	}
}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	HandleKoopasDropOut();
	HandleKoopasReborn();
	if (!isHold)
	{
		vy += ay * dt;
		if (state == KOOPAS_STATE_WALKING && level == SMART_KOOPAS)
		{
			if (vx > 0)NavBox->SetPosition(x + KOOPAS_BBOX_WIDTH, y);
			else NavBox->SetPosition(x - KOOPAS_BBOX_WIDTH, y);
			NavBox->Update(dt, coObjects);
			float navX, navY;
			NavBox->GetPosition(navX, navY);
			if (navY - y >= KOOPAS_NAVBOX_DISTANCE)vx = -vx;

		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	else if(state == KOOPAS_STATE_ATTACKED_BY_TAIL) {
		SetState(KOOPAS_STATE_INSHELL);
	}
}

void Koopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	if (level == NORMAL_KOOPAS)GetKoopasAni(aniId);
	else if (level == SMART_KOOPAS)GetRedKoopasAni(aniId);
	else if (level == PARA_KOOPAS)GetParaKoopasAni(aniId);
	if(CAnimations::GetInstance()->Get(aniId))
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	else RenderBoundingBox();
	//NavBox->Render();
}

void Koopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Koopas::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		if (level == PARA_KOOPAS)
		{
			if (e->ny < 0)
				vy = -KOOPAS_JUMP_SPEED;
		}
		else {
			vy = 0;
			if (state == KOOPAS_STATE_ATTACKED_BY_TAIL)
			{
				SetState(KOOPAS_STATE_INSHELL);
			}
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		if (state != KOOPAS_STATE_ATTACKED_BY_TAIL)
		{
			vx = -vx;
			nx = -nx;
		}
	}
	if (dynamic_cast<QuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<Koopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (e->obj->objType == OBJECT_TYPE_BREAKABLE_BRICK)
		OnCollisionWithBreakableBrick(e);

}

void Koopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	QuestionBrick* QBrick = dynamic_cast<QuestionBrick*>(e->obj);

	//Check qbrick
	if (!QBrick->innitItemSuccess && state == KOOPAS_STATE_INSHELL_ATTACK) {
		if (e->nx != 0)QBrick->SetState(QUESTION_BRICK_STATE_START_INNIT);
	}
}

void Koopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPAS_STATE_INSHELL_ATTACK)
	{
		if (e->nx && goomba->GetState() != GOOMBA_STATE_DIEBYSHELL)
		{
			goomba->nx = nx;
			goomba->SetState(GOOMBA_STATE_DIEBYSHELL);
		}
	}
}

void Koopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	Koopas* koopas = dynamic_cast<Koopas*>(e->obj);
	if (koopas->state == KOOPAS_STATE_INSHELL_ATTACK) {
		if (e->nx || e->ny)
		SetState(KOOPAS_STATE_DIE_BY_SHELL);
	}
}

void Koopas::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
	BreakableBrick* breakBrick = dynamic_cast<BreakableBrick*>(e->obj);
	if (e->nx != 0 && state == KOOPAS_STATE_INSHELL_ATTACK && !breakBrick->haveButton)
	{
		breakBrick->SetState(BREAKABLE_BRICK_STATE_BREAK_DOWN);
	}
}

void Koopas::GetKoopasAni(int& IdAni)
{
	if (state == KOOPAS_STATE_WALKING)
	{
		if (vx > 0)IdAni = ID_ANI_KOOPAS_WALKING_RIGHT;
		else IdAni = ID_ANI_KOOPAS_WALKING_LEFT;
	}
	else if (state == KOOPAS_STATE_REBORN) IdAni = ID_ANI_KOOPAS_REBORN;
	else if (IsAttackedByTail)IdAni = ID_ANI_KOOPAS_ATTACKED_BY_TAIL;
	else if (state == KOOPAS_STATE_INSHELL || state == KOOPAS_STATE_DIE_BY_SHELL)IdAni = ID_ANI_KOOPAS_INSHELL;
	else if (state == KOOPAS_STATE_INSHELL_ATTACK)IdAni = ID_ANI_KOOPAS_INSHELL_ATTACK;
}

void Koopas::GetRedKoopasAni(int& IdAni)
{
	if (state == KOOPAS_STATE_WALKING)
	{
		if (vx > 0)IdAni = ID_ANI_REDKOOPAS_WALKING_RIGHT;
		else IdAni = ID_ANI_REDKOOPAS_WALKING_LEFT;
	}
	else if (state == KOOPAS_STATE_REBORN) IdAni = ID_ANI_REDKOOPAS_REBORN;
	else if (IsAttackedByTail)IdAni = ID_ANI_REDKOOPAS_ATTACKED_BY_TAIL;
	else if (state == KOOPAS_STATE_INSHELL || state == KOOPAS_STATE_DIE_BY_SHELL)IdAni = ID_ANI_REDKOOPAS_INSHELL;
	else if (state == KOOPAS_STATE_INSHELL_ATTACK)IdAni = ID_ANI_REDKOOPAS_INSHELL_ATTACK;
	
}

void Koopas::GetParaKoopasAni(int& IdAni)
{
	if (vx >= 0)IdAni = ID_ANI_KOOPAS_HAVE_WING_RIGHT;
	else IdAni = ID_ANI_KOOPAS_HAVE_WING_LEFT;
}

Koopas::Koopas(float x, float y, int Level):CGameObject(x,y)
{
	level = Level;
	SetState(KOOPAS_STATE_WALKING);
	NavBox = new NavigationBox(x, y);
	IsAttackedByTail = isHold = false;
	ay = KOOPAS_GRAVITY;
}

void Koopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		IsAttack = true;
		InShell = false;
		isHold = false;
		IsAttackedByTail = false;
		y -= (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HIDDEN) / 2;
		break;
	case KOOPAS_STATE_INSHELL:
		vx = 0;
		InShell = true;
		IsAttack = false;
		WaitingRebornTime = GetTickCount64();
		break;
	case KOOPAS_STATE_INSHELL_ATTACK:
		vx = nx*KOOPAS_WALKING_SPEED * 5;
		InShell = true;
		IsAttack = true;
		break;
	case KOOPAS_STATE_DIE_BY_SHELL:
		vx = nx * GOOMBA_DIEBYSHELL_VX;
		vy = -GOOMBA_DIEBYSHELL_VY;
		InShell = true;
		IsAttack = false;
		break;
	case KOOPAS_STATE_ATTACKED_BY_TAIL:
		vx = nx * GOOMBA_DIEBYSHELL_VX;
		vy = -GOOMBA_DIEBYSHELL_VY;
		InShell = true;
		IsAttack = false;
		IsAttackedByTail = true;
		break;
	case KOOPAS_STATE_REBORN:
		ReborningTime = GetTickCount64();
		break;
	default:
		break;
	}
}
