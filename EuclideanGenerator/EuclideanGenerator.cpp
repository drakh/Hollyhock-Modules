#include "EuclideanGenerator.h"
#include "bjorklund.h"

const AnsiCharPtr UserModuleBase::MODULE_NAME = "euclidean generator";
const AnsiCharPtr UserModuleBase::MODULE_DESC = "euclidean generator module";
const AnsiCharPtr UserModuleBase::MODULE_VERSION = "1.0";
const int MAX_SIZE = 256;
int steps = 16;
int beats = 0;

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
		pParamInfo->ParamType = ptDataField;
		pParamInfo->Caption = "length";
		pParamInfo->DefaultValue = (TPrecision)steps;
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputLength;
		pParamInfo->MaxValue = MAX_SIZE;
		pParamInfo->MinValue = 0;
		break;

		// dtfInputB
	case 1:
		pParamInfo->ParamType = ptDataField;
		pParamInfo->Caption = "pulses";
		pParamInfo->DefaultValue = (TPrecision)beats;
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputPulses;
		pParamInfo->MaxValue = MAX_SIZE;
		pParamInfo->MinValue = 0;
		break;
		// generate
	case 2:
		pParamInfo->ParamType = ptButton;
		pParamInfo->Caption = "generate";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputGenerate;
		break;

		// dftOutput
	case 3:
		pParamInfo->ParamType = ptArray;
		pParamInfo->Caption = "output";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->DontSave = TRUE;
		pParamInfo->MinValue = 0;
		pParamInfo->MaxValue = 1;
		pParamInfo->ReadOnly = TRUE;
		pParamInfo->IsShared = TRUE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dftOutput;
		break;

		// default case
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
				steps = (int)sdkGetEvtData(dtfInputLength);
			}
			if ((paramIndex == 1) && (Message->lParam == MSG_CHANGE))
			{
				beats = (int)sdkGetEvtData(dtfInputPulses);
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
	const std::string beat= bjorklund(beats, steps);
	const char *cstr = beat.c_str();
	sdkSetEvtSize(dftOutput, steps);
	for (int i = 0; i < steps; i++)
	{
		sdkSetEvtArrayData(dftOutput, i, (TPrecision)(cstr[i] - '0'));
	}
}


