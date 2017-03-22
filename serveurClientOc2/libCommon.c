#include "libCommon.h"

//Retourne l'heure sur la machine
char* checkHour(){
	//Renvoi l'heure et les minutes
	time_t t = time(NULL);
	//struct tm tm = *localtime(&t);
	char *hour;
	char *min;
	char *tps;
	//sprintf(hour,"%d",tm.tm_hour);
	//sprintf(min,"%d",tm.tm_min);
	tps=strcat(hour,":");
	tps=strcat(tps,min);
	printf("Il est %s",tps);
	return tps;

}

void getError(char *nameFunction,int errorNumber)
{
	perror(nameFunction);
	exit(errorNumber);
}
