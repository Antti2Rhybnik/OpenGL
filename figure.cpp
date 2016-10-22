#include "figure.hpp"

void Figure::move(glm::vec3 moveVec_) {

    for (glm::vec3 &v : vertexes) {
        v += moveVec_;
    }

}

void Figure::drawGL(GLenum renderType_) const {

    for (Triangle tr : triagIndexes) {

        glBegin(renderType_);
            glVertex3f(vertexes[tr.a]);
            glVertex3f(vertexes[tr.b]);
            glVertex3f(vertexes[tr.c]);
        glEnd();
    }

}

void Figure::rotateX(float angle_, glm::vec2 pos_YoZ) {

    glm::vec3 normal = glm::vec3(1, 0, 0);
    glm::vec3 pos3d = glm::vec3(0, pos_YoZ.x, pos_YoZ.y);
    for (glm::vec3 &v : vertexes) {

        pos3d.x = v.x;
        glm::vec3 rotor = pos3d - v;
        rotor = glm::rotate(rotor, angle_, normal);
        v = pos3d + rotor;
    }

}

void Figure::rotateY(float angle_, glm::vec2 pos_XoZ) {

    glm::vec3 normal = glm::vec3(0, 1, 0);
    glm::vec3 pos3d = glm::vec3(pos_XoZ.x, 0, pos_XoZ.y);
    for (glm::vec3 &v : vertexes) {

        pos3d.y = v.y;
        glm::vec3 rotor = pos3d - v;
        rotor = glm::rotate(rotor, angle_, normal);
        v = pos3d + rotor;
    }

}

void Figure::rotateZ(float angle_, glm::vec2 pos_XoY) {

    glm::vec3 normal = glm::vec3(0, 0, 1);
    glm::vec3 pos3d = glm::vec3(pos_XoY.x, pos_XoY.y, 0);
    for (glm::vec3 &v : vertexes) {

        pos3d.z = v.z;
        glm::vec3 rotor = pos3d - v;
        rotor = glm::rotate(rotor, angle_, normal);
        v = pos3d + rotor;
    }

}

std::vector<glm::vec3>* Figure::getVertexes() {
    return &vertexes;
}


void Figure::increase(float koeff_) {

    for (glm::vec3 &v : vertexes) {
        v *= koeff_;
    }

}