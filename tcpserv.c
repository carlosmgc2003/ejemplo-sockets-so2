/*
 * Ejemplo de server TCP.
 */

#include	"inet.h"

#define		SERV_TCP_PORT	8888

int sockfd, newsockfd, clilen, childpid;

void recibir (void)
{
    char linea[2000];
    int longitud;
    int rcv_bytes;
    printf("FUNCION RECIBIR ACTIVADA\n");
    strcpy (linea, "");
    
    do
    {
	longitud = 2000;
	strcpy (linea, "");
	rcv_bytes = recv (newsockfd, linea, longitud, 0);
	linea[rcv_bytes] = '\0';
	printf("socket: %d\total lineas recibidas: %s\n" , newsockfd, linea);
    }
    while (rcv_bytes != 0);
    printf( "TERMINA DE RECIBIR \n");
}

int
main(void)
{
	struct sockaddr_in	cli_addr, serv_addr;
	/*
	 * Open a TCP socket (an Internet stream socket).
	 */

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("server: can't open stream socket");
		return -1 ;
	}
	
	/*
	 * Bind our local address so that the client can send to us.
	 */

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family      = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port        = htons(SERV_TCP_PORT);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		{
		  perror("server: can't bind local address");
		  return -1;
		 }

	listen(sockfd, 5);

	for ( ; ; ) 
	{
		/*
		 * Wait for a connection from a client process.
		 * This is an example of a concurrent server.
		 */

		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
		if (newsockfd < 0)
		{
			perror("server: accept error");
			return -1;
		}

		if ( (childpid = fork()) < 0)
		{
			perror("server: fork error");
			return -1;
		}
		
		else if (childpid == 0) 	/* child process */
			
		{	
			close(sockfd);		/* close original socket */
			recibir();
			close(newsockfd);	
			return 0;
		}

		close(newsockfd);		/* parent process */
	}
}	
	
