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
	printf("j\n");
	checkLengthName(P[3]);
	printf("k\n");
	initClient(sock,sin,h,P[1],P[2]);
	printf("l\n");
	interface(P[3],sock);
	printf("m\n");
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
