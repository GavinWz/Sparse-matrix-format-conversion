CC = gcc
#CC = cl

hyb_to_st: hyb_to_st_test.c hyb_to_st.obj
	$(CC) hyb_to_st_test.c hyb_to_st.obj -o hyb_to_st
hyb_to_st.obj: hyb_to_st.c 
	$(CC) -c hyb_to_st.c -o hyb_to_st.obj

clean:
	rm *.o hyb_to_st.exe *.obj