#include <cstdio> // perror
#include <iostream> // cout, cin 
#include <cstdlib> // exit, EXIT_FAILURE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // inet_ntoa()
#include <arpa/inet.h> // inet_ntoa()
#include <cstring> // memset() - zero padding
#include <unistd.h> // close() - closing the sock

#include <string> //getline -- user input

using namespace std;

#define ERROR -1
#define MAXBUFFER 1024

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in server;

	// Create client sock
	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("Socket error");
		exit(EXIT_FAILURE);
	}

	// Create server adderess data structure
	server.sin_family = AF_INET; // IPv4
	server.sin_port = htons(atoi(argv[2])); // server port
	server.sin_addr.s_addr = inet_addr(argv[1]); // server IP
	memset(&server.sin_zero, 0, 8); // last 8 bytes 

	// Connect with the server
	if ((connect(sock, (struct sockaddr *) &server, sizeof server)) == ERROR)
	{
		perror("Connect error");
		exit(EXIT_FAILURE);
	}

	cout << "Connected to server with IP address " << inet_ntoa(server.sin_addr) << " and port " << ntohs(server.sin_port) << endl;

	while(1)
	{
		string input;
		getline(cin, input); // read user input
		send(sock, input.c_str(), input.length(), 0); // send it to server

		char recv_buffer[MAXBUFFER];
		int len = recv(sock, &recv_buffer, sizeof recv_buffer, 0);
		recv_buffer[len] = '\0'; // enforcing the end of string

		cout << "Recieved: " << recv_buffer << endl;
	}

	close(sock);
}