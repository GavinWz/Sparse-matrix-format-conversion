CC = gcc

dia_to_st: dia_to_st_test.c dia_to_st.o 
	$(CC) dia_to_st_test.c dia_to_st.o -o dia_to_st

dia_to_st.o: dia_to_st.c
	$(CC) -c dia_to_st.c

clean:
	rm *.o test.exe