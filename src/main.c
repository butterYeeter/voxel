#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/shaders.h"


void set_uniform1f(unsigned int program, const char *uniform_id, float value) {
	int  location = glGetUniformLocation(program, uniform_id);
	glUseProgram(program);
	glUniform1f(location, value);
}

void set_uniform1i(unsigned int program, const char *uniform_id, int value) {
	int  location = glGetUniformLocation(program, uniform_id);
	glUseProgram(program);
	glUniform1i(location, value);
}


void window_resize_callback(GLFWwindow *window, int width, int height) {
	glViewport(0,0,width,height);
}

void process_input(GLFWwindow* window, const unsigned int program)
{
	static float mix = 0.0f;
	// printf("%.2f\n", mix);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if(mix < 1.0f) {
			mix += 0.0005f;
    		set_uniform1f(program, "m", mix);
    	}
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if(mix > 0.0f) {
			mix -= 0.0005f;
    		set_uniform1f(program, "m", mix);
    	}
    } else if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float vertices[] = {
		-1.0, -1.0f, 0.0f,	0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,	1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};

	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	// unsigned int vshader, fshader;
	// vshader = glCreateShader(GL_VERTEX_SHADER);
	// glShaderSource(vshader, 1, &vsrc, NULL);
	// glCompileShader(vshader);
	// fshader = glCreateShader(GL_FRAGMENT_SHADER);
	// glShaderSource(fshader, 1, &fsrc, NULL);
	// glCompileShader(fshader);

	// unsigned int program = glCreateProgram();
	// glAttachShader(program, vshader);
	// glAttachShader(program, fshader);
	// glLinkProgram(program);
	// glUseProgram(program);
	ShaderProgram program = shader_program_new("assets/vert.glsl", "assets/frag.glsl");
	glUseProgram(program.id);

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);



  	float time = glfwGetTime();
	while(!glfwWindowShouldClose(window)) {
		process_input(window, program.id);
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	printf("\033[H\033[2J");
	return 0;
}




