#pragma once
#include "GameObject.h"

#define PORTAL_OF_PIPE_BBOX_SIZE	16

class PortalOfPipe :
    public CGameObject
{	// target scene to switch to 

	float width;
	float height;
public:
	PortalOfPipe(float X, float Y) {
		x = X;
		y = Y;
	};
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

