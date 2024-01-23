#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 33546
#define MSG_MAX_LEN 100

int main()
{
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  char server_message[2000], client_message[2000];

  // Clean buffers:
  memset(server_message, '\0', sizeof(server_message));
  memset(client_message, '\0', sizeof(client_message));

  if (0 > sock)
  {
    perror("Sock");
    exit(-1);
  }

  struct sockaddr_in addr = {0};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("10.100.23.129");

  if (0 > connect(sock, (struct sockaddr *)&addr, sizeof(addr)))
  {
    perror("connect");
    return -1;
  }

  for (int i = 0; i < 1; i++)
  {
    sleep(1);

    char msg[] = "Connect to: 10.100.23.14:42069";
    // msg[0] = i + '0';

    if (0 > sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&addr, sizeof(addr)))
    {
      perror("send");
      return -1;
    }

    char buff[100] = {'\0'};

    if (0 > recv(sock, (char *)buff, sizeof(buff), 0))
    {
      perror("recvfrom");
      return -1;
    }

    printf("%s\n", buff);
  }

  close(sock);

  return 0;
}