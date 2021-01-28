clean: 
	rm  *.o lab3


lab3: lab3.o
	gcc -o lab3 lab3.o	

lab.o: lab3.c
	gcc -Wall -c lab3.c
