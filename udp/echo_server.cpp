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

int main(int argc, char* argv[])
{
	int port = (argc>1)?atoi(argv[1]):12345; // server port number

	int sock, child_sock;
	struct sockaddr_in server, client;

	char recv_buffer[MAXBUFFER]; // Buffer to receive the data from client
	int recv_bytes; // number of received bytes

	// Create socket at the server
	if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR)
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
	unsigned int sock_len = sizeof(sockaddr_in);
	if ((bind(sock, (struct sockaddr *) &server, sock_len)) ==ERROR )
	{
		perror("Bind error");
		exit(EXIT_FAILURE);
	}

	cout << "Echo server started on port " << port << endl; // server screen message

	char msg[] = "Hi client! Welcome to the echo server!"; // client screen message
	while(1)
	{
		if(((recv_bytes = recvfrom(sock, &recv_buffer, sizeof recv_buffer, 0,(struct sockaddr *) &client, &sock_len)) == ERROR))
		{
			perror("Accpet error");
			exit(EXIT_FAILURE);
		}

		cout << "Client with IP address " << inet_ntoa(client.sin_addr) << " and port " << ntohs(client.sin_port) << " connected and sent following " << recv_bytes << " bytes" << endl;
		recv_buffer[recv_bytes] = '\0'; // To enforce the string termination 
		cout << recv_buffer << endl;

		int sent_bytes = sendto(sock, recv_buffer, recv_bytes, 0, (struct sockaddr *) &client, sock_len);
		if (sent_bytes == ERROR)
		{
			perror("Send error");
			exit(EXIT_FAILURE);
		}

		cout << "Sent " << sent_bytes << " bits to the client" << endl << endl;
	}

	close(sock);
	return 0;
}