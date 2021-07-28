#pragma once
#include "Missile.h"

class Image;
class EnemyMissile : public Missile
{
private:

	float angle;
	Image* img;
	Image* pattern2Img;

	bool isAceSecondAttack;
	bool isFloorCollision;


	int missileType;
	int currFrameX, currFrameY;
	int elapsedTime;
	FPOINT effectPos;
	//	RECT rc;

		//bool elpasedTime = 0;

public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	//virtual void Fire() = 0;

	void SetAngle(float _angle) { angle = _angle; }
	void SetPos(float posX, float posY) { pos.x = posX, pos.y = posY; }
	void SetIsFire(bool _isFire) { isFire = _isFire; }
	bool GetIsFire() { return isFire; }
	FPOINT GetPos() { return pos; }
	void SetSpeed(float _speed) { speed = _speed; }

	void SetisAceSecondAttack(bool _isAceSecondAttack) { isAceSecondAttack = _isAceSecondAttack; }
	bool GetIsAceSecondAttack() { return isAceSecondAttack; }
	void SetMissileType(int _missileType) { missileType = _missileType; }
	float GetRadius() { return radius; }
	void SetEffectPos(FPOINT pos) { effectPos = pos; }
	void SetIsFloorCollision(bool _isFloorCollision) { isFloorCollision = _isFloorCollision; }
	bool GetIsFloorCollision() { return isFloorCollision; }
};
