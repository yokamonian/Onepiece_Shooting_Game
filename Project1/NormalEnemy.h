#pragma once
#include "Enemy.h"

class NormalEnemy : public Enemy
{
protected:


public:
	virtual HRESULT Init() = 0;		
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
};

