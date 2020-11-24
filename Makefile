all: map1 map2

map1: main.o list.o recorddata.o kd.o nearest.o
	gcc main.o list.o recorddata.o kd.o nearest.o -o map1 -g -lm

map2: main2.o list.o recorddata.o kd.o radius.o
	gcc main2.o list.o recorddata.o kd.o radius.o -o map2 -g -lm

main.o: main.c header.h
	gcc -c -g main.c

main2.o: main2.c header.h
	gcc -c -g main2.c 

recorddata.o: recorddata.c header.h
	gcc -c -g recorddata.c

list.o: list.c header.h
	gcc -c -g list.c

kd.o: kd.c header.h
	gcc -c -g kd.c

nearest.o: nearest.c header.h
	gcc -c -g nearest.c

radius.o: radius.c header.h
	gcc -c -g radius.c

clean:
	rm *.o output