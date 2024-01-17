build/main: build/main.o build/shaders.o
	gcc -o $@ $? -lglad -lglfw -lm

build/main.o: src/main.c
	gcc -c $< -o $@

build/shaders.o: src/shaders.c
	gcc -c $< -o $@

clean:
	rm -rf build/*.o	
