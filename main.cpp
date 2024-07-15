#include "Windows.h"
#include "Mitsubishi_Socket_Communication.h"
#include <iostream>
#include "EZSocketNc.h"
#include "EZSocketNcDef.h"
#include "EZSocketNcErr.h"

int main() {
	NcComObject(true); 
	NcCommunication(EZNC_SYS_MAGICBOARD64, 10, 1);


	char ip[4];
	int port;
	std::cin >> ip[0]>>ip[1]>>ip[2]>>ip[3] >> port;

	long errorMessage = NcTCPIP(ip, port);
	std::cout << errorMessage;
}