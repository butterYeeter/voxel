#include "../include/uniforms.h"
#include <stdio.h>

Uniform uniform_new(const ShaderProgram *shader, const char *name, UniformType type) {
    Uniform uniform;
    uniform.program = shader->id;
    uniform.name = name;
    uniform.location = glGetUniformLocation(shader->id, name);
    uniform.type = type;
    return uniform;
}


void uniform_update(const Uniform *uniform, const void *value) {
    glUseProgram(uniform->program);
    switch (uniform->type) {
        case INT:
            glUniform1iv(uniform->location, 1, (const GLint*)value);
            break;
        case UINT:
            glUniform1uiv(uniform->location, 1, (const GLuint*)value);
            break;
        case FLOAT:
            glUniform1fv(uniform->location, 1, (const GLfloat*)value);
            break;
        case DOUBLE:
            // glUniform1dv(uniform->location, 1, (const GLdouble*)value);
            break;
        case BOOL:
            glUniform1iv(uniform->location, 1, (const GLint*)value); // GLSL bools are set as GLint
            break;
        case SAMPLER2D: // Sampler2D is an int uniform indicating the texture unit index
        case SAMPLER2D_ARRAY:
            glUniform1iv(uniform->location, 1, (const GLint*)value);
            break;
        case VEC2:
            glUniform2fv(uniform->location, 1, (const GLfloat*)value);
            break;
        case VEC3:
            glUniform3fv(uniform->location, 1, (const GLfloat*)value);
            break;
        case VEV4:
            glUniform4fv(uniform->location, 1, (const GLfloat*)value);
            break;
        case MAT4:
            glUniformMatrix4fv(uniform->location, 1, GL_FALSE, (const GLfloat*)value);
            break;
        default:
            fprintf(stderr, "Unknown uniform type: %d\n", uniform->type);
            break;
    }
}
