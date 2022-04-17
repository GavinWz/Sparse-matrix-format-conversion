CC = gcc
#CC = cl


st_to_cc: st_to_cc_test.c st_to_cc.obj
	$(CC) -fopenmp st_to_cc_test.c st_to_cc.obj -o st_to_cc
st_to_cc.obj: st_to_cc.c 
	$(CC) -c -fopenmp st_to_cc.c -o st_to_cc.obj


clean:
	rm *.o st_to_cc.exe *.obj