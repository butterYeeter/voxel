#include <GLFW/glfw3.h>

#include "../include/camera.h"

Vec3 *vec3_new(float x, float y, float z) {
    Vec3 *v = malloc(sizeof(Vec3));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

void vec3_add(Vec3 *vec, vec3 add) {
    vec->x += add[0];
    vec->y += add[1];
    vec->z += add[2];
}

Camera camera_new() {

    return (Camera){
        .view = GLM_MAT4_IDENTITY_INIT,
        .perspective = GLM_MAT4_IDENTITY_INIT,
        .position = vec3_new(0.0, 0.0, 0.0),
        .orientation = vec3_new(0.0, 0.0, -1.0),
        .up = vec3_new(0.0, 1.0, 0.0),
        .speed = 0.7f,
        .toggled = true,
    };
}

void camera_inputs(Camera *camera, GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if(camera->toggled) {
		    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }

		camera->toggled = !camera->toggled;
        return;
	}
    
    if (!camera->toggled) {
        return;
    }

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3 orientation = {camera->orientation->x, 0.0, camera->orientation->z};
        glm_vec3_scale(orientation, camera->speed, orientation);
        vec3_add(camera->position, orientation);
    }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 orientation = {camera->orientation->x, camera->orientation->y, camera->orientation->z};
        vec3 up = {camera->up->x, camera->up->y, camera->up->z};
        
        glm_vec3_cross(orientation, up, orientation);
        glm_vec3_normalize(orientation);
        glm_vec3_negate(orientation);

        glm_vec3_scale(orientation, camera->speed, orientation);
        vec3_add(camera->position, orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3 orientation = {camera->orientation->x, 0.0, camera->orientation->z};
        glm_vec3_scale(orientation, -camera->speed, orientation);
        vec3_add(camera->position, orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 orientation = {camera->orientation->x, camera->orientation->y, camera->orientation->z};
        vec3 up = {camera->up->x, camera->up->y, camera->up->z};
        
        glm_vec3_cross(orientation, up, orientation);
        glm_vec3_normalize(orientation);

        glm_vec3_scale(orientation, camera->speed, orientation);
        vec3_add(camera->position, orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        vec3 up = {camera->up->x, camera->up->y, camera->up->z};
		glm_vec3_scale(up, camera->speed * 2, up);
        vec3_add(camera->position, up);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        vec3 up = {camera->up->x, camera->up->y, camera->up->z};
		glm_vec3_scale(up, camera->speed * -2, up);
        vec3_add(camera->position, up);
	}
	// if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    //     vec3 up = {camera->up->x, camera->up->y, camera->up->z};
	// 	glm_vec3_scale(up, camera->speed, up);
    //     glm_vec3_negate(up);
    //     vec3_add(camera->position, up);
	// }

	// Handles mouse inputs
	{

			// glfwSetCursorPos(window, (800 / 2), (800 / 2));
		// }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = 20.0 * (float)(mouseY - (800 / 2)) / 800;
		float rotY = 20.0 * (float)(mouseX - (800 / 2)) / 800;

        vec3 temp_orientation;

        vec3 orientation = {camera->orientation->x, camera->orientation->y, camera->orientation->z};
        vec3 up = {camera->up->x, camera->up->y, camera->up->z};

        glm_vec3_cross(orientation, up, temp_orientation);
        glm_vec3_normalize(temp_orientation);

		// glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
        glm_vec3_rotate(orientation, glm_rad(-rotX), temp_orientation); 

		// if (abs(glm_angle(newOrientation, Up) - glm_radians(90.0f)) <= glm_radians(85.0f))
		// {
		// 	Orientation = newOrientation;
		// }
        

		// Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
        glm_vec3_rotate(orientation, glm_rad(-rotY), up);

        camera->orientation->x = orientation[0];
        camera->orientation->y = orientation[1];
        camera->orientation->z = orientation[2];

        // if (camera->first_click) {
		glfwSetCursorPos(window, (800 / 2), (800 / 2));
        // }
	}
}

static float x = 0;

void camera_update(Camera *camera, GLFWwindow *window) {
    camera_inputs(camera, window);


	// Makes camera look in the right direction from the right position
	// view = glm::lookAt(Position, Position + Orientation, Up);

	// glm::mat4 view = glm::mat4(1.0f);
	// glm::mat4 projection = glm::mat4(1.0f);

	// // Makes camera look in the right direction from the right position
	// view = glm::lookAt(Position, Position + Orientation, Up);
	// // Adds perspective to the scene
	// projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    glm_mat4_identity(camera->view);
    glm_mat4_identity(camera->perspective);
    
    vec3 orientation = {camera->orientation->x, camera->orientation->y, camera->orientation->z};
    vec3 position = {camera->position->x, camera->position->y, camera->position->z};
    vec3 up = {camera->up->x, camera->up->y, camera->up->z};

    vec3 center;
    glm_vec3_add(position, orientation, center);
    glm_lookat(position, center, up, camera->view);

    glm_perspective(glm_rad(45.0f), 1.0f, 0.1f, 1000.0f, camera->perspective);
    glm_mat4_mul(camera->perspective, camera->view, camera->view);

    // x+=0.1;
    // glm_translate(camera->view, pos);

    
    // mat4 position = GLM_MAT4_IDENTITY_INIT;
    // vec3 pos = {0.0, 2.0, -10.0};
    // glm_translate(position, pos);

    // mat4 rotation = GLM_MAT4_IDENTITY_INIT;
    // mat4 perspective = GLM_MAT4_IDENTITY_INIT;

    // glm_mat4_mul(perspective, position, position);
}