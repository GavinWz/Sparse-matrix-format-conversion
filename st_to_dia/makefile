CC = gcc

test: st_to_dia_test.c st_to_dia.o 
	$(CC) st_to_dia_test.c st_to_dia.o -o test.exe

st_to_dia.o: st_to_dia.c
	$(CC) -c st_to_dia.c

clean:
	rm *.o test.exe