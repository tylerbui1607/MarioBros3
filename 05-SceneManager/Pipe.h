#pragma once
#include "GameObject.h"

#define ID_SPRITE_PIPE_MOUTH 131313
#define ID_SPRITE_PIPE_BODY 141414

#define SPRITE_TILE_SIZE	16
class Pipe :
    public CGameObject
{
	public:
		int Width, Height, TileSize;
		Pipe(float x, float y, int width, int height) : CGameObject(x, y) {
			Width = width;
			Height = height;
		}
		void Render() { 
			CSprites* sprite = CSprites::GetInstance();
			int SpriteY = y - Height / 2 + SPRITE_TILE_SIZE/2;
			for (int i = 0; i < Height / SPRITE_TILE_SIZE; i++)
			{
				if (i < 1)
					sprite->Get(ID_SPRITE_PIPE_MOUTH)->Draw(x, SpriteY);
				else
					sprite->Get(ID_SPRITE_PIPE_BODY)->Draw(x, SpriteY);
				SpriteY += SPRITE_TILE_SIZE;
			}
		};
		void Update(DWORD dt) {
		}
		void GetBoundingBox(float& l, float& t, float& r, float& b);
		int IsBlocking() { return 1; };
		int IsCollidable() { return 1; }
	};


