#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	if (mario->GetState() != MARIO_STATE_TRANSFORM_RACOON && mario->GetState() != RACOON_STATE_TRANSFORM_MARIO)
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			if(mario->GetMarioLevel()>MARIO_LEVEL_SMALL && !mario->CheckMarioHoldKoopas())
			mario->SetState(MARIO_STATE_SIT);
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
		case DIK_R: // reset
			//Reload();
			break;
		case DIK_A:
			mario->SetState(MARIO_STATE_ATTACK);
			break;
		}
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() != MARIO_STATE_TRANSFORM_RACOON && mario->GetState() != RACOON_STATE_TRANSFORM_MARIO)
	{
		switch (KeyCode)
		{
		case DIK_S:
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
			break;
		case DIK_DOWN:
			if(mario->CheckIsSitting())
			mario->SetState(MARIO_STATE_SIT_RELEASE);
			break;
		case DIK_A:
			if (mario->CheckMarioHoldKoopas())
				mario->SetState(MARIO_STATE_RELEASE_KOOPAS);
			break;
		}
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() != MARIO_STATE_TRANSFORM_RACOON && mario->GetState() != RACOON_STATE_TRANSFORM_MARIO)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_A) && mario->CheckMarioIsOnPlatform())
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
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}