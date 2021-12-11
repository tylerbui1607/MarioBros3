#include "MarioTail.h"
#include "Goomba.h"
#include "QuestionBrick.h"
#include "Koopas.h"
#include "BreakableBrick.h"
void MarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = x + TAIL_BBOX_WIDTH;
	bottom = y + TAIL_BBOX_HEIGHT;
}

void MarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			if (dynamic_cast<CGoomba*>(coObjects->at(i)))
				OnCollisionWithGoomba(coObjects->at(i));
			else if (dynamic_cast<QuestionBrick*>(coObjects->at(i)))
				OnCollisionWithQuestionBrick(coObjects->at(i));
			else if (dynamic_cast<Koopas*>(coObjects->at(i)))
				OnCollisionWithKoopas(coObjects->at(i));
			else if (dynamic_cast<BreakableBrick*>(coObjects->at(i)))
				OnCollisionWithBreakableBrick(coObjects->at(i));
		}
	}
}

void MarioTail::Render()
{
	RenderBoundingBox();
}

void MarioTail::OnCollisionWithGoomba(LPGAMEOBJECT& obj)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(obj);
	goomba->SetState(GOOMBA_STATE_DIEBYSHELL);
}

void MarioTail::OnCollisionWithQuestionBrick(LPGAMEOBJECT& obj)
{
	QuestionBrick* qbrick = dynamic_cast<QuestionBrick*>(obj);
	if (!qbrick->innitItemSuccess) {
		qbrick->SetState(QUESTION_BRICK_STATE_START_INNIT);
	}
}

void MarioTail::OnCollisionWithKoopas(LPGAMEOBJECT& obj)
{
	Koopas* koopas = dynamic_cast<Koopas*>(obj);
	koopas->nx = nx;
	koopas->SetState(KOOPAS_STATE_ATTACKED_BY_TAIL);
}

void MarioTail::OnCollisionWithBreakableBrick(LPGAMEOBJECT& obj)
{
	BreakableBrick* breakableBrick = dynamic_cast<BreakableBrick*>(obj);
	if (breakableBrick->haveButton && !breakableBrick->buttonCreated)
	{
		breakableBrick->SetState(BREAKABLE_BRICK_STATE_CREATE_BUTTON);
	}
	else if (!breakableBrick->haveButton) {
		obj->Delete();
	}
}
