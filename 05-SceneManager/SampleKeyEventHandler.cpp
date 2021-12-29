#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (CGame::GetInstance()->current_scene != 1)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetState() != MARIO_STATE_TRANSFORM_RACOON && mario->GetState() != RACOON_STATE_TRANSFORM_MARIO)
		{
			switch (KeyCode)
			{
			case DIK_DOWN:
				if (!mario->canGotoHiddenMap)
				{
					if (mario->GetMarioLevel() > MARIO_LEVEL_SMALL && !mario->CheckMarioHoldKoopas())
						mario->SetState(MARIO_STATE_SIT);
				}
				else {
					mario->SetState(MARIO_STATE_GO_IN_HIDDEN_MAP);
				}
				break;
			case DIK_S:
					if (mario->GetMarioLevel() == MARIO_LEVEL_RACOON && mario->GetSpeedStack() == MARIO_MAX_SPEED_STACK)
					{
						mario->SetState(MARIO_STATE_FLYING);
					}
					if (!mario->isFlying)
					{
						if (mario->CheckMarioIsOnPlatform())
							mario->SetState(MARIO_STATE_JUMP);
						else if (mario->GetMarioLevel() == MARIO_LEVEL_RACOON)
						{
							mario->SetState(MARIO_STATE_SLOW_FALLING);
						}
					}
				break;
			case DIK_1:
				mario->SetLevel(MARIO_LEVEL_SMALL);
				break;
			case DIK_2:
				mario->SetLevel(MARIO_LEVEL_BIG);
				break;
			case DIK_3:
				mario->SetLevel(MARIO_LEVEL_RACOON);
				break;
			case DIK_0:
				mario->SetState(MARIO_STATE_DIE);
				break;
			case DIK_A:
				mario->SetState(MARIO_STATE_ATTACK);
				break;
			case DIK_H:
				mario->SetState(MARIO_STATE_GO_IN_HIDDEN_MAP);
				break;
			case DIK_R:
				mario->Reset();
				break;
			case DIK_L:
				CGame::GetInstance()->resetLastItem = true;
				break;
			}
		}
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	if (CGame::GetInstance()->current_scene != 1)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetState() != MARIO_STATE_TRANSFORM_RACOON && mario->GetState() != RACOON_STATE_TRANSFORM_MARIO)
		{
			switch (KeyCode)
			{
			case DIK_S:
				if(!mario->isOnPlatform)
				mario->SetState(MARIO_STATE_RELEASE_JUMP);
				break;
			case DIK_DOWN:
				if (mario->CheckIsSitting())
					mario->SetState(MARIO_STATE_SIT_RELEASE);
				break;
			case DIK_A:
				if (mario->CheckMarioHoldKoopas())
					mario->SetState(MARIO_STATE_RELEASE_KOOPAS);
				break;
			}
		}
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	if (game->current_scene != 1)
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetState() != MARIO_STATE_TRANSFORM_RACOON && mario->GetState() != RACOON_STATE_TRANSFORM_MARIO)
		{
			if (game->IsKeyDown(DIK_RIGHT))
			{
				if (game->IsKeyDown(DIK_A) && !mario->CheckIsFlying())
				{
					mario->SetState(MARIO_STATE_RUNNING_RIGHT);
				}
				else
					mario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
			else if (game->IsKeyDown(DIK_LEFT))
			{
				if (game->IsKeyDown(DIK_A) && mario->CheckMarioIsOnPlatform())
					mario->SetState(MARIO_STATE_RUNNING_LEFT);
				else
					mario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			else if (game->IsKeyDown(DIK_UP)) {
				if (mario->canGotoHiddenMap)
				{
					mario->SetState(MARIO_STATE_GO_OUT_HIDDEN_MAP);
				}
			}
			else
				mario->SetState(MARIO_STATE_IDLE);
		}
	}
}