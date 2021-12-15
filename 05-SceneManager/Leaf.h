#pragma once
#include "GameObject.h"
#define LEAF_GRAVITY 0.001f

#define LEAF_WIDTH  16
#define LEAF_HEIGHT  14

#define LEAF_INNIT_SPEED    0.1f

#define LEAF_STATE_INNIT 1
#define LEAF_STATE_FALLING 2

#define ID_ANI_LEAF_FALLING_RIGHT
#define ID_ANI_LEAF_FALLING_RIGHT   80001
#define ID_ANI_LEAF_FALLING_LEFT   80002
class Leaf :
    public CGameObject
{
protected:
    bool isInnited;
    float startY;
    int ItemType;
    DWORD MovingTime;
public:
    Leaf(float x, float y) :CGameObject(x, y) {
        isInnited = false;
        startY = y;
        ItemType = 1;
        isitem = true;
        MovingTime = 0;
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
        if (isInnited)
        {
            vy = LEAF_GRAVITY * dt;
            LeafMoving();
        }
        else if (vy != 0)
        {
            if (startY - y > 30)
                SetState(LEAF_STATE_FALLING);
        }
        x += vx * dt;
        y += vy * dt;
    }

    void Render() {
        CAnimations* animations = CAnimations::GetInstance();
        int aniId = ID_ANI_LEAF_FALLING_LEFT;
        if (vx >= 0)aniId = ID_ANI_LEAF_FALLING_RIGHT;
        else aniId = ID_ANI_LEAF_FALLING_LEFT;
        animations->Get(aniId)->Render(x, y);
    }
    void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
        left = x - LEAF_WIDTH / 2;
        top = y - LEAF_HEIGHT / 2;
        right = left + LEAF_WIDTH;
        bottom = top + LEAF_HEIGHT;
    }
    void SetState(int state) {
        switch (state) {
        case LEAF_STATE_INNIT:
            vy = -LEAF_INNIT_SPEED;
            break;
        case LEAF_STATE_FALLING:
            vy = 0;
            vx = 0.05;
            isInnited = true;
            MovingTime = GetTickCount64();
            break;
        default:break;
        }
    }
    void LeafMoving()
    {
        if (GetTickCount64() - MovingTime >= 600)
        {
           vx = -vx;
           MovingTime = GetTickCount64();
        }
    }
    int IsBlocking() {
        return 0;
    }
    int IsCollidable() {
        return 1;
    }
};

