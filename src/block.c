#include "../include/block.h"

static float vertices[] = {
    -0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 	0.0f, 0.0f, 1.0f,
    0.5f,   0.5f, -0.5f,	1.0f, 1.0f, 0.0f,
    -0.5f,-0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f,  -0.5f, 	0.0f, 1.0f, 0.0f,
    0.5f,-0.5f,    0.5f,	0.0f, 0.0f, 1.0f,
    -0.5f,-0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,
    0.5f,-0.5f,   -0.5f,	0.0f, 1.0f, 0.0f,
    0.5f, 0.5f,   -0.5f,	0.0f, 0.0f, 1.0f,
    0.5f,-0.5f,   -0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f,-0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f,-0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f,   0.5f,	0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,
    0.5f,-0.5f,    0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f,-0.5f,   0.5f,	0.0f, 1.0f, 0.0f,
    -0.5f,-0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f,   0.5f,	1.0f, 0.0f, 0.0f,
    -0.5f,-0.5f,   0.5f,	0.0f, 1.0f, 0.0f,
    0.5f,-0.5f,    0.5f,	0.0f, 0.0f, 1.0f,
    0.5f, 0.5f,    0.5f,	1.0f, 1.0f, 0.0f,
    0.5f,-0.5f,   -0.5f,	1.0f, 0.0f, 0.0f,
    0.5f, 0.5f,   -0.5f,	0.0f, 1.0f, 0.0f,
    0.5f,-0.5f,   -0.5f,	0.0f, 0.0f, 1.0f,
    0.5f, 0.5f,    0.5f,	1.0f, 1.0f, 0.0f,
    0.5f,-0.5f,    0.5f,	1.0f, 0.0f, 0.0f,
    0.5f, 0.5f,    0.5f,	0.0f, 1.0f, 0.0f,
    0.5f, 0.5f,   -0.5f,	1.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,
    0.5f, 0.5f,    0.5f,	1.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,   0.5f,	0.0f, 1.0f, 0.0f,
    0.5f, 0.5f,    0.5f,	1.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,   0.5f,	0.0f, 1.0f, 0.0f,
    0.5f,-0.5f,    0.5f,	1.0f, 0.0f, 0.0f,
};

Block block_new(float x, float y, float z) {
    float position[3] = {x, y, z};
    Block block;
    block.vertices = malloc(sizeof(float) * sizeof(vertices)/sizeof(vertices[0]));
    for (int stride = 0; stride < (sizeof(vertices)/sizeof(vertices[0])) - 3; stride += 6) {
        for (int i = 0; i < 6; i++) {
            if (i <= 2) { //position
                block.vertices[stride + i] = vertices[stride + i] + position[i];
            }
            else { //rgb
                block.vertices[stride + i] = vertices[stride + i];
            }
        }
    }
    return block;
}