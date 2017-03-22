defaut : serveur client

#CFLAGS = -Wall -DDEBUG
#CFLAGS = -Wall

serveur : serveur.o libHour.o libServer.o
	cc -o serveur serveur.o libHour.o libServer.o

serveur.o : serveur.c libHour.c libServer.c
	cc -c serveur.c libHour.c libServer.c

client : client.o libHour.o libClient.o
	cc -o client client.o libHour.o libClient.o 

client.o : client.c libHour.c  libClient.c
	cc -c client.c libHour.c libClient.c

clean :
	rm -f serveur client *.o





