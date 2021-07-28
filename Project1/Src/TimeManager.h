#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Timer;
/// <summary>
/// TimeManager : Time 클래스를 활용. 게임 내 각종 타이머 매니저 클래스.
/// </summary>
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* timer;			// 타이머
	char strText[256];		
	bool isGameStart;		// 게임시작 여부

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float lockFPS = 0.0f);
	virtual void Render(HDC hdc);


	float GetWorldCount();
	float GetCurrTime();

	float GetDeltaTime();
	void SetIsGameStart(bool _isGameStart) { isGameStart = _isGameStart; }

	void ResetWt();
	Timer* GetTimer() { return timer; }
};

