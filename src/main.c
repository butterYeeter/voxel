#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/shaders.h"
#include "../include/uniforms.h"
#include "../include/camera.h"
#include "../include/block.h"
#include "../include/chunk.h"

int window_width = 800;
int window_height = 800;

void window_resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0,0,width,height);
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Hello Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
  	glfwSwapInterval(1);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}
	glfwSetWindowSizeCallback(window, window_resize_callback);
	glEnable(GL_DEPTH_TEST);

	// Block block = block_new(0.0, 0.0, 0.0);
	Chunk chunk = chunk_new();
	for (int x = 0; x < 640; x++) {
		for (int z = 0; z < 640; z++) {
			chunk_add_block(&chunk, block_new(x, sinf(x)+sinf(0.5 * z)+sinf(0.3 * x)+cosf(0.3 * x), z));
		}
	}
	chunk_build_mesh(&chunk);

	ShaderProgram program = shader_program_new("assets/vert.glsl", "assets/frag.glsl");
	glUseProgram(program.id);

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// glGenBuffers(1, &vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferData(GL_ARRAY_BUFFER, chunk.blocks[0].num_vertices * chunk.num_blocks, chunk.mesh, GL_STATIC_DRAW);
	chunk_upload_mesh(&chunk);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Uniform rota = uniform_new(&program, "rot", MAT4);

	float angle = 180.0f;
	float last_time = glfwGetTime();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	Camera camera = camera_new();
	float index = 0.0f;


	while(!glfwWindowShouldClose(window)) {
		if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)) {
			exit(1);
		}



		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera_update(&camera, window);
		uniform_update(&rota, camera.view);

		float time = glfwGetTime();
		// glDrawArrays(GL_TRIANGLES, 0, 12*3 * chunk.num_blocks);
		if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
			chunk_add_block(&chunk, block_new(index + 2.0f, 0.0f, 0.0f));
			chunk_build_mesh(&chunk);
			index += 1.0f;
		}
		chunk_render(&chunk, vao);	

		glfwSwapBuffers(window);
		glfwPollEvents();
		last_time = time;
	}

	glfwTerminate();
	printf("\033[H\033[2J");
	return 0;
}




