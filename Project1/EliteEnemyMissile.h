#pragma once
#include "Missile.h"

class EliteEnemyMissile : public Missile
{
private:
	float angle;
	Image* img;

public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	void SetAngle(float _angle) { angle = _angle; }
	void SetPos(float posX, float posY) { pos.x = posX, pos.y = posY; }
	void SetIsFire(bool _isFire) { isFire = _isFire; }
	bool GetIsFire() { return isFire; }
	FPOINT GetPos() { return pos; }

};

