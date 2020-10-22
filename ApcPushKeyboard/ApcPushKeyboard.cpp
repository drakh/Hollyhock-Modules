#include "ApcPushKeyboard.h"

const AnsiCharPtr UserModuleBase::MODULE_NAME = "apc push";
const AnsiCharPtr UserModuleBase::MODULE_DESC = "Push style keyboard for APC mini";
const AnsiCharPtr UserModuleBase::MODULE_VERSION = "1.0";
const int MAX_SIZE = 256;

void CreateModule(void*& pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new ApcPushKeyboard();
}

void DestroyModule(void* pModule)
{
	delete ((ApcPushKeyboard*)pModule);
}

void GetBrowserInfo(ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = UserModuleBase::MODULE_NAME;
	pModuleInfo->Description = UserModuleBase::MODULE_DESC;
	pModuleInfo->Version = UserModuleBase::MODULE_VERSION;
}

void ApcPushKeyboard::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	//identification of the module
	pModuleInfo->Name = MODULE_NAME;
	pModuleInfo->Description = MODULE_DESC;
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->NumberOfParams = 4;
	pModuleInfo->Version = MODULE_VERSION;
	pModuleInfo->CanBeSavedInPreset = FALSE;
}

void ApcPushKeyboard::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{
	// all parameters declared in the module class		
	switch (ParamIndex)
	{
	case 0:

		pParamInfo->ParamType = ptMidi;
		pParamInfo->Caption = "APC in";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->ReadOnly = TRUE;
		pParamInfo->IsShared = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &apcIn;
		break;
	case 1:
		pParamInfo->ParamType = ptArray;
		pParamInfo->Caption = "scale config";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->DontSave = TRUE;
		pParamInfo->MinValue = 0;
		pParamInfo->MaxValue = 12;
		pParamInfo->ReadOnly = TRUE;
		pParamInfo->IsShared = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &scaleConfig;
		break;
	case 2:
		pParamInfo->ParamType = ptMidi;
		pParamInfo->Caption = "APC out";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->IsShared = FALSE;
		pParamInfo->EventPtr = &apcOut;
		break;
	case 3:
		pParamInfo->ParamType = ptMidi;
		pParamInfo->Caption = "MIDI out";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->IsShared = FALSE;
		pParamInfo->EventPtr = &midiOut;
		break;
	default:
		break;
	}
}

void ApcPushKeyboard::onCallBack(UsineMessage* Message)
{
	try
	{
	}
	catch (...)
	{
		//sdkTraceErrorChar("error");
	}
}

void ApcPushKeyboard::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {

}