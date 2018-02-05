
#ifndef __RGBA_COLOR_MODULE_H__
#define __RGBA_COLOR_MODULE_H__
#include "../../sdk/UserDefinitions.h"  
#include <iostream>
#include <cmath>
#include <limits>
class EuclideanGenerator : public UserModuleBase
{
public:
	EuclideanGenerator(){};
	virtual ~EuclideanGenerator(){};
public:
	void onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo);
	void onCallBack (UsineMessage *Message);
private:
	//-------------------------------------------------------------------------
	// parameters events
	UsineEventPtr dtfInputPulses;
	UsineEventPtr dtfInputLength;
	UsineEventPtr dtfInputGenerate;
	UsineEventPtr dftOutput;
	inline void updateCellsValues();
};

#endif //__RGBA_COLOR_MODULE_H__