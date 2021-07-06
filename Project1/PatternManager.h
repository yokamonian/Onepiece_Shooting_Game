#pragma once
#include "pch.h"
#include "SingletonBase.h"
#include "ActionElement.h"

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

