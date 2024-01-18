build/main: build/shaders.o build/uniforms.o src/main.c
	gcc -g -o $@ $? -lglad -lglfw -lm

# build/main.o: src/main.c
# 	gcc -g -c $< -o $@

# build/shaders.o: src/shaders.c
	# gcc -g -c $< -o $@

build/uniforms.o: src/uniforms.c
	gcc -g -c $< -o $@

clean:
	rm -rf build/*.o	
