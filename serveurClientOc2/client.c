#include "libHour.h"
#include "libClient.h"
#define LBUF 10

/*
 *Code pour le client
 */

int main(int N,char *P[]){
  int sock;
  struct sockaddr_in sin;
  struct hostent *h;
  char nom[LBUF],addr[LBUF];
  checkLengthName(P[3]);
  initClient(sock,sin,h,P[1],P[2]);
  interface(P[3],sock);
  close(sock);
 }

/*
int main(int argc, char** argv) {
	char test[] = "1-toto-8h53";
	char* sd =  malloc (sizeof (char) * strlen("1-toto-8h53"));
	strcpy(sd, serialisation(deserialisation(test)));
	assert(strcmp("1-toto-8h53", sd) == 0);

	struct Reveil reveil;
	reveil.nom = "toto";
	reveil.hour ="8:3";
	struct Reveil ds = deserialisation(serialisation(reveil));
	assert(strcmp(reveil.nom, ds.nom) == 0);
	assert(strcmp(reveil.hour, ds.hour) == 0);

	return 0;
}*/
