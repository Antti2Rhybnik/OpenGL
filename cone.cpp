#include "cone.hpp"


Cone::Cone(float radius_, float height_, int vertSegms_, int radSegms_) {

    if (vertSegms_ < 1) { vertSegms_ = 1; }
    if (radSegms_ < 4) { radSegms_ = 4; }

    radius = radius_;
    height = height_;
    vertSegms = vertSegms_;
    radSegms = radSegms_;


    float rotAngle = (float) (2 * pi() / radSegms);
    float tan = height / radius;

    float shiftVertVec = height / vertSegms;
    float shiftRotVec = shiftVertVec / tan;

    glm::vec3 X_Normal = glm::vec3(x(1), y(0), z(0));
    glm::vec3 Y_Normal = glm::vec3(x(0), y(1), z(0));
    glm::vec3 Z_Normal = glm::vec3(x(0), y(0), z(1));

    glm::vec3 vertVec = -Z_Normal * height;
    glm::vec3 rotVec = X_Normal * radius;
    glm::vec3 currVertex = glm::vec3(x(0), y(0), z(0));

    for (int h = 0; h < vertSegms; ++h) {

        rotVec = X_Normal * (radius - h * shiftRotVec);
        vertVec = -Z_Normal * (height - h * shiftVertVec);

        for (int r = 0; r < radSegms; ++r) {
            currVertex = vertVec + rotVec;
            vertexes.push_back(currVertex);
            rotVec = glm::rotate(rotVec, rotAngle, Z_Normal);
        }
    }

    /* top */
    vertexes.push_back(glm::vec3(x(0), y(0), z(0)));
    /* bottom */
    vertexes.push_back(glm::vec3(x(0), y(0), z(-height)));

    Triangle tr = Triangle();
    for (int r = 0; r < radSegms; ++r) {
        tr.a = layer(0, r);
        tr.b = (int) (vertexes.size() - 1);
        tr.c = layer(0, r + 1);
        triagIndexes.push_back(tr);
    }

    for (int r = 0; r < radSegms; ++r) {
        tr.a = layer(vertSegms - 1, r);
        tr.b = layer(vertSegms - 1, r + 1);
        tr.c = (int) (vertexes.size() - 2);
        triagIndexes.push_back(tr);
    }

    for (int h = 0; h < vertSegms - 1; ++h) {
        for (int r = 0; r < radSegms; ++r) {
            tr.a = layer(h, r);
            tr.b = layer(h, r + 1);
            tr.c = layer(h + 1, r);
            triagIndexes.push_back(tr);
        }
    }

    for (int h = vertSegms - 1; h > 0; --h) {
        for (int r = 0; r <= radSegms; ++r) {
            tr.a = layer(h, r);
            tr.b = layer(h - 1, r + 1);
            tr.c = layer(h, r + 1);
            triagIndexes.push_back(tr);
        }
    }

}




Cone::Cone(float radius_, float height_, int vertSegms_, int radSegms_, glm::vec3 pos) : Cone(radius_, height_,
                                                                                              vertSegms_, radSegms_) {
    this->move(pos);
}


float Cone::getRadius() const {
    return radius;
}

float Cone::getHeight() const {
    return height;
}


inline int Cone::layer(int numLay, int shift) const {
    return ((radSegms * numLay) + ((shift >= radSegms) ? shift % radSegms : shift));
}