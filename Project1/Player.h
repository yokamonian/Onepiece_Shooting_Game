#pragma once
#include "pch.h"
#include "Object.h"

class MissileManager;
class Jong_airplane;
class Sung_airplane;
class Young_airplane;
class Player : public Object
{
private:
	int charNum;
	bool move;
	bool isDamaged;
	int playerlife;
	MissileManager* missileMgr;

	Jong_airplane* jong;
	Sung_airplane* sung;
	Young_airplane* young;
	PlayerState playerState;
	
	RECT skillRect;
	bool skillOn;

	FPOINT playerPos;
	int playerGage;


public:
	virtual HRESULT Init(int selectIdx);
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);
	bool Onhit(FPOINT point);
	void PowerUp();

	FPOINT GetPlayerPos() { return playerPos; }
	int GetGage() { return playerGage; }

	void SetLife(int _life) { playerlife = _life; }
	int GetLife() { return playerlife; }
	PlayerState GetPlayerState() { return playerState; }
	bool GetSkillOn() { return skillOn; }
	RECT GetSkillRect() { return skillRect; }
	FPOINT GetPos() { return pos; }
};