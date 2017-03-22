#include "libHour.h"

//Retourne l'heure sur la machine
char* checkHour(){
	//Renvoi l'heure et les minutes
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char *hour;
	char *min;
	char *tps;
	sprintf(hour,"%d",tm.tm_hour);
	sprintf(min,"%d",tm.tm_min);
	tps=strcat(hour,":");
	tps=strcat(tps,min);
	printf("Il est %s",tps);
	return tps;

}

//Vérifie si le client est toujours connecté au serveur
void checkConnected(){

}

void insertHourWake(struct Reveil *tabReveil,int sock) // Insert la nouvelle heure du réveil dans la listes
{
	char *newNom,*newHour;
	struct Reveil rev;
	read(sock,(void*)&newNom,100);
	printf("Valeur reçue %s\n",newNom);
	//On récupère les informations envoyés par les sockets
	printf("%s souhaite etre reveille a %s",newNom,newHour);
	//On déterminer le nombre de case que compose notre tableau de réveuk
	int sizeTab = sizeof(tabReveil) / sizeof(struct Reveil);
	tabReveil[sizeTab+1] = rev;
	printf("Heure bien ajoute\n");
}


void deleteHour(struct Reveil *tabReveil,char *hourToDelete) //Supprime le réveil d'un utilisateur dans la liste
{
	int index;
	//On déterminer le nombre de case que compose notre tableau de réveuk
	int sizeTab = sizeof(tabReveil) / sizeof(struct Reveil);
	for(index = 0;index <sizeTab;index++){
		if(tabReveil[index].heure_reveil == hourToDelete){
			tabReveil[index].heure_reveil = "null";
			tabReveil[index].nom = "null";
		}
	}
}


//Reception message (pour le test des sockets)
void receiveMessage(int nsock,char *tab){
	int i;
	read(nsock,(void*)tab,100);
	printf("Reception d'un message:\n");
	printf("%s\n",tab);
}

int reveil(int nsock,int sock,char valueChoice) //Reçoit l'ensemble des valeurs
{
	switch(valueChoice){

		case '1'://Insertion Réveil
			insertHourWake(tabReveil,sock);
			close(nsock);
			break;
		case '2'://Modification reveil
			//updateHourToWake(tabReveil,sig.rev,sock);
			close(nsock);
			break;
		case '4':
			close(nsock);
			break;
		default:
			//checkHour();
			printf("Affichage heure");
			close(nsock);
			break;
	};
	return 0;
}

char getCapsuleValue(int sock) //Fonction permettant de récupérer 
{
	char *tab;
	read(sock,(void*)&tab,100);
	return tab[0];	
}

//Demande à l'utilisateur l'heure à laquelle il souhaite être réveillé
void scanHourToWake(int sock,char *nom)
{
	char remplir[6];
	printf("Entrez l'heure a laquelle vous souhaitez etre reveille:\n(Format:HH:MM inutile de preciser les 0 pour les valeurs inferieures a 10)\n\0 ");
	scanf("%s",&remplir);
	printf("Vous souhaitez donc %s, etre reveille a %s \n",nom,remplir);
	printf("Preparation de l'envoi\n");
	/*On concatene les données reçus */
	char *capsule,*firstpart,*secpart; 
	char *debut= "1-";
	char *milieu = "-";
	printf("%s\n",debut);
	printf("%s\n",milieu);
	printf("n\n");
	firstpart = strcat(debut,nom);
	printf("%s",firstpart);
	printf("o\n");
	secpart = strcat(firstpart,milieu);
	printf("%s",secpart);
	printf("p\n");
	capsule = strcat(secpart,remplir);
	printf("q\n");
	printf("%s",capsule);
	if(write(sock,(void*)&capsule,100) == -1){
		printf("Echec de l'envoi du signal\n");
		exit(5);
	}else{
		printf("Message envoyé\n");
	}
}


void updateHourToWake(struct Reveil *tabReveil,struct Reveil hourUpdated,int sock)//Modifie l'heure de réveil de l'utilisateur
{
	int index;
	//On déterminer le nombre de case que compose notre tableau de réveuk
	int sizeTab = sizeof(tabReveil) / sizeof(struct Reveil);
	for(index = 0;index <sizeTab;index++){
		//Dans le cas où le nom correspond
		if(tabReveil[index].nom == hourUpdated.nom){
			tabReveil[index].heure_reveil = hourUpdated.heure_reveil;
		}
	}
}


int checkLengthName(char *nom)
{
	if(strlen(nom) > 10){
		fprintf(stderr,"Utilisation: ./client nom_serveur port pseudo ");
		exit(1);
	}
	return strlen(nom);
}

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
