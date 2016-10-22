#include "sphere.hpp"

Sphere::Sphere(float radius_, int vertSegms_, int horizSegms_) {

    glm::vec3 Norm_X = glm::vec3(x(1), y(0), z(0));
    glm::vec3 Norm_Y = glm::vec3(x(0), y(1), z(0));
    glm::vec3 Norm_Z = glm::vec3(x(0), y(0), z(1));


    if (vertSegms_ < 1) { vertSegms_ = 1; }
    if (horizSegms_ < 4) { horizSegms_ = 4; }

    radius = radius_;
    vertSegms = vertSegms_;
    horizSegms = horizSegms_;

    int magicSegms = (vertSegms + 2) * 2;

    float rotAngleVert = (float) (2 * pi() / magicSegms);
    float rotAngleHoriz = (float) (2 * pi() / horizSegms);

    glm::vec3 rotVect = glm::vec3(0, 0, -radius);
    rotVect = glm::rotate(rotVect, rotAngleVert, Norm_Y);
    glm::vec3 currVertex = glm::vec3(0, 0, 0);

    for (int vs = 0; vs < vertSegms + 1; ++vs) {

        for (int hs = 0; hs < horizSegms; ++hs) {
            currVertex = rotVect;
            vertexes.push_back(currVertex);
            rotVect = glm::rotate(rotVect, rotAngleHoriz, Norm_Z);

        }

        rotVect = glm::rotate(rotVect, rotAngleVert, Norm_Y);
    }

    /* top */
    vertexes.push_back(glm::vec3(x(0), y(0), z(radius)));
    /* bottom */
    vertexes.push_back(glm::vec3(x(0), y(0), z(-radius)));


    Triangle tr = Triangle();
    for (int hs = 0; hs < horizSegms; ++hs) {
        tr.a = layer(0, hs);
        tr.b = (int) (vertexes.size() - 1);
        tr.c = layer(0, hs + 1);
        triagIndexes.push_back(tr);
    }

    for (int hs = 0; hs < horizSegms; ++hs) {
        tr.a = layer(vertSegms, hs);
        tr.b = layer(vertSegms, hs + 1);
        tr.c = (int) (vertexes.size() - 2);
        triagIndexes.push_back(tr);
    }

    for (int vs = 0; vs < vertSegms; ++vs) {
        for (int hs = 0; hs < horizSegms; ++hs) {
            tr.a = layer(vs, hs);
            tr.b = layer(vs, hs + 1);
            tr.c = layer(vs + 1, hs);
            triagIndexes.push_back(tr);
        }
    }

    for (int vs = vertSegms; vs > 0; --vs) {
        for (int hs = 0; hs <= horizSegms; ++hs) {
            tr.a = layer(vs, hs);
            tr.b = layer(vs - 1, hs + 1);
            tr.c = layer(vs, hs + 1);
            triagIndexes.push_back(tr);
        }
    }

}

Sphere::Sphere(float radius_, int vertSegms_, int horizSegms_, glm::vec3 pos_)  : Sphere(radius_, vertSegms_, horizSegms_) {
    this->move(pos_);
}


inline int Sphere::layer(int numLay, int shift) const {
    return ((horizSegms * numLay) + ((shift >= horizSegms) ? shift % horizSegms : shift));
}