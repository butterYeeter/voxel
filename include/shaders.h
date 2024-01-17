#ifndef __SHADERS_H
#define __SHADERS_H

#include <glad/glad.h>
#include <stdbool.h>


typedef struct Shader {
    GLuint id;
    GLint type;
    GLint compile_status;
} Shader;

typedef struct ShaderProgram {
    Shader vertex_shader;
    Shader fragment_shader;
    GLuint id;
    GLint link_status;
} ShaderProgram;

Shader shader_new(const char * const path, GLint type);
void shader_delete(ShaderProgram program, Shader shader);
bool shader_check(Shader shader);

ShaderProgram shader_program_new(const char * const vertex_source, const char * const fragment_source);
void shader_program_delete(ShaderProgram program);
bool shader_program_check(ShaderProgram program);


#endif