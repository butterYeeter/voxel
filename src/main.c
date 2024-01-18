#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/shaders.h"
#include "../include/uniforms.h"

int window_width = 640;
int window_height = 640;

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	float vertices[] = {
		// vertices				// rgb colors
		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 	0.0f, 0.0f, 1.0f,
		0.5f, 0.5f,-0.5f,	1.0f, 1.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f, 	0.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,	0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, 0.5f,-0.5f,	0.0f, 0.0f, 1.0f,
		0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,	0.0f, 0.0f, 1.0f,
		0.5f,-0.5f, 0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,	0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,	0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,	1.0f, 1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,	1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,-0.5f,	0.0f, 1.0f, 0.0f,
		0.5f,-0.5f,-0.5f,	0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,	1.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,	1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, 0.5f,-0.5f,	1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,	0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f,-0.5f, 0.5f,	1.0f, 0.0f, 0.0f
	};



	ShaderProgram program = shader_program_new("assets/vert.glsl", "assets/frag.glsl");
	glUseProgram(program.id);

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// mat4 rot;
	// glm_mat4_identity(rot);
	// glm_rotate(rot, glm_rad(90.0f), (vec3){0.0f, 0.0f, 1.0f});
	mat4 rot;
	glm_mat4_identity(rot);
	glm_rotate(rot, 0.5f, (vec3){0.0f, 1.0f, 1.0f});
	Uniform rota = uniform_new(&program, "rot", MAT4);
	uniform_update(&rota, &rot);


	float angle = 180.0f;
	float last_time = glfwGetTime();
	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		float time = glfwGetTime();
		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glm_rotate(rot, glm_rad(angle*(time - last_time)), (vec3){0.0f, 1.0f, 0.0f});
		glm_rotate(rot, glm_rad(120.0f*(time - last_time)), (vec3){0.0f, 0.0f, 1.0f});
		uniform_update(&rota, &rot);
		angle += 0.005f;
		if(angle > 360.0f) angle = 0.0f;

		glfwSwapBuffers(window);
		glfwPollEvents();
		last_time = time;
	}
	

	glfwTerminate();
	printf("\033[H\033[2J");
	return 0;
}




