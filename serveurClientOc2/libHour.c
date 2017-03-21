#include "libHour.h"

//Retourne l'heure sur la machine
void checkHour(){
	//Renvoi l'heure et les minutes
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("Il est %d:%d\n",tm.tm_hour,tm.tm_min);

}

//Vérifie si le client est toujours connecté au serveur
void checkConnected(){

}

void insertHourWake(struct Reveil *tabReveil,int sock) // Insert la nouvelle heure du réveil dans la listes
{
	char *newNom,*newHour;
	struct Reveil rev;
	//On récupère les informations envoyés par les sockets
	read(sock,(void*)&newNom,10);
	read(sock,(void*)&newHour,5);
	printf("%s souhaite etre reveille a %s",newNom,newHour);
	rev.nom = newNom;
	rev.heure_reveil = newHour;
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
			checkHour();
			close(nsock);
			break;
	};
	return 0;
}

//Demande à l'utilisateur l'heure à laquelle il souhaite être réveillé
void scanHourToWake(int sock,char *nom)
{
	char remplir[5];
	char value = '1';
	printf("Entrez l'heure a laquelle vous souhaitez etre reveille:(Format:HH:MM inutile de preciser les 0 valeurs inferieures a 10)\n\0 ");
	fgets(remplir,5,stdin);
	fgets(remplir,5,stdin);
	printf("Preparation de l'envoi\n");
	printf("Vous souhaitez donc %s, etre reveille a %s \n",nom,remplir);
	struct Reveil rev;
	rev.nom = nom;
	rev.heure_reveil = remplir;
	printf("La taille de la structure est %d",sizeof(rev));
	if(write(sock,(void*)&value,sizeof(value)) == -1){
		printf("Echec de l'envoi du signal\n");
		exit(5);
	}else{
		if(write(sock,(void*)&,sizeof(nom)) == -1){
			printf("Echec de l'envoi du nom\n");
			exit(6);
		}else{
				printf("Message envoyé\n");
		}
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
