#include "libHour.h"
#include "libClient.h"
#define LBUF 10

/*
 *Code pour le client
 */



void interface(char *nom,int sock);

int main(int N,char *P[]){
  int sock;
  struct sockaddr_in sin;
  struct hostent *h;
  char nom[LBUF],addr[LBUF];
  printf("j\n");
  checkLengthName(P[3]);
  printf("k\n");
  initClient(sock,sin,h,P[1],P[2]);
  printf("l\n");
  interface(P[3],sock);
  printf("m\n");
  close(sock);
}

