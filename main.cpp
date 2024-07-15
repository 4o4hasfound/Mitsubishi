#include "Windows.h"
#include "Mitsubishi_Socket_Communication.h"
#include <iostream>

int main() {
	char ip[4];
	int port;
	std::cin >> ip[0]>>ip[1]>>ip[2]>>ip[3] >> port;
	NcComObject(true);
	long errorMessage = (NcTCPIP(ip, port));
	std::cout << errorMessage;
}