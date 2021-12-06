#pragma once
#include "GameObject.h"
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
			/*CSprites* sprite = CSprites::GetInstance();
			int drawy = y + TileSize;
			for (int i = 0; i < Height / 16; i++)
			{
				if (i < 2)
					animation_set->at(i)->Render(i * TileSize + x, y);
				else if (i % 2 == 0)
				{

					animation_set->at(Ani_Body_Right)->Render(x, drawy);
				}
				else
				{
					animation_set->at(Ani_Body_Left)->Render(x + TileSize, drawy);
					drawy += TileSize;
				}
			}*/
		};
		void Update(DWORD dt) {
		}
		void GetBoundingBox(float& l, float& t, float& r, float& b);
		int IsBlocking() { return 1; };
		int IsCollidable() { return 1; }
	};


