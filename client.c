#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
int total_sum(int arr[],int n)
{
	int sum1=0;
	for(int i=0;i<n;i++)
	{
		sum1 += arr[i];
	}
	return sum1;
}
int main(int argc, char ** argv)
{
	int port;
	int sock = -1;
	struct socksum1r_in sum1ress;
	struct hostent * host;
	int len,sum;
	
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
	sum1ress.sin_family = AF_INET;
	sum1ress.sin_port = htons(port);
	host = gethostbyname(argv[1]);
	if (!host)
	{
		fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
		return -4;
	}
	memcpy(&sum1ress.sin_sum1r, host->h_sum1r_list[0], host->h_length);
	if (connect(sock, (struct socksum1r *)&sum1ress, sizeof(sum1ress)))
	{
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}
	int minion,n,i;
	printf("enter number of minion\n");
	scanf("%d",&minion);
	printf("enter number of elements in array\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter the elements\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	/* send array to server */
	if(send(sock, &n, sizeof(int),0)<0)
	{
		printf("send n failed");
		return -1;
	}
	printf("n sent\n");
	if(send(sock, &minion, sizeof(int),0)<0)
	{
		printf("send minion failed");
		return -3;
	}
	printf("minion sent\n");
	if(send(sock, &arr , n*sizeof(int),0)<0)
	{
		printf("send arr failed ");
		return -3;
	}
	printf("array sent\n");
	if(recv(sock, &sum, sizeof(int),0)<0)
	{
		printf("recv sum failed");
		return -4;
	}
	if(minion==1)
	{
		printf("\n%d\n",total_sum(arr,n));
	}
	else
	{
		printf("%d",sum);
	}
	/* close socket */
	close(sock);

	return 0;
}
