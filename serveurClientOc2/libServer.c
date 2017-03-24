#include "libServer.h"
void cleanZomb(int S){
	wait(NULL);
}

int createSocket(int sock)
{
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		//On arrête le programme dans le cas où la socket n'a pu être créée.
		getError("socket",1);
	}
	return sock;
}

struct sockaddr_in bindSocket(int sock,struct sockaddr_in Sin)
{
	if(bind(sock,(struct sockaddr*)&Sin,sizeof(Sin))<0){
		//On arrête le programme dans le cas où la socket n'a pu se lier à un port.
		getError("bind",2);
	}
	return Sin;
}

int  getSockName(int sock,struct sockaddr_in Sin,int sockName,int ln)
{
	if( sockName = getsockname(sock,(struct sockaddr*)&Sin,(socklen_t*)&ln) < 0){
		//On arrête le programme dans le cas où le programme n'a pu récupérer le nom de la socket
		getError("getsockname",3);
	}
	return sockName;
}

void socketListen(int sock)
{
	if(listen(sock,5) < 0){
		getError("listen",4);
	}
}

int initServer(int sock,int ln,struct sockaddr_in Sin){
	//On supprime d'abord l'ensemble des processus zombie.
	signal(SIGCHLD,cleanZomb);
	//Création de la socket
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		//On arrête le programme dans le cas où la socket n'a pu être créée.
		getError("socket",1);
	}
	//On attache la socket au port voulu
	if(bind(sock,(struct sockaddr*)&Sin,sizeof(Sin))<0){
		//On arrête le programme dans le cas où la socket n'a pu se lier à un port.
		getError("bind",2);
	}
	ln = sizeof(Sin);
	int sockName;
	//On retourne le nom de la socket.
	if( sockName = getsockname(sock,(struct sockaddr*)&Sin,(socklen_t*)&ln) < 0){
		//On arrête le programme dans le cas où le programme n'a pu récupérer le nom de la socket
		getError("getsockname",3);
	}
	printf("Le serveur est attache au port %u\n",ntohs(Sin.sin_port));
	//checkHour();
	//Définition du nombre d'appels simultanés autorisés
	if(listen(sock,5) < 0){
		getError("listen",4);
	}
	return sock;	
}

void serverWait(int sock,int nsock,int pid,struct sockaddr_in Sin,int ln){
	sock = initServer(sock,ln,Sin);
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
			printf("%s",readMessage(nsock));
			char valueChosen = getTypeValue(readMessage(nsock));
			printf("Valeur reçue: %s\n",valueChosen);
			reveil(nsock,sock,valueChosen);
		}
		close(nsock);
	}
}

char getTypeValue(char nom[])
{
	char** valueFound;
	valueFound = str_split(nom,'-');
	return *valueFound[0];
}

struct Reveil deserialisation(char* nom){
	struct Reveil result;
	char** valueFound;
	valueFound = str_split(nom,'-');
	result.nom = valueFound[1];
	result.hour = valueFound[2];
	return result;
}

char* serialisation(struct Reveil reveil) {
	char *result = malloc (sizeof (char) * (strlen(reveil.nom) + strlen(reveil.hour) + 5));
	strcat(result,"1-");
	strcat(result,reveil.nom);
	strcat(result,"-");
	strcat(result,reveil.hour);
	return result;
}

