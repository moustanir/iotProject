#include "libHour.h"
struct sockaddr_in Sin = {AF_INET};


int main(int N,char *P[]){
	int ln,sock,nsock,pid;
	initServer(sock,ln,Sin);
	serverWait(sock,nsock,pid,Sin,ln);	
}	
