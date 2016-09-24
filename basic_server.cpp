#include <cstdio> // perror
#include <iostream> // cout, cin 
#include <cstdlib> // exit, EXIT_FAILURE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // inet_ntoa()
#include <arpa/inet.h> // inet_ntoa()
#include <cstring> // memset() - zero padding
#include <unistd.h> // close() - closing the socket

using namespace std;

#define ERROR -1
#define MAXBUFFER 1024
#define MAX_CLIENTS 5

int main(){
	int port = 1234;

	int server_sock, client_sock;
	struct sockaddr_in server, client;

	// message
	char msg[] = "Hi client! Welcome to my server!";

	// Create parent socket at the server
	if( (server_sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("Socket error");
		exit(EXIT_FAILURE);
	}

	// Create server adderess data structure
	server.sin_family = AF_INET; // IPv4
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY; // All interfaces
	memset(&server.sin_zero, 0, 8); // last 8 bytes 

	// Bind
	unsigned int len = sizeof(sockaddr_in);
	if ((bind(server_sock, (struct sockaddr *) &server, len)) ==ERROR )
	{
		perror("Bind error");
		exit(EXIT_FAILURE);
	}

	// Listen
	if((listen(server_sock, MAX_CLIENTS) == ERROR)) // 5 clients
	{
		perror("Listen error");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		if(((client_sock = accept(server_sock, (struct sockaddr *) &client, &len)) == ERROR))
		{
			perror("Accpet error");
			exit(EXIT_FAILURE);
		}

		cout << "Client with IP address " << inet_ntoa(client.sin_addr) << " and port " << ntohs(client.sin_port) << "connected" << endl;

		int sent_bytes = send(client_sock, msg, strlen(msg), 0);

		cout << "Sent bytes " << sent_bytes << endl;

		close(client_sock);
	}

	return 0;
}