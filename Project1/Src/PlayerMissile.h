#pragma once
#include "Missile.h"

class Image;
class PlayerMissile : public Missile
{
private:

	float angle;
	Image* playerMissileImg;
	int charNum;
	int missileType;

public:

	virtual HRESULT Init(/*int charNum*/);
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	void SetAngle(float _angle) { angle = _angle; }
	void SetPos(float posX, float posY) { pos.x = posX, pos.y = posY; }
	void SetIsFire(bool _isFire) { isFire = _isFire; }
	bool GetIsFire() { return isFire; }
	FPOINT GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetMissileType(int _missileType) { missileType = _missileType; }

};

