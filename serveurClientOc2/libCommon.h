#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Reveil{
	char * nom;
	char *hour;
};

void getError(char* nameFunction,int errorNumber);
void sendMessage(int sock,char* nom);
char* readMessage(int sock);
char** str_split(char* a_str,const char a_delim);

