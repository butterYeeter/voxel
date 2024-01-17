main: main.c
	gcc -o $@ $? -lglad -lglfw -lm
	
