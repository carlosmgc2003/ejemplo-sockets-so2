/*
	manda_tcp.c
*/

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<stdio.h>
#include	<string.h>

#define		SERV_PORT_ADDR		8888

int sockfd;

int
mandar ( void )
{
	char linea[2000];

	printf("Dentro de mandar\n");

	for ( ; ; )
	{
		printf("Linea a mandar: ");
		gets(linea);
		send( sockfd, linea, strlen(linea), 0);
		if ( strcmp(linea, "salir") == 0 )
			return 0;
	}


}

int
main ( int argc , char ** argv )
{
	struct sockaddr_in serv_addr;

	if ( argc != 2 )
	{
		printf("Usage: %s <address>\n", argv[0]);
		return -1;
	}

	bzero( (char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(SERV_PORT_ADDR);

	/* Opens TCP socket */
	if ( ( sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 )
	{
		perror( "client: No anduvo socket()\n");
		return -1;
	}

	/* Connects */
	if ( connect (sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0 )
	{
		perror("client: No anduvo connect()\n");
		return -1;
	}

	mandar();

	close(sockfd);

	return 0;
}

