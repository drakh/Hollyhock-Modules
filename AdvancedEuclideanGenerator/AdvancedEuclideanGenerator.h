
#ifndef __RGBA_COLOR_MODULE_H__
#define __RGBA_COLOR_MODULE_H__
#include "UserDefinitions.h"  
#include <iostream>
#include <cmath>
#include <limits>
class AdvancedEuclideanGenerator : public UserModuleBase
{
public:
	AdvancedEuclideanGenerator(){};
	virtual ~AdvancedEuclideanGenerator(){};
public:
	void onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo);
	void onCallBack (UsineMessage *Message);
private:
	//-------------------------------------------------------------------------
	// parameters events
	UsineEventPtr dtfInputSteps;
	UsineEventPtr dtfInputBeats;
	UsineEventPtr dtfInputAccents;
	UsineEventPtr dtfInputGenerate;
	UsineEventPtr dftBeatsOut;
	UsineEventPtr dftAccentsOut;
	inline void updateCellsValues();
	int steps = 16;
	int beats = 0;
	int accents = 0;
};

#endif //__RGBA_COLOR_MODULE_H__