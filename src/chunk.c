#include "../include/chunk.h"

Chunk chunk_new() {
    Chunk chunk;
    chunk.num_blocks = 0;
    chunk.blocks = malloc(sizeof(Block) * chunk.num_blocks);
    chunk.mesh_size = 0;
    chunk.mesh = malloc(sizeof(float) * chunk.mesh_size);

    glGenBuffers(1, &chunk.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return chunk;
}

void chunk_add_block(Chunk *chunk, Block block) {
    chunk->num_blocks++;
    chunk->blocks = realloc(chunk->blocks, sizeof(Block) * chunk->num_blocks);
    chunk->blocks[chunk->num_blocks-1] = block;
}

void chunk_build_mesh(Chunk *chunk) {   
    chunk->mesh = (float *)realloc(chunk->mesh, sizeof(float) * (36 * 6) * chunk->num_blocks);
    
    //build chunk
    for (size_t i = 0; i < chunk->num_blocks; i++) {
        memcpy(chunk->mesh + (36 * 6) * i, chunk->blocks[i].vertices, sizeof(float) * (36 * 6));
    }
}

void chunk_upload_mesh(const Chunk *chunk) {
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (36 * 6) * chunk->num_blocks, chunk->mesh, GL_STATIC_DRAW);
}

void chunk_render(Chunk *chunk, GLuint vao) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
    glDrawArrays(GL_TRIANGLES, 0, 12*3 * chunk->num_blocks);
}
