#include "EuclideanGenerator.h"
#include "../libs/bjorklund.h"

const AnsiCharPtr UserModuleBase::MODULE_NAME = "euclidean generator";
const AnsiCharPtr UserModuleBase::MODULE_DESC = "Simple euclidean sequence generator";
const AnsiCharPtr UserModuleBase::MODULE_VERSION = "1.2";
const int MAX_SIZE = 256;

void CreateModule(void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new EuclideanGenerator();
}

void DestroyModule(void* pModule)
{
	delete ((EuclideanGenerator*)pModule);
}

void GetBrowserInfo(ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = UserModuleBase::MODULE_NAME;
	pModuleInfo->Description = UserModuleBase::MODULE_DESC;
	pModuleInfo->Version = UserModuleBase::MODULE_VERSION;
}

void EuclideanGenerator::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{

	//identification of the module
	pModuleInfo->Name = MODULE_NAME;
	pModuleInfo->Description = MODULE_DESC;
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clDataModuleColor);
	pModuleInfo->NumberOfParams = 4;
	pModuleInfo->Version = MODULE_VERSION;
	pModuleInfo->DontProcess = TRUE;
	pModuleInfo->CanBeSavedInPreset = FALSE;
}

void EuclideanGenerator::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{
	// all parameters declared in the module class		
	switch (ParamIndex)
	{
		// dtfInputA
	case 0:
		pParamInfo->ParamType = ptDataFader;
		pParamInfo->Caption = "sequence length";
		pParamInfo->DefaultValue = (TPrecision)steps;
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputSteps;
		pParamInfo->MaxValue = MAX_SIZE;
		pParamInfo->MinValue = 0;
		pParamInfo->Format = "%.0f";
		pParamInfo->Scale = scLinear;
		break;
	case 1:
		pParamInfo->ParamType = ptDataFader;
		pParamInfo->Caption = "beats";
		pParamInfo->DefaultValue = (TPrecision)beats;
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputBeats;
		pParamInfo->MaxValue = MAX_SIZE;
		pParamInfo->MinValue = 0;
		pParamInfo->Format = "%.0f";
		pParamInfo->Scale = scLinear;
		break;
	case 2:
		pParamInfo->IsSeparator = true;
		pParamInfo->ParamType = ptButton;
		pParamInfo->Caption = "generate";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputGenerate;
		break;
	case 3:
		pParamInfo->ParamType = ptArray;
		pParamInfo->Caption = "beats array";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->DontSave = TRUE;
		pParamInfo->MinValue = 0;
		pParamInfo->MaxValue = 1;
		pParamInfo->ReadOnly = TRUE;
		pParamInfo->IsShared = TRUE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dftBeatsOut;
		break;
	default:
		break;
	}
}

void EuclideanGenerator::onCallBack(UsineMessage* Message)
{
	try
	{
		if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
		{
			int paramIndex = (int)Message->wParam;
			if ((paramIndex == 0) && (Message->lParam == MSG_CHANGE))
			{
				steps = (int)sdkGetEvtData(dtfInputSteps);
			}
			if ((paramIndex == 1) && (Message->lParam == MSG_CHANGE))
			{
				beats = (int)sdkGetEvtData(dtfInputBeats);
			}
			if ((paramIndex == 2) && (Message->lParam == MSG_CHANGE))
			{
				updateCellsValues();
			}
		}
	}
	catch (...)
	{
		//sdkTraceErrorChar("error");
	}
}

void EuclideanGenerator::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {
	updateCellsValues();
}

void EuclideanGenerator::updateCellsValues()
{
	if (beats > steps) beats = steps;
	const std::string beat= bjorklund(beats, steps);
	const char *cstr = beat.c_str();
	sdkSetEvtSize(dftBeatsOut, steps);
	for (int i = 0; i < steps; i++)
	{
		sdkSetEvtArrayData(dftBeatsOut, i, (TPrecision)(cstr[i] - '0'));
	}
}


