#version 330 core
in vec3 Color;

out vec4 FragColor;

void main() {
	// FragColor = vec4(.2, .9, .9, 1.);
	FragColor = vec4(Color, 1.0);	
}

