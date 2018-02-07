#include "stdafx.h"
#include "AdminstratorComDll.h"

extern CGTDriverCmd*	g_GTDriver;

SERVODRIVERCOMDLL_API short AdminGetGTDriverObject(CGTDriverCmd** pDevice)
{
	*pDevice = g_GTDriver;
	return RTN_SUCCESS;
}
