
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  int port = 8080;
  int mySocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mySocket == -1) {
    printf("EXIT_FAILURE");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serverAdress;
  memset(&serverAdress, 0, sizeof(serverAdress));

  serverAdress.sin_family = AF_INET;
  serverAdress.sin_port = htons(port);
  serverAdress.sin_addr.s_addr = INADDR_ANY;

  int bindResult =
      (bind(mySocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress)));
  if (bindResult == -1) {
    printf("EXIT_FAILURE");
    exit(EXIT_FAILURE);
  }

  printf("bind success\n");

  if (listen(mySocket, 10) == -1) {
    printf("EXIT_FAILURE");
    exit(EXIT_FAILURE);
  }

  printf("Listening on port %d:\n", port);

  struct sockaddr_in clientAdress;

  socklen_t clientAdressLen = sizeof(clientAdress);

  int clientSocket =
      accept(mySocket, (struct sockaddr *)&clientAdress, &clientAdressLen);

  if (clientSocket == -1) {
    printf("client socket failed.\n");
    close(mySocket);
    exit(EXIT_FAILURE);
  } else {
    printf("Connection established with client %s.\n",
           inet_ntoa(clientAdress.sin_addr));
    char *response = "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/plain\r\n"
                     "Content-Length: 27\r\n\r\n"
                     "hello from my test server.\n";

    send(clientSocket, response, strlen(response), 0);
  }

  close(mySocket);
  close(clientSocket);

  return 0;
}
