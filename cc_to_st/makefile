CC = gcc
#CC = cl

cc_to_st: cc_to_st_test.c cc_to_st.obj
	$(CC) cc_to_st_test.c cc_to_st.obj -o cc_to_st
cc_to_st.obj: cc_to_st.c 
	$(CC) -c cc_to_st.c -o cc_to_st.obj

clean:
	rm *.o cc_to_st.exe *.obj