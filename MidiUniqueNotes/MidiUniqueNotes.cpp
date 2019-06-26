#include "MidiUniqueNotes.h"
#include <map> 
#include <iterator> 
void CreateModule(void*& pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new MidiUniqueNotes();
}
void DestroyModule(void* pModule)
{
	delete ((MidiUniqueNotes*)pModule);
}

const AnsiCharPtr UserModuleBase::MODULE_NAME = "MIDI unique notes";
const AnsiCharPtr UserModuleBase::MODULE_DESC = "passes unique notes highest velocity taken";
const AnsiCharPtr UserModuleBase::MODULE_VERSION = "1.1";

void GetBrowserInfo(ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = UserModuleBase::MODULE_NAME;
	pModuleInfo->Description = UserModuleBase::MODULE_DESC;
	pModuleInfo->Version = UserModuleBase::MODULE_VERSION;
}

void MidiUniqueNotes::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{

	//identification of the module
	pModuleInfo->Name = MODULE_NAME;
	pModuleInfo->Description = MODULE_DESC;
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->NumberOfParams = 2;
	pModuleInfo->Version = MODULE_VERSION;
	pModuleInfo->CanBeSavedInPreset = FALSE;
}

//----------------------------------------------------------------------------
// parameters and process
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Parameters description
void MidiUniqueNotes::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{
	// all parameters declared in the module class		
	switch (ParamIndex)
	{
		// midiIn
	case 0:
		pParamInfo->ParamType = ptMidi;
		pParamInfo->Caption = "in";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
		pParamInfo->EventPtr = &midiIn;
		break;

		// midiOut
	case 1:
		pParamInfo->ParamType = ptMidi;
		pParamInfo->Caption = "out";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->EventPtr = &midiOut;
		break;

	default:
		break;
	}
}
void MidiUniqueNotes::onCallBack(UsineMessage* Message)
{
	try
	{
		if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
		{
			int paramIndex = (int)Message->wParam;
			if ((paramIndex == 0) && (Message->lParam == MSG_CHANGE))
			{
				filterNotes();
			}
		}
	}
	catch (...)
	{
		// sdkTraceErrorChar("error");
	}
}

void MidiUniqueNotes::filterNotes()
{
	std::map<unsigned char, UsineMidiCode> notesOn;
	std::map<unsigned char, UsineMidiCode> notesOff;
	int sizeMidiIn = sdkGetEvtSize(midiIn);
	sdkSetEvtSize(midiOut, 0);
	if (sizeMidiIn > 0)
	{
		for (int i = 0; i < sizeMidiIn; i++)
		{
			UsineMidiCode code = sdkGetEvtArrayMidi(midiIn, i);
			if (code.Msg == MIDI_NOTEON || code.Msg == MIDI_NOTEOFF)
			{
				if (code.Msg == MIDI_NOTEON) {
					if (notesOn.count(code.Data1) > 0) {
						const UsineMidiCode note = notesOn[code.Data1];
						if (code.Data2 > note.Data2) {
							notesOn[code.Data1] = code;
						}
					}
					else {
						notesOn[code.Data1] = code;
					}
				}
				else {
					if (notesOff.count(code.Data1) == 0) {
						notesOff[code.Data1] = code;
					}
				}
			}
		}
	}
	sdkSetEvtSize(midiOut, notesOn.size() + notesOff.size());
	std::map<unsigned char, UsineMidiCode>::iterator itr;
	int i = 0;
	for (itr = notesOn.begin(); itr != notesOn.end(); ++itr) {
		const UsineMidiCode note = itr->second;
		sdkSetEvtArrayMidi(midiOut, i, note);
		i++;
	}
	for (itr = notesOff.begin(); itr != notesOff.end(); ++itr) {
		const UsineMidiCode note = itr->second;
		sdkSetEvtArrayMidi(midiOut, i, note);
		i++;
	}
	notesOn.clear();
	notesOff.clear();
}

