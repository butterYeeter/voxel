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

extern Shader shader_new(const char * const path, GLint type);
extern void shader_delete(ShaderProgram program, Shader shader);
extern bool shader_check(Shader shader);

extern ShaderProgram shader_program_new(const char * const vertex_source, const char * const fragment_source);
extern void shader_program_delete(ShaderProgram program);
extern bool shader_program_check(ShaderProgram program);


#endif