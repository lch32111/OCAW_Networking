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
Description of getaddrinfo :
    Given node and service, which identify an internet host and a service,
    getaddrinfo() returns one or more addrinfo structures, each of which
    contains an Internet addreess that can be specified in a call to bind(2)
    or connect(2). The getaddrinfo() function combines the functionality 
    provided by the gethostbyname(3) and getservbyname(3) functions into
    a single interface, but unlike the latter functions, getaddrinfo() is
    reentrant and allows programs to eliminate IPv4-versus-IPv6 dependencies

    The addrinfo structure used by getaddrinfo() contains the following fields:

        struct addrinfo
        {
            int                 ai_flags;
            int                 ai_family;
            int                 ai_socktype;
            int                 ai_protocol;
            socklen_t           ai_addrlen;
            struct sockaddr*	ai_addr;
	    char*		ai_canonname;
	    struct addrinfo*	ai_next;
        };
	
    The hints argument points to an addrinfo structure that specifies
    criteria for selecting the socket address structures returned in the
    list pointed to by res. If hints is not NULL it points to an
    addrinfo structure whose ai_family, ai_socktype, and ai_protocol
    specify criteria that limit the set of socket addresses returned by
    getaddrinfo(), as follows:~~

*/

void main(int argc, char* argv[])
{
	printf("Program : %s\n", argv[0]);

	int status;
	struct addrinfo hints;
	struct addrinfo* servinfo;  // will point to the results
    
    memset(&hints, 0, sizeof hints);    // make sure the struct is empty 
    hints.ai_family = AF_UNSPEC;        // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;        // fill in my IP for me

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // servinfo now points to a linked list of 1 or more struct addrinfos

    // ... do everything until you don't need servinfo anymore ...
    
    freeaddrinfo(servinfo); // free the linked-list.
}
