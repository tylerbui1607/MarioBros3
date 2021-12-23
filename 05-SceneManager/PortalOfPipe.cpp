#include "PortalOfPipe.h"

void PortalOfPipe::Render()
{
}

void PortalOfPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PORTAL_OF_PIPE_BBOX_SIZE / 2;
	t = y - PORTAL_OF_PIPE_BBOX_SIZE / 2;
	r = l + PORTAL_OF_PIPE_BBOX_SIZE;
	b = t + PORTAL_OF_PIPE_BBOX_SIZE;
 }
