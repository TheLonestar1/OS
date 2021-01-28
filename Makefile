clean: 
	rm  *.o lab3


lab3: lab3.o
	gcc -o lab3 lab3.o	

lab.o: src/lab3.c
	gcc -Wall -c src/lab3.c

serv: server.o libworld.so
	gcc -o serv server.o -lpthread -L. -lworld -Wl,-rpath,.

server.o: src/server.c
	gcc -lpthread -c src/server.c

libworld.so: rem.o
	gcc -shared -o libworld.so rem.o

rem.o: src/rem.c
	gcc -c -fPIC src/rem.c
