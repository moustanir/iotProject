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

char** str_split(char* a_str, const char a_delim)
{
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;
	/* Count how many elements will be extracted. */
	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}
	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);
	/* Add space for terminating null string so caller
	 * 	 *        knows where the list of returned strings ends. */
	count++;
	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}



struct Reveil serialisation(char nom[]){
	struct Reveil rev;
	char *noms;
	char **valueFound;
	valueFound = str_split(nom,'-');
	rev.nom = valueFound[2];
	rev.hour = valueFound[3];
	return rev;
}
