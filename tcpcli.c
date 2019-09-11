/*
 * Ejemplo de cliente TCP
 */

#include	"inet.h"
#include <stdlib.h>

int sockfd;

/* Envia caracteres */

int
enviar (void)
{
    char linea [2000];
    printf("FUNCION ENVIAR ACTIVA\n");
    for (; ;)
    {
	printf("COMPLETE LINEA A ENVIAR - salir - 0\n");
	gets (linea);
	send( sockfd, linea, strlen(linea), 0);
	if (strcmp (linea, "salir") == 0)
	    return 0;
    }
}


int main(int argc, char ** argv)
{
	struct sockaddr_in	serv_addr;

	char * pname = argv[0];

	/*
	 * Fill in the structure "serv_addr" with the address of the
	 * server that we want to connect with.
	 */

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); /* SERV_HOST_ADDR */
	serv_addr.sin_port        = htons(SERV_PORT_ADDR);

	/*
	 * Open a TCP socket (an Internet stream socket).
	 */

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("client: can't open stream socket\n");
		return -1 ;
	}	
	/*
	 * Connect to the server.
	 */

	if (connect(sockfd, (struct sockaddr *) &serv_addr,
							sizeof(serv_addr)) < 0)
	{
		perror("client: can't connect to server");
		return -1 ;
	}
	
	enviar();		/* envia caracteres por el socket */

	close(sockfd);
	exit(0);
}
