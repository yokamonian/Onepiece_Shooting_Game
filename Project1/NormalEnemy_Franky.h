#pragma once
#include "NormalEnemy.h"

class Image;
class MissileManager;
class NormalEnemy_Franky : public NormalEnemy
{
private:

	float angle;	//플레이어의 위치를 받을 변수.
	FPOINT playerPos;
	int maxFrameX[2]{ 1, 0 };
	int myState; //0이면 기본 상태, 1이면 플레이어를 무는 상태, 2이면 죽는 모션


	Image* img;
	bool isAppear;
	int elipsedTime;
	int maxKeyFrameX;
	bool isDamaged;
	MissileManager* EnemyMissileMgr;
	int fireCount;
	bool isRender;
	float holdX, holdY;
	int waveId;
	int frame;
	int waveTime;
	int myWaveId;
	int waveNum[5] = { 1,2,3,4,5 };
	vector<ActionElement*> patterns;
	int pIdx;
	float endTime;

	bool isHit = false;


public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void SetDamaged(bool b) { isDamaged = b; }
	bool GetDamaged() { return isDamaged; }

	void SetIsApear(bool _isApear) { isAppear = _isApear; }
	bool getIsApear() { return isAppear; }
	bool OnHit(FPOINT point);

	void SetAngle(float _angle) { angle = _angle; }
	void SetPlayerPos(FPOINT _playerPos) { playerPos = _playerPos; }
	void SetWaveId(float _waveId) { waveId = _waveId; }
	void SetWaveTime(int time) { waveTime = time; }
	void SetPos(float posX, float posY) { pos.x = posX, pos.y = posY; }
	FPOINT GetPos() { return pos; }
	void SetLife(int _life) { life = _life; }

	NormalEnemy_Franky();
	~NormalEnemy_Franky();
};

