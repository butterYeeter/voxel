#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>
#include <cglm/struct.h>
#include <stdbool.h>

typedef struct {
    float x, y, z;
} Vec3;

typedef struct Camera {
    mat4 view;
    mat4 perspective;
    Vec3 *position;
    Vec3 *orientation;
    Vec3 *up;
    float speed;
    bool toggled;
} Camera;

Vec3 *vec3_new(float x, float y, float z);
Camera camera_new();
void camera_update(Camera *camera, GLFWwindow *window);

#endif