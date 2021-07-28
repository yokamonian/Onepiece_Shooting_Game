#pragma once
#include "pch.h"
#include "SingletonBase.h"
#include "ActionElement.h"

/// <summary>
/// PatternManager : 미사일이나 이동 시 패턴을 저장하기 위한 매니저.
/// </summary>
class PatternManager : public SingletonBase<PatternManager>
{
private:
	vector<vector<ActionElement*> > vcPatternArray;
	vector<ActionElement*> temporaryNumArr;



public:
	virtual HRESULT Init();
	virtual void Release();

	void AddPattern(vector<ActionElement*> temporaryNumArr);
	vector<ActionElement*> GetPattern(int id) { return vcPatternArray[id]; }

	PatternManager();
	~PatternManager();
};

