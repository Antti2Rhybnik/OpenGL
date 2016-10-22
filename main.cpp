#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>
#include <vector>
#include <unistd.h>

#include "tor.hpp"
#include "cone.hpp"
#include "sphere.hpp"
#include "cylinder.hpp"
#include "morpher.hpp"


int loopDelay = 0;
glm::vec3 cameraPos = glm::vec3(1.0f, 0.5f, 0.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);

Tor* tor = nullptr;
Cone* cone = nullptr;
Sphere* sphere = nullptr;
Cylinder* cylinder = nullptr;
Morpher* morpher1 = nullptr;
Morpher* morpher2 = nullptr;


static void initFigures() {

    tor = new Tor(5, 1, 20, 15);
    cone = new Cone(5, 10, 21, 20, glm::vec3(0, 0, 5));
    cylinder = new Cylinder(5, 10, 20, 20, glm::vec3(0, 0, 5));

    sphere = new Sphere(7, 20, 20);
    sphere->rotateZ(1*(float)pi(),glm::vec2(0,0));

    morpher1 = new Morpher(cone, sphere, 100);
    morpher2 = new Morpher(cylinder, sphere, 100);

}


static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    GLfloat cameraSpeed = 0.1f;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        std::cout << "ESC key has been pressed" << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_W) {
        std::cout << "W key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(cameraTarget - cameraPos);
        cameraPos += cameraSpeed * move_vec;
        cameraTarget += cameraSpeed * move_vec;
    }

    if (key == GLFW_KEY_S) {
        std::cout << "S key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(cameraTarget - cameraPos);
        cameraPos -= cameraSpeed * move_vec;
        cameraTarget -= cameraSpeed * move_vec;

    }

    if (key == GLFW_KEY_A) {
        std::cout << "A key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));
        cameraPos -= move_vec * cameraSpeed;
        cameraTarget -= move_vec * cameraSpeed;
    }

    if (key == GLFW_KEY_D) {
        std::cout << "D key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));
        cameraPos += move_vec * cameraSpeed;
        cameraTarget += move_vec * cameraSpeed;
    }

    if (key == GLFW_KEY_LEFT) {
        std::cout << "LEFT key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));
        cameraPos += move_vec * cameraSpeed;
    }

    if (key == GLFW_KEY_RIGHT) {
        std::cout << "RIGHT key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(glm::cross(cameraTarget - cameraPos, cameraUp));
        cameraPos -= move_vec * cameraSpeed;
    }

    if (key == GLFW_KEY_UP) {
        std::cout << "UP key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(cameraUp);
        cameraPos += move_vec * cameraSpeed;
        glm::vec3 new_up = glm::normalize(
                glm::cross(glm::cross(cameraTarget - cameraPos, cameraUp), cameraTarget - cameraPos));
        cameraUp = new_up;
    }


    if (key == GLFW_KEY_DOWN) {
        std::cout << "DOWN key has been pressed" << std::endl;
        glm::vec3 move_vec = glm::normalize(cameraUp);
        cameraPos -= move_vec * cameraSpeed;
        glm::vec3 new_up = glm::normalize(
                glm::cross(glm::cross(cameraTarget - cameraPos, cameraUp), cameraTarget - cameraPos));
        cameraUp = new_up;
    }


}

static void drawCameraTarget() {

    glBegin(GL_LINES);
    glVertex3f(cameraTarget.x, cameraTarget.y, cameraTarget.z);
    glVertex3f(cameraTarget.x, cameraTarget.y, cameraTarget.z + 0.1f);

    glVertex3f(cameraTarget.x, cameraTarget.y, cameraTarget.z);
    glVertex3f(cameraTarget.x, cameraTarget.y + 0.1f, cameraTarget.z);

    glVertex3f(cameraTarget.x, cameraTarget.y, cameraTarget.z);
    glVertex3f(cameraTarget.x + 0.1f, cameraTarget.y, cameraTarget.z);
    glEnd();

}


static void rotateAndIncrease() {

}


void display(GLFWwindow *window) {

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glPolygonMode(GL_FRONT, GL_LINE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-width / 100, width / 100, -height / 100, height / 100, -1000, 1000);
//    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    lookAt(cameraTarget, cameraPos, cameraUp);

    glClear(GL_COLOR_BUFFER_BIT);

    drawCameraTarget();
//    glColor3f(0.f, 0.f, 1.f);
    tor->drawGL(GL_LINE_LOOP);
//    glColor3f(1.f, 0.f, 1.f);
//    glColor3f(1.f, 0.f, 0.f);
//    sphere.drawGL(GL_LINE_LOOP);
//    cylinder->drawGL(GL_LINE_LOOP);
//    cone.drawGL(GL_LINE_LOOP);
//    cylinder.drawGL(GL_TRIANGLES);



    if (loopDelay++ % 3 == 0) {
//        cylinder.rotateZ(3, glm::vec2(0, 0));
//        sphere.rotateX(3, glm::vec2(0, 0));
//        cone.rotateZ(3, glm::vec2(0, 0));
        tor->increase(0.99);
        morpher1->morph();
        morpher2->morph();
    }


}

int main(int argc, char **argv) {

    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(800, 800, "Lab1", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    initFigures();
    while (!glfwWindowShouldClose(window)) {
        display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}