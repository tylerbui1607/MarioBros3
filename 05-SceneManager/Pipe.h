#pragma once
#include "GameObject.h"

#define ID_SPRITE_PIPE_MOUTH 131313
#define ID_SPRITE_PIPE_BODY 141414

#define ID_SPRITE_H_MAP_PIPE_MOUTH 161616
#define ID_SPRITE_H_MAP_PIPE_BODY 151515

#define SPRITE_TILE_SIZE	16

#define NORMAL_PIPE	1
#define HIDDEN_MAP_PIPE	2
#define SPECIAL_PIPE	3
#define SPECIAL_PIPE_HIDDEN_MAP_PIPE	4

class Pipe :
    public CGameObject
{
	int AllowRender;
	public:
		int PipeType;
		int Width, Height, TileSize;
		Pipe(float x, float y, int width, int height, int allowRender, int type) : CGameObject(x, y) {
			Width = width;
			Height = height;
			AllowRender = allowRender;
			PipeType = type;
		}
		void Render() { 
			if (AllowRender != 0)
			{
				if (PipeType != HIDDEN_MAP_PIPE && PipeType != SPECIAL_PIPE_HIDDEN_MAP_PIPE)
				{
					CSprites* sprite = CSprites::GetInstance();
					int SpriteY = y - Height / 2 + SPRITE_TILE_SIZE / 2;
					for (int i = 0; i < Height / SPRITE_TILE_SIZE; i++)
					{
						if (i < 1)
							sprite->Get(ID_SPRITE_PIPE_MOUTH)->Draw(x, SpriteY);
						else
							sprite->Get(ID_SPRITE_PIPE_BODY)->Draw(x, SpriteY);
						SpriteY += SPRITE_TILE_SIZE;
					}
				}
				else 
				{
					CSprites* sprite = CSprites::GetInstance();
					int SpriteY = y - Height / 2 + SPRITE_TILE_SIZE / 2;
					for (int i = 0; i < Height / SPRITE_TILE_SIZE; i++)
					{
						if (i == Height / SPRITE_TILE_SIZE-1)
							sprite->Get(ID_SPRITE_H_MAP_PIPE_MOUTH)->Draw(x, SpriteY);
						else
							sprite->Get(ID_SPRITE_H_MAP_PIPE_BODY)->Draw(x, SpriteY);
						SpriteY += SPRITE_TILE_SIZE;
					}
				}
			}
		};
		void Update(DWORD dt) {
		}
		void GetBoundingBox(float& l, float& t, float& r, float& b);
		int IsBlocking() { return 1; };
		int IsCollidable() { return 1; }
	};


