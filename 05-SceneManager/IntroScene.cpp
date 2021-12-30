#include "IntroScene.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"


#include "SampleKeyEventHandler.h"
#include "HUD.h"
using namespace std;


IntroScene::IntroScene(int id, LPCWSTR filePath) :CScene(id, filePath)
{
	key_handler = new CSampleKeyHandler(this);
	redMario = greenMario = new CMario(0,0);
	platform = new CPlatform(0, 0, 0, 0, 0, 0, 0, 0);
	isDoneSeq1 = isDoneSeq2 = isFirstJump = false;
	SequenceTime = 0;
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define SCENE_SECTION_MAP	3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void IntroScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void IntroScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void IntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int j = i + 1;
		int frame_time = atoi(tokens[j].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}


void IntroScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void IntroScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		}
	}

	f.close();
	redMario =  new CMario(8, 182);
	greenMario = new CMario(242, 182);
	redMario->SetLevel(MARIO_LEVEL_BIG);
	greenMario->SetLevel(MARIO_LEVEL_BIG);
	redMario->isOnPlatform = true;
	greenMario->isOnPlatform = true;
	leaf->SetState(LEAF_STATE_FALLING);
	platform = new CPlatform(8, 204, 16, 16, 39, 51000, 52000, 53000);
	platform->IsAllowRender = true;
	objects.push_back(redMario);
	objects.push_back(greenMario);
	objects.push_back(leaf);
	objects.push_back(platform);
	Camera::GetInstance()->SetCamPos(0, 0);
	DebugOut(L"[INFO] Done loading Introscene  %s\n", sceneFilePath);
	CGame::GetInstance()->IsSwitchScene = false;
}

void IntroScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	if(!leaf->IsDeleted())
	coObjects.push_back(objects[2]);
	coObjects.push_back(objects[3]);
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsAllowUpdate && !objects[i]->IsDeleted())
		{
			objects[i]->Update(dt, &coObjects);
		}
	}
	ScriptIntro();
	curtain->Update(dt);
	BlackMariobros3->Update(dt);
}

void IntroScene::Render()
{
	
	background->Render();
	BlackMariobros3->Render();
	if (MainMariobros3->isAllowRender)
		MainMariobros3->Render();
	if (NumberMariobros3->isAllowRender)
		NumberMariobros3->Render();
	if (ChoosePlayerMariobros3->isAllowRender)
		ChoosePlayerMariobros3->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		if(objects[i]->IsAllowRender && !objects[i]->IsDeleted())
			objects[i]->Render();
	}
	if(curtain->isAllowRender)
		curtain->Render();
}

/*
*	Clear all objects from this scene
*/
void IntroScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void IntroScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}


