#CC = gcc
CC = cl

st_to_cr: st_to_cr_test.c st_to_cr.obj
	$(CC) st_to_cr_test.c st_to_cr.obj -o st_to_cr
st_to_cr.obj: st_to_cr.c 
	$(CC) -c st_to_cr.c -o st_to_cr.obj

clean:
	rm *.o st_to_cr.exe *.obj