#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSG_MAX_LEN 100
#define PORT 20004

void *reciever()
{
  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (0 > sock)
  {
    perror("Socket");
    exit(-1);
  }

  struct sockaddr_in addr = {0};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);

  if (0 > bind(sock, (struct sockaddr *)&addr, sizeof(addr)))
  {
    perror("Bind");
    exit(-1);
  }

  char buff[MSG_MAX_LEN] = {'\0'};

  int len = recvfrom(sock, (char *)buff, MSG_MAX_LEN, MSG_WAITALL, (struct sockaddr *)&addr, NULL);

  printf("%s\n", buff);

  close(sock);

  return NULL;
}

void *sender(void *args)
{
  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (0 > sock)
  {
    perror("Sock");
    exit(-1);
  }

  struct sockaddr_in addr = {0};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("10.100.23.129");

  if (0 > sendto(sock, (char *)args, strlen((char *)args), 0, (struct sockaddr *)&addr, sizeof(addr)))
  {
    perror("sendto");
    exit(-1);
  }

  close(sock);
}

int main(int argc, char *argv[])
{
  pthread_t reciever_thread, sender_thread;

  pthread_create(&reciever_thread, NULL, reciever, "Reciever thread");
  pthread_create(&sender_thread, NULL, sender, (void *)argv[1]);

  pthread_join(reciever_thread, 0);
  pthread_join(reciever_thread, 0);

  return 0;
}