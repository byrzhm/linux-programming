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
  struct sockaddr_in address;
  unsigned addrlen = sizeof(address);
  char buf[BUFSZ];
  char ip_str[16];

  signal(SIGCHLD, SIG_IGN);

  if ((lstn_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(lstn_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(lstn_fd, 5) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    conn_fd = accept(lstn_fd, (struct sockaddr *)&address, &addrlen);
    if (conn_fd < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    inet_ntop(AF_INET, &(address.sin_addr), ip_str, INET_ADDRSTRLEN);
    printf("Connected by %s:%d\n", ip_str, ntohs(address.sin_port));

    if (fork() == 0) {
      close(lstn_fd);
      for (;;) {
        ret = read(conn_fd, buf, 1024);
        if (ret == 0) {
          break;
        }

        if (ret < 0) {
          perror("read");
          exit(EXIT_FAILURE);
        }

        buf[ret] = '\0';
        printf("Client: %s\n", buf);
      }
      close(conn_fd);
      printf("Disconnected by %s:%d\n", ip_str, ntohs(address.sin_port));
      exit(0);
    }
    close(conn_fd);
  }

  close(lstn_fd);
  return 0;
}