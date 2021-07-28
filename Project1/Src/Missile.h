#pragma once
#include "Object.h"

class Image;
class Missile : public Object
{
protected:

	bool isFire;

	//Image* img;
	//Image* km;
	//int charNum;
	//bool isEnemy;
	//int testcount;

public:

	virtual HRESULT Init(int charNum);
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	
	/*bool GetIsEnemy() { return isEnemy; }
	void SetIsEnemy(bool _isEnemy) { isEnemy = _isEnemy; }*/
};

