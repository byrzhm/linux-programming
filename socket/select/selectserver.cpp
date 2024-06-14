#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <set>

const int SERVERPORT = 65432;
const int SERVERBACKLOG = 5;

fd_set current_sockets;
std::set<int> sockets_set;

int setup_server(int, int);
int accept_new_connection(int);
void handle_connection(int);

int main() {
  int server_socket, client_socket;
  fd_set ready_sockets;

  server_socket = setup_server(SERVERPORT, SERVERBACKLOG);
  sockets_set.insert(server_socket);

  // initialize the set of current sockets
  FD_ZERO(&current_sockets);
  FD_SET(server_socket, &current_sockets);

  for (;;) {
    ready_sockets = current_sockets; // equivalent to memcpy

    // notice: the first argument is the highest file descriptor in the set + 1
    if (select(*sockets_set.rbegin() + 1, &ready_sockets, NULL, NULL, NULL) <
        0) {
      perror("Failed to select");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= *sockets_set.rbegin(); ++i) {
      if (FD_ISSET(i, &ready_sockets)) {
        if (i == server_socket) {
          client_socket = accept_new_connection(server_socket);
          sockets_set.insert(client_socket);
          FD_SET(client_socket, &current_sockets);
        } else {
          handle_connection(i);
        }
      }
    }
  }

  return 0;
}

int setup_server(int port, int backlog) {
  int server_socket, rc;
  struct sockaddr_in server_addr;

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  rc =
      bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (rc < 0) {
    perror("Failed to bind server socket");
    exit(EXIT_FAILURE);
  }

  rc = listen(server_socket, backlog);
  if (rc < 0) {
    perror("Failed to listen on server socket");
    exit(EXIT_FAILURE);
  }

  return server_socket;
}

int accept_new_connection(int server_socket) {
  int client_socket;
  struct sockaddr_in client_addr;
  unsigned addr_size = sizeof(client_addr);

  client_socket =
      accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
  if (client_socket < 0) {
    perror("Failed to accept connection");
    exit(EXIT_FAILURE);
  }

  printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr),
         ntohs(client_addr.sin_port));

  return client_socket;
}

void handle_connection(int client_socket) {
  int rc;
  char buf[1024];
  struct sockaddr_in client_addr;
  unsigned addr_size = sizeof(client_addr);

  getpeername(client_socket, (struct sockaddr *)&client_addr, &addr_size);

  rc = read(client_socket, buf, sizeof(buf));
  if (rc == 0) {
    close(client_socket);
    sockets_set.erase(client_socket);
    FD_CLR(client_socket, &current_sockets);
    printf("Connection closed by %s:%d\n", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));
    return;
  }

  if (rc < 0) {
    perror("Failed to read from client");
    close(client_socket);
    sockets_set.erase(client_socket);
    FD_CLR(client_socket, &current_sockets);
    return;
  }

  buf[rc] = '\0';

  printf("Received message from %s:%d: %s\n", inet_ntoa(client_addr.sin_addr),
         ntohs(client_addr.sin_port), buf);

  return;
}