#include "PatternManager.h"
#include "Movement.h"



HRESULT PatternManager::Init()
{
	return S_OK;
}

void PatternManager::Release()
{
	//if (!vcPatternArray.empty())
	//{
	//	for (int i = 0; i < maxBehaviorCount; i++)
	//	{
	//		if (vcPatternArray[i].empty())
	//			continue;
	//		vcPatternArray[i].clear();
	//	}
	//	vcPatternArray.clear();
	
//}

}


void PatternManager::AddPattern(vector<ActionElement*> temporaryNumArr)
{
	vcPatternArray.push_back(temporaryNumArr);
}





PatternManager::PatternManager()
{
}


PatternManager::~PatternManager()
{
}
