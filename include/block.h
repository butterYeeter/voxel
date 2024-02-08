#ifndef __BLOCK_H__
#define __BLOCK_H__

typedef struct {
    float *vertices;
} Block;

Block block_new() {
    Block block;
    block.vertices = (float *)malloc(sizeof(float) * );
    
    return block;
}

#endif