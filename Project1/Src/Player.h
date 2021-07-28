#pragma once
#include "pch.h"
#include "Object.h"

class MissileManager;
class Jong_airplane;
class Sung_airplane;
class Young_airplane;
/// <summary>
/// Player : 3종의 비행기를 컨트롤하는 플레이어 클래스.
/// </summary>
class Player : public Object
{
private:
	int charNum;					// 비행기종 번호
	bool move;						// 이동여부
	bool isDamaged;					// 피격여부
	int playerlife;					// 체력
	MissileManager* missileMgr;		// 미사일 매니저

	// 기체
	Jong_airplane* jong;
	Sung_airplane* sung;
	Young_airplane* young;

	PlayerState playerState;		// 플레이어 상태
	
	RECT skillRect;					// 스킬 판정 구간

	bool skillOn;					// 스킬 사용 여부

	FPOINT playerPos;				// 플레이어 위치
	int playerGage;					// 회피 게이지


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