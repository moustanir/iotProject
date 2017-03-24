#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

void initClient(int sock,struct sockaddr_in sin,struct hostent *h,char *ip,char *port);
void interface(char *nom,int sock);
void scanHourToWake(int sock,char* nom);
