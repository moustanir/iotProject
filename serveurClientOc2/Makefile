defaut : serveur client

#CFLAGS = -Wall -DDEBUG
#CFLAGS = -Wall

serveur : serveur.o libHour.o libServer.o libCommon.o
	cc -o serveur serveur.o libHour.o libServer.o libCommon.o

serveur.o : serveur.c libHour.c libServer.c libCommon.c
	cc -c serveur.c libHour.c libServer.c libCommon.c

client : client.o libHour.o libClient.o libCommon.o libCommon.o
	cc -o client client.o libHour.o libClient.o libCommon.o

client.o : client.c libHour.c  libClient.c libCommon.c
	cc -c client.c libHour.c libClient.c libCommon.c

clean :
	rm -f serveur client *.o





