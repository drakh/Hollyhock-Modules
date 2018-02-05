#include "AdvancedEuclideanGenerator.h"
#include "../libs/bjorklund.h"

const AnsiCharPtr UserModuleBase::MODULE_NAME = "advanced euclidean generator";
const AnsiCharPtr UserModuleBase::MODULE_DESC = "Euclidean generator with accents distribution";
const AnsiCharPtr UserModuleBase::MODULE_VERSION = "1.1";
const int MAX_SIZE = 256;
int steps = 16;
int beats = 0;
int accents = 0;

void CreateModule(void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new AdvancedEuclideanGenerator();
}

void DestroyModule(void* pModule)
{
	delete ((AdvancedEuclideanGenerator*)pModule);
}

void GetBrowserInfo(ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = UserModuleBase::MODULE_NAME;
	pModuleInfo->Description = UserModuleBase::MODULE_DESC;
	pModuleInfo->Version = UserModuleBase::MODULE_VERSION;
}

void AdvancedEuclideanGenerator::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{

	//identification of the module
	pModuleInfo->Name = MODULE_NAME;
	pModuleInfo->Description = MODULE_DESC;
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clDataModuleColor);
	pModuleInfo->NumberOfParams = 6;
	pModuleInfo->Version = MODULE_VERSION;
	pModuleInfo->DontProcess = TRUE;
	pModuleInfo->CanBeSavedInPreset = FALSE;

}

void AdvancedEuclideanGenerator::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
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
		pParamInfo->ParamType = ptDataFader;
		pParamInfo->Caption = "accents";
		pParamInfo->DefaultValue = (TPrecision)beats;
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputAccents;
		pParamInfo->MaxValue = MAX_SIZE;
		pParamInfo->MinValue = 0;
		pParamInfo->Format = "%.0f";
		pParamInfo->Scale = scLinear;
		break;
	case 3:
		pParamInfo->IsSeparator = true;
		pParamInfo->ParamType = ptButton;
		pParamInfo->Caption = "generate";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dtfInputGenerate;
		break;
	case 4:
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
	case 5:
		pParamInfo->ParamType = ptArray;
		pParamInfo->Caption = "accents array";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->DontSave = TRUE;
		pParamInfo->MinValue = 0;
		pParamInfo->MaxValue = 1;
		pParamInfo->ReadOnly = TRUE;
		pParamInfo->IsShared = TRUE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &dftAccentsOut;
		break;
	default:
		break;
	}
}

void AdvancedEuclideanGenerator::onCallBack(UsineMessage* Message)
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
				accents = (int)sdkGetEvtData(dtfInputAccents);
			}
			if ((paramIndex == 3) && (Message->lParam == MSG_CHANGE))
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

void AdvancedEuclideanGenerator::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {
	updateCellsValues();
}

void AdvancedEuclideanGenerator::updateCellsValues()
{
	if (beats > steps) beats = steps;
	
	if (accents > beats) accents = beats;
	
	const std::string beat= bjorklund(beats, steps);

	const std::string accent = bjorklund(accents, beats);

	const char *beats_str = beat.c_str();
	const char *accents_str = accent.c_str();
	int b = 0;
	sdkSetEvtSize(dftBeatsOut, steps);
	sdkSetEvtSize(dftAccentsOut, steps);

	for (int i = 0; i < steps; i++)
	{
		const int beat_i = (beats_str[i] - '0');
		int accent_i = 0;
		if (beat_i == 1) {
			accent_i = (accents_str[b] - '0');
			b++;
		}
		sdkSetEvtArrayData(dftBeatsOut, i, (TPrecision)beat_i);
		sdkSetEvtArrayData(dftAccentsOut, i, (TPrecision)accent_i);
	}
}


