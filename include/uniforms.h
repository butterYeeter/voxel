#ifndef __UNIFORMS_H__
#define __UNIFORMS_H__

#include <glad/glad.h>
#include "shaders.h"

typedef enum UniformTyep {
    INT,
    UINT,
    FLOAT,
    DOUBLE,
    BOOL,
    SAMPLER2D,
    SAMPLER2D_ARRAY,
    VEC2,
    VEC3,
    VEV4,
    MAT4
} UniformType;

typedef struct Uniform {
    GLint location;
    GLuint program;
    UniformType type;
    const char *name;
} Uniform;



Uniform uniform_new(const ShaderProgram *shader, const char *name, UniformType type);
void uniform_update(const Uniform *uniform, const void *value);

#endif