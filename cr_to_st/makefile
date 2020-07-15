CC = gcc
#CC = cl

cr_to_st: cr_to_st_test.c cr_to_st.obj
	$(CC) cr_to_st_test.c cr_to_st.obj -o cr_to_st
cr_to_st.obj: cr_to_st.c 
	$(CC) -c cr_to_st.c -o cr_to_st.obj

clean:
	rm *.o cr_to_st.exe *.obj