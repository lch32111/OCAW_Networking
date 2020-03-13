#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/* Some notes for studying network

struct sockaddr
{
	unsigned short 	sa_family;	// address family AF_xxx : AF_INET or AF_INET6
	char 		sa_data[14];	// 14 bytes of protocol address
};

this is the important bit: a pointer to a struct sockaddr_in 
can be cast to a pointer to a struct sockaddr and vice-versa

// Internet address ( a structure for historical reasons )
struct in_addr
{
	uint32_t s_addr;	// that's a 32-bit int (4 bytes)
};

struct sockaddr_in
{
	short int		sin_family;	// Address family, AF_INET
	unsigned short int	sin_port;	// Port number
	struct in_addr		sin_addr;	// Internet address
	unsigned char		sin_zero[8];	// Same size as struct sock addr
};

struct in6_addr
{
	unsigned char s6_addr[16];	// Ipv6 address
};

struct sockaddr_in6
{
	u_int16_t	sin6_family;	// address family, AF_INET6
	u_int16_t	sin6_port;	// port number, Network Byte Order
	u_int32_t	sin6_flowinfo;	// IPv6 flow information
	struct in6_addr sin6_addr;	// IPv6 address
	u_int32_t	sin6_scope_id;	// ScopeID
};

struct sockaddr_storage
{
	sa_family_t 	ss_family;	// address family

	// all this is padding, implementation specific, ignore it:
	char	__ss_pad1[_SS_PAD1SIZE];
	int64_t	__ss_align;
	char	__ss_pad2[_SS_PAD2SIZE];
};


int getaddrinfo(const char* node 		// e.g. "www.example.com" or IP
		const char* service		// e.g. "http" or port number
		const struct addrinfo* hints,
		struct addrinfo** res);
*/
