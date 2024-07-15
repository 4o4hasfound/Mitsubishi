// Mitsubishi_Socket_Communication.cpp : 定義 DLL 應用程式的匯出函式。
//

#include <atlbase.h>
#include "stdio.h"
#include "Mitsubishi_Socket_Communication.h"
#include "EZSocketNc.h"
#include "EZSocketNcDef.h"
#include "EZSocketNcErr.h"
#include "EZSocketNcOle.h"
#include <string>
#include "atlconv.h"

// Communication object
IEZNcCommunication3 *pIEZNcCom = NULL; 

// Interface
IEZNcCommonVariable2 *pIEZNcVariable = NULL;
IEZNcTime *pIEZNcTime = NULL;
IEZNcParameter3 *pIEZNcParameter = NULL;
IEZNcSystem *pIEZNcSystem = NULL;
IEZNcDevice *pIEZNcDevice = NULL;

HRESULT hr = S_OK;

EzNcsocketTCPIP long NcTCPIP(char Mechine_IP[], long IP_Port)
{
	// ANSI char = char 1 byte 0 ~ 255 
	// OLE	char = wchar(wide character) = short 2 byte
	LONG EZNcTCPIP_Error = NULL;
	LPCOLESTR NcipAddress = NULL;

	USES_CONVERSION;

	// ANSI to OLE
	NcipAddress = A2COLE(Mechine_IP);

	hr = pIEZNcCom->SetTCPIPProtocol(NcipAddress, IP_Port, &EZNcTCPIP_Error);
	return EZNcTCPIP_Error;
}
EzNcsocketCom long NcCommunication(long Mechine_SystemType, long Mechine_Number, bool Mechine_OpenClose) {
	LONG EZNcCommunication_Error = NULL;
	// EZNCST_OPEN stOpen;

	// memset(&stOpen, 0x00, sizeof(stOpen));
	if (Mechine_OpenClose)
	{
		hr = pIEZNcCom->Open2(Mechine_SystemType, Mechine_Number, 10, &EZNcCommunication_Error);

		if (hr == S_FALSE) {
			// Open2 failed
		}
	}
	else
	{
		hr = pIEZNcCom->Close(&EZNcCommunication_Error);
		if (hr == S_FALSE) {
			// Close failed
		}
		pIEZNcCom->Release();
	}
	return EZNcCommunication_Error;
}
EzNcsocketCommandVar long NcCommandVar(long CommandVarNumber, bool CommandMode, double &data)
{
	// CommandMode:
	//		true(1): write
	//		false(0): read

	LONG EZNcCommonVariable_Error = 0;
	hr = CreateEZNcCommonVariable(pIEZNcCom, pIEZNcVariable);

	LONG itype = 0;
	if (CommandMode == false)
	{
		pIEZNcVariable->CommonVRead(CommandVarNumber, &data, &itype, &EZNcCommonVariable_Error);
	}
	else
	{
		pIEZNcVariable->CommonVWrite(CommandVarNumber, data, 1, &EZNcCommonVariable_Error);
	}
	pIEZNcVariable->Release();
	return EZNcCommonVariable_Error;
}
EzNcsocketTime long NcTime(long &pDate, long &pGetClockData, long &pGetStartTime, long &pGetRunTime)
{
	LONG EZNcTime_Error = 0;
	hr = CreateEZNcTime(pIEZNcCom, pIEZNcTime);
	pIEZNcTime->GetClockData(&pDate, &pGetClockData, &EZNcTime_Error);
	pIEZNcTime->GetStartTime(&pGetStartTime, &EZNcTime_Error);
	pIEZNcTime->GetRunTime(&pGetRunTime, &EZNcTime_Error);
	pIEZNcTime->Release();
	return EZNcTime_Error;
}
EzNcsocketDevice long NcDevice(char Device_Item[], long Data_Type, bool Device_Read_Write, DWORD &Device_Data)
{
	LONG EZNcDevice_Error = 0;
	hr = CreateEZNcDevice(pIEZNcCom, pIEZNcDevice);
	DWORD Lengh = 2;
	LPCOLESTR Device = 0;
	DWORD Device_Type = EZNC_PLC_BIT;
	LPDWORD Value = 0;
	USES_CONVERSION;
	Device = A2COLE(Device_Item);
	switch (Data_Type)
	{
	case 1:
		Device_Type = EZNC_PLC_BIT;
		break;
	case 2:
		Device_Type = EZNC_PLC_BYTE;
		break;
	case 3:
		Device_Type = EZNC_PLC_WORD;
		break;
	case 4:
		Device_Type = EZNC_PLC_DWORD;
		break;
	default:
		break;
	}
	if (Device_Read_Write == false)
	{
		pIEZNcDevice->ReadBlockDevice(Lengh, Device, Device_Type, &Value, &EZNcDevice_Error);
		Device_Data = *Value;
	}
	else
	{
		Value = &Device_Data;
		pIEZNcDevice->WriteBlockDevice(Lengh, Device, Device_Type, Value, &EZNcDevice_Error);
	}
	pIEZNcDevice->Release();
	return EZNcDevice_Error;
}
EzNcsocketParameter long NcParameter(char Parameter_Data[], long &pItem)
{
	hr = CreateEZNcParameter(pIEZNcCom, pIEZNcParameter);
	LONG EZNcParameter_Error = 0;
	LONG pGroup = 34;
	LONG pSize = 1;
	LONG pAxis = 1;
	LPCOLESTR Value = 0;
	USES_CONVERSION;
	Value = A2COLE(Parameter_Data);
	pIEZNcParameter->SetParameterData2(pGroup, pItem, pSize, pAxis, &Value, &EZNcParameter_Error);
	pIEZNcParameter->Release();
	return EZNcParameter_Error;
}
EzNcSystem long NcSystem(char *ErrorCode)
{
	hr = CreateEZNcSystem(pIEZNcCom, pIEZNcSystem);
	LONG EZNcSystem_Error = 0;
	LONG iMessageNum = 10;
	LONG AlarmType = 0;
	LPOLESTR ppwszBuffer = 0;
	LPTSTR AlarmBuffer = 0;
	pIEZNcSystem->GetAlarm(iMessageNum, AlarmType, &ppwszBuffer, &EZNcSystem_Error);
	USES_CONVERSION;
	const char *test = "";
	test = OLE2A(ppwszBuffer);
	int c = strlen(test);
	for (int i = 0; i <= c; i++)
	{
		*(ErrorCode + i) = *(test + i);
	}
	pIEZNcSystem->Release();
	return EZNcSystem_Error;
}
// CreateObject: Create or delete object
ComObject void NcComObject(bool CreateObject) 	// COM initialization
{
	if (CreateObject)
	{
		CLSID clsid;
		hr = CoInitialize(NULL);
		// Class ID from Program ID
		// "EZSocketNc.EZNcCommunication": Program ID
		hr = CLSIDFromProgID(L"EZSocketNc.EZNcCommunication", &clsid);

		hr = CoCreateInstance(clsid,
			NULL,
			CLSCTX_ALL,
			IID_IEZNcCommunication3,
			(void **)&pIEZNcCom);
	}
	else
	{
		CoFreeUnusedLibraries();
	}
}