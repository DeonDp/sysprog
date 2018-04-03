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

	int i,sock,sock_recv,addr_size,bytes_received;
	char text[80];
	struct sockaddr_in my_addr,recv_addr;
	unsigned short listen_port=60000;

	int play,xp,yp;
	char *lc;
	

	/* ... socket has been created ... */
	sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
		printf("socket() failed\n");

	/* make local address structure */
	memset(&my_addr, 0, sizeof (my_addr)); /* clr structure */
	my_addr.sin_family = AF_INET; /* address family */
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* my IP */
	my_addr.sin_port = htons(listen_port);


	/* ... socket has been bound ... */
	i=bind(sock, (struct sockaddr *) &my_addr, sizeof (my_addr));
	if (i < 0)
		printf("bind() failed\n");

	
	/* socket is listening */
	i=listen(sock,5);
	if (i < 0)
		printf("listen() failed\n");

     /* ... socket accepted a connection... */
	addr_size=sizeof(recv_addr);
	/* incoming xion -- get new socket to receive data on */
	sock_recv=accept(sock, (struct sockaddr *) &recv_addr,&addr_size);

	bytes_received=recv(sock_recv,text,80,0);
	if (strcmp(text,"start") == 0) {
		startBoard();
		drawBoard();
		printf("Welcome\n");
		play=0;
		while (1) {

			/* receive some data */
			bytes_received=recv(sock_recv,text,80,0);
			text[bytes_received]=0;
			if (strcmp(text,"quit") == 0) {
				printf("quiting server\n");
				break;
			}
			xp=getXcoordinate(text);
			yp=getYcoordinate(text);
			lc=getuserL(text,play);
			printf("%d\n%d\n%s\n",xp,yp,lc);
			makePlay(xp,yp,lc);
			printf("Now Receiving: %s\n",text);
			drawBoard();
			play++;
		}
	}
	

	/* ... socket communication is finished ... */
	i=close(sock_recv);
	if (i < 0)
		printf("close() failed\n");
	close(sock);

}
