#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv)
{
	int port;
	int sock = -1;
	struct sockaddr_in address;
	struct hostent * host;
	int len;
	
	/* checking commandline parameter */
	if (argc != 3)
	{
		printf("usage: %s hostname port text\n", argv[0]);
		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[2], "%d", &port) <= 0)
	{
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	/* create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
		return -3;
	}

	/* connect to server */
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname(argv[1]);
	if (!host)
	{
		fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
		return -4;
	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
	{
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}
	int n,low,up;
	/* sup text to server */
	read(sock, &n, sizeof(int));
	int arr[n];
	if(recv(sock, arr, n*sizeof(int),0)<0)
	{
		printf("recv arr failed");
		return -6;
	}
	if(recv(sock, &low , sizeof(int),0)<0)
	{
		printf("recv low failed");
		return -7;
	}
	//printf("\n low = %d \n",low);
	if(recv(sock, &up , sizeof(int),0)<0)
	{
		printf("recv up failed");
		return -8;
	}
	//printf("\n up = %d \n",up);

	int i,sum=0;
	for(i=low;i<=up;i++)
	{
		sum+=arr[i];
	}
	//printf("\n sum = %d \n",sum);
	if(sup(sock, &sum ,sizeof(int),0)<0)
	{
		printf("sup sum failed");
		return -9;
	}
	/* close socket */
	close(sock);

	return 0;
}
