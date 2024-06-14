#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 65432;
const int BUFSZ = 1024;

int main() {
  int lstn_fd, conn_fd, ret;
  unsigned addr_len;
  struct sockaddr_in server_addr, client_addr;
  char buf[BUFSZ];
  char ip_str[16]; // XXX.XXX.XXX.XXX\0

  lstn_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (lstn_fd < 0) {
    perror("\nsocket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY; // any interface

  ret = bind(lstn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0) {
    perror("\nbind");
    exit(1);
  }

  ret = listen(lstn_fd, 5);
  if (ret < 0) {
    perror("\nlisten");
    exit(1);
  }

  addr_len = sizeof(client_addr);
  conn_fd = accept(lstn_fd, (struct sockaddr *)&client_addr, &addr_len);
  if (conn_fd < 0) {
    perror("\naccept");
    exit(1);
  }

  inet_ntop(AF_INET, &(client_addr.sin_addr), ip_str, INET_ADDRSTRLEN);
  printf("Connected by %s:%d\n", ip_str, ntohs(client_addr.sin_port));

  for (;;) {
    ret = read(conn_fd, buf, BUFSZ);
    if (ret < 0) {
      perror("\nread");
      exit(1);
    }

    if (ret == 0) {
      printf("\nClient disconnected\n");
      break;
    }

    buf[ret] = '\0';

    printf("\nReceived: %s", buf);
  }

  close(conn_fd);
  close(lstn_fd);
  return 0;
}