#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void main(int argc, char* argv[])
{
	printf("Client Program : %s\n", argv[0]);

	int status;
	struct addrinfo hints;
	struct addrinfo* servinfo;	// will point to the resultsv

	memset(&hints, 0, sizeof hints);	// make sure the struct is empty
	hints.ai_family = AF_UNSEPC;		// don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;	// TCP stream sockets

	status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);

	// servinfo now points to a linked list of 1 or more struct addrinfos


	exit(0);
}
