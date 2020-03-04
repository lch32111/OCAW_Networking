#include <stdio.h>
#include <inttypes.h>
#include <arpa/inet.h>

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
