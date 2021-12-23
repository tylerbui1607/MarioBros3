#pragma once
#include "GameObject.h"

#define PORTAL_OF_PIPE_BBOX_SIZE	16
#define GATE_IN	0
#define GATE_OUT	1
class PortalOfPipe :
    public CGameObject
{	// target scene to switch to 


	float width;
	float height;
public:
	int typeGate;
	PortalOfPipe(float X, float Y, int Gate) {
		x = X;
		y = Y;
		typeGate = Gate;
	};
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

