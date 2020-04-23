	#include <sys/types.h>
  #include <sys/socket.h>
  #include <netdb.h>
	#include <errno.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>

int main(int argc, char *argv[]) {
	char* HOST = argv[1];
  char* PORT = argv[2];

	int sockfd = -1;

	struct addrinfo *servinfo, *p, hints;
	memset(&hints, 00, sizeof(hints));
      hints.ai_family      = AF_UNSPEC;    // IPv4 or IPv6
      hints.ai_socktype    = SOCK_STREAM;  // TCP toggle

  int status = getaddrinfo(HOST, PORT, &hints, &servinfo);
		if (status){
      fprintf(stderr,  "Unable to connect to %s:%s: %s\n", HOST, PORT, gai_strerror(status));
      return 1;
  }

	for(p = servinfo; p && sockfd < 0; p = p->ai_next) {
	  if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
	    //perror("client: socket");
	    continue;
	  }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) < 0) {
      close(sockfd);
      sockfd = -1;
      continue;
    }

  }
		freeaddrinfo(servinfo);
	if (sockfd < 0) {
    fprintf(stderr, "Unable to connect to %s:%s: %s\n", HOST, PORT,strerror(errno));
    exit(1);
  }
	 //else{
		printf("Connected to %s:%s\n", HOST, PORT);
	//}

	FILE *socks = fdopen(sockfd, "w+");
    if (!socks) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(sockfd);
        return 1;
    }

	char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stdin)) {
			fputs(buffer, socks);
			fgets(buffer, BUFSIZ, socks);
			fputs(buffer, stdout);
    }

	fclose(socks);

	return 0;

}

/// referenced echo client from lecture 21
