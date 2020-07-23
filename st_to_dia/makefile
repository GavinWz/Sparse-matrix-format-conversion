CC = gcc

st_to_dia: st_to_dia_test.c st_to_dia.o 
	$(CC) st_to_dia_test.c st_to_dia.o -o st_to_dia

st_to_dia.o: st_to_dia.c
	$(CC) -c st_to_dia.c

clean:
	rm *.o test.exe