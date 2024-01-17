#include "../include/shaders.h"

#include <stdio.h>
#include <stdlib.h>


Shader shader_new(const char * const path, GLint type) {
    FILE *src_file;
    int num_bytes;
    char *src;

    src_file = fopen(path, "r");
    if(src_file == NULL) {
        printf("Failed to open file %s\n", path);
    }
    fseek(src_file, 0, SEEK_END);
    num_bytes = ftell(src_file);
    rewind(src_file);
    src = malloc(num_bytes + 1);
    fread(src, num_bytes, 1, src_file);
    src[num_bytes] = '\0';
    fclose(src_file);
    
    const GLchar *srcs[] = {src};

    
    Shader shader = {.type=type, .compile_status=GL_FALSE};
    shader.id = glCreateShader(shader.type);
    glShaderSource(shader.id, 1, srcs, NULL);
    glCompileShader(shader.id);
    glGetShaderiv(shader.id, GL_COMPILE_STATUS, &shader.compile_status);


    free(src);
    return shader;
}


void shader_delete(ShaderProgram program, Shader shader) {
    glDetachShader(program.id, shader.id);
    glDeleteShader(shader.id);
}


bool shader_check(Shader shader) {
    switch(shader.compile_status) {
        case GL_FALSE:
            char buf[1024];
            GLint retval;
            glGetShaderiv(shader.id, GL_INFO_LOG_LENGTH, &retval);
            glGetShaderInfoLog(shader.id, retval, NULL, buf);
            printf("Error compiling shader: %s\n", buf);
            return false;
            break;
        case GL_TRUE:
            return true;
    }
}


ShaderProgram shader_program_new(const char * const vertex_source, const char * const fragment_source) {
    ShaderProgram program = {.link_status=GL_FALSE};
    program.vertex_shader = shader_new(vertex_source, GL_VERTEX_SHADER);
    if(!shader_check(program.vertex_shader)) {
        shader_delete(program, program.vertex_shader);
        printf("Vertex shader died\n");
        exit(1);
    }

    program.fragment_shader = shader_new(fragment_source, GL_FRAGMENT_SHADER);
    if(!shader_check(program.fragment_shader)) {
        shader_delete(program, program.vertex_shader);
        shader_delete(program, program.fragment_shader);
        printf("Fragment shader died\n");
        exit(1);
    }

    program.id = glCreateProgram();
    glAttachShader(program.id, program.vertex_shader.id);
    glAttachShader(program.id, program.fragment_shader.id);
    glLinkProgram(program.id);
    glGetProgramiv(program.id, GL_LINK_STATUS, &program.link_status);
    if(!shader_program_check(program)) {
        shader_program_delete(program);
        printf("Shader prog died");
        exit(1);
    }

    return program;
}


void shader_program_delete(ShaderProgram program) {
    shader_delete(program, program.vertex_shader);
    shader_delete(program, program.fragment_shader);
    glDeleteProgram(program.id);
}


bool shader_program_check(ShaderProgram program) {
    switch(program.link_status) {
        case GL_FALSE:
            char buf[1024];
            GLint retval;
            glGetProgramiv(program.id, GL_INFO_LOG_LENGTH, &retval);
            glGetProgramInfoLog(program.id, retval, NULL, buf);
            printf("Error linking shader program: %s\n", buf);
            return false;
            break;
        case GL_TRUE:
            return true;
    }
}
