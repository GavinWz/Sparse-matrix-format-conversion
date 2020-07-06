CC = gcc

hyb_to_st: hyb_to_st_test.c hyb_to_st.o
	$(CC) hyb_to_st_test.c hyb_to_st.o -o hyb_to_st
hyb_to_st.o: hyb_to_st.c 
	$(CC) -c hyb_to_st.c

clean:
	rm *.o hyb_to_st.exe *.obj