#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libHour.h"
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
	if(N != 4){
		if(strlen(P[3]) > 10){
			fprintf(stderr,"Utilisation: ./client nom_serveur port pseudo ");
			exit(1);
		}
	}
	//Initialisation socket
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		perror("socket");
		exit(2);
	}
	if(!(h=gethostbyname(P[1]))){
		perror("gethostbyname");
		exit(3);
	}

	//Initialisation de sin
	bzero(&sin,sizeof(sin));
	sin.sin_family = AF_INET;
	bcopy(h->h_addr,&sin.sin_addr,h->h_length);
	sin.sin_port = htons(atoi(P[2]));
	//Tentative de connexion à la socket distante
	if(connect(sock,(struct sockaddr*)&sin,sizeof(sin))<0){
		printf("Connect erreur");
		perror("connect");
		exit(4);
	}
	interface(P[3],sock);
	close(sock);
}


void interface(char *nom,int sock){
	int choiceValue;
	printf("Bienvenue sur votre interface de reveil! %s\n",nom);
	printf("Que voulez-vous faire?\n");
	printf("1-Ajouter un réveil\n2-Modifier heure de réveil\n3-Supprimer mon réveil\n4-Quitter\n");
	scanf("%d",&choiceValue);
	switch(choiceValue){
		case 1:
			scanHourToWake(sock,nom);	
			break;
		case 2:
			printf("Modification Reveil\n");
			break;
		case 3:
			printf("Suppression Reveil\n");
			break;
		case 4:
			printf("Arrêt processus..\n");
			exit(5);
			break;
		default:
			printf("Arrêt processus..\n");
			exit(5);
			break;
	};


}
