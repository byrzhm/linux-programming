#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// const char IP[] = "127.0.0.1";
const char IP[] = "10.29.98.43";
const int PORT = 65432;
const int BUFSZ = 1024;

int main() {
  int sock_fd, ret;
  struct sockaddr_in server_addr;
  char buf[BUFSZ];

  sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock_fd < 0) {
    perror("\nsocket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, IP, &(server_addr.sin_addr));

  ret = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0) {
    perror("\nconnect");
    exit(1);
  }

  for (;;) {
    printf("\nSend: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
      break;
    }

    ret = write(sock_fd, buf, strlen(buf));
    if (ret < 0) {
      perror("\nwrite");
      exit(1);
    }

    if (strcmp(buf, "exit\n") == 0) {
      break;
    }
  }

  close(sock_fd);
  return 0;
}
