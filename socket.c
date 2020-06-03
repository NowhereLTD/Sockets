#include "socket.h"

Socket newSocket(int family, int type, int proto) {
	int sockfd = socket(family, type, proto);
	int one = 1;

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

	if (sockfd == -1) {
		exit(-1);
	}
	Socket s;
	s.sockfd = sockfd;
	s.family = family;
	s.type = type;
	s.proto = proto;
	return s;
}

int setSockOpt(Socket* socket, int level, int optName, int* optValue) {
	int result = setsockopt(socket->sockfd, level, optName, optValue, sizeof(int));
	if (result < 0) {
		exit(result);
	}
	return result;
}

int bindSocket(Socket* socket, int port) {
	SockAddrIn addr;
	addr.sinFamily = socket->family;
	addr.sinPort = htons(port);
	addr.sinAddr.sAddr = htonl(INADDR_ANY);
	int size = sizeof(SockAddrIn);
	void* tmp = &addr;
	int result = bind(socket->sockfd, (struct sockaddr_in* ) tmp, size);
	if (result < 0) {
		printf("%i", result);
		exit(result);
	}
	return result;
}

int listenSocket(Socket* socket) {
	int backlog = 128;
	int result = listen(socket->sockfd, backlog);
	if (result < 0) {
		printf("%i", result);
		exit(result);
	}
	return result;
}

Socket listenServer(int port) {
	Socket sock = newSocket(AF_INET, SOCK_STREAM, 0);
	bindSocket(&sock, port);
	listenSocket(&sock);
}

Socket acceptSocket(Socket* socket) {
	struct sockaddr addr;
	int size = 128;
	int sockfd = accept(socket->sockfd, &addr, &size);
	if (sockfd < 0) {
		exit(-1);
	}
	Socket s;
	s.sockfd = sockfd;
	s.family = socket->family;
	s.type = socket->type;
	s.proto = socket->proto;
	return s;
}

char* recvSocket(Socket* socket, int bufsize) {
	char* buffer = malloc(bufsize);
	recv(socket->sockfd, buffer, bufsize, 0);
	return buffer;
}