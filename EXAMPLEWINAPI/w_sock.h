#pragma once

#pragma comment(lib,"ws2_32.lib")
#include "winsock2.h"
#include "windows.h"
#include "vector"
using namespace std;
#pragma warning(disable:4996)
class w_sock
{
public:
	SOCKADDR_IN addr;
	int size_addr;
	SOCKET sock;
	vector<SOCKET>connections;
	vector<string>data;
};

