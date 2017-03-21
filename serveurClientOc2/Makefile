defaut : serveur client

#CFLAGS = -Wall -DDEBUG
#CFLAGS = -Wall

serveur : serveur.o libHour.o
	cc -o serveur serveur.o libHour.o

serveur.o : serveur.c libHour.c
	cc -c serveur.c libHour.c

client : client.o libHour.o
	cc -o client client.o libHour.o 

client.o : client.c libHour.c 
	cc -c client.c libHour.c

clean :
	rm -f serveur client *.o





