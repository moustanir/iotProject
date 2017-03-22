#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

void initClient(int sock,struct sockaddr_in sin,struct hostent *h,char *ip,char *port);
void interface(char *nom,int sock);
char ** str_split(char *a_str,const char a_delim);
struct Reveil serialisation(char nom[]);
