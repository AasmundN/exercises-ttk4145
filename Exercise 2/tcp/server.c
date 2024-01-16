#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 33546

int main()
{
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (0 > sock)
  {
    perror("socket");
    return -1;
  }

  /*
   * Configure server
   */
  struct sockaddr_in server = {0};
  server.sin_family = AF_INET;
  server.sin_port = htons(42069);

  if (0 > bind(sock, (struct sockaddr *)&server, sizeof(server)))
  {
    perror("bind");
    return -1;
  }

  if (0 > listen(sock, 5))
  {
    perror("listen");
    return -1;
  }

  printf("Listening...\n");

  struct sockaddr_in conn;

  socklen_t len = (socklen_t)sizeof(conn);

  int connfd = accept(sock, (struct sockaddr *)&conn, &len);

  if (0 > connfd)
  {
    perror("accept");
    return -1;
  }

  int flags = 1;
  setsockopt(connfd, IPPROTO_TCP, TCP_NODELAY, (void *)&flags, sizeof(flags));

  while (1)
  {
    char buffer[100] = {'\0'};
    printf("Write message: ");
    fgets(buffer, sizeof(buffer), stdin);

    char *newline = strchr(buffer, '\n');
    int index = (int)(newline - buffer);

    buffer[index] = '\0';

    if (0 > send(connfd, buffer, sizeof(buffer), 0))
    {
      perror("sendto");
      return -1;
    }

    int len = recv(connfd, buffer, sizeof(buffer), 0);

    if (0 > len)
    {
      perror("recv");
      return -1;
    }

    buffer[len] = '\0';
    printf("\n%s\n\n", buffer);
  }

  close(sock);
  close(connfd);

  return 0;
}