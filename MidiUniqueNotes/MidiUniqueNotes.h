#ifndef __RGBA_COLOR_MODULE_H__
#define __RGBA_COLOR_MODULE_H__

#include "UserDefinitions.h"  
#include <iostream>
#include <cmath>
#include <limits>


class MidiUniqueNotes : public UserModuleBase
{
public:
	MidiUniqueNotes() {};
	virtual ~MidiUniqueNotes() {};
public:
	void onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);
	void onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo);
	void onCallBack (UsineMessage *Message);
private:
	UsineEventPtr midiIn;
	UsineEventPtr midiOut;
private:
	void updateRgbaFromColorChooser();
	void updateColorChooserFromRgba();
	void filterNotes();
};

#endif //__RGBA_COLOR_MODULE_H__