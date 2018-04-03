#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* system type definitions */
#include <sys/socket.h> /* network system functions */
#include <netinet/in.h> /* protocol & struct definitions */
#include <arpa/inet.h>
#include <string.h> 
#include <time.h>
#include <unistd.h> 
#include "MyScrabble.c"

char *main() {

	int i,sock,bytes_sent;
	char text[80],buf[80];
	struct sockaddr_in addr_send;
	char *server_ip="127.0.0.1";
	unsigned short server_port=60000;

	char *uc;

	/* ... socket has been created ... */
	sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
		printf("socket() failed\n");


	/* create socket address structure to connect to */
	memset(&addr_send, 0, sizeof (addr_send)); /* clr structure */
	addr_send.sin_family = AF_INET; /* address family */
	addr_send.sin_addr.s_addr = inet_addr(server_ip);
	addr_send.sin_port = htons(server_port);

	/* ... socket has been connected ... */
	i=connect(sock, (struct sockaddr *) &addr_send, sizeof (addr_send));
	if (i < 0)
		printf("connect() failed\n");


	/* send some data */
	//uc=getPlayerMove();
	//printf("%s sent\n",uc);
	//bytes_sent=send(sock,uc,strlen(uc),0);
	printf("Enter start to begin a new game\n");
	scanf("%s",text);
	bytes_sent=send(sock,text,strlen(text),0);

	while (1){
		/* send some data */
		//printf("Send? ");
		//scanf("%s",text);
		printf("%s sent\n",text);
		uc=getPlayerMove();
		printf("%s sent\n",uc);
		//strcpy(text,uc);
		//printf("%s sent\n",text);
		bytes_sent=send(sock,uc,strlen(uc),0);
		printf("%s sent indeed\n",uc);
		if (strcmp(uc,"quit") == 0) 
			break;
		
	}
	close(sock);
}