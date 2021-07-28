#include "NormalEnemy.h"

HRESULT NormalEnemy::Init()
{
	pos = { 0.0f , 0.0f };
	speed = 10.0f;
	life = 1;


	return S_OK;
}

void NormalEnemy::Release()
{
}

void NormalEnemy::Update()
{

}

void NormalEnemy::Render(HDC hdc)
{

}
