#pragma once
#include "NormalEnemy.h"

class Image;
class MissileManager;
/// <summary>
/// 기본 적군 기체 쵸파의 정보를 담는 클래스.
/// </summary>
class NormalEnemy_Choppa : public NormalEnemy
{
private:

	float angle;							// 플레이어의 위치를 받을 변수.
	FPOINT playerPos;						// 플레이어의 위치
	int maxFrameX[3]{ 3, 3, 2 };
	int myState;							// 0이면 기본 상태, 1이면 플레이어를 무는 상태, 2이면 죽는 모션

	Image* img;
	bool isAppear;							// 생성 여부
	int elipsedTime;						// 경과 시간
	int maxKeyFrameX;						// 최대 x 프레임 수
	bool isDamaged;							// 피격 여부
	MissileManager* EnemyMissileMgr;		// 적군 미사일 매니저
	int fireCount;							// 발사 카운트
	bool isRender;
	int frame;

	// 웨이브
	int waveTime;
	int myWaveId;
	int waveId;

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

	NormalEnemy_Choppa();
	~NormalEnemy_Choppa();
};

