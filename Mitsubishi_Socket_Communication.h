#pragma once
#pragma once

#include <iostream>

#define EzNcsocketTCPIP
EzNcsocketTCPIP long NcTCPIP(char Mechine_IP[], long IP_Port);

#define EzNcsocketCom
EzNcsocketCom long NcCommunication(long Mechine_SystemType, long Mechine_Number, bool Mechine_OpenClose);

#define EzNcsocketCommandVar
EzNcsocketCommandVar long NcCommandVar(long CommandVarNumber, bool CommandMode, double& data);

#define EzNcsocketTime
EzNcsocketTime long NcTime(long& pDate, long& pGetClockData, long& pGetStartTime, long& pGetRunTime);

#define EzNcsocketDevice 
EzNcsocketDevice long NcDevice(char Device_Item[], long Data_Type, bool Device_Read_Write, DWORD& Device_Data);

#define EzNcsocketParameter
EzNcsocketParameter long NcParameter(char Parameter_Data[], long& pItem);

#define EzNcSystem
EzNcSystem long NcSystem(char* ErrorCode);

#define ComObject
ComObject void NcComObject(bool CreateObject);