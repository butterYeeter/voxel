#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *vertices;
} Block;

Block block_new(float x, float y, float z);

#endif