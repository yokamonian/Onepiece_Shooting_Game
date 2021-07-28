#pragma once
#include "Object.h"

class Image;
class PowerUp : public Object
{
	Image* powerUpImg;
	float angle;

	FPOINT center;

	bool isCollision;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	void SetCenter(FPOINT _pos) { center = _pos; }
	FPOINT GetCenter() { return center; }
	void SetIsCollision(bool _isCollision) { isCollision = _isCollision; }
	//void SetCenter(FPOINT)
};

