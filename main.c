#include "socket.h"
#include <stdio.h>

int main() {
	Socket s = listenServer(1024);

	while (1) {
		Socket client = acceptSocket(&s);
		char* buffer = recvSocket(&client, 1024);
		printf("%s\n", buffer);
	}

	return 0;
}