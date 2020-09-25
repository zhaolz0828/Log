#pragma once
#include <TapQuoteAPIDataType.h>


struct ShareMemoryTool
{
	HANDLE		MapFile;
	HANDLE		L_Mutex = NULL;
	HANDLE		L_Event = NULL;
};


typedef TapAPIQuoteWhole* deliver_;
typedef MockFile* MK;
