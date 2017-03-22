#include "libServer.h"

void cleanZomb(int S){
	wait(NULL);
}

void getError(char *nameFunction,int errorNumber)
{
	perror(nameFunction);
	exit(errorNumber);
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
	printf("a\n");
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
		//On arrête le programme dans le cas où la socket n'a pu être créée.
		getError("socket",1);
	}
	printf("b\n");
	//On attache la socket au port voulu
	if(bind(sock,(struct sockaddr*)&Sin,sizeof(Sin))<0){
		//On arrête le programme dans le cas où la socket n'a pu se lier à un port.
		getError("bind",2);
	}
	printf("c\n");
	ln = sizeof(Sin);
	int sockName;
	//On retourne le nom de la socket.
	if( sockName = getsockname(sock,(struct sockaddr*)&Sin,(socklen_t*)&ln) < 0){
		//On arrête le programme dans le cas où le programme n'a pu récupérer le nom de la socket
		getError("getsockname",3);
	}
	printf("d\n");
	printf("Le serveur est attache au port %u\n",ntohs(Sin.sin_port));
	//checkHour();
	//Définition du nombre d'appels simultanés autorisés
	if(listen(sock,5) < 0){
		getError("listen",4);
	}
	printf("e\n");	
	return sock;	
}

void serverWait(int sock,int nsock,int pid,struct sockaddr_in Sin,int ln){
	sock = initServer(sock,ln,Sin);
	printf("f\n");
	for(;;){
		printf("g\n");
		if((nsock=accept(sock,(struct sockaddr*)&Sin,(socklen_t*)&ln))<0){
			perror("accept");
			exit(5);
		}
		printf("h\n");
		if((pid=fork())== -1){
			perror("fork");
			exit(6);
		}
		printf("i\n");
		if(pid == 0){
			char valueChosen = getCapsuleValue(nsock);
			printf("Valeur reçue: %s\n",valueChosen);
			reveil(nsock,sock,valueChosen);
		}
		printf("j\n");
		close(nsock);
	}
}
