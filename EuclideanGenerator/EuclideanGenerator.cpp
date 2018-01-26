#include "EuclideanGenerator.h"


void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new EuclideanGenerator();
}

void DestroyModule (void* pModule) 
{
    // cast is important to call the good destructor
	delete ((EuclideanGenerator*)pModule);
}

const AnsiCharPtr UserModuleBase::MODULE_NAME = "euclidean generator";
const AnsiCharPtr UserModuleBase::MODULE_DESC = "euclidean generator module";
const AnsiCharPtr UserModuleBase::MODULE_VERSION = "1.0";

void GetBrowserInfo(ModuleInfo* pModuleInfo) 
{
	pModuleInfo->Name				= UserModuleBase::MODULE_NAME;
	pModuleInfo->Description		= UserModuleBase::MODULE_DESC;
	pModuleInfo->Version			= UserModuleBase::MODULE_VERSION;
}

void EuclideanGenerator::onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) 
{

	//identification of the module
	pModuleInfo->Name				= MODULE_NAME;
	pModuleInfo->Description		= MODULE_DESC;
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor          = sdkGetUsineColor(clDataModuleColor);
	pModuleInfo->NumberOfParams     = 4;
	pModuleInfo->Version			= MODULE_VERSION;
	pModuleInfo->DontProcess		= TRUE;
	pModuleInfo->CanBeSavedInPreset = FALSE;

}

//-----------------------------------------------------------------------------
// query system and init methodes
//-----------------------------------------------------------------------------
// query system not used

//void DataMultiplyExampleExample::onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) 
//{
//}

//----------------------------------------------------------------------------
// parameters and process
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Parameters description
void EuclideanGenerator::onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo)
{
	// all parameters declared in the module class		
	switch (ParamIndex) 
	{
	// dtfInputA
	case 0:
		pParamInfo->ParamType		= ptDataField;
		pParamInfo->Caption			= "length";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
		pParamInfo->CallBackType	= ctImmediate;
		pParamInfo->EventPtr        = &dtfInputLength;

		break;

	// dtfInputB
	case 1:
		pParamInfo->ParamType		= ptDataField;
		pParamInfo->Caption			= "pulses";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
		pParamInfo->CallBackType	= ctImmediate;
		pParamInfo->EventPtr        = &dtfInputPulses;
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
		pParamInfo->ParamType		= ptArray;
		pParamInfo->Caption			= "output";
		pParamInfo->IsInput			= FALSE;
		pParamInfo->IsOutput		= TRUE;
		pParamInfo->DontSave		= TRUE;
		pParamInfo->EventPtr        = &dftOutput;

		break;

	// default case
	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// Parameters callback
void EuclideanGenerator::onCallBack (UsineMessage* Message)
{
	try
	{
        if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
        {
            int paramIndex = (int)Message->wParam;

		    if ((paramIndex == 3) && (Message->lParam == MSG_CHANGE))
		    {
			    // sdkMultEvt3 (dtfInputA, dtfInputB, dftOutput);
		    }
        }
	}
	catch (...)
	{
		//sdkTraceErrorChar("error");
	}
}



