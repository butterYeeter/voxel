#ifndef ___CHUNK_H___
#define ___CHUNK_H___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"

typedef struct {
    Block *blocks;
    size_t num_blocks;
    float *mesh;
    size_t mesh_size;
} Chunk;

Chunk chunk_new();
void chunk_add_block(Chunk *chunk, Block block);
void chunk_build_mesh(Chunk *chunk);

#endif
