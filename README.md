# SocketLab: Basic socket programs in C++

## TCP models
Here is a summary of the files in the tcp folder:
- basic_server.cpp: Starts a basic TCP server that sends a welcome string to the client. Specify the port as the input argument or a default port 12345 is used. Use telnet to connect to this server.
- echo_server.cpp: Starts an echo client. Specify the port as the input argument or a default port 12345 is used. Works with telnet too.
- echo_client.cpp: Starts an echo client. Specify IP address of the server and the port to connect to. Write messages and hear back the same message from the echo server.
- compute_server.cpp: Calculates the sum of the numbers it receives from the client and sends it to the client.
- compute_client.cpp: Reads the numbers from "numbers.txt" and sends them to compute server to get the sum of those numbers. Specify the IP address and the port of the compute server as arguments.
- numbers.txt: Contains the numbers needed by compute client.

## UDP models
Here is a summary of the files in the udp folder:
- echo_server.cpp: Starts the echo server. Clients can use the IP and port of this server to send data to it which will be echoed.
- test_echo_server: Executable bash script. Send string to the echo_server using UDP.

## Background material
- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/)
- [Video tutorials](https://www.youtube.com/playlist?list=PL0JmC-T2nhdgJ2Lw5YdufR8MffaQdAvEf) from TheSecurityTube 

## Contributor
[Pranav Sakulkar](http://www-scf.usc.edu/~sakulkar/)