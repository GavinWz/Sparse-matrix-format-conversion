CC=gcc

st_to_hyb: st_to_hyb_test.c st_to_hyb.o
	$(CC) st_to_hyb_test.c st_to_hyb.o -o st_to_hyb

st_to_hyb.o: st_to_hyb.c
	$(CC) -c st_to_hyb.c

clean:
	rm *.o st_to_hyb.exe