#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include "libHour.h"
struct sockaddr_in Sin = {AF_INET};

void cleanZomb(int S){
	wait(NULL);
}


int main(int N,char *P[]){
	int ln,sock,nsock,pid;
	
	//On supprime d'abord l'ensemble des processus zombie.
	signal(SIGCHLD,cleanZomb);
	
	//Création de la socket
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		//On arrête le programme dans le cas où la socket n'a pu être créée.
		perror("socket");
		exit(1);
	}
	//On attache la socket au port voulu
	if(bind(sock,(struct sockaddr*)&Sin,sizeof(Sin))<0){
		//On arrête le programme dans le cas où la socket n'a pu se lier à un port.
		perror("bind");
		exit(2);
	}
	ln = sizeof(Sin);
	int sockName;
	//On retourne le nom de la socket.
	if( sockName = getsockname(sock,(struct sockaddr*)&Sin,(socklen_t*)&ln) < 0){
		//On arrête le programme dans le cas où le programme n'a pu récupérer le nom de la socket
		perror("getsockname");
		exit(3);
	}
	printf("Le serveur est attache au port %u\n",ntohs(Sin.sin_port));
	checkHour();
	//Définition du nombre d'appels simultanés autorisés
	if(listen(sock,5) < 0){
		perror("listen");
		exit(4);
	}
	char tab[100];
	for(;;){
		if((nsock=accept(sock,(struct sockaddr*)&Sin,(socklen_t*)&ln))<0){
			perror("accept");
			exit(5);
		}
		if((pid=fork())== -1){
			perror("fork");
			exit(6);
		}
		if(pid == 0){
			printf("Reception message\n");
			char valueChosen = '3';
			read(nsock,(void*)&valueChosen,sizeof(valueChosen));
			printf("Valeur reçue: %s\n",valueChosen);
			reveil(nsock,sock,valueChosen);
		}
		close(nsock);
	}
	
}	
