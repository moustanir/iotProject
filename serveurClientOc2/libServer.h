#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include "libCommon.h"

static struct sockaddr_in Sin = {AF_INET};
void cleanZomb(int S);
int createSocket(int sock);
struct sockaddr_in bindSocket(int sock,struct sockaddr_in Sin);
int  getSockName(int sock,struct sockaddr_in Sin,int sockName,int ln);
void socketListen(int sock);
struct Reveil deserialisation(char* nom);
char* serialisation(struct Reveil reveil);
//Pour initialiser le serveur
int initServer(int sock,int ln,struct sockaddr_in Sin);
void serverWait(int sock,int nsock,int pid,struct sockaddr_in Sin,int ln);
char getTypeValue(char *nom);
