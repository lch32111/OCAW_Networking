#include <stdio.h>
#include <inttypes.h>
#include <arpa/inet.h>

// Reference struct
struct sockaddr_ref
{
	unsigned short 	sa_family;	// address family, AF_XXX
	char		sa_data[14];	// 14 bytes of protocl address
};

struct addrinfo_ref
{
	int ai_flags;			// AI_PASSIVE, AI_CANONNAME, etc.
	int ai_family;			// AF_INET, AF_INET6, AF_UNSPEC
	int ai_socktype;		// SOCK_STREAM (TCP), SOCK_DGRAM (UDP)
	int ai_protocol;		// use 0 for "any"
	size_t ai_addrlen;		// size of ai_addr in bytes
	struct sockaddr_ref* ai_addr;	// struct sockaddr_in or _in6
	char* ai_canonname;		// full canonical hostname

	struct addrinfo_ref* ai_next;	// linked list, next node
};

struct in_addr_ref
{
	uint32_t s_addr;	// that's a 32-bit int (4 bytes)
};

struct sockaddr_in_ref
{
	short int 		sin_family;	// Address family, AF_INET
	unsigned short int 	sin_port;	// Port number
	struct in_addr_ref	sin_addr;	// Internet address
	unsigned char		sin_zero[8];	// Same size as struct sockaddr
};

struct in6_addr_ref
{
	unsigned char s_addr[16];	// IPv6 address
};

struct sockaddr_in6_ref
{
	u_int16_t 		sin6_family;	// address family, AF_INET6
	u_int16_t 		sin6_port;	// port number, Network Byte Order
	u_int32_t 		sin6_flowinfo;	// IPv6 flow information
	struct in6_addr_ref 	sin6_addr;	// IPv6 address
	u_int32_t		sin6_scope_id;	// Scope ID
};

int main(int argc, char* argv[])
{
	printf("Hello Networking World!\n");

	struct sockaddr_in sa;
	int ret = 0;

	ret = inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr));
	if (ret == 1)
	{
		printf("Success on inet_pton\n");
	}
	else
	{
		printf("Fail on inet_pton\n");
	}

	printf("sockaddr_in print\n");

	printf("sin_family : %hd\n", sa.sin_family);
	printf("sin_port : %hu\n", sa.sin_port);
	printf("sin_addr.s_addr : %"PRIu32"\n", sa.sin_addr.s_addr);

	printf("INET_ADDRSTRLEN : %d\n", INET_ADDRSTRLEN);
	printf("INET6_ADDRSTRLEN : %d\n", INET6_ADDRSTRLEN);

	char ip4[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
	printf("The IPv4 address is %s\n", ip4);

	return 0;
}
