#pragma once
#include "NormalEnemy.h"

class Image;
class MissileManager;
class NormalEnemy_Shiki : public NormalEnemy
{
private:

	float angle;	//�÷��̾��� ��ġ�� ���� ����.
	FPOINT playerPos;
	int maxFrameX[3]{ 1, 3, 2 };
	int myState; //0�̸� �⺻ ����, 1�̸� �÷��̾ ���� ����, 2�̸� �״� ���


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

	ActionElement* ae3;
	ActionElement* ae6;

	vector<ActionElement*> P3;
	vector<ActionElement*> P6;


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

	NormalEnemy_Shiki();
	~NormalEnemy_Shiki();
};

