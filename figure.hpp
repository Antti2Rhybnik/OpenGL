#ifndef OPENGL1_FIGURE_HPP
#define OPENGL1_FIGURE_HPP


#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utils.hpp"

struct Triangle {
    int a;
    int b;
    int c;
};

class Figure {

protected:
    std::vector<glm::vec3> vertexes;
    std::vector<Triangle> triagIndexes;

public:

    std::vector<glm::vec3>* getVertexes();
    void drawGL(GLenum renderType_) const;
    void move(glm::vec3 moveVec_);
    void rotateX(float angle_, glm::vec2 pos_YoZ);
    void rotateY(float angle_, glm::vec2 pos_XoZ);
    void rotateZ(float angle_, glm::vec2 pos_XoY);
    void increase(float koeff_);

};


#endif //OPENGL1_FIGURE_HPP
