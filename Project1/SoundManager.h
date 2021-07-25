#pragma once
#include "pch.h"
#include "SingletonBase.h"

// FMOD 관련
#include "inc\fmod.hpp"
#pragma comment (lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER			15
#define EXTRACHANNELBUFFER	5
#define TOTALSOUNDBUFFER	SOUNDBUFFER + EXTRACHANNELBUFFER

/// <summary>
/// SoundManager : 인 게임 내 사운드를 관리하는 매니저 클래스.
/// </summary>
class SoundManager : public SingletonBase<SoundManager>
{
private:
	FMOD::System*	system;
	Sound**			sound;
	Channel**		channel;

	map<string, Sound**>	mapSoundDatas;
public:
	HRESULT Init();
	void Release();
	void Update();

	void AddSound(string key, string filePath, bool isBGM = false, bool isLoop = false);	// 사운드 추가
	void Play(string key, float volume = 1.0f); // 범위 0.0f~ 1.0f							// 플레이
	void Stop(string key);																	// 정지
	void Pause(string key);																	// 일시정지
	void Resume(string key);																// 일시정지해제

	SoundManager();
	~SoundManager();


};

