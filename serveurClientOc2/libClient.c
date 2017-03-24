#include "libClient.h"
#include "libCommon.h"


void initClient(int sock,struct sockaddr_in sin,struct hostent *h,char *ip,char *port){
	//Initialisation socket
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		perror("socket");
		exit(2);
	}
	if(!(h=gethostbyname(ip))){
		perror("gethostbyname");
		exit(3);
	}
	//Initialisation de sin
	bzero(&sin,sizeof(sin));
	sin.sin_family = AF_INET;
	bcopy(h->h_addr,&sin.sin_addr,h->h_length);
	sin.sin_port = htons(atoi(port));
	//Tentative de connexion à la socket distante
	if(connect(sock,(struct sockaddr*)&sin,sizeof(sin))<0){
		perror("connect");
		exit(4);
	}
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


void scanHourToWake(int sock,char *nom)
{
	char remplir[6];
	printf("Entrez l'heure a laquelle vous souhaitez etre reveille:\n(Format:HH:MM inutile de preciser les 0 pour les valeurs inferieures a 10)\n\0 ");
	scanf("%s",&remplir);
	printf("Vous souhaitez donc %s, etre reveille a %s \n",nom,remplir);
	printf("Preparation de l'envoi\n");
	char *result = malloc (sizeof (char) * (strlen(nom) + strlen(remplir) + 5));
	strcat(result,"1-");
	strcat(result,nom);
	strcat(result,"-");
	strcat(result,remplir);
	sendMessage(sock,result);
}

