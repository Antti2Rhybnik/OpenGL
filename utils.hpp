#ifndef OPENGL1_UTILS_HPP
#define OPENGL1_UTILS_HPP

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <cmath>

static inline float x(float x_) {
    return x_;
}

static inline float y(float x_) {
    return x_;
}

static inline float z(float x_) {
    return x_;
}

static inline void glVertex3f(glm::vec3 v_) {
    return glVertex3f(v_.x, v_.y, v_.z);
}

static inline long double pi() {
    return 3.141592653589793238462643383279502884L;
}

static void lookAt(glm::vec3 &cameraTarget_, glm::vec3 &cameraPos_, glm::vec3 &cameraUp_) {
    gluLookAt(cameraTarget_.x,
              cameraTarget_.y,
              cameraTarget_.z,
              cameraPos_.x,
              cameraPos_.y,
              cameraPos_.z,
              cameraUp_.x,
              cameraUp_.y,
              cameraUp_.z);
}

static inline float length3(glm::vec3& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


#endif //OPENGL1_UTILS_HPP
