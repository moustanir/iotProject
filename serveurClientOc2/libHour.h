#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

struct Reveil{
	char *nom;
	char *heure_reveil;
};

struct SignalReveil{
	int val;
	struct Reveil rev;
};

//Valeur Signaux
#define revNew 1
#define revUp  2

static struct Reveil *tabReveil;
//Prototypes fonctions


void checkConnected(); //Verifie si les utilisateurs sont toujours connectés au serveur
void checkHour(); //Affiche l'heure
void deleteHour(struct Reveil *tabReveil,char *hourToDelete);//Supprime le réveil une fois passé
void insertHourWake(struct Reveil *tabReveil,int sock);// Insert la nouvelle heure du réveil dans la liste
void receiveMessage(int nsock,char *tab);//Reçoit les messages
void scanHourToWake(int sock,char *nom); //Demande à l'utilisateur son heure à laquelle il se réveille
void updateHourToWake(struct Reveil *tabReveil,struct Reveil hourUpdated,int sock);//Modifie l'heure de réveil de l'utilisateur
int reveil(int nsock,int sock,char valueChoice); //Reçoit un signal et redirige les données vers le bon signal
