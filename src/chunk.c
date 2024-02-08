#include "../include/chunk.h"

Chunk chunk_new() {
    Chunk chunk;
    chunk.num_blocks = 0;
    chunk.blocks = malloc(sizeof(Block) * chunk.num_blocks);
    chunk.mesh_size = 0;
    chunk.mesh = malloc(sizeof(float) * chunk.mesh_size);

    return chunk;
}

void chunk_add_block(Chunk *chunk, Block block) {
    chunk->num_blocks++;
    chunk->blocks = realloc(chunk->blocks, sizeof(Block) * chunk->num_blocks);
    chunk->blocks[chunk->num_blocks-1] = block;
}

void chunk_build_mesh(Chunk *chunk) {   
    chunk->mesh = realloc(chunk->mesh, sizeof(float) * (36 * 6) * chunk->num_blocks);
    
    for (size_t i = 0; i < chunk->num_blocks; i++) {
        memcpy(chunk->mesh + (36 * 6) * i, chunk->blocks[i].vertices, sizeof(float) * (36 * 6));
    }
}