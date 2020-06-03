#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#ifndef __SOCKET_H
#define __SOCKET_H

typedef struct {
	int sockfd;
	int family;
	int type;
	int proto;
} Socket;

typedef struct {
	int sAddr;
} InAddr;

typedef struct {
	int sinFamily;
	int sinPort;
	InAddr sinAddr;
} SockAddrIn;

typedef struct {
	int aiFamily;
	int aiSockType;
	int aiFlags;
	int aiProtocol;
	int aiAddrLen;
	void* aiAddr;
	void* aiCanonName;
	void* aiNext;
} AddrInfo;

Socket newSocket(int family, int type, int proto);
int setSockOpt(Socket* socket, int level, int optName, int* optValue);
int bindSocket(Socket* socket, int port);
int listenSocket(Socket* socket);
char* recvSocket(Socket* socket, int bufsize);
Socket listenServer(int port);
Socket acceptSocket(Socket* socket);

#endif