/*
 * udp_client.c
 *
 *  Created on: 29 янв. 2018 г.
 *      Author: jake
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int sock;
	char msg[]="Hi, Server!";
	char buf[256];
	struct sockaddr_in local;
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if (sock < 0)
		{
		perror("socket error");
		exit(1);
		}
	inet_aton("127.0.0.1",&(local.sin_addr));
	local.sin_port = htons(1235);
	local.sin_family = AF_INET;

	sendto(sock,msg,sizeof(msg),0,(struct sockaddr*)&local,sizeof(local));
	recvfrom(sock,buf,sizeof(buf),0,0,0);
	printf("%s\n",buf);

	shutdown(sock,SHUT_RDWR);
	close(sock);

	return 0;
}
