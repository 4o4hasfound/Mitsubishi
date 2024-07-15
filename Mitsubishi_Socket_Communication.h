#pragma once
#pragma once

#define EzNcsocketTCPIP __declspec (dllimport)
EzNcsocketTCPIP long NcTCPIP(char Mechine_IP[], long IP_Port);

#define EzNcsocketCom __declspec (dllimport)
EzNcsocketCom long NcCommunication(long Mechine_SystemType, long Mechine_Number, bool Mechine_OpenClose);

#define EzNcsocketCommandVar __declspec (dllimport)
EzNcsocketCommandVar long NcCommandVar(long CommandVarNumber, bool CommandMode, double& data);

#define EzNcsocketTime __declspec (dllimport)
EzNcsocketTime long NcTime(long& pDate, long& pGetClockData, long& pGetStartTime, long& pGetRunTime);

#define EzNcsocketDevice __declspec (dllimport)
EzNcsocketDevice long NcDevice(char Device_Item[], long Data_Type, bool Device_Read_Write, DWORD& Device_Data);

#define EzNcsocketParameter __declspec (dllimport)
EzNcsocketParameter long NcParameter(char Parameter_Data[], long& pItem);

#define EzNcSystem __declspec (dllimport)
EzNcSystem long NcSystem(char* ErrorCode);

#define ComObject __declspec (dllimport)
ComObject void NcComObject(bool CreateObject);