#make file overview :
all:
	gcc -c Horn_Schunk.c -o Horn_Schunk 
	gcc -c FiltreDeGausse.c -o FiltreDeGausse 
	gcc -c Matrix.c -o Matrix 
	gcc -c myBmpGris.c -o myBmpGris 
	gcc main.c -o main FiltreDeGausse myBmpGris Matrix Horn_Schunk
clean:
	$(RM) main