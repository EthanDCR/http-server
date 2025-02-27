
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int mySocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mySocket == -1) {
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in serverAdress;
  memset(&serverAdress, 0, sizeof(serverAdress));

  serverAdress.sin_family = AF_INET;
  serverAdress.sin_port = htons(8080);
  serverAdress.sin_addr.s_addr = INADDR_ANY;

  int bindResult =
      (bind(mySocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress)));
  if (bindResult == -1) {
    exit(EXIT_FAILURE);
  }

  if (listen(mySocket, 10) == -1) {
    exit(EXIT_FAILURE);
  }

  return 0;
}
