#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/shaders.h"

int window_width = 640;
int window_height = 640;

void window_resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0,0,width,height);
}


int main() {
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Hello Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
  	glfwSwapInterval(1);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}
	glfwSetWindowSizeCallback(window, window_resize_callback);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LESS);
	// glDepthMask(GL_TRUE);

	float vertices[] = {
		-1.0, -1.0f, 0.0f,	0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,	1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-1.0, -1.0f, 0.0f,	0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};


	ShaderProgram program = shader_program_new("assets/vert.glsl", "assets/frag.glsl");
	glUseProgram(program.id);

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


  	float time = glfwGetTime();
	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	printf("\033[H\033[2J");
	return 0;
}




