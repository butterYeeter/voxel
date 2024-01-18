build/main: build/camera.o build/shaders.o build/uniforms.o src/main.c
	gcc -g -o $@ $? -lglad -lglfw -lm

# build/main.o: src/main.c
# 	gcc -g -c $< -o $@

# build/shaders.o: src/shaders.c
	# gcc -g -c $< -o $@

build/uniforms.o: src/uniforms.c
	gcc -g -c $< -o $@

build/camera.o: src/camera.c
	gcc -g -c $< -o $@

clean:
	rm -rf build/*.o	
