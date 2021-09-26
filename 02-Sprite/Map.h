#pragma once

#include <iostream>
#include <fstream>
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"


class Map
{

	LPCWSTR MapFilePath;
	LPCWSTR MapPNG;
	int Num_Rows, Num_Cols;
	int num_row_read, num_col_read;
	int Tile_Width, Tile_Height;
	int Id;

	int tilemap[300][300];

public:
	Map(int ID, LPCWSTR FilePath_data, int Num_Rows, int  Num_Cols, int Num_row_read, int Num_col_read, int map_width = 16, int map_height = 16);
	~Map();
	void Load();
	void LoadMap();
	void Draw();
};
