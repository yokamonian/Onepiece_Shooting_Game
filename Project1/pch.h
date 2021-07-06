#pragma once

#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <ctime>
using namespace std;

#include "KeyManager.h"
#include "ImageMgr.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "PatternManager.h"
// enum, struct, .h, #define
#include "macroFunction.h"
#include "ActionElement.h"

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

enum class PlayerState
{
	IDLE,
	BACK,
	AVOID,
	SKILL
};

enum class EliteEnemyState
{
	PATTERN1, // 일반 공격
	PATTERN2, // 바람개비
	PATTERN3,
	IDLE,
	DIE
};


enum class BossEnemyState
{
	IDLE,
	PATTERN1,
	GUARD,
	PATTERN2,
	PATTERN3,
	PATTERN4,
	DIE,
};

#define WINSIZE_X	1200	
#define WINSIZE_Y	900
#define WINSTART_X	50
#define WINSTART_Y	50

#define PI			3.141592

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;