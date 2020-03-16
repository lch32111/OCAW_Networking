/*
From Page 22 ~

#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);

So the most correct thing to do is
to use AF_INET in your sockaddr_in and
PF_INET in your call to socket().

What you really want to do is use the values from
the results of the call to getaddrinfo() and
feed them into socket() directly like this:

int s;
struct addrinfo hints, *res;

// do the lookup
// [pretend we already filled out the "hints" struct]
getaddrinfo("www.example.com", "http", &hints, &res);

// again you should do error-checking on getaddrinfo(), and walk
// the "res" linked list looking for valid entries instead of just
// assuming the first one is good (like many of these examples do).
// See the section on client/server for real examples.

s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

bind() - What port am I on?
Once you have a socket, you might have to associate that socket with a port on your local machine.
(This is commonly done if you're going to listen() for incoming connections on specific port -
multiplayer network games do this when they tell you to "connect to 192.168.5.10 port 3490".)
The port number is used by the kernel to match an incoming packet to a certain process's socket
descriptor. If you're going to only be doing a connect() (because you're the client, not ther server),
this is probably be unnecessary. Read it anyway, just for kicks.

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


Here is the synopsis for the bind() system call:

#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr* my_addr, int addrlen);

sockfd is the socket file descriptor returned by socket(). my_addr is a pointer to a struct
sockaddr that contains information about your address, namely, port and IP address.
addrlen is the length in bytes of that address

s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
bind(s, res->ai_addr, res->ai_addrlen);

connect() - Hey, you!

int connect(int sockfd, struct sockaddr* serv_addr, int addrlen);

sockfd = socket(res->ai_family, res_ai_socktype, res->ai_protocol);

connect(sockfd, res->ai_addr, res->ai_addrlen);

Also, notice that we didn't call bind(). Basically, we don't care about our local port number;
we only care where we're going (the remote port). The kernel will choose a local port for us, and
the site we connect to will automatically get this information from us. No worries.

listen() - Will somebody please call me?
you want to wait for incoming connections and handle them in some way.
The process is two step: first you listen(), then you accept().

int listen(int sockfd, int backlog);

backlog is the number of connections allwed on the incoming queue. What does that mean?
Well, incoming connectiosn are going to wait in this queue until you accept() them and
this is the limit on how many can queue up. Most systems silently limit this number to
about 20; you can probably get away with setting it to 5 or 10.

Well, as you can probably imagine, we need to call bind() before we call listen() so that
the server is running on a specific port. (You have to be able to tell your buddies which
port to connect to!) So if you're going to be listening for incoming connections, the sequence
of system calls you'll make is

getaddrinfo();
socket();
bind();
listen();
/ accept goes here/

accept() - "Thank you for calling port 3490."

You call accept() and you tell it to get the pending connection. It'll return
to you a brand new socket file descriptor to use for this single connection!

the newly created socket is finally ready to send() and recv().

int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);

addr will usually be a pointer to a local struct sockaddr_storage. This is where the information
about the incoming connection will go (and with it you can determine which host is calling you 
from which port). addrlen is a local integer variable that should be set to sizeof(struct sockaddr_storage)
before its address is passed to accept()


send() and recv() - Talk to me, baby!
These two functions are for communicating over stream sockets or connected datagram sockets.
If you want to use regular unconnected datagram sockets, you'll need to see the section on sendto()
and recvfrom(), below.

int send(int sockfd, const void* msg, int len, int flags);
msg is a pointer to the data you want to send, and len is the length of that data in bytes.
Just set flags to 0. (See the send() man page for more information concerning flags.)

send() returns the number of bytes actually sent out - this might be less than the nubmer you told it
to send! 


int recv(int sockfd, void* buf, int len, int flags);

buf is the buffer to read the information into, len is the maximum length of the buffer,
and flags can again be set to 0.

recv returns the number of bytes actually read into the buffer, or -1 on error (with errno set, accordingly).

Wait! recv() can return 0. This can meany only one thing: the remote side has closed the connection on you!
A return value of 0 is recv()'s way of letting you know this has occurred.


sendto() and recvfrom() - Talk to me, DGRAM-style

int sendto(int sockfd, const void* msg, int len, unsigned int flags, const struct sockaddr* to, socklen_t tolen);

to is a pointer to a struct sockaddr (which will probably be another struct sockaddr_in or struct sockaddr_in6
or struct sockaddr_storage that you cast at the last minute) which contains the destination IP address and port.
tolen, an int dep down, can simply be set to sizeof *to or sizeof(struct sockaddr_storage).


int recv(int sockfd, void* buf, int len, unsigned int flags,
	 struct sockaddr* from, int* fromlen);
from is a pointer to local struct sockaddr_storage that will be filled with the IP address and port
of the originating machine. fromlen is a pointer to a local int that should be initializd to sizeof
*from or sizeof(struct sockaddr_storage).
When the function returns, fromlen will contain the length of the address actually stored in from.

Remember, if you connect() a datagram socket, you can then simply use send() and recv() for all your
transactions. The socket itself is still a datagram socket and the packets still use UPD, but
the socket interface will automatically add the destination and source information for you.

close() and shutdown() - Get outta my face!

You can just use the regular Unix file descriptor clsoe() function: close(sockfd);
This will prevent any more reads and writes to the socket. Anyone attempting to read or
write the socket on the remote end receive an error.

Just in case you want a little more control over how the socket closes, you can use the shutdown() function.
It allows you to cut off communication in a certain direction, or both ways (just like close() does).
Synopsis:

int shutdown(int sockfd, int how);
how is one of the following:
	0 / Further receives are disallowed
	1 / Further sends are disallowed
	2 / Further sends and receives are disallowed (like close())

(Except to remember that if you're using Windows and Winsock that you should call closesocket()
 instead of close().)

getpeername() - Who are you?

The function getpeername() will tell you who is at the other end of a connected stream socket.
The synopsis:

int getpeername(int sockfd, struct sockaddr* addr, int* addrlen);

gethostname() - Who am I?

It returns the name of the computer that your program is running on.
The name can then be used by gethostbyname(), below, to determine the IP address
of your local machine.

#include <unistd.h>

int gethostname(char* hostname, size_t size);
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char hostnamebuf[128] = {0, };

	if(gethostname(hostnamebuf, 128) == 0)
		printf("host name : %s\n", hostnamebuf);

	return 0;
}
























