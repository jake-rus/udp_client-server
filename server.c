/*
 * udp_server.c
 *
 *  Created on: 28.01.2018
 *      Author: jake
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

// функция отправки всех данных
int sendall(int sock, char *buf, int len, int flag)
{
	int total =0;
	int n;

	while (total< len)
	{
		n = send(sock,buf+total,len-total,flag);
		if (n == -1) break;
		total += n;
	}
	return (n == -1 ? -1 : total);
}

int main(void)
{
	int sock;
	char msg[]="Hello, Client!!!";
	char buf[256];
	struct sockaddr_in local;
	struct sockaddr_in from;
	int fromlen = sizeof(from);
	// обнуление длины и структур
	memset(&from,0,fromlen);
	bzero(&local, sizeof(local));
	bzero(&from, fromlen);

/* Инициализация сокета*/
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if (sock < 0)
		{
		perror("socket error");
		exit(1);
		}
	//inet_aton("127.0.0.1",&(local.sin_addr));
	local.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // или так
	local.sin_port = htons(1235);
	local.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr*) &local, sizeof(local)) < 0)
		{
		perror("binding error");
		exit(2);
		}

/* Прием пакетов */
	if (recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&from,&fromlen) <0)
		{
		perror("recvfrom error");
		exit(3);
		}
	printf("%s\n",buf);
	sendto(sock,msg,sizeof(msg),0,(struct sockaddr*)&from, fromlen);

/* Закрытие сокета*/
	sleep(1);
	shutdown(sock,SHUT_RDWR);
	close(sock);

	return 0;
}
