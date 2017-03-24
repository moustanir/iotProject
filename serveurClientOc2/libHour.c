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
	char newNom,newHour;
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
		if(tabReveil[index].hour == hourToDelete){
			tabReveil[index].hour = "null";
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


void updateHourToWake(struct Reveil *tabReveil,struct Reveil hourUpdated,int sock)//Modifie l'heure de réveil de l'utilisateur
{
	int index;
	//On déterminer le nombre de case que compose notre tableau de réveuk
	int sizeTab = sizeof(tabReveil) / sizeof(struct Reveil);
	for(index = 0;index <sizeTab;index++){
		//Dans le cas où le nom correspond
		if(tabReveil[index].nom == hourUpdated.nom){
			tabReveil[index].hour = hourUpdated.hour;
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
