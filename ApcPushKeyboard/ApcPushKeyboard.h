
#ifndef __RGBA_COLOR_MODULE_H__
#define __RGBA_COLOR_MODULE_H__
#include "UserDefinitions.h"  
#include <iostream>
#include <cmath>
#include <limits>
class ApcPushKeyboard : public UserModuleBase
{
public:
	ApcPushKeyboard(){};
	virtual ~ApcPushKeyboard(){};
public:
	void onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo);
	void onCallBack (UsineMessage *Message);
private:
private:
	UsineEventPtr apcIn;
	UsineEventPtr scaleConfig;
	UsineEventPtr apcOut;
	UsineEventPtr midiOut;
};

#endif //__RGBA_COLOR_MODULE_H__